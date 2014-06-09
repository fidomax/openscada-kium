
//OpenSCADA system module DAQ.MSO file: mso_daq.h
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

#ifndef MSO_DAQ_H
#define MSO_DAQ_H

#include <string>
#include <vector>
#include <map>
#include <deque>

#include <tsys.h>

#undef _
#define _(mess) mod->I18N(mess)

#define MaxLenReq 200

using std::string;
using std::vector;
using std::map;
using std::deque;
using namespace OSCADA;

//*************************************************
//* DAQ modul info!                               *
#define DAQ_ID		"MSO"
#define DAQ_NAME	_("MSO")
#define DAQ_TYPE	SDAQ_ID
#define DAQ_SUBVER	SDAQ_VER
#define DAQ_MVER	"0.0.1"
#define DAQ_AUTHORS	_("Maxim Kochetkov")
#define DAQ_DESCR	_("Allow realisation of MSO client service. Supported MSO-CAN protocols.")
#define DAQ_LICENSE	"GPL2"
//*************************************************

namespace MSO
{

//******************************************************
//* TMSOPrm                                             *
//******************************************************
class TMSOContr;

class TMSOPrm : public TParamContr
{
    public:
	//Methods
	TMSOPrm( string name, TTipParam *tp_prm );
	~TMSOPrm( );

	void enable( );
	void disable( );

	TElem &elem( )		{ return p_el; }
	TMSOContr &owner( );

    protected:
	void	cntrCmdProc( XMLNode *opt );	//Control interface command process

    private:
	//Methods
	void postEnable( int flag );
	void vlGet( TVal &val );
	void vlSet( TVal &val, const TVariant &pvl );
	void vlArchMake( TVal &val );

        //Attributes
	//string		m_attrLs;
	TElem		p_el;		//Work atribute elements
	ResString	acq_err;
};

//******************************************************
//* TMSOContr                                           *
//******************************************************
class TMSOContr: public TController
{
    public:
	//Methods
	TMSOContr( string name_c, const string &daq_db, TElem *cfgelem);
	~TMSOContr( );

	string getStatus( );

	long long period( )	{ return mPer; }
	string	cron( )		{ return mSched; }
	int	prior( )	{ return mPrior; }

	AutoHD<TMSOPrm> at( const string &nm )	{ return TController::at(nm); }

	void regVal( int addr, const string &dt = "TT" );		//Register value for acquisition
	int  getValR( int addr, ResString &err, bool in = false );	//Get register value
	float  getValTT( int addr, ResString &err);	                //Get TT
	int  getValTC( int addr, ResString &err);	                //Get TC val
	int  getStateTC( int addr, ResString &err);	                //Get TC state
	char getValC( int addr, ResString &err, bool in = false );	//Get coins value
	void setValR( int val, int addr, ResString &err );			//Set register value
	void setValC( char val, int addr, ResString &err );		//Set coins value
	string MSOReq( string &pdu );
	bool HandleData(unsigned int node, unsigned int channel, unsigned int type, unsigned int param, unsigned int flag, const string &ireqst);

    protected:
	//Methods
	void disable_( );
	void start_( );
	void stop_( );
	void cntrCmdProc( XMLNode *opt );	//Control interface command process
	bool cfgChange( TCfg &cfg );

    private:
	//Data
	class SDataRec
	{
	    public:
		SDataRec( int ioff, int v_rez );

		int	off;			//Data block start offset
		string	val;			//Data block values kadr
		ResString	err;		//Acquisition error text
	};
        class STTRec
        {
	    public:
		STTRec(unsigned int adr);

		float	val;            //TT value
		unsigned int addr;
		ResString	err;		//Acquisition error text
        };
        class STCRec
        {
	    public:
		STCRec(unsigned int adr);

		int val;            //TC value
		int state;            //TC value
		unsigned int addr;
		ResString	err;		//Acquisition error text
        };

	//Methods
	TParamContr *ParamAttach( const string &name, int type );

	static void *Task( void *icntr );
	void setCntrDelay( const string &err );

	//Attributes
	Res     req_res;
	int	&mPrior,			//Process task priority
	    &mNode;             //MSO Addres
	TCfg	&mSched,			// Calc schedule
		&mAddr;				//Transport device address

	int	&reqTm;				//Request timeout in ms

	long long mPer;

	bool	prc_st,				//Process task active
		endrun_req;			//Request to stop of the Process task
        vector<STTRec>          acqTT;          //Acquisition data blocks for TT
        vector<STCRec>          acqTC;          //Acquisition data blocks for TC
	vector<SDataRec>	acqBlks;	//Acquisition data blocks for registers
	vector<SDataRec>	acqBlksIn;	//Acquisition data blocks for input registers
	vector<SDataRec>	acqBlksCoil;	//Acquisition data blocks for coils
	vector<SDataRec>	acqBlksCoilIn;	//Acquisition data blocks for input coils

	double	tmGath;				//Gathering time

	float numRx, numTx;
};

//*************************************************
//* TTpContr                                      *
//*************************************************
class TTpContr: public TTipDAQ
{
    public:
	//Methods
	TTpContr( string name );
	~TTpContr( );
	bool DataIn(const string &ireqst, const string &sender);

    protected:
	//Methods
	void	load_( );
	void	save_( );

	bool redntAllow( )	{ return true; }

    private:
	//Methods
	void	postEnable( int flag );
	TController *ContrAttach( const string &name, const string &daq_db );
};

extern TTpContr *mod;

} //End namespace

#endif //MSO_DAQ_H
