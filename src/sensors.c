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
    pax_adc_input(PIO_AIN_A15, &SENS_ECT_V, FALSE);
    
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
    pax_adc_input(PIO_AIN_A10, &SENS_ACT_V, FALSE);
    
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

void SENS_Calc5MS()
{
    //TPS sensor
    
    //Read the sensor
    pax_adc_input(PIO_AIN_A13, &SENS_TPS_V, FALSE);
    
    //proc AI input
    put_process_analog_input(SENS_TPS_V,
                             0.05,
                             &SENS_TPS,
                             %SENS_TPS_RAW_MIN_FLT,
                             &SENS_TPS_RAW_MAX_FLT,
                             &SENS_TPS_SLEW_RATE_FLT,
                             &SENS_TPS_ENG_MIN_FLT,
                             &SENS_TPS_ENG_MAX_FLT,
                             &SENS_TPS_TRANSIENT_FLT,
                             &SENS_TPS_PROC_PAI_CAL,
                             &SENS_TPS_PROC_PAI_WORK);
    //Combine errors
    SENS_TPS_LIMPIN = (SENS_TPS_RAW_MIN_FLT |
                       SENS_TPS_RAW_MAX_FLT |
                       SENS_TPS_SLEW_RATE_FLT |
                       SENS_TPS_ENG_MIN_FLT |
                       SENS_TPS_ENG_MAX_FLT |
                       SENS_TPS_TRANSIENT_FLT);
    
    //PVS sensor
    
    //Read the sensor
    pax_adc_input(PIO_AIN_A12, &SENS_PVS_V, FALSE);
    
    //proc AI input
    put_process_analog_input(SENS_PVS_V,
                             0.05,
                             &SENS_PVS,
                             %SENS_PVS_RAW_MIN_FLT,
                             &SENS_PVS_RAW_MAX_FLT,
                             &SENS_PVS_SLEW_RATE_FLT,
                             &SENS_PVS_ENG_MIN_FLT,
                             &SENS_PVS_ENG_MAX_FLT,
                             &SENS_PVS_TRANSIENT_FLT,
                             &SENS_PVS_PROC_PAI_CAL,
                             &SENS_PVS_PROC_PAI_WORK);
    //Combine errors
    SENS_PVS_LIMPIN = (SENS_PVS_RAW_MIN_FLT |
                       SENS_PVS_RAW_MAX_FLT |
                       SENS_PVS_SLEW_RATE_FLT |
                       SENS_PVS_ENG_MIN_FLT |
                       SENS_PVS_ENG_MAX_FLT |
                       SENS_PVS_TRANSIENT_FLT);
    
    //MAP sensor
    
    //Read the sensor
    pax_adc_input(PIO_AIN_A3, &SENS_MAP_V, FALSE);
    
    //proc AI input
    put_process_analog_input(SENS_MAP_V,
                             0.05,
                             &SENS_MAP,
                             %SENS_MAP_RAW_MIN_FLT,
                             &SENS_MAP_RAW_MAX_FLT,
                             &SENS_MAP_SLEW_RATE_FLT,
                             &SENS_MAP_ENG_MIN_FLT,
                             &SENS_MAP_ENG_MAX_FLT,
                             &SENS_MAP_TRANSIENT_FLT,
                             &SENS_MAP_PROC_PAI_CAL,
                             &SENS_MAP_PROC_PAI_WORK);
    //Combine errors
    SENS_MAP_LIMPIN = (SENS_MAP_RAW_MIN_FLT |
                       SENS_MAP_RAW_MAX_FLT |
                       SENS_MAP_SLEW_RATE_FLT |
                       SENS_MAP_ENG_MIN_FLT |
                       SENS_MAP_ENG_MAX_FLT |
                       SENS_MAP_TRANSIENT_FLT);

}

//Angular task
void SENS_CalcTDC()
{
    //Need to process this
}

//Init for sensors
void SENS_Init()
{
    //ECT sensor
    pax_adc_input(PIO_AIN_A15,&SENS_ECT_V,TRUE);
    put_process_analog_input_init(&SENS_ECT_PROC_PAI_WORK);
    //ACT sensor
    pax_adc_input(PIO_AIN_A10,&SENS_ACT_V,TRUE);
    put_process_analog_input_init(&SENS_ACT_PROC_PAI_WORK);
    //TPS sensor
    pax_adc_input(PIO_AIN_A13,&SENS_TPS_V,TRUE);
    put_process_analog_input_init(&SENS_TPS_PROC_PAI_WORK);
    //PVS sensor
    pax_adc_input(PIO_AIN_A12,&SENS_PVS_V,TRUE);
    put_process_analog_input_init(&SENS_PVS_PROC_PAI_WORK);
    //MAP sensor
    pax_adc_input(PIO_AIN_A3,&SENS_MAP_V,TRUE);
    put_process_analog_input_init(&SENS_MAP_PROC_PAI_WORK);
    
    //Configure MAP angle sampling
    /*pan_config_angular_ad_fxd(ang_pri_channel,
                              PIO_AD_GROUP_1,
                              1,
                              ang_pri_angles);
    */
}