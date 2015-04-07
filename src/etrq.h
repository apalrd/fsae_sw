/*
Copyright 2014, 2015 Andrew Palardy
Kettering University CSC/FSAE Engine Software
Engine Drivers
*/
//
// Andrew Palardy
// Fuel
// Data File
//

#include "openecu.h"
#include "fsae_sw.h"
#include "fuel.h"


//RAM
//Pulse widths
extern F32 FUEL_PW_Prim;
extern F32 FUEL_PW_Sec;
extern F32 FUEL_PW_Dead;
//Mass
extern F32 FUEL_Mass;
extern F32 FUEL_Mass_Prim;
extern F32 FUEL_Mass_Sec;
extern F32 FUEL_Mass_Stoich;
//Desired Fuel Air
extern F32 FUEL_FA_Des;
extern F32 FUEL_FA_LeanLim;
//Angles
extern F32 FUEL_VIT_Ang;
//Injector characterization
extern F32 FUEL_Inj_Slope_Prim;
extern F32 FUEL_Inj_Slope_Sec;
extern F32 FUEL_Inj_DP_Prim;
extern F32 FUEL_Inj_DP_Sec;
extern F32 FUEL_Inj_Prs_Prim;
extern F32 FUEL_Inj_Prs_Sec;
extern F32 FUEL_Inj_Prs_Rail;
//Injector Limits
extern F32 FUEL_Inj_PW_Lim;
extern F32 FUEL_Inj_Mass_Lim;
extern F32 FUEL_Inj_Pct_Split;
//Start Fuel
extern F32 FUEL_PW_Start;
extern F32 FUEL_PW_Start_Raw;

//DIAL CAL
extern F32 DIAL_FUEL_PW_Prim;
extern BOOL DIAL_FUEL_PW_Prim_Sel;
extern F32 DIAL_FUEL_PW_Sec;
extern BOOL DIAL_FUEL_PW_Sec_Sel;
extern F32 DIAL_FUEL_Mass_Prim;
extern BOOL DIAL_FUEL_Mass_Prim_Sel;
extern F32 DIAL_FUEL_Mass_Sec;
extern BOOL DIAL_FUEL_Mass_Sec_Sel;
extern F32 DIAL_FUEL_Mass;
extern BOOL DIAL_FUEL_Mass_Sel;

//CAL
//Lean Limit
extern OE_CAL F32 FUEL_FA_LeanLim_Surf[];
//VIT angles surface
extern OE_CAL F32 FUEL_VIT_Surf[];
//start fuel
extern OE_CAL F32 FUEL_PW_Start_Surf[];
//Stoich FA
extern F32 FUEL_FA_Stoich_Cal;
//Req Fuel for start
extern F32 FUEL_REQ;
//Injector Characterization
extern F32 FUEL_PW_Dead_Tbl[];
extern F32 FUEL_PW_Slope_Tbl[];
extern F32 FUEL_Idx_InjPrs_Tbl[];
extern F32 FUEL_Inj_Prs_Rail_Cal;