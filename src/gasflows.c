//
// Andrew Palardy
// Gas Flows calculation
//

#include "openecu.h"
#include "fsae_sw.h"
#include "gasflows.h"
#include "com_idx.h"
#include "epm.h"
#include "sensors.h"

//Functions for calculating out flows in the 10ms task
void GF_Calc10MS()
{
    //First calculate GF_CyclesPerSec from RPM
    GF_CyclesPerSec = RPM / 120;
}

//Calculate the density corrections in the 320ms task
void GF_Calc320MS()
{
    //Thermal factors
    
    //Determine temperatures
    GF_Temp = SENS_ACT + DEG_C_TO_K;
    
    //Calculate the normal gas factor
    GF_GasFac = 1/(GF_SpecificGasConst * GF_Temp);
    
}

//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_CalcTDC()
{
    //This task is responsible for calculating GF_Charge and
    //GF_PortMassFlow in the TDC task for fuel and spark
    
    //GF MAP must be set by the sensors module!
    
    //Determine VE for charge
    put_cal_map_2d_f32((F32)RPM,
                       GF_MAP,
                       17,
                       17,
                       IDX_RPM,
                       GF_MAPIdx,
                       GF_VESurf,
                       &GF_VEBase);
    //Process dial
    if(DIAL_GF_VEBase_Sel)
    {
        GF_VEBase = DIAL_GF_VEBase;
    }
    
    //Determine GF Charge before VE Corrs for charge ratio
    GF_ChargeBase = GF_MAP * GF_CylDispEff * GF_GasFac * GF_VEBase;
    
    //Use Charge Ratio to determine VE Corr
    GF_VECorr = 0
    GF_O2S = 0;
    
    //Use VE Corr and O2S to adjust charge
    GF_Charge = GF_ChargeBase * (1 + GF_VECorr) * (1 + GF_O2S);
    
    //Calculate Port Mass Flow from charge
    GF_PortMassFlow = GF_Charge * GF_CyclesPerSec * 1; //Hardcoded 1 cylinder engine
    
}
