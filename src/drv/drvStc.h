/* drvStc.h */
/* share/src/drv $Id$ */
/*
 * The following are specific driver routines for the AMD STC
 *
 * NOTE: if multiple threads use these routines at once you must provide locking
 * so command/data sequences are gauranteed. See mz8310_driver.c for examples.
 *
 *
 *      Author: Jeff Hill
 *      Date:   Feb 89
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 * Modification Log:
 * -----------------
 *
 * joh  022089  Init Release
 * joh  082493  ANSI C and EPICS return codes
 */

/*
 * AMD STC constants
 */
#define CHANONCHIP              5U
#define CHIPCHAN                (channel%CHANONCHIP)
#define CHIPNUM                 (channel/CHANONCHIP)

#define STC_RESET               *pcmd = 0xffU
#define STC_BUS16               *pcmd = 0xefU
#define STC_SET_MASTER_MODE(D)  {*pcmd = 0x17U; *pdata=(D);}
#define STC_MASTER_MODE         (*pcmd = 0x17U, *pdata)

#define STC_CTR_INIT(MODE,LOAD,HOLD)\
{*pcmd = CHIPCHAN+1; *pdata = (MODE); *pdata = (LOAD); *pdata= (HOLD);}

#define STC_CTR_READ(MODE,LOAD,HOLD)\
{*pcmd = CHIPCHAN+1; (MODE) = *pdata; (LOAD) = *pdata; (HOLD) = *pdata;}

#define STC_SET_TC(D)           *pcmd = 0xe0U | ((D)?8:0)|(CHIPCHAN+1U)

#define STC_LOAD                *pcmd = 0x40U | 1<<(CHIPCHAN)
#define STC_STEP                *pcmd = 0xf0U | (CHIPCHAN+1U)
#define STC_ARM                 *pcmd = 0x20U | 1<<CHIPCHAN
#define STC_DISARM              *pcmd = 0xc0U | 1<<CHIPCHAN




/*
 * return type of the stc routines
 */
typedef long    stcStat;
#define STC_SUCCESS	0


stcStat stc_io_report(
volatile unsigned char  *pcmd,
volatile unsigned short *pdata
);


stcStat stc_init(
volatile unsigned char  *pcmd,
volatile unsigned short	*pdata,
unsigned 		master_mode
);

stcStat stc_one_shot_read(
unsigned 		*preset,
unsigned short 		*edge0_count,
unsigned short 		*edge1_count,
volatile unsigned char  *pcmd,
volatile unsigned short *pdata,
unsigned 		channel,
unsigned 		*int_source 
);

stcStat stc_one_shot(
unsigned 		preset,
unsigned 		edge0_count,
unsigned 		edge1_count,
volatile unsigned char  *pcmd,
volatile unsigned short *pdata,
unsigned 		channel,
unsigned 		int_source 
);

