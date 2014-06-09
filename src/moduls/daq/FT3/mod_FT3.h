//!!! Module name, file name and module's license. Change for your need.
//OpenSCADA system module DAQ.ft3 file: mod_ft3.h
/***************************************************************************
 *   Copyright (C) 2009 by Roman Savochenko                                *
 *   rom_as@oscada.org, rom_as@fromru.com                                  *
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

//!!! Multi-including this header file prevent. Change for your include file name
#ifndef MOD_ft3_H
#define MOD_ft3_H

/*//!!! System's includings. Add need for your module includings.
#include <string>
#include <vector>

//!!! OpenSCADA module's API includings. Add need for your module includings.
#include <tcontroller.h>
#include <ttipdaq.h>
#include <tparamcontr.h>
*/
#include <string>
#include <vector>
#include <map>
#include <deque>

#include <tsys.h>

#include "da.h"

//!!! Individual module's translation function define. Don't change it!
#undef _
#define _(mess) mod->I18N(mess)


typedef struct sMsg  // структура сообщения
	{	
		uint8_t D[252]; // данные
		uint8_t L; // длина
		uint8_t C; // управление
		uint8_t A; // адрес получателя
		uint8_t B; // адрес отправителя
//		uint8_t N;
	} tagMsg;


typedef enum eCodFT3 {
	ResetChan = 0x0,
	ResData2  = 0x1,
	SetData   = 0x3,
	TimSync   = 0x4,
	Reset     = 0x5,
	Winter    = 0x6,
	Summer    = 0x7,
	ReqData1  = 0xA,
	ReqData2  = 0xB,
	ReqData   = 0xC,
	AddrReq   = 0xD,

	GOOD2  = 0,
	BAD2   = 1,
	GOOD3  = 8,
	BAD3   = 9
} CodFT3;
typedef enum eModeTask {
		TaskNone 	= 0,
		TaskIdle 	= 1,
		TaskRefresh	= 2,
		TaskSet		= 3
} ModeTask;
#define task_None 0
#define task_Idle 1
#define task_Refresh 2




using std::string;
using std::vector;
using std::map;
using std::deque;
using namespace OSCADA;

//!!! Module's meta-information.
//*************************************************
//* Modul info!                                   *
#define MOD_ID		"FT3"
#define MOD_NAME	_("DAQ FT3")
#define MOD_TYPE	SDAQ_ID
#define VER_TYPE	SDAQ_VER
#define MOD_VER		"0.1.0"
#define AUTHORS		_("Maxim Kothetkov, Olga Avdeyeva, Olga Kuzmickaya")
#define DESCRIPTION	_("Allow realisation of FT3 client service")
#define LICENSE		"GPL2"
//*************************************************

//!!! All module's objects you must include into self (individual) namespace. Change namespace for your module.
namespace FT3
{

//!!! DAQ-subsystem parameter object realisation define. Add methods and attributes for your need.
//*************************************************
//* Modft3::TMdPrm                               *
//*************************************************
class TMdContr;

class TMdPrm : public TParamContr
{
    friend class DA;
    public:
	//Methods
	//!!! Constructor for DAQ-subsystem parameter object.
	TMdPrm( string name, TTipParam *tp_prm );
	//!!! Destructor for DAQ-subsystem parameter object.
	~TMdPrm( );

	//!!! Parameter's structure element link function
	TElem &elem( )		{ return p_el; }

	//!!! Processing virtual functions for enable and disable parameter
	void enable( );
	void disable( );

	//!!! Direct link to parameter's owner controller
	TMdContr &owner( );

 //       ResString &devTp;	//Device type
//	ResString devTp;

	TElem	p_el;			//Work atribute elements
	uint16_t Task(uint16_t);
	uint16_t HandleEvent(uint8_t *);
	bool	needApply;

	//!!! Get data from Logic FT3 parameter
	uint8_t GetData(uint16_t, uint8_t *);

		

    protected:
	//Methods
	//!!! Processing virtual functions for load and save parameter to DB
	void load_( );
	void save_( );

    private:
	//Methods
	//!!! Post-enable processing virtual function
	void postEnable( int flag );
	//!!! Processing virtual function for OpenSCADA control interface comands
	void cntrCmdProc( XMLNode *opt );
	//!!! Processing virtual function for setup archive's parameters which associated with the parameter on time archive creation
	void vlArchMake( TVal &val );
	void vlSet( TVal &val, const TVariant &pvl );
	void vlGet( TVal &val );

	//Attributes
	//!!! Parameter's structure element
	DA	*mDA;

};

//!!! DAQ-subsystem controller object realisation define. Add methods and attributes for your need.
//*************************************************
//* Modft3::TMdContr                             *
//*************************************************
class TMdContr: public TController
{
    friend class TMdPrm;
    public:
	//Methods
	//!!! Constructor for DAQ-subsystem controller object.
	TMdContr( string name_c, const string &daq_db, ::TElem *cfgelem );
	//!!! Destructor for DAQ-subsystem controller object.
	~TMdContr( );

	//!!! Status processing function for DAQ-controllers
	string getStatus( );

	//!!! The controller's background task properties
	double	period( )	{ return vmax(m_per,0.1); }
	int	prior( )	{ return m_prior; }

	//!!! Request for connection to parameter-object of this controller
	AutoHD<TMdPrm> at( const string &nm )	{ return TController::at(nm); }

	//!!! Make transaction to transport
  	bool Transact(tagMsg * t);

  	//!!! Convert FT3 DateTime to time_t
	time_t DateTimeToTime_t(uint8_t * );

	//!!! Convert time_t to FT3 DateTime
	void Time_tToDateTime(uint8_t *,time_t );

	//!!! Process commands to Logic FT3 controller
	bool ProcessMessage(tagMsg *,tagMsg *);


    uint8_t devAddr;
	//bool Transact(tagMsg *);

    protected:

	//Methods
	//!!! Parameters register function, on time it enable, for fast processing into background task.
	void prmEn( const string &id, bool val );

	//!!! Processing virtual functions for start and stop DAQ-controller
	void start_( );
	void stop_( );


	//!!! FT3 CRC
	uint16_t CRC(char *data, uint16_t length);
	void MakePacket(tagMsg *msg,char *io_buf,uint16_t *len);
	bool VerCRC(char *p, uint16_t l);
	uint16_t VerifyPacket(char *t, uint16_t *l);  
	uint16_t ParsePacket(char *t, uint16_t l, tagMsg * msg);
	uint16_t Len(uint16_t l);
	
	//!!! Get data from Logic FT3 controller
	uint8_t GetData(uint16_t, uint8_t *);

    private:
	//Methods
	//!!! Processing virtual functions for self object-parameter creation.
	TParamContr *ParamAttach( const string &name, int type );
	//!!! Background task's function for periodic data acquisition.
	static void *DAQTask( void *icntr );
	static void *LogicTask( void *icntr );
	void cntrCmdProc( XMLNode *opt );

	//Attributes
//	ResString &mAddr;	//Transport device address
	//!!! The resource for Enable parameters.
	Res	en_res;		//Resource for enable params
	//!!! The links to the controller's background task properties into config.
	int64_t	&m_per,		// s
		&m_prior;	// Process task priority

	//!!! Background task's sync properties
	bool	prc_st,		// Process task active
		endrun_req;	// Request to stop of the Process task

	bool NeedInit;

	int	mNode;

	//!!! Enabled and processing parameter's links list container.
	vector< AutoHD<TMdPrm> >  p_hd;

	double	tm_gath;	// Gathering time
        uint8_t FCB2,FCB3;


};

//!!! Root module object define. Add methods and attributes for your need.
//*************************************************
//* Modft3::TTpContr                             *
//*************************************************
class TTpContr: public TTipDAQ
{
    public:
	//Methods
	//!!! Constructor for Root module object.
	TTpContr( string name );
	//!!! Destructor for Root module object.
	~TTpContr( );

    protected:
	//Methods
	//!!! Post-enable processing virtual function
	void postEnable( int flag );

	//!!! Processing virtual functions for load and save Root module to DB
	void load_( );
	void save_( );

	//!!! The flag for redundantion mechanism support by module detection
	bool redntAllow( )	{ return true; }

    private:
	//Methods
	//!!! Processing virtual functions for self object-controller creation.
	TController *ContrAttach( const string &name, const string &daq_db );

	//!!! Module's comandline options for print help function.
	string optDescr( );
};

//!!! The module root link
extern TTpContr *mod;

} //End namespace Modft3

#endif //MOD_ft3_H
