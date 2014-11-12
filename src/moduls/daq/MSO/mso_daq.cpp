//OpenSCADA system module DAQ.MSO file: MSO_daq.cpp
/***************************************************************************
 *   Copyright (C) 2011-2012 by Maxim Kochetkov                            *
 *   fido_max@inbox.ru                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <getopt.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>

#include <ttiparam.h>
#include <tdaqs.h>

#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "MezTT.h"
#include "MezTC.h"
#include "MezTU.h"
#include "MezTI.h"
#include "MezTR.h"

#include "mso_daq.h"

MSO::TTpContr *MSO::mod;

using namespace MSO;

//******************************************************
//* TTpContr                                           *
//******************************************************
TTpContr::TTpContr( string name ) : TTipDAQ(DAQ_ID)
{
    mod		= this;

    mName	= DAQ_NAME;
    mType	= DAQ_TYPE;
    mVers	= DAQ_MVER;
    mAuthor	= DAQ_AUTHORS;
    mDescr	= DAQ_DESCR;
    mLicense	= DAQ_LICENSE;
    mSource	= name;
}

TTpContr::~TTpContr()
{

}

void TTpContr::postEnable( int flag )
{
    TTipDAQ::postEnable( flag );

    //> Controler's bd structure
    fldAdd( new TFld("PRM_BD_TT",_("TT Parameteres table"),TFld::String,TFld::NoFlag,"30","") );
    fldAdd( new TFld("PRM_BD_TC",_("TC Parameteres table"),TFld::String,TFld::NoFlag,"30","") );
    fldAdd( new TFld("PRM_BD_TU",_("TU Parameteres table"),TFld::String,TFld::NoFlag,"30","") );
    fldAdd( new TFld("PRM_BD_TI",_("TI Parameteres table"),TFld::String,TFld::NoFlag,"30","") );
    fldAdd( new TFld("PRM_BD_TR",_("TI Parameteres table"),TFld::String,TFld::NoFlag,"30","") );
    fldAdd( new TFld("SCHEDULE",_("Acquisition schedule"),TFld::String,TFld::NoFlag,"100","1") );
    fldAdd( new TFld("PRIOR",_("Gather task priority"),TFld::Integer,TFld::NoFlag,"2","0","-1;99") );
//    fldAdd( new TFld("PROT",_("MSO protocol"),TFld::String,TFld::Selected,"5","TCP","TCP;RTU;ASCII",_("TCP/IP;RTU;ASCII")) );
    fldAdd( new TFld("ADDR",_("Transport address"),TFld::String,TFld::NoFlag,"30","") );
    fldAdd( new TFld("NODE",_("Destination node"),TFld::Integer,TFld::NoFlag,"20","1","0;255") );
//    fldAdd( new TFld("FRAG_MERGE",_("Data fragments merge"),TFld::Boolean,TFld::NoFlag,"1","0") );
    fldAdd( new TFld("TM_REQ",_("Connection timeout (ms)"),TFld::Integer,TFld::NoFlag,"5","0","0;10000") );
//    fldAdd( new TFld("TM_REST",_("Restore timeout (s)"),TFld::Integer,TFld::NoFlag,"3","30","0;3600") );
//    fldAdd( new TFld("REQ_TRY",_("Request tries"),TFld::Integer,TFld::NoFlag,"1","3","1;10") );

    //> Parameter type bd structure
    int t_prm = tpParmAdd("tp_TT","PRM_BD_TT",_("TT"));
    tpPrmAt(t_prm).fldAdd( new TFld("DEV_ID",_("Device address"),TFld::Integer,TCfg::NoVal,"2","0","0;15") );

    t_prm = tpParmAdd("tp_TC","PRM_BD_TC",_("TC"));
    tpPrmAt(t_prm).fldAdd( new TFld("DEV_ID",_("Device address"),TFld::Integer,TCfg::NoVal,"2","0","0;15") );

    t_prm = tpParmAdd("tp_TU","PRM_BD_TU",_("TU"));
    tpPrmAt(t_prm).fldAdd( new TFld("DEV_ID",_("Device address"),TFld::Integer,TCfg::NoVal,"2","0","0;15") );

    t_prm = tpParmAdd("tp_TI","PRM_BD_TI",_("TI"));
    tpPrmAt(t_prm).fldAdd( new TFld("DEV_ID",_("Device address"),TFld::Integer,TCfg::NoVal,"2","0","0;15") );

    t_prm = tpParmAdd("tp_TR","PRM_BD_TR",_("TR"));
    tpPrmAt(t_prm).fldAdd( new TFld("DEV_ID",_("Device address"),TFld::Integer,TCfg::NoVal,"2","0","0;15") );
}

void TTpContr::load_( )
{
    //> Load parameters from command line

}

void TTpContr::save_()
{

}

TController *TTpContr::ContrAttach( const string &name, const string &daq_db )
{
    return new TMdContr(name,daq_db,this);
}

//******************************************************
//* TMdContr                                           *
//******************************************************
TMdContr::TMdContr( string name_c, const string &daq_db, TElem *cfgelem ) :
	TController( name_c, daq_db, cfgelem ), prc_st(false), endrun_req(false), tmGath(0),
	numRx(0), numTx(0),
	mSched(cfg("SCHEDULE")), mPrior(cfg("PRIOR").getId()),
	mAddr(cfg("ADDR")),mNode(cfg("NODE").getId()),
	reqTm(cfg("TM_REQ").getId())
{
    pthread_mutexattr_t attrM;
    pthread_mutexattr_init(&attrM);
    pthread_mutexattr_settype(&attrM, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&enRes, &attrM);
    pthread_mutexattr_destroy(&attrM);

    cfg("PRM_BD_TT").setS("MSOPrm_TT_"+name_c);
    cfg("PRM_BD_TC").setS("MSOPrm_TC_"+name_c);
    cfg("PRM_BD_TU").setS("MSOPrm_TU_"+name_c);
    cfg("PRM_BD_TI").setS("MSOPrm_TI_"+name_c);
    cfg("PRM_BD_TR").setS("MSOPrm_TR_"+name_c);

}

TMdContr::~TMdContr()
{
    if(run_st) stop();

    pthread_mutex_destroy(&enRes);
}

string TMdContr::getStatus( )
{
    string val = TController::getStatus( );

    if( startStat( ) && !redntUse( ) )
    {
//	if( tmDelay > -1 )
//	{
//	    val += TSYS::strMess(_("Connection error. Restoring in %.6g s."),tmDelay);
//	    val.replace(0,1,"10");
//	}
//	else
//	{
	    if( period() ) val += TSYS::strMess(_("Call by period %g s. "),(1e-9*period()));
	    else val += TSYS::strMess(_("Call by cron '%s'. "),cron().c_str());
	    val += TSYS::strMess(_("Gather data time %.6g ms. Read %g frames. Write %g frames."),
				    tmGath,numRx,numTx);
//	}
    }

    return val;
}

TParamContr *TMdContr::ParamAttach( const string &name, int type )
{
    return new TMdPrm( name, &owner().tpPrmAt(type) );
}

bool TTpContr::DataIn(const string &ireqst, const uint32_t node )
{
//    unsigned int node = strtoul(sender.c_str(),NULL,0);

    unsigned int mso = (node>>10)&0xFF;
    unsigned int channel = (node>>4)&0x3F;
    unsigned int type = (node>>18)&0xFF;
    unsigned int param = (node)&0x7;
    unsigned int flag = (node>>26)&0x7;
 //   AT91C_CAN_MIDE | priority_N << 26 | identifier_TC << 18 | MSO_Addres << 10 | ChannelNumber << 3
    if (mess_lev() == TMess::Debug) mess_debug("DataIn"," sender<%u> mso<%u> channel<%u> type<%u> param<%u> flag<%u>",node,mso,channel,type,param,flag);
    vector<string> lst;
    SYS->daq().at().at("MSO").at().list(lst);
    for(int i_l=0; i_l < lst.size(); i_l++){
        AutoHD<TMdContr> t = SYS->daq().at().at("MSO").at().at(lst[i_l]);
        if (t.at().HandleData(mso, channel, type, param, flag, ireqst)) break;
    }
    return true;
}

bool TMdContr::HandleData(unsigned int node, unsigned int channel, unsigned int type, unsigned int param, unsigned int flag, const string &ireqst)
{
//    mess_info("ContrHandle","node %u mNode %u flag %u",node, mNode,flag);
    if ((flag == 7)&& (node==mNode))
    {
//        mess_info("ContrHandle","node %u found!",node);
    	MtxAlloc prmRes(enRes, true);
		for(unsigned i_p=0; i_p < pHd.size(); i_p++)
			if (pHd[i_p].at().HandleEvent(channel,type,param,flag,ireqst)) return true;
//		vector<string> lst;
//		list(lst);
//		for(int i_l=0; i_l < lst.size(); i_l++){
//			AutoHD<TMdPrm> t = at(lst[i_l]);
//			mess_info("ContrHandle","trying  %u",i_l);
//			if (t.at().HandleEvent(channel,type,param,flag,ireqst)) return true;


//		}
		prmRes.unlock();
/*        if (type==11){
            mess_info("typeHandle","type %u found!",param);
            mess_info("typeHandle","acqTT size is %u",acqTT.size());
            for( int i_b = 0; i_b < acqTT.size(); i_b++ )
            {
                if (acqTT[i_b].addr==channel)
                {
                    mess_info("ParamHandle","channel %u found!",channel);

		            acqTT[i_b].val = *(float *)(ireqst.data());
		            acqTT[i_b].err.setVal("");
		            mess_info("ParamHandle","new value: %f",acqTT[i_b].val);
		            return true;
                }
            }
        }
        if (type==10){
            mess_info("typeHandle","type %u found!",param);
            mess_info("typeHandle","acqTC size is %u",acqTC.size());
            for( int i_b = 0; i_b < acqTC.size(); i_b++ )
            {
                if (acqTC[i_b].addr==channel)
                {
                    mess_info("ParamHandle","channel %u found!",channel);

		            acqTC[i_b].val = *(int *)(ireqst.data());
		            acqTC[i_b].state = *(int *)(ireqst.data()+4);
		            acqTC[i_b].err.setVal("");
		            mess_info("ParamHandle","new value: %d state: %d",acqTC[i_b].val,acqTC[i_b].state);
		            return true;
                }
            }
        }*/
    }
    return false;
}

void TMdContr::disable_( )
{
}

void TMdContr::start_( )
{
    if( prc_st ) return;

    //> Establish connection
    AutoHD<TTransportOut> tr = SYS->transport().at().at(TSYS::strSepParse(mAddr,0,'.')).at().outAt(TSYS::strSepParse(mAddr,1,'.'));
    try { tr.at().start(); }
    catch( TError err ){ mess_err(err.cat.c_str(),"%s",err.mess.c_str()); }

    //> Schedule process
    mPer = TSYS::strSepParse(cron(),1,' ').empty() ? vmax(0,(int64_t)(1e9*atof(cron().c_str()))) : 0;

    //> Clear statistic
    numRx = numTx = 0;

    //> Start the gathering data task
    SYS->taskCreate( nodePath('.',true), mPrior, TMdContr::Task, this );
}

void TMdContr::stop_( )
{
    //> Stop the request and calc data task
    SYS->taskDestroy( nodePath('.',true), &endrun_req );

    //> Clear statistic
    numRx = numTx = 0;
    pHd.clear();
}

void TMdContr::prmEn( TMdPrm *prm, bool val )
{
    unsigned i_prm;

    MtxAlloc res(enRes, true);
    for(i_prm = 0; i_prm < pHd.size(); i_prm++)
	if(&pHd[i_prm].at() == prm) break;

    if(val && i_prm >= pHd.size())	pHd.push_back(prm);
    if(!val && i_prm < pHd.size())	pHd.erase(pHd.begin()+i_prm);
}
bool TMdContr::cfgChange( TCfg &co, const TVariant &pc )
{
	TController::cfgChange(co, pc);


    return true;
}

int TMdContr::getStateTC( int addr, ResString &err )
{
    float rez = EVAL_REAL;
    ResAlloc res( req_res, false );
    for( int i_b = 0; i_b < acqTC.size(); i_b++ )
    {
        if (acqTC[i_b].addr==addr)
        {
            err.setVal( acqTC[i_b].err.getVal() );
 //           mess_info("getValTT","%u",i_b);
            if( err.getVal().empty() ) {
		        rez = (acqTC[i_b].state);
            }
        }
    }

/*    for( int i_b = 0; i_b < acqTT.size(); i_b++ )
	if( (addr*2) >= workCnt[i_b].off && (addr*2+2) <= (workCnt[i_b].off+workCnt[i_b].val.size()) )
	{
	    err.setVal( workCnt[i_b].err.getVal() );
	    if( err.getVal().empty() )
		rez = (unsigned short)(workCnt[i_b].val[addr*2-workCnt[i_b].off]<<8)|(unsigned char)workCnt[i_b].val[addr*2-workCnt[i_b].off+1];
	    break;
	}*/
    return rez;
}

int TMdContr::getValR( int addr, ResString &err, bool in )
{
    int rez = EVAL_INT32;
 /*   ResAlloc res( req_res, false );
    vector< SDataRec >	&workCnt = in ? acqBlksIn : acqBlks;
    for( int i_b = 0; i_b < workCnt.size(); i_b++ )
	if( (addr*2) >= workCnt[i_b].off && (addr*2+2) <= (workCnt[i_b].off+workCnt[i_b].val.size()) )
	{
	    err.setVal( workCnt[i_b].err.getVal() );
	    if( err.getVal().empty() )
		rez = (unsigned short)(workCnt[i_b].val[addr*2-workCnt[i_b].off]<<8)|(unsigned char)workCnt[i_b].val[addr*2-workCnt[i_b].off+1];
	    break;
	}*/
    return rez;
}

char TMdContr::getValC( int addr, ResString &err, bool in )
{
    char rez = EVAL_BOOL;
/*    ResAlloc res( req_res, false );
    vector< SDataRec >	&workCnt = in ? acqBlksCoilIn : acqBlksCoil;
    for( int i_b = 0; i_b < workCnt.size(); i_b++ )
	if( addr >= workCnt[i_b].off && (addr+1) <= (workCnt[i_b].off+workCnt[i_b].val.size()) )
	{
	    err.setVal( workCnt[i_b].err.getVal() );
	    if( err.getVal().empty() )
		rez = workCnt[i_b].val[addr-workCnt[i_b].off];
	    break;
	}*/
    return rez;
}

void TMdContr::setValR( int val, int addr, ResString &err )
{
/*    //> Encode request PDU (Protocol Data Units)
    string pdu;
    pdu = (char)0x6;		//Function, preset single register
    pdu += (char)(addr>>8);	//Address MSB
    pdu += (char)addr;		//Address LSB
    pdu += (char)(val>>8);	//Data MSB
    pdu += (char)val;		//Data LSB
    //> Request to remote server
    err.setVal( MSOReq(pdu) );
    if( err.getVal().empty() ) numWReg++;
    //> Set to acquisition block
    ResAlloc res( req_res, false );
    for( int i_b = 0; i_b < acqBlks.size(); i_b++ )
	if( (addr*2) >= acqBlks[i_b].off && (addr*2+2) <= (acqBlks[i_b].off+acqBlks[i_b].val.size()) )
	{
	    acqBlks[i_b].val[addr*2-acqBlks[i_b].off]   = (char)(val>>8);
	    acqBlks[i_b].val[addr*2-acqBlks[i_b].off+1] = (char)val;
	    break;
	}*/
}

void TMdContr::setValC( char val, int addr, ResString &err )
{
/*    //> Encode request PDU (Protocol Data Units)
    string pdu;
    pdu = (char)0x5;		//Function, preset single coil
    pdu += (char)(addr>>8);	//Address MSB
    pdu += (char)addr;		//Address LSB
    pdu += (char)val?0xFF:0x00;	//Data MSB
    pdu += (char)0x00;		//Data LSB
    //> Request to remote server
    err.setVal( MSOReq(pdu) );
    if( err.getVal().empty() ) numWCoil++;
    //> Set to acquisition block
    ResAlloc res( req_res, false );
    for( int i_b = 0; i_b < acqBlksCoil.size(); i_b++ )
	if( addr >= acqBlksCoil[i_b].off && (addr+1) <= (acqBlksCoil[i_b].off+acqBlksCoil[i_b].val.size()) )
	{
	    acqBlksCoil[i_b].val[addr-acqBlksCoil[i_b].off] = val;
	    break;
	}*/
}

int TMdContr::MSOReq( unsigned int channel, unsigned int type, unsigned int param, const string &pdu)
{
//	mess_info("MSOReq","MSOReq");
   AutoHD<TTransportOut> tr = SYS->transport().at().at(TSYS::strSepParse(mAddr,0,'.')).at().outAt(TSYS::strSepParse(mAddr,1,'.'));
    if( !tr.at().startStat() ) tr.at().start();
    struct can_frame frame;
    frame.can_id =  priority_R << PosPriority | type << PosType | mNode << PosAdress | channel << PosChannel | param |CAN_EFF_FLAG;
    //0x3|CAN_EFF_FLAG;
    /*  for (i=0; i<8;i++)
      {
       frame.data[i] =i;
      }*/

       //strcpy( frame.data, "foo" );
    frame.can_dlc = 0;//strlen( frame.data );
    if (mess_lev() == TMess::Debug) mess_debug(nodePath().c_str(),"MSOReq id<%08X> dlc<%u>",frame.can_id,frame.can_dlc);
   // tro.messIO(mbap.data(), mbap.size(), buf, sizeof(buf), reqTm, true);
    try{ tr.at().messIO((const char *)&frame, sizeof(frame),NULL,0,0,true); } catch(TError err){ return false; }

    return true;
}

bool TMdContr::MSOSet( unsigned int channel, unsigned int type, unsigned int param, const string &pdu)
{
	mess_info("MSOSet","MSOSet");
   AutoHD<TTransportOut> tr = SYS->transport().at().at(TSYS::strSepParse(mAddr,0,'.')).at().outAt(TSYS::strSepParse(mAddr,1,'.'));
    if( !tr.at().startStat() ) tr.at().start();
    struct can_frame frame;
    frame.can_id =  priority_W << PosPriority | type << PosType | mNode << PosAdress | channel << PosChannel | param |CAN_EFF_FLAG;
    //0x3|CAN_EFF_FLAG;
    /*  for (i=0; i<8;i++)
      {
       frame.data[i] =i;
      }*/

       //strcpy( frame.data, "foo" );
    frame.can_dlc = 8;//strlen( frame.data );
    for (int i=0; i<8;i++)
        {
         frame.data[i] = pdu.data()[i];
//         mess_info("MSOSet","MSOSet %02X",frame.data[i]);
        }
    if (mess_lev() == TMess::Debug) mess_debug(nodePath().c_str(),"MSOSet id<%08X> dlc<%u>",frame.can_id,frame.can_dlc);
    tr.at().messIO((const char *)&frame, sizeof(frame));
//    mess_info("---------MSOSet","---------MSOSet");

    return true;
}

bool TMdContr::MSOSetV( unsigned int channel, unsigned int type, unsigned int param, const string &pdu)
{
	mess_info("MSOSetV","MSOSetV");
   AutoHD<TTransportOut> tr = SYS->transport().at().at(TSYS::strSepParse(mAddr,0,'.')).at().outAt(TSYS::strSepParse(mAddr,1,'.'));
    if( !tr.at().startStat() ) tr.at().start();
    struct can_frame frame;
    frame.can_id =  priority_V << PosPriority | type << PosType | mNode << PosAdress | channel << PosChannel | param |CAN_EFF_FLAG;
    //0x3|CAN_EFF_FLAG;
    /*  for (i=0; i<8;i++)
      {
       frame.data[i] =i;
      }*/

       //strcpy( frame.data, "foo" );
    frame.can_dlc = 8;//strlen( frame.data );
    for (int i=0; i<8;i++)
        {
         frame.data[i] = pdu.data()[i];
//         mess_info("MSOSet","MSOSet %02X",frame.data[i]);
        }
    if (mess_lev() == TMess::Debug) mess_debug(nodePath().c_str(),"MSOSet id<%08X> dlc<%u>",frame.can_id,frame.can_dlc);
    tr.at().messIO((const char *)&frame, sizeof(frame));
//    mess_info("---------MSOSet","---------MSOSet");

    return true;
}

void *TMdContr::Task( void *icntr )
{
    string pdu;
    TMdContr &cntr = *(TMdContr *)icntr;

    cntr.endrun_req = false;
    cntr.prc_st = true;

    try
    {
	while( !cntr.endrun_req )
	{
//		vector<string> lst;
//		cntr.list(lst);
		MtxAlloc prmRes(cntr.enRes, true);
//		for(int i_l=0; i_l < lst.size(); i_l++){
//			AutoHD<TMdPrm> t = cntr.at(lst[i_l]);
//			t.at().Task(0);
//		}
		for(unsigned i_p=0; i_p < cntr.pHd.size(); i_p++)
		    cntr.pHd[i_p].at().Task(0);
		prmRes.unlock();

	    TSYS::taskSleep(cntr.period(),cntr.period()?0:TSYS::cron(cntr.cron()));
	}
    }
    catch( TError err )	{ mess_err( err.cat.c_str(), err.mess.c_str() ); }

    cntr.prc_st = false;

    return NULL;
}

uint16_t TMdPrm::Task(uint16_t cod)
{
	if (enableStat()){
		if (mDA) {
	//    	if (mDA->IsNeedUpdate()) mDA->Task(TaskRefresh);
			return mDA->Task(cod);
		} else {
			return 0;
		}
	}

}

uint16_t TMdPrm::HandleEvent(unsigned int channel,unsigned int type,unsigned int param,unsigned int flag,const string &ireqst)
{
	if (enableStat()){
		if (mDA) {
			return mDA->HandleEvent(channel,type,param,flag,ireqst);
		} else {
			return 0;
		}
	} else {
		return 0;
	}

}

void TMdContr::setCntrDelay( const string &err )
{
/*    tmDelay = restTm;
    ResAlloc res( req_res, false );
    for( int i_b = 0; i_b < acqBlksCoil.size(); i_b++ )	acqBlksCoil[i_b].err.setVal( err );
    for( int i_b = 0; i_b < acqBlksCoilIn.size(); i_b++ )	acqBlksCoilIn[i_b].err.setVal( err );
    for( int i_b = 0; i_b < acqBlks.size(); i_b++ )	acqBlks[i_b].err.setVal( err );
    for( int i_b = 0; i_b < acqBlksIn.size(); i_b++ )	acqBlksIn[i_b].err.setVal( err );*/
}

void TMdContr::cntrCmdProc( XMLNode *opt )
{
    //> Get page info
    if(opt->name() == "info")
    {
	TController::cntrCmdProc(opt);
	ctrMkNode("fld",opt,-1,"/cntr/cfg/ADDR",cfg("ADDR").fld().descr(),RWRWR_,"root",SDAQ_ID,3,"tp","str","dest","select","select","/cntr/cfg/trLst");
	ctrMkNode("fld",opt,-1,"/cntr/cfg/SCHEDULE",cfg("SCHEDULE").fld().descr(),RWRWR_,"root",SDAQ_ID,4,"tp","str","dest","sel_ed",
	    "sel_list","1;1e-3;* * * * *;10 * * * *;10-20 2 */2 * *",
	    "help",_("Schedule is writed in seconds periodic form or in standard Cron form.\n"
		     "Seconds form is one real number (1.5, 1e-3).\n"
		     "Cron it is standard form '* * * * *'. Where:\n"
		     "  - minutes (0-59);\n"
		     "  - hours (0-23);\n"
		     "  - days (1-31);\n"
		     "  - month (1-12);\n"
		     "  - week day (0[sunday]-6)."));
	return;
    }
    //> Process command to page
    string a_path = opt->attr("path");
    if(a_path == "/cntr/cfg/trLst" && ctrChkNode(opt))
    {
	vector<string> sls;
	SYS->transport().at().outTrList(sls);
	for(int i_s = 0; i_s < sls.size(); i_s++)
	    opt->childAdd("el")->setText(sls[i_s]);
    }
    else TController::cntrCmdProc(opt);
}

TMdContr::SDataRec::SDataRec( int ioff, int v_rez ) : off(ioff)
{
    val.assign(v_rez,0);
    err.setVal(_("11:Value not gathered."));
}

TMdContr::STTRec::STTRec(unsigned int adr) : addr(adr), val(0.0)
{
    err.setVal(_("11:Value not gathered."));
}

TMdContr::STCRec::STCRec(unsigned int adr) : addr(adr), val(0), state(0)
{
    err.setVal(_("11:Value not gathered."));
}

//******************************************************
//* TMdPrm                                             *
//******************************************************
TMdPrm::TMdPrm( string name, TTipParam *tp_prm ) :
    TParamContr( name, tp_prm ),
    p_el("w_attr")
    //m_attrLs(cfg("ATTR_LS").getS())
{

}

TMdPrm::~TMdPrm( )
{
    nodeDelAll( );
}

void TMdPrm::postEnable( int flag )
{
    TParamContr::postEnable(flag);
    if( !vlElemPresent(&p_el) )	vlElemAtt(&p_el);
}

TMdContr &TMdPrm::owner( )	{ return (TMdContr&)TParamContr::owner(); }

void TMdPrm::enable()
{
    if( enableStat() )	return;
    TParamContr::enable();
    for(unsigned i_f = 0; i_f < p_el.fldSize(); )
    {
	try { p_el.fldDel(i_f); }
	catch(TError err) { mess_warning(err.cat.c_str(),err.mess.c_str()); i_f++; }
    }
    if (mDA) {delete mDA; mDA = NULL;}

    if(type().name == "tp_TT" ) mDA = new MezTT(this, cfg("DEV_ID").getI());
    if(type().name == "tp_TC" ) mDA = new MezTC(this, cfg("DEV_ID").getI());
    if(type().name == "tp_TU" ) mDA = new MezTU(this, cfg("DEV_ID").getI());
    if(type().name == "tp_TI" ) mDA = new MezTI(this, cfg("DEV_ID").getI());
    if(type().name == "tp_TR" ) mDA = new MezTR(this, cfg("DEV_ID").getI());
    owner().prmEn(this, true);	//Put to process
}

void TMdPrm::disable()
{
    if( !enableStat() )  return;

    owner().prmEn(this, false);	//Remove from process
    TParamContr::disable();

    //> Set EVAL to parameter attributes
    vector<string> ls;
    elem().fldList(ls);
    for(int i_el = 0; i_el < ls.size(); i_el++)
	vlAt(ls[i_el]).at().setS( EVAL_STR, 0, true );
}

void TMdPrm::vlGet( TVal &val )
{
//    mess_info("-----------vlGET","%s",val.name().c_str());
    if( !enableStat() || !owner().startStat() )
    {
	if( val.name() == "err" )
	{
	    if( !enableStat() )			val.setS(_("1:Parameter is disabled."),0,true);
	    else if(!owner().startStat())	val.setS(_("2:Acquisition is stoped."),0,true);
	}
	else val.setS(EVAL_STR,0,true);
	return;
    }

    if( owner().redntUse( ) ) return;
}

void TMdPrm::vlSet( TVal &valo, const TVariant &vl, const TVariant &pvl  )
{
    if( !enableStat() || !owner().startStat() )	valo.setI( EVAL_INT, 0, true );
    string rez;

    //> Send to active reserve station
    if( owner().redntUse( ) )
    {
	if( valo.getS(0,true) == pvl.getS() ) return;
	XMLNode req("set");
	req.setAttr("path",nodePath(0,true)+"/%2fserv%2fattr")->childAdd("el")->setAttr("id",valo.name())->setText(valo.getS(0,true));
	SYS->daq().at().rdStRequest(owner().workId(),req);
	return;
    }
    if (mDA) {
        mDA->setVal(valo);
    } else {
        return;
    }
}

void TMdPrm::vlArchMake( TVal &val )
{
    if( val.arch().freeStat() ) return;
    val.arch().at().setSrcMode( TVArchive::ActiveAttr, val.arch().at().srcData() );
    val.arch().at().setPeriod( owner().period() ? owner().period()/1e3 : 1000000 );
    val.arch().at().setHardGrid( true );
    val.arch().at().setHighResTm( true );
}

void TMdPrm::cntrCmdProc( XMLNode *opt )
{
    //> Get page info
    if(opt->name() == "info")
    {
	TParamContr::cntrCmdProc(opt);
	return;
    }
    //> Process command to page
    TParamContr::cntrCmdProc(opt);
}
