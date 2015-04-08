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
F32 FUEL_PW_Prim = 0;
F32 FUEL_PW_Sec = 0;
F32 FUEL_PW_Dead = 0;
//Mass
F32 FUEL_Mass = 0;
F32 FUEL_Mass_Prim = 0;
F32 FUEL_Mass_Sec = 0;
F32 FUEL_Mass_Stoich = 0;
//Desired Fuel Air
F32 FUEL_FA_Des = 0;
F32 FUEL_FA_LeanLim = 0;
//Angles
F32 FUEL_VIT_Ang = 0;
//Injector characterization
F32 FUEL_Inj_Slope_Prim = 0;
F32 FUEL_Inj_Slope_Sec = 0;
F32 FUEL_Inj_DP_Prim = 0;
F32 FUEL_Inj_DP_Sec = 0;
F32 FUEL_Inj_Prs_Prim = 0;
F32 FUEL_Inj_Prs_Sec = 0;
F32 FUEL_Inj_Prs_Rail = 0;
//Injector Limits
F32 FUEL_Inj_PW_Lim = 0;
F32 FUEL_Inj_Mass_Lim = 0;
F32 FUEL_Inj_Pct_Split = 0;
//Start Fuel
F32 FUEL_PW_Start = 0;
F32 FUEL_PW_Start_Raw = 0;

//DIAL CAL
OE_CAL F32 DIAL_FUEL_PW_Prim = 0;
OE_CAL BOOL DIAL_FUEL_PW_Prim_Sel = 0;
OE_CAL F32 DIAL_FUEL_PW_Sec = 0;
OE_CAL BOOL DIAL_FUEL_PW_Sec_Sel = 0;
OE_CAL F32 DIAL_FUEL_Mass_Prim = 0;
OE_CAL BOOL DIAL_FUEL_Mass_Prim_Sel = 0;
OE_CAL F32 DIAL_FUEL_Mass_Sec = 0;
OE_CAL BOOL DIAL_FUEL_Mass_Sec_Sel = 0;
OE_CAL F32 DIAL_FUEL_Mass = 0;
OE_CAL BOOL DIAL_FUEL_Mass_Sel = 0;
OE_CAL F32 DIAL_SPK_DWELL = 1000;
OE_CAL BOOL DIAL_SPK_DWELL_Sel = 0;

//CAL
//Lean Limit
OE_CAL F32 FUEL_FA_LeanLim_Surf[17*17] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
//VIT angles surface
OE_CAL F32 FUEL_VIT_Surf[17*17] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
//Drop Dead angle
OE_CAL F32 FUEL_DropDead_Ang = 0;
//start fuel
OE_CAL F32 FUEL_PW_Start_Surf[17*17] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
//Stoich FA
OE_CAL F32 FUEL_FA_Stoich_Cal = 0.1024;
//Req Fuel for start
OE_CAL F32 FUEL_REQ = 8.15;
//Injector Characterization
OE_CAL F32 FUEL_PW_Dead_Tbl[17] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
OE_CAL F32 FUEL_PW_Slope_Tbl[5] = {
    0,  0,  0,  0,  0
};
OE_CAL F32 FUEL_Idx_InjPrs_Tbl[5] = {
    0,  0,  0,  0,  0
};
OE_CAL F32 FUEL_Inj_Prs_Rail_Cal = 400;