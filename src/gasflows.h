//
// Gasflows
//

#ifndef _GASFLOWS_H
#define _GASFLOWS_H

//General definition: C to K
#define DEG_C_TO_K 273.3

//RAM data
//MAP
extern F32 GF_MAP;
//GF_Charge is mg/cyc/cyl
extern F32 GF_Charge;
//GF_PortMassFlow charge but in mg/sec
extern F32 GF_PortMassFlow;
//Base Charge before corrections
extern F32 GF_ChargeBase;
//Volumetric Efficiency final
extern F32 GF_VEBase;
//Volumetric efficiency correction adaption
extern F32 GF_VECorr;
//O2 correction integral
extern F32 GF_O2S;
//Charge Predicted calculated from CalcMAPPred
extern F32 GF_ChargePred;
//Port mass flow predicted
extern F32 GF_PortMassFlowPred;
//Gas Factors (1/(R*T)) calculated in 320ms task
extern F32 GF_GasFac;
//Gasflow temperature
extern F32 GF_Temp;
//Calculated in 10ms task from RPM
extern F32 GF_CyclesPerSec;
//Charge Ratio
extern F32 GF_ChargeRat;

//Dial Cals
extern OE_CAL U8 DIAL_GF_VEBase_Sel;
extern OE_CAL F32 DIAL_GF_VEBase;

//Cals
//Effective Displacement of cylinder
extern OE_CAL F32 GF_CylDispEff;
//Effective number of cylinders
extern OE_CAL U8 GF_CylNumberEff;
//Specific gas constant
extern OE_CAL F32 GF_SpecificGasConst;

//Tables
extern OE_CAL F32 GF_MAPIdx[];

//Surfaces
extern OE_CAL F32 GF_VESurf[];

#endif