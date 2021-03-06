//
// Andrew Palardy
// Sensor Processing
// Data File
//

#include "openecu.h"
#include "fsae_sw.h"
#include "sensors.h"

//ECT sensor
F32 SENS_ECT; //DegC
S16 SENS_ECT_V; //Volts (raw)
BOOL SENS_ECT_RAW_MIN_FLT;
BOOL SENS_ECT_RAW_MAX_FLT;
BOOL SENS_ECT_SLEW_RATE_FLT;
BOOL SENS_ECT_ENG_MIN_FLT;
BOOL SENS_ECT_ENG_MAX_FLT;
BOOL SENS_ECT_TRANSIENT_FLT;
BOOL SENS_ECT_LIMPIN; //OR of all faults
//ECT sensor CAL
OE_CAL F32 SENS_ECT_MIN_RAW_VAL = 90;
OE_CAL F32 SENS_ECT_MAX_RAW_VAL = 4000;
OE_CAL S32 SENS_ECT_ENG_LKP_SIZE = 17;
OE_CAL F32 SENS_ECT_ENG_LKP_X = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
OE_CAL F32 SENS_ECT_ENG_LKP_Y = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
OE_CAL F32 SENS_ECT_ENG_MIN_VAL = -40;
OE_CAL F32 SENS_ECT_ENG_MAX_VAL = 130;
OE_CAL F32 SENS_ECT_ENG_DEFAULT_VAL = 80;
OE_CAL F32 SENS_ECT_FLT_RISE_RATE = 0.5;
OE_CAL F32 SENS_ECT_FLT_FALL_RATE = 0.25;
OE_CAL F32 SENS_ECT_FLT_CLEAR_LEV = 0.5;
OE_CAL F32 SENS_ECT_FLT_SLEW_RATE = 1000000;
//ECT sensor const
static const PUT_ANALOGUE_CAL_DATA_T SENS_ECT_PROC_PAI_CAL =
{
    &SENS_ECT_MIN_RAW_VAL,
    &SENS_ECT_MAX_RAW_VAL,
    &SENS_ECT_ENG_LKP_SIZE,
    SENS_ECT_ENG_LKP_X,
    SENS_ECT_ENG_LKP_Y,
    &SENS_ECT_ENG_MIN_VAL,
    &SENS_ECT_ENG_MAX_VAL,
    &SENS_ECT_FLT_RISE_RATE,
    &SENS_ECT_FLT_FALL_RATE,
    &SENS_ECT_FLT_CLEAR_LEV,
    &SENS_ECT_ENG_DEFAULT_VAL,
    &SENS_ECT_FLT_SLEW_RATE
};
static PUT_ANALOGUE_WORKSPACE_T SENS_ECT_PROC_PAI_WORK;
//ACT sensor
F32 SENS_ACT; //DegC
S16 SENS_ACT_V; //Volts (raw)
BOOL SENS_ACT_RAW_MIN_FLT;
BOOL SENS_ACT_RAW_MAX_FLT;
BOOL SENS_ACT_SLEW_RATE_FLT;
BOOL SENS_ACT_ENG_MIN_FLT;
BOOL SENS_ACT_ENG_MAX_FLT;
BOOL SENS_ACT_TRANSIENT_FLT;
BOOL SENS_ACT_LIMPIN; //OR of all faults
//ACT sensor CAL
OE_CAL F32 SENS_ACT_MIN_RAW_VAL = 90;
OE_CAL F32 SENS_ACT_MAX_RAW_VAL = 4000;
OE_CAL S32 SENS_ACT_ENG_LKP_SIZE = 17;
OE_CAL F32 SENS_ACT_ENG_LKP_X = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
OE_CAL F32 SENS_ACT_ENG_LKP_Y = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
OE_CAL F32 SENS_ACT_ENG_MIN_VAL = -40;
OE_CAL F32 SENS_ACT_ENG_MAX_VAL = 130;
OE_CAL F32 SENS_ACT_ENG_DEFAULT_VAL = 80;
OE_CAL F32 SENS_ACT_FLT_RISE_RATE = 0.5;
OE_CAL F32 SENS_ACT_FLT_FALL_RATE = 0.25;
OE_CAL F32 SENS_ACT_FLT_CLEAR_LEV = 0.5;
OE_CAL F32 SENS_ACT_FLT_SLEW_RATE = 1000000;
//ACT sensor const
static const PUT_ANALOGUE_CAL_DATA_T SENS_ACT_PROC_PAI_CAL =
{
    &SENS_ACT_MIN_RAW_VAL,
    &SENS_ACT_MAX_RAW_VAL,
    &SENS_ACT_ENG_LKP_SIZE,
    SENS_ACT_ENG_LKP_X,
    SENS_ACT_ENG_LKP_Y,
    &SENS_ACT_ENG_MIN_VAL,
    &SENS_ACT_ENG_MAX_VAL,
    &SENS_ACT_FLT_RISE_RATE,
    &SENS_ACT_FLT_FALL_RATE,
    &SENS_ACT_FLT_CLEAR_LEV,
    &SENS_ACT_ENG_DEFAULT_VAL,
    &SENS_ACT_FLT_SLEW_RATE
};
static PUT_ANALOGUE_WORKSPACE_T SENS_ACT_PROC_PAI_WORK;
//MAP sensor (sampled 10ms for diagnostics, also at TDC undiagnosed
F32 SENS_MAP; //kPa
F32 SENS_MAP_TDC; //kPa, lower of last 2 samples
F32 SENS_MAP_TDC1;
F32 SENS_MAP_TDC2;
S16 SENS_MAP_V; //Volts (raw)
S16 SENS_MAP_TDC1_V; //Volts (raw)
S16 SENS_MAP_TDC2_V;
BOOL SENS_MAP_RAW_MIN_FLT;
BOOL SENS_MAP_RAW_MAX_FLT;
BOOL SENS_MAP_SLEW_RATE_FLT;
BOOL SENS_MAP_ENG_MIN_FLT;
BOOL SENS_MAP_ENG_MAX_FLT;
BOOL SENS_MAP_TRANSIENT_FLT;
BOOL SENS_MAP_LIMPIN; //OR of all faults
//MAP sensor CAL
OE_CAL F32 SENS_MAP_MIN_RAW_VAL = 90;
OE_CAL F32 SENS_MAP_MAX_RAW_VAL = 4000;
OE_CAL S32 SENS_MAP_ENG_LKP_SIZE = 4;
OE_CAL F32 SENS_MAP_ENG_LKP_X = {
    0,  0,  0,  0
};
OE_CAL F32 SENS_MAP_ENG_LKP_Y = {
    0,  0,  0,  0
};
OE_CAL F32 SENS_MAP_ENG_MIN_VAL = -40;
OE_CAL F32 SENS_MAP_ENG_MAX_VAL = 130;
OE_CAL F32 SENS_MAP_ENG_DEFAULT_VAL = 80;
OE_CAL F32 SENS_MAP_FLT_RISE_RATE = 0.5;
OE_CAL F32 SENS_MAP_FLT_FALL_RATE = 0.25;
OE_CAL F32 SENS_MAP_FLT_CLEAR_LEV = 0.5;
OE_CAL F32 SENS_MAP_FLT_SLEW_RATE = 1000000;
//MAP sensor const
static const PUT_ANALOGUE_CAL_DATA_T SENS_MAP_PROC_PAI_CAL =
{
    &SENS_MAP_MIN_RAW_VAL,
    &SENS_MAP_MAX_RAW_VAL,
    &SENS_MAP_ENG_LKP_SIZE,
    SENS_MAP_ENG_LKP_X,
    SENS_MAP_ENG_LKP_Y,
    &SENS_MAP_ENG_MIN_VAL,
    &SENS_MAP_ENG_MAX_VAL,
    &SENS_MAP_FLT_RISE_RATE,
    &SENS_MAP_FLT_FALL_RATE,
    &SENS_MAP_FLT_CLEAR_LEV,
    &SENS_MAP_ENG_DEFAULT_VAL,
    &SENS_MAP_FLT_SLEW_RATE
};
static PUT_ANALOGUE_WORKSPACE_T SENS_MAP_PROC_PAI_WORK;
//TPS sensor
F32 SENS_TPS; //DegC
S16 SENS_TPS_V; //Volts (raw)
BOOL SENS_TPS_RAW_MIN_FLT;
BOOL SENS_TPS_RAW_MAX_FLT;
BOOL SENS_TPS_SLEW_RATE_FLT;
BOOL SENS_TPS_ENG_MIN_FLT;
BOOL SENS_TPS_ENG_MAX_FLT;
BOOL SENS_TPS_TRANSIENT_FLT;
BOOL SENS_TPS_LIMPIN; //OR of all faults
//TPS sensor CAL
OE_CAL F32 SENS_TPS_MIN_RAW_VAL = 90;
OE_CAL F32 SENS_TPS_MAX_RAW_VAL = 4000;
OE_CAL S32 SENS_TPS_ENG_LKP_SIZE = 5;
OE_CAL F32 SENS_TPS_ENG_LKP_X = {
    0,  0,  0,  0,  0
};
OE_CAL F32 SENS_TPS_ENG_LKP_Y = {
    0,  0,  0,  0,  0
};
OE_CAL F32 SENS_TPS_ENG_MIN_VAL = 0;
OE_CAL F32 SENS_TPS_ENG_MAX_VAL = 100;
OE_CAL F32 SENS_TPS_ENG_DEFAULT_VAL = 80;
OE_CAL F32 SENS_TPS_FLT_RISE_RATE = 0.5;
OE_CAL F32 SENS_TPS_FLT_FALL_RATE = 0.25;
OE_CAL F32 SENS_TPS_FLT_CLEAR_LEV = 0.5;
OE_CAL F32 SENS_TPS_FLT_SLEW_RATE = 1000000;
//TPS sensor const
static const PUT_ANALOGUE_CAL_DATA_T SENS_TPS_PROC_PAI_CAL =
{
    &SENS_TPS_MIN_RAW_VAL,
    &SENS_TPS_MAX_RAW_VAL,
    &SENS_TPS_ENG_LKP_SIZE,
    SENS_TPS_ENG_LKP_X,
    SENS_TPS_ENG_LKP_Y,
    &SENS_TPS_ENG_MIN_VAL,
    &SENS_TPS_ENG_MAX_VAL,
    &SENS_TPS_FLT_RISE_RATE,
    &SENS_TPS_FLT_FALL_RATE,
    &SENS_TPS_FLT_CLEAR_LEV,
    &SENS_TPS_ENG_DEFAULT_VAL,
    &SENS_TPS_FLT_SLEW_RATE
};
static PUT_ANALOGUE_WORKSPACE_T SENS_TPS_PROC_PAI_WORK;
//Second sensor RAM
F32 SENS_TPS2;
S16 SENS_TPS2_V;
BOOL SENS_TPS_1_2_FLT;
//Second sensor cals
OE_CAL F32 SENS_TPS2_ENG_LKP_X = {
    0,  0,  0,  0,  0
};
OE_CAL F32 SENS_TPS2_ENG_LKP_Y = {
    0,  0,  0,  0,  0
};
//Second sensor faults
OE_CAL F32 SENS_TPS_1_2_FLT_DIFF = 10;
OE_CAL F32 SENS_TPS_1_2_FLT_DIFF_RISE_RATE = 0.5;
OE_CAL F32 SENS_TPS_1_2_FLT_DIFF_FALL_RATE = 0.25;
OE_CAL F32 SENS_TPS_1_2_FLT_DIFF_CLEAR_LEV = 0.5;
//PVS sensor
F32 SENS_PVS; //DegC
S16 SENS_PVS_V; //Volts (raw)
BOOL SENS_PVS_RAW_MIN_FLT;
BOOL SENS_PVS_RAW_MAX_FLT;
BOOL SENS_PVS_SLEW_RATE_FLT;
BOOL SENS_PVS_ENG_MIN_FLT;
BOOL SENS_PVS_ENG_MAX_FLT;
BOOL SENS_PVS_TRANSIENT_FLT;
BOOL SENS_PVS_LIMPIN; //OR of all faults
//PVS sensor CAL
F32 SENS_PVS_MIN_RAW_VAL = 90;
F32 SENS_PVS_MAX_RAW_VAL = 4000;
S32 SENS_PVS_ENG_LKP_SIZE = 5;
F32 SENS_PVS_ENG_LKP_X = {
    0,  0,  0,  0,  0
};
F32 SENS_PVS_ENG_LKP_Y = {
    0,  0,  0,  0,  0
};
F32 SENS_PVS_ENG_MIN_VAL = 0;
F32 SENS_PVS_ENG_MAX_VAL = 100;
F32 SENS_PVS_ENG_DEFAULT_VAL = 80;
F32 SENS_PVS_FLT_RISE_RATE = 0.5;
F32 SENS_PVS_FLT_FALL_RATE = 0.25;
F32 SENS_PVS_FLT_CLEAR_LEV = 0.5;
F32 SENS_PVS_FLT_SLEW_RATE = 1000000;
//PVS sensor const
static const PUT_ANALOGUE_CAL_DATA_T SENS_PVS_PROC_PAI_CAL =
{
    &SENS_PVS_MIN_RAW_VAL,
    &SENS_PVS_MAX_RAW_VAL,
    &SENS_PVS_ENG_LKP_SIZE,
    SENS_PVS_ENG_LKP_X,
    SENS_PVS_ENG_LKP_Y,
    &SENS_PVS_ENG_MIN_VAL,
    &SENS_PVS_ENG_MAX_VAL,
    &SENS_PVS_FLT_RISE_RATE,
    &SENS_PVS_FLT_FALL_RATE,
    &SENS_PVS_FLT_CLEAR_LEV,
    &SENS_PVS_ENG_DEFAULT_VAL,
    &SENS_PVS_FLT_SLEW_RATE
};
static PUT_ANALOGUE_WORKSPACE_T SENS_PVS_PROC_PAI_WORK;