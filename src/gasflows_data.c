//
// Andrew Palardy
// Gas Flows Data

//Includes
#include "openecu.h"
#include "gasflows.h"

//RAM data
//MAP
F32 GF_MAP;
//GF_Charge is mg/cyc/cyl
F32 GF_Charge;
//GF_PortMassFlow charge but in mg/sec
F32 GF_PortMassFlow;
//Base Charge before corrections
F32 GF_ChargeBase;
//Volumetric Efficiency final
F32 GF_VEBase;
//Volumetric efficiency correction adaption
F32 GF_VECorr;
//O2 correction integral
F32 GF_O2S;
//Charge Predicted calculated from CalcMAPPred
F32 GF_ChargePred;
//Port mass flow predicted
F32 GF_PortMassFlowPred;
//Gas Factors (1/(R*T)) calculated in 320ms task
F32 GF_GasFac;
//Gasflow temperature
F32 GF_Temp;
//Calculated in 10ms task from RPM
F32 GF_CyclesPerSec;
//Charge Ratio
F32 GF_ChargeRat;

//Dial Cals
OE_CAL U8 DIAL_GF_VEBase_Sel = 0;
OE_CAL F32 DIAL_GF_VEBase = 0.0;

//Cals
//Effective Displacement of cylinder
OE_CAL F32 GF_CylDispEff = 0.449;
//Effective number of cylinders
OE_CAL U8 GF_CylNumberEff = 1;
//Specific gas constant
OE_CAL F32 GF_SpecificGasConst = 0.00;

//Tables
OE_CAL F32 GF_MAPIdx[17] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

//Surfaces
OE_CAL F32 GF_VESurf[17*17] = {
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