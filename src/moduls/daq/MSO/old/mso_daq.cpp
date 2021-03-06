
//OpenSCADA system module DAQ.MSO file: MSO_daq.cpp
/***************************************************************************
 *   Copyright (C) 2007-2010 by Maxim Kochetkov                            *
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
    fldAdd( new TFld("PRM_BD",_("Parameteres table"),TFld::String,TFld::NoFlag,"30","") );
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
    int t_prm = tpParmAdd("std","PRM_BD",_("Standard"));
    tpPrmAt(t_prm).fldAdd( new TFld("ATTR_LS",_("Attributes list"),TFld::String,TFld::FullText|TCfg::NoVal|TCfg::TransltText,"1000","") );
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
    return new TMSOContr(name,daq_db,this);
}

//******************************************************
//* TMSOContr                                           *
//******************************************************
TMSOContr::TMSOContr( string name_c, const string &daq_db, TElem *cfgelem ) :
	TController( name_c, daq_db, cfgelem ), prc_st(false), endrun_req(false), tmGath(0),
	numRx(0), numTx(0),
	mSched(cfg("SCHEDULE")), mPrior(cfg("PRIOR").getId()),
	mAddr(cfg("ADDR")),mNode(cfg("NODE").getId()),
	reqTm(cfg("TM_REQ").getId())
{
    cfg("PRM_BD").setS("MSOPrm_"+name_c);
}

TMSOContr::~TMSOContr()
{
    if(run_st) stop();
}

string TMSOContr::getStatus( )
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

TParamContr *TMSOContr::ParamAttach( const string &name, int type )
{
    return new TMSOPrm( name, &owner().tpPrmAt(type) );
}

bool TTpContr::DataIn(const string &ireqst, const string &sender )
{
    unsigned int node = strtoul(sender.c_str(),NULL,0);

    unsigned int mso = (node>>10)&0xFF;
    unsigned int channel = (node>>4)&0x3F;
    unsigned int type = (node>>18)&0xFF;
    unsigned int param = (node)&0x7;
    unsigned int flag = (node>>26)&0x7;
 //   AT91C_CAN_MIDE | priority_N << 26 | identifier_TC << 18 | MSO_Addres << 10 | ChannelNumber << 3
    mess_info("DataIn"," sender<%s> mso<%u> channel<%u> type<%u> param<%u> flag<%u>",sender.c_str(),mso,channel,type,param,flag);
    vector<string> lst;
    SYS->daq().at().at("MSO").at().list(lst);
    for(int i_l=0; i_l < lst.size(); i_l++){
        AutoHD<TMSOContr> t = SYS->daq().at().at("MSO").at().at(lst[i_l]);
        if (t.at().HandleData(mso, channel, type, param, flag, ireqst)) break;
    }
    return true;
}

bool TMSOContr::HandleData(unsigned int node, unsigned int channel, unsigned int type, unsigned int param, unsigned int flag, const string &ireqst)
{
    mess_info("ContrHandle","node %u mNode %u",node, mNode);
    if (node==mNode)
    {
        mess_info("ContrHandle","node %u found!",node);
        if (type==11){
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
        }
    }
    return false;
}

void TMSOContr::disable_( )
{
    //> Clear acquisition data block
    acqTT.clear();
    acqTC.clear();
/*    acqBlks.clear();
    acqBlksIn.clear();
    acqBlksCoil.clear();
    acqBlksCoilIn.clear();*/
}

void TMSOContr::start_( )
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
    SYS->taskCreate( nodePath('.',true), mPrior, TMSOContr::Task, this );
}

void TMSOContr::stop_( )
{
    //> Stop the request and calc data task
    SYS->taskDestroy( nodePath('.',true), &endrun_req );

    //> Clear statistic
    numRx = numTx = 0;
}

bool TMSOContr::cfgChange( TCfg &icfg )
{
    TController::cfgChange(icfg);

/*    if( icfg.fld().name() == "PROT" )
    {
	cfg("REQ_TRY").setView(icfg.getS()!="TCP");
	if( startStat() ) stop();
    }
    else if( icfg.fld().name() == "FRAG_MERGE" && enableStat( ) ) disable( );*/

    return true;
}

void TMSOContr::regVal( int addr, const string &dt )
{
    if( addr < 0 )	return;

    ResAlloc res( req_res, true );
    if( dt == "TT")
    {
        mess_info(nodePath().c_str(),_("RegValTT %d."),addr);
        acqTT.insert(acqTT.begin(),STTRec(addr));
        mess_info(nodePath().c_str(),_("RegValTT size %d."),acqTT.size());
    }
    if( dt == "TC")
    {
        mess_info(nodePath().c_str(),_("RegValTC %d."),addr);
        acqTC.insert(acqTC.begin(),STCRec(addr));
        mess_info(nodePath().c_str(),_("RegValTC size %d."),acqTC.size());
    }

    //> Register to acquisition block
    /*if( dt == "R" || dt == "RI" )
    {
	vector< SDataRec > &workCnt = (dt == "RI") ? acqBlksIn : acqBlks;
	int i_b;
	for( i_b = 0; i_b < workCnt.size(); i_b++ )
	{
	    if( (reg*2) < workCnt[i_b].off )
	    {
		if( (mMerge || (reg*2+2) >= workCnt[i_b].off) && (workCnt[i_b].val.size()+workCnt[i_b].off-(reg*2)) < MaxLenReq )
		{
		    workCnt[i_b].val.insert(0,workCnt[i_b].off-reg*2,0);
		    workCnt[i_b].off = reg*2;
		}
		else workCnt.insert(workCnt.begin()+i_b,SDataRec(reg*2,2));
	    }
	    else if( (reg*2+2) > (workCnt[i_b].off+workCnt[i_b].val.size()) )
	    {
		if( (mMerge || reg*2 <= (workCnt[i_b].off+workCnt[i_b].val.size())) && (reg*2+2-workCnt[i_b].off) < MaxLenReq )
		{
		    workCnt[i_b].val.append((reg*2+2)-(workCnt[i_b].off+workCnt[i_b].val.size()),0);
		    //>> Check for allow mergin to next block
		    if( !mMerge && i_b+1 < workCnt.size() && (workCnt[i_b].off+workCnt[i_b].val.size()) >= workCnt[i_b+1].off )
		    {
			workCnt[i_b].val.append(workCnt[i_b+1].val,workCnt[i_b].off+workCnt[i_b].val.size()-workCnt[i_b+1].off,string::npos);
			workCnt.erase(workCnt.begin()+i_b+1);
		    }
		}
		else continue;
	    }
	    break;
	}
	if( i_b >= workCnt.size() )
	    workCnt.insert(workCnt.begin()+i_b,SDataRec(reg*2,2));
    }
    //> Coils
    else if( dt == "C" || dt == "CI" )
    {
	vector< SDataRec > &workCnt = (dt == "CI") ? acqBlksCoilIn : acqBlksCoil;
	int i_b;
	for( i_b = 0; i_b < workCnt.size(); i_b++ )
	{
	    if( reg < workCnt[i_b].off )
	    {
		if( (mMerge || (reg+1) >= workCnt[i_b].off) && (workCnt[i_b].val.size()+workCnt[i_b].off-reg) < MaxLenReq*8 )
		{
		    workCnt[i_b].val.insert(0,workCnt[i_b].off-reg,0);
		    workCnt[i_b].off = reg;
		}
		else workCnt.insert(workCnt.begin()+i_b,SDataRec(reg,1));
	    }
	    else if( (reg+1) > (workCnt[i_b].off+workCnt[i_b].val.size()) )
	    {
		if( (mMerge || reg <= (workCnt[i_b].off+workCnt[i_b].val.size())) && (reg+1-workCnt[i_b].off) < MaxLenReq*8 )
		{
		    workCnt[i_b].val.append((reg+1)-(workCnt[i_b].off+workCnt[i_b].val.size()),0);
		    //>> Check for allow mergin to next block
		    if( !mMerge && i_b+1 < workCnt.size() && (workCnt[i_b].off+workCnt[i_b].val.size()) >= workCnt[i_b+1].off )
		    {
			workCnt[i_b].val.append(workCnt[i_b+1].val,workCnt[i_b].off+workCnt[i_b].val.size()-workCnt[i_b+1].off,string::npos);
			workCnt.erase(workCnt.begin()+i_b+1);
		    }
		}
		else continue;
	    }
	    break;
	}
	if( i_b >= workCnt.size() )
	    workCnt.insert(workCnt.begin()+i_b,SDataRec(reg,1));
    }*/
}
float TMSOContr::getValTT( int addr, ResString &err )
{
    float rez = EVAL_REAL;
    ResAlloc res( req_res, false );
    for( int i_b = 0; i_b < acqTT.size(); i_b++ )
    {
        if (acqTT[i_b].addr==addr)
        {
            err.setVal( acqTT[i_b].err.getVal() );
 //           mess_info("getValTT","%u",i_b);
            if( err.getVal().empty() ) {
		        rez = (acqTT[i_b].val);
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

int TMSOContr::getValTC( int addr, ResString &err )
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
		        rez = (acqTC[i_b].val);
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

int TMSOContr::getStateTC( int addr, ResString &err )
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

int TMSOContr::getValR( int addr, ResString &err, bool in )
{
    int rez = EVAL_INT;
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

char TMSOContr::getValC( int addr, ResString &err, bool in )
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

void TMSOContr::setValR( int val, int addr, ResString &err )
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

void TMSOContr::setValC( char val, int addr, ResString &err )
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

string TMSOContr::MSOReq( string &pdu )
{
 /*  AutoHD<TTransportOut> tr = SYS->transport().at().at(TSYS::strSepParse(mAddr,0,'.')).at().outAt(TSYS::strSepParse(mAddr,1,'.'));
    if( !tr.at().startStat() ) tr.at().start();

    XMLNode req(mPrt);
    req.setAttr("id",id())->
	setAttr("reqTm",TSYS::int2str(reqTm))->
	setAttr("node",TSYS::int2str(mNode))->
	setAttr("reqTry",TSYS::int2str(connTry))->
	setText(pdu);

    tr.at().messProtIO(req,"MSO");

    if( !req.attr("err").empty() )
    {
	if( atoi(req.attr("err").c_str()) == 14 ) numErrCon++;
	else numErrResp++;
	return req.attr("err");
    }
    pdu = req.text();*/
    return "";
}

void *TMSOContr::Task( void *icntr )
{
    string pdu;
    TMSOContr &cntr = *(TMSOContr *)icntr;

    cntr.endrun_req = false;
    cntr.prc_st = true;

    try
    {
	while( !cntr.endrun_req )
	{
//	    if( cntr.tmDelay > 0 )	{ sleep(1); cntr.tmDelay = vmax(0,cntr.tmDelay-1); continue; }

/*	    long long t_cnt = TSYS::curTime();

#if OSC_DEBUG >= 3
	    mess_debug(cntr.nodePath().c_str(),_("Fetch coils' and registers' blocks."));
#endif
	    ResAlloc res( cntr.req_res, false );

	    //> Get coils
	    for( int i_b = 0; i_b < cntr.acqBlksCoil.size(); i_b++ )
	    {
		if( cntr.endrun_req ) break;
		if( cntr.redntUse( ) ) { cntr.acqBlksCoil[i_b].err.setVal(_("4:Server failure.")); continue; }
		//>> Encode request PDU (Protocol Data Units)
		pdu = (char)0x1;					//Function, read multiple coils
		pdu += (char)(cntr.acqBlksCoil[i_b].off>>8);		//Address MSB
		pdu += (char)cntr.acqBlksCoil[i_b].off;			//Address LSB
		pdu += (char)(cntr.acqBlksCoil[i_b].val.size()>>8);	//Number of coils MSB
		pdu += (char)cntr.acqBlksCoil[i_b].val.size();		//Number of coils LSB
		//>> Request to remote server
		cntr.acqBlksCoil[i_b].err.setVal( cntr.MSOReq(pdu) );
		if( cntr.acqBlksCoil[i_b].err.getVal().empty() )
		{
		    if( (cntr.acqBlksCoil[i_b].val.size()/8+((cntr.acqBlksCoil[i_b].val.size()%8)?1:0)) != (pdu.size()-2) )
			cntr.acqBlksCoil[i_b].err.setVal(_("15:Response PDU size error."));
		    else
		    {
			for( int i_c = 0; i_c < cntr.acqBlksCoil[i_b].val.size(); i_c++ )
			    cntr.acqBlksCoil[i_b].val[i_c] = (bool)((pdu[2+i_c/8]>>(i_c%8))&0x01);
			cntr.numRCoil += cntr.acqBlksCoil[i_b].val.size();
		    }
		}
		else if( atoi(cntr.acqBlksCoil[i_b].err.getVal().c_str()) == 14 )
		{
		    cntr.setCntrDelay(cntr.acqBlksCoil[i_b].err.getVal());
		    break;
		}
	    }
	    if( cntr.tmDelay > 0 )	continue;
	    //> Get input's coils
	    for( int i_b = 0; i_b < cntr.acqBlksCoilIn.size(); i_b++ )
	    {
		if( cntr.endrun_req ) break;
		if( cntr.redntUse( ) ) { cntr.acqBlksCoilIn[i_b].err.setVal(_("4:Server failure.")); continue; }
		//>> Encode request PDU (Protocol Data Units)
		pdu = (char)0x2;					//Function, read multiple input's coils
		pdu += (char)(cntr.acqBlksCoilIn[i_b].off>>8);	//Address MSB
		pdu += (char)cntr.acqBlksCoilIn[i_b].off;		//Address LSB
		pdu += (char)(cntr.acqBlksCoilIn[i_b].val.size()>>8);	//Number of coils MSB
		pdu += (char)cntr.acqBlksCoilIn[i_b].val.size();	//Number of coils LSB
		//>> Request to remote server
		cntr.acqBlksCoilIn[i_b].err.setVal( cntr.MSOReq(pdu) );
		if( cntr.acqBlksCoilIn[i_b].err.getVal().empty() )
		{
		    if( (cntr.acqBlksCoilIn[i_b].val.size()/8+((cntr.acqBlksCoilIn[i_b].val.size()%8)?1:0)) != (pdu.size()-2) )
			cntr.acqBlksCoilIn[i_b].err.setVal(_("15:Response PDU size error."));
		    else
		    {
			for( int i_c = 0; i_c < cntr.acqBlksCoilIn[i_b].val.size(); i_c++ )
			    cntr.acqBlksCoilIn[i_b].val[i_c] = (bool)((pdu[2+i_c/8]>>(i_c%8))&0x01);
			cntr.numRCoilIn += cntr.acqBlksCoilIn[i_b].val.size();
		    }
		}
		else if( atoi(cntr.acqBlksCoilIn[i_b].err.getVal().c_str()) == 14 )
		{
		    cntr.setCntrDelay(cntr.acqBlksCoilIn[i_b].err.getVal());
		    break;
		}
	    }
	    if( cntr.tmDelay > 0 )	continue;
	    //> Get registers
	    for( int i_b = 0; i_b < cntr.acqBlks.size(); i_b++ )
	    {
		if( cntr.endrun_req ) break;
		if( cntr.redntUse( ) ) { cntr.acqBlks[i_b].err.setVal(_("4:Server failure.")); continue; }
		//>> Encode request PDU (Protocol Data Units)
		pdu = (char)0x3;				//Function, read multiple registers
		pdu += (char)((cntr.acqBlks[i_b].off/2)>>8);	//Address MSB
		pdu += (char)(cntr.acqBlks[i_b].off/2);		//Address LSB
		pdu += (char)((cntr.acqBlks[i_b].val.size()/2)>>8);	//Number of registers MSB
		pdu += (char)(cntr.acqBlks[i_b].val.size()/2);	//Number of registers LSB
		//>> Request to remote server
		cntr.acqBlks[i_b].err.setVal( cntr.MSOReq(pdu) );
		if( cntr.acqBlks[i_b].err.getVal().empty() )
		{
		    if( cntr.acqBlks[i_b].val.size() != (pdu.size()-2) ) cntr.acqBlks[i_b].err.setVal(_("15:Response PDU size error."));
		    else
		    {
			cntr.acqBlks[i_b].val.replace(0,cntr.acqBlks[i_b].val.size(),pdu.data()+2,cntr.acqBlks[i_b].val.size());
			cntr.numRReg += cntr.acqBlks[i_b].val.size()/2;
		    }
		}
		else if( atoi(cntr.acqBlks[i_b].err.getVal().c_str()) == 14 )
		{
		    cntr.setCntrDelay(cntr.acqBlks[i_b].err.getVal());
		    break;
		}
	    }
	    if( cntr.tmDelay > 0 )	continue;
	    //> Get input registers
	    for( int i_b = 0; i_b < cntr.acqBlksIn.size(); i_b++ )
	    {
		if( cntr.endrun_req ) break;
		if( cntr.redntUse( ) ) { cntr.acqBlksIn[i_b].err.setVal(_("4:Server failure.")); continue; }
		//>> Encode request PDU (Protocol Data Units)
		pdu = (char)0x4;				//Function, read multiple input registers
		pdu += (char)((cntr.acqBlksIn[i_b].off/2)>>8);	//Address MSB
		pdu += (char)(cntr.acqBlksIn[i_b].off/2);		//Address LSB
		pdu += (char)((cntr.acqBlksIn[i_b].val.size()/2)>>8);	//Number of registers MSB
		pdu += (char)(cntr.acqBlksIn[i_b].val.size()/2);	//Number of registers LSB
		//>> Request to remote server
		cntr.acqBlksIn[i_b].err.setVal( cntr.MSOReq(pdu) );
		if( cntr.acqBlksIn[i_b].err.getVal().empty() )
		{
		    if( cntr.acqBlksIn[i_b].val.size() != (pdu.size()-2) ) cntr.acqBlksIn[i_b].err.setVal(_("15:Response PDU size error."));
		    else
		    {
			cntr.acqBlksIn[i_b].val.replace(0,cntr.acqBlksIn[i_b].val.size(),pdu.data()+2,cntr.acqBlksIn[i_b].val.size());
			cntr.numRRegIn += cntr.acqBlksIn[i_b].val.size()/2;
		    }
		}
		else if( atoi(cntr.acqBlksIn[i_b].err.getVal().c_str()) == 14 )
		{
		    cntr.setCntrDelay(cntr.acqBlksIn[i_b].err.getVal());
		    break;
		}
	    }
	    res.release();

	    if( cntr.tmDelay <= 0 ) cntr.tmDelay--;

	    //> Calc acquisition process time
	    cntr.tmGath = 1e-3*(TSYS::curTime()-t_cnt);*/

	    TSYS::taskSleep(cntr.period(),cntr.period()?0:TSYS::cron(cntr.cron()));
	}
    }
    catch( TError err )	{ mess_err( err.cat.c_str(), err.mess.c_str() ); }

    cntr.prc_st = false;

    return NULL;
}

void TMSOContr::setCntrDelay( const string &err )
{
/*    tmDelay = restTm;
    ResAlloc res( req_res, false );
    for( int i_b = 0; i_b < acqBlksCoil.size(); i_b++ )	acqBlksCoil[i_b].err.setVal( err );
    for( int i_b = 0; i_b < acqBlksCoilIn.size(); i_b++ )	acqBlksCoilIn[i_b].err.setVal( err );
    for( int i_b = 0; i_b < acqBlks.size(); i_b++ )	acqBlks[i_b].err.setVal( err );
    for( int i_b = 0; i_b < acqBlksIn.size(); i_b++ )	acqBlksIn[i_b].err.setVal( err );*/
}

void TMSOContr::cntrCmdProc( XMLNode *opt )
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

TMSOContr::SDataRec::SDataRec( int ioff, int v_rez ) : off(ioff)
{
    val.assign(v_rez,0);
    err.setVal(_("11:Value not gathered."));
}

TMSOContr::STTRec::STTRec(unsigned int adr) : addr(adr), val(0.0)
{
    err.setVal(_("11:Value not gathered."));
}

TMSOContr::STCRec::STCRec(unsigned int adr) : addr(adr), val(0), state(0)
{
    err.setVal(_("11:Value not gathered."));
}

//******************************************************
//* TMSOPrm                                             *
//******************************************************
TMSOPrm::TMSOPrm( string name, TTipParam *tp_prm ) :
    TParamContr( name, tp_prm ),
    p_el("w_attr")
    //m_attrLs(cfg("ATTR_LS").getS())
{

}

TMSOPrm::~TMSOPrm( )
{
    nodeDelAll( );
}

void TMSOPrm::postEnable( int flag )
{
    TParamContr::postEnable(flag);
    if( !vlElemPresent(&p_el) )	vlElemAtt(&p_el);
}

TMSOContr &TMSOPrm::owner( )	{ return (TMSOContr&)TParamContr::owner(); }

void TMSOPrm::enable()
{
mess_info(nodePath().c_str(),"-------------");
    if( enableStat() )	return;
mess_info(nodePath().c_str(),"-------------");
    TParamContr::enable();
    string m_attrLs = cfg("ATTR_LS").getS();
    //> Parse MSO attributes and convert to string list
    vector<string> als;
    string ai,          //Channel number
           sel,         //String to parse
           atp,         //Channel type (TT,TC)
           //aprm,        //Channel param
           //atp_m,
           //atp_sub,

           aid,         //Variable ID
           anm;         //Variable Name
           //awr;         //Read/Write
    for( int ioff = 0; (sel=TSYS::strSepParse(m_attrLs,0,'\n',&ioff)).size(); )
    {
    mess_info(nodePath().c_str(),sel.c_str());
        atp   = TSYS::strSepParse(sel,0,':');
        if( atp.empty() ) atp = "TT";
//	atp_m = TSYS::strSepParse(atp,0,'_');
//	atp_sub = TSYS::strSepParse(atp,1,'_');
	//awr   = TSYS::strSepParse(sel,1,':');
	    ai    = TSYS::strSepParse(sel,1,':');
//	aprm  = TSYS::strSepParse(sel,3,':');
        aid   = TSYS::strSepParse(sel,2,':');
        if( aid.empty() ) aid = atp+ai;
        anm   = TSYS::strSepParse(sel,3,':');
        if( anm.empty() ) anm = atp+ai;

        if( vlPresent(aid) && !p_el.fldPresent(aid) ) continue;
        TFld::Type tp = TFld::Real;
        if ( atp  == "TT")
        {
            mess_info(nodePath().c_str(),_("TT"));
            string tmpId=aid+"_Value";
            mess_info(nodePath().c_str(),tmpId.c_str());
            if( !p_el.fldPresent(aid) )
	        {
                mess_info(nodePath().c_str(),_("add"));
                p_el.fldAdd( new TFld(tmpId.c_str(),"",tp,TFld::NoFlag) );
                int el_id = p_el.fldId(tmpId);
                unsigned flg = TFld::NoWrite|TVal::DirRead;
                p_el.fldAt(el_id).setFlg( flg );
                p_el.fldAt(el_id).setDescr( anm+ "_Value");
                p_el.fldAt(el_id).setReserve( atp+":"+ai+":value" );
                owner().regVal( strtol(ai.c_str(),NULL,0), atp );
            }
            als.push_back(tmpId);
//          if ( aprm == "MesTime" || aprm == "Mode"
        }
        else if (atp == "TC")
        {
            tp = TFld::Integer;
            mess_info(nodePath().c_str(),_("TC"));
            string tmpId=aid+"_Value";
            mess_info(nodePath().c_str(),tmpId.c_str());
            if( !p_el.fldPresent(aid) )
	        {
                mess_info(nodePath().c_str(),_("add"));
                p_el.fldAdd( new TFld(tmpId.c_str(),"",tp,TFld::NoFlag) );
                int el_id = p_el.fldId(tmpId);
                unsigned flg = TFld::NoWrite|TVal::DirRead;
                p_el.fldAt(el_id).setFlg( flg );
                p_el.fldAt(el_id).setDescr( anm+ "_Value");
                p_el.fldAt(el_id).setReserve( atp+":"+ai+":value" );
                owner().regVal( strtol(ai.c_str(),NULL,0), atp );
            }
            als.push_back(tmpId);
            mess_info(nodePath().c_str(),_("TC"));
            tmpId=aid+"_State";
            mess_info(nodePath().c_str(),tmpId.c_str());
            if( !p_el.fldPresent(aid) )
	        {
                mess_info(nodePath().c_str(),_("add"));
                p_el.fldAdd( new TFld(tmpId.c_str(),"",tp,TFld::NoFlag) );
                int el_id = p_el.fldId(tmpId);
                unsigned flg = TFld::NoWrite|TVal::DirRead;
                p_el.fldAt(el_id).setFlg( flg );
                p_el.fldAt(el_id).setDescr( anm+ "_State");
                p_el.fldAt(el_id).setReserve( atp+":"+ai+":state" );
                //owner().regVal( strtol(ai.c_str(),NULL,0), atp );
            }
            als.push_back(tmpId);
//          if ( aprm == "MesTime" || aprm == "Mode"
        }
//	if( atp[0]=='C' || (atp_sub.size() && atp_sub[0] == 'b') ) tp = TFld::Boolean;
//	else if( atp_sub == "f" ) tp = TFld::Real;

/*	if( !p_el.fldPresent(aid) || p_el.fldAt(p_el.fldId(aid)).type() != tp )
	{
	    if( p_el.fldPresent(aid)) p_el.fldDel(p_el.fldId(aid));
	    p_el.fldAdd( new TFld(aid.c_str(),"",tp,TFld::NoFlag) );
	}
	int el_id = p_el.fldId(aid);

	unsigned flg = (awr=="rw") ? TVal::DirWrite|TVal::DirRead :
				     ((awr=="w") ? TVal::DirWrite : TFld::NoWrite|TVal::DirRead);
	if( atp.size() >= 2 && atp[1] == 'I' )	flg = (flg & (~TVal::DirWrite)) | TFld::NoWrite;
	p_el.fldAt(el_id).setFlg( flg );
	p_el.fldAt(el_id).setDescr( anm );

	if( flg&TVal::DirRead )
	{
	    int reg = strtol(ai.c_str(),NULL,0);
	    owner().regVal(reg,atp_m);
	    if( atp[0] == 'R' && (atp_sub == "i4" || atp_sub == "f") )
	    {
		int reg2 = TSYS::strSepParse(ai,1,',').empty() ? (reg+1) : strtol(TSYS::strSepParse(ai,1,',').c_str(),NULL,0);
		owner().regVal( reg2, atp_m );
		ai = TSYS::int2str(reg)+","+TSYS::int2str(reg2);
	    }
	}
	p_el.fldAt(el_id).setReserve( atp+":"+ai );

	als.push_back(aid);*/
    }

    //> Check for delete DAQ parameter's attributes
    for( int i_p = 0; i_p < p_el.fldSize(); i_p++ )
    {
	int i_l;
	for( i_l = 0; i_l < als.size(); i_l++ )
	    if( p_el.fldAt(i_p).name() == als[i_l] )
		break;
	if( i_l >= als.size() )
	    try{ p_el.fldDel(i_p); i_p--; }
	    catch(TError err){ mess_warning(err.cat.c_str(),err.mess.c_str()); }
    }
}

void TMSOPrm::disable()
{
    if( !enableStat() )  return;

    TParamContr::disable();

    //> Set EVAL to parameter attributes
    vector<string> ls;
    elem().fldList(ls);
    for(int i_el = 0; i_el < ls.size(); i_el++)
	vlAt(ls[i_el]).at().setS( EVAL_STR, 0, true );
}

void TMSOPrm::vlGet( TVal &val )
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

//    int off = 0;
    string tp = TSYS::strSepParse(val.fld().reserve(),0,':');
//    string atp_sub = TSYS::strSepParse(tp,1,'_');
//    bool isInputs = (tp.size()>=2 && tp[1]=='I');
    string aids = TSYS::strSepParse(val.fld().reserve(),1,':');
    string fld = TSYS::strSepParse(val.fld().reserve(),2,':');
    int aid = strtol(aids.c_str(),NULL,0);
    if( !tp.empty() )
    {
        if (tp == "TT")
        {
            if (fld=="value") val.setR(owner().getValTT(aid,acq_err),0,true);
        }
        if (tp == "TC")
        {
            if      (fld=="state") val.setI(owner().getStateTC(aid,acq_err),0,true);
            else if (fld=="value") val.setI(owner().getValTC(aid,acq_err),0,true);
        }
/*	if( tp[0] == 'C' ) val.setB(owner().getValC(aid,acq_err,isInputs),0,true);
	if( tp[0] == 'R' )
	{
	    int vl = owner().getValR(aid,acq_err,isInputs);
	    if( !atp_sub.empty() && atp_sub[0] == 'b' ) val.setB((vl>>atoi(atp_sub.c_str()+1))&1,0,true);
	    else if( !atp_sub.empty() && atp_sub == "f" )
	    {
		int vl2 = owner().getValR( strtol(TSYS::strSepParse(aids,1,',').c_str(),NULL,0), acq_err, isInputs );
		if( vl == EVAL_INT || vl2 == EVAL_INT ) val.setR(EVAL_REAL,0,true);
		union { uint32_t i; float f; } wl;
		wl.i = ((vl2&0xffff)<<16) | (vl&0xffff);
		val.setR(wl.f,0,true);
	    }
	    else if( !atp_sub.empty() && atp_sub == "i2" )	val.setI((int16_t)vl,0,true);
	    else if( !atp_sub.empty() && atp_sub == "i4" )
	    {
		int vl2 = owner().getValR( strtol(TSYS::strSepParse(aids,1,',').c_str(),NULL,0), acq_err, isInputs );
		if( vl == EVAL_INT || vl2 == EVAL_INT ) val.setI(EVAL_INT,0,true);
		val.setI((int)(((vl2&0xffff)<<16)|(vl&0xffff)),0,true);
	    }
	    else val.setI(vl,0,true);
	}*/
    }
    else if( val.name() == "err" )
    {
//	if( acq_err.getVal().empty() )
	val.setS("0",0,true);
//	else				val.setS(acq_err.getVal(),0,true);
    }
}

void TMSOPrm::vlSet( TVal &valo, const TVariant &pvl )
{
/*    if( !enableStat() )	valo.setS( EVAL_STR, 0, true );

    //> Send to active reserve station
    if( owner().redntUse( ) )
    {
	if( valo.getS(NULL,true) == pvl.getS() ) return;
	XMLNode req("set");
	req.setAttr("path",nodePath(0,true)+"/%2fserv%2fattr")->childAdd("el")->setAttr("id",valo.name())->setText(valo.getS(NULL,true));
	SYS->daq().at().rdStRequest(owner().workId(),req);
	return;
    }

    string vl = valo.getS(NULL,true);
    if( vl == EVAL_STR || vl == pvl.getS() ) return;

    //> Direct write
    int off = 0;
    string tp = TSYS::strSepParse(valo.fld().reserve(),0,':',&off);
    string atp_sub = TSYS::strSepParse(tp,1,'_');
    string aids = TSYS::strSepParse(valo.fld().reserve(),0,':',&off);
    int aid = strtol(aids.c_str(),NULL,0);

    if( !tp.empty() )
    {
	if( tp[0] == 'C' )	owner().setValC(valo.getB(NULL,true),aid,acq_err);
	if( tp[0] == 'R' )
	{
	    if( !atp_sub.empty() && atp_sub[0] == 'b' )
	    {
		int vl = owner().getValR(aid,acq_err);
		if( vl != EVAL_INT )
		    owner().setValR( valo.getB(NULL,true) ? (vl|(1<<atoi(atp_sub.c_str()+1))) : (vl & ~(1<<atoi(atp_sub.c_str()+1))), aid, acq_err);
	    }
	    else if( !atp_sub.empty() && atp_sub == "f" )
	    {
		union { uint32_t i; float f; } wl;
		wl.f = valo.getR(NULL,true);
		owner().setValR( wl.i&0xFFFF, aid, acq_err );
		owner().setValR( (wl.i>>16)&0xFFFF, strtol(TSYS::strSepParse(aids,1,',').c_str(),NULL,0), acq_err );
	    }
	    else if( !atp_sub.empty() && atp_sub == "i4" )
	    {
		int vl = valo.getI(NULL,true);
		owner().setValR( vl&0xFFFF, aid, acq_err );
		owner().setValR( (vl>>16)&0xFFFF, strtol(TSYS::strSepParse(aids,1,',').c_str(),NULL,0), acq_err );
	    }
	    else owner().setValR(valo.getI(NULL,true),aid,acq_err);
	}
    }*/
}

void TMSOPrm::vlArchMake( TVal &val )
{
    if( val.arch().freeStat() ) return;
    val.arch().at().setSrcMode( TVArchive::ActiveAttr, val.arch().at().srcData() );
    val.arch().at().setPeriod( owner().period() ? owner().period()/1e3 : 1000000 );
    val.arch().at().setHardGrid( true );
    val.arch().at().setHighResTm( true );
}

void TMSOPrm::cntrCmdProc( XMLNode *opt )
{
    //> Get page info
    if(opt->name() == "info")
    {
	TParamContr::cntrCmdProc(opt);
	ctrMkNode("fld",opt,-1,"/prm/cfg/ATTR_LS",cfg("ATTR_LS").fld().descr(),RWRWR_,"root",SDAQ_ID,1,
	    "help",_("Attributes configuration list. List must be written by lines in format: [dt:numb:id:name]\n"
		    "Where:\n"
		    "  dt - MSO data type (TT,TC).\n"
		    "  numb - MSO channel number (dec, hex or octal);\n"
		    "  id - created attribute identifier;\n"
		    "  name - created attribute name.\n"
		    "Example:\n"
		    "  'R_b10:25:r:rBit:Reg bit' - get bit 10 from register 25."));
	return;
    }
    //> Process command to page
    TParamContr::cntrCmdProc(opt);
}
