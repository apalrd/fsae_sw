//
// Andrew Palardy
// Fuel
// Data File
//

#include "openecu.h"
#include "fsae_sw.h"
#include "etrq.h"

//RAM
U8 ETRQ_ENG_MODE = 0;
BOOL ETRQ_Open_Pdl_Req = false;
F32 ETRQ_Des_TPS = 0.0;
F32 ETRQ_ETC_Integral = 0;
F32 ETRQ_ETC_Pterm = 0;
F32 ETRQ_ETC_Iterm = 0;
F32 ETRQ_ETC_Dterm = 0;
F32 ETRQ_ETC_Output = 0;
F32 ETRQ_ETC_Error = 0;
F32 ETRQ_ETC_ErrorLast = 0;
F32 ETRQ_ETC_DC = 0.0;

//Motor Control cals
OE_CAL F32 ETRQ_ETC_kP = 0;
OE_CAL F32 ETRQ_ETC_kI = 0;
OE_CAL F32 ETRQ_ETC_kD = 0;
OE_CAL BOOL ETRQ_ETC_EN = false;
//Motor PWM cals
OE_CAL F32 ETRQ_ETC_Freq = 200.0;
//Motor dials
OE_CAL BOOL DIAL_ETRQ_ETC_DC_SEL = false;
OE_CAL F32 DIAL_ETRQ_ETC_DC = 0.0;
//Motor mode
OE_CAL PDX_HBRIDGE_MODE_T ETRQ_ETC_Mode = PDX_UNI_FORWARD;
static PDX_HBRIDGE_MODE_T ETRQ_ETC_ModeLast = PDX_UNI_NO_DRIVE;