//
// Andrew Palardy
// Sensor Processing
//


#include "openecu.h"
#include "fsae_sw.h"
#include "sensors.h"


void SEN_Calc320MS()
{
    //ECT sensor
    
    //Read the sensor
    pax_adc_inpit(PIO_AIN_A19, &SENS_ECT_V, FALSE);
    
    //proc AI input
    put_process_analog_input(SENS_ECT_V,
                             0.320,
                             &SENS_ECT,
                             %SENS_ECT_RAW_MIN_FLT,
                             &SENS_ECT_RAW_MAX_FLT,
                             &SENS_ECT_SLEW_RATE_FLT,
                             &SENS_ECT_ENG_MIN_FLT,
                             &SENS_ECT_ENG_MAX_FLT,
                             &SENS_ECT_TRANSIENT_FLT,
                             &SENS_ECT_PROC_PAI_CAL,
                             &SENS_ECT_PROC_PAI_WORK);
    //Combine errors
    SENS_ECT_LIMPIN = (SENS_ECT_RAW_MIN_FLT |
                       SENS_ECT_RAW_MAX_FLT |
                       SENS_ECT_SLEW_RATE_FLT |
                       SENS_ECT_ENG_MIN_FLT |
                       SENS_ECT_ENG_MAX_FLT |
                       SENS_ECT_TRANSIENT_FLT);
    
    //ACT sensor
    
    //Read the sensor
    pax_adc_inpit(PIO_AIN_A19, &SENS_ACT_V, FALSE);
    
    //proc AI input
    put_process_analog_input(SENS_ACT_V,
                             0.320,
                             &SENS_ACT,
                             %SENS_ACT_RAW_MIN_FLT,
                             &SENS_ACT_RAW_MAX_FLT,
                             &SENS_ACT_SLEW_RATE_FLT,
                             &SENS_ACT_ENG_MIN_FLT,
                             &SENS_ACT_ENG_MAX_FLT,
                             &SENS_ACT_TRANSIENT_FLT,
                             &SENS_ACT_PROC_PAI_CAL,
                             &SENS_ACT_PROC_PAI_WORK);
    //Combine errors
    SENS_ACT_LIMPIN = (SENS_ACT_RAW_MIN_FLT |
                       SENS_ACT_RAW_MAX_FLT |
                       SENS_ACT_SLEW_RATE_FLT |
                       SENS_ACT_ENG_MIN_FLT |
                       SENS_ACT_ENG_MAX_FLT |
                       SENS_ACT_TRANSIENT_FLT);
    
}