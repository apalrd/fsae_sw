//
// Andrew Palardy
// Spark
//


#include "openecu.h"
#include "fsae_sw.h"
#include "fuel.h"
#include "com_idx.h"
#include "epm.h"
#include "gasflows.h"

//Angular task calculation of fuel
void Fuel_CalcTDC()
{
    //Determine lean limit
    put_cal_map_2d_f32((F32)RPM,
                       GF_Charge,
                       17,
                       17,
                       IDX_RPM,
                       IDX_Charge,
                       FUEL_FA_LeanLim_Surf,
                       &FUEL_FA_LeanLim);
    
    
    //Determine desired FA ratio
    FUEL_FA_Des = min(ETRQ_FA_Des,FUEL_FA_LeanLim);
    
    //Determine base fuel mass to inject
    FUEL_Mass_Stoich = GF_Charge * FUEL_FA_Stoich_Cal;
    
    //Determine adjusted fuel mass to inject
    FUEL_Mass = FUEL_Mass_Stoich * FUEL_FA_Des;
    
    //Determine transient fuel compensation
    //None for now
    
    //Determine final fuel mass desired
    //No adjustments for now
    
    //Dials
    if(DIAL_FUEL_Mass_sel)
    {
        FUEL_Mass = DIAL_FUEL_Mass;
    }
    
    //Determine injector pulse width limits
    //I'll get to second injector later
    FUEL_Mass_Prim = FUEL_Mass;
    FUEL_Mass_Sec = 0;
    
    //Dials
    if(DIAL_FUEL_Mass_Prim_sel)
    {
        FUEL_Mass_Prim = DIAL_FUEL_Mass_Prim;
    }
    if(DIAL_FUEL_Mass_Sec_sel)
    {
        FUEL_Mass_Sec = DIAL_FUEL_Mass_Sec;
    }
    
    //Injector characterization
    //Injector pressures
    FUEL_Inj_Prs_Prim = GF_MAP;
    FUEL_Inj_Prs_Sec = GF_TIP;
    
    //Injector DP
    FUEL_Inj_DP_Prim = FUEL_Inj_Prs_Rail - FUEL_Inj_Prs_Prim;
    FUEL_Inj_DP_Sec = FUEL_Inj_Prs_Rail - FUEL_Inj_Prs_Sec;
    
    //Injector Slopes
    put_cal_map_1d_f32(FUEL_Inj_DP_Prim,
                       5,
                       FUEL_Idx_InjPrs_Tbl,
                       FUEL_PW_Slope_Tbl,
                       &FUEL_Inj_Slope_Prim);
    put_cal_map_1d_f32(FUEL_Inj_DP_Sec,
                       5,
                       FUEL_Idx_InjPrs_Tbl,
                       FUEL_PW_Slope_Tbl,
                       &FUEL_Inj_Slope_Sec);
    
    //Injector Offset
    put_cal_map_1d_f32(SENS_VBatt,
                       17,
                       IDX_VBatt,
                       FUEL_PW_Dead_Tbl,
                       &FUEL_PW_Dead);
    
    
    //Fuel pulse widths
    FUEL_PW_Prim = FUEL_Mass_Prim * FUEL_Inj_Slope_Prim;
    FUEL_PW_Sec = FUEL_Mass_Sec * FUEL_Inj_Slope_Sec;
    
    
    //Dials
    if(DIAL_FUEL_PW_Prim_Sel)
    {
        FUEL_PW_Prim = DIAL_FUEL_PW_Prim;
    }
    if(DIAL_FUEL_PW_Sec_Sel)
    {
        FUEL_PW_Sec = DIAL_FUEL_PW_Sec;
    }
    
    //VIT
    put_cal_map_2d_f32((F32)RPM,
                       GF_Charge,
                       17,
                       17,
                       IDX_RPM,
                       IDX_Charge,
                       FUEL_VIT_Surf,
                       &FUEL_VIT_Ang);
    
    //Start Fuel
    put_cal_map_2d_f32((F32)RPM,
                       SENS_ECT,
                       17,
                       17,
                       IDX_RPM,
                       IDX_ECT,
                       FUEL_PW_Start_Surf,
                       &FUEL_PW_Start_Raw);
    
    //Start pulse
    FUEL_PW_Start = FUEL_PW_Start_Raw * FUEL_REQ;
    
    //Determine which pulse to use
    
#error "Start fuel fix me"
    
}

//Init for engine drivers
void Fuel_Init()
{
    //Set start fuel based on ECT
}