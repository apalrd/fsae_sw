/*
Copyright 2014, 2015 Andrew Palardy
Kettering University CSC/FSAE Engine Software
Engine Drivers
*/

#include "openecu.h"
#include "fsae_sw.h"


//Engine configuration
extern F32 ENGDRVS_TDC_ANGLES[];
//Cam/Crank config
extern U8 ENGDRVS_CRANK_TEETH;
extern U8 ENGDRVS_CRANK_MISS_TEETH;
//Injector config
extern PDX_LCHAN_T ENGDRVS_INJ_CHANS[];
//Spark config
extern PDX_LCHAN_T ENGDRVS_SPK_CHANS[];
//Software config
extern F32 ENGDRVS_SW_CALC_ANGLE;
extern PAX_LCHAN_T ENGDRVS_SW_PRI_CHAN;
extern F32 ENGDRVS_SW_PRI_ANG[];

//Engine RAM
extern U8 ENGDRVS_CUR_CYL;
extern U8 CURRENT_CYLINDER;//Shortcut variable
//Cam/Crank RAM
extern BOOL ENGDRVS_SYNC_MOVE;
extern BOOL ENGDRVS_SYNC_WITH_CRANK;
extern BOOL ENGDRVS_SYNC_WITH_CAM;
extern BOOL ENGDRVS_SYNC_VALID_CRANK;
extern BOOL ENGDRVS_SYNC_VALID_ENG;
extern F32 ENGDRVS_SYNC_ANG_CRANK;
extern F32 ENGDRVS_SYNC_ANG_ENG;
extern F32 ENGDRVS_SPD_AVG;
extern F32 ENGDRVS_SPD;
extern F32 RPM; //Shortcut variable
extern F32 ENGINE_POSITION; //Shortcut variable
//Injector RAM
extern F32 ENGDRVS_INJ_DEADTIME;
extern F32 ENGDRVS_INJ1_TIME;
extern F32 ENGDRVS_INJ2_TIME;
extern F32 ENGDRVS_INJ_FIRING_ANG;
extern F32 ENGDRVS_INJ_DROP_DEAD_ANG;
//Spark RAM
extern F32 ENGDRVS_SPK_DWELL;
extern F32 ENGDRVS_SPK_ANG;
extern F32 ENGDRVS_SPK_START_ANG;
//Software RAM
extern S16 ENGDRVS_SW_PRI_V;