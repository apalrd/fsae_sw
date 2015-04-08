/*
Copyright 2014, 2015 Andrew Palardy
Kettering University CSC/FSAE Engine Software
Spark header
*/

#ifndef _SPARK_H
#define _SPARK_H

//RAM
extern F32 SPK_ADV_Base;
extern F32 SPK_ADV;
extern F32 SPK_DWELL;

//DIAL CAL
extern F32 DIAL_SPK_ADV;
extern BOOL DIAL_SPK_ADV_Sel;
extern F32 DIAL_SPK_DWELL;
extern BOOL DIAL_SPK_DWELL_Sel;

//CAL
//Spark Advance (indexed by RPM and GF_CHARGE
extern F32 SPK_ADV_PowerOn_Surf[];
extern F32 SPK_ADV_PowerOff_Surf[];
//Start Spark (indexed by ECT)
extern F32 SPK_ADV_Start_Tbl];
//Dwell (indexed by batt)
extern F32 SPK_DWELL_Tbl[];

//Functions
void Spark_Calc40MS();
void Spark_CalcTDC();
void Spark_Init();

#endif