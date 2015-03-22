//
// Andrew Palardy
// Engine drivers
//


#include "openecu.h"
#include "fsae_sw.h"
#include "engdrvs.h"

void ENGDRVS_Calc5MS()
{
    //Cam sync
    pan_get_cam_wheel_sync(PIO_CAM_WHEEL_PRIMARY,
                           &ENGDRVS_SYNC_WITH_CAM);
    //Crank sync
    pan_get_crank_wheel_sync(PIO_CRANK_WHEEL_PRIMARY,
                             &ENGDRVS_SYNC_WITH_CRANK);
    
    //Crank moving
    pan_get_crank_wheel_movement(PIO_CRANK_WHEEL_PRIMARY,
                                 &ENGDRVS_SYNC_MOVE);
    
    //Crank angle
    pan_get_crank_wheel_angle(PIO_CRANK_WHEEL_PRIMARY,
                              &ENGDRVS_SYNC_VALID_CRANK,
                              &ENGDRVS_SYNC_ANG_CRANK);
    
    //Engine angle
    pan_get_engine_angle(&ENGDRVS_SYNC_VALID_ENG,
                         &ENGDRVS_SYNC_ANG_ENG);
    
    //Update ENGINE_POSITION
    ENGINE_POSITION = ENGDRVS_SYNC_ANG_ENG;
}


//Angular task final
void ENGDRVS_CalcTDC2()
{
    //Set the engine actuators
    F32 active_inj;
    
    //Spark
    ENGDRVS_SPK_ANG = SPARK_ACTUAL_CYL1;
    ENGDRVS_SPK_DWELL = SPARK_DWELL;
    
    //Calculate angular dwell time
#error "Need to calculate angular dwell time"
    
    pan_set_spark(CURRENT_CYLINDER,
                  ENGDRVS_SPK_START_ANG,
                  ENGDRVS_SPK_ANG);
    
    //Fuel
    ENGDRVS_INJ_DEAD_TIME = INJ_DEAD_TIME;
    ENGDRVS_INJ1_TIME = INJ_PRIM_TIME;
    ENGDRVS_INJ2_TIME = INJ_SEC_TIME;
    ENGDRVS_INJ_FIRING_ANG = INJ_VIT_ANG;
    ENGDRVS_INJ_DROP_DEAD_ANG = INJ_DROP_DEAD_ANG;
    
    //Active injector
    active_inj = ENGDRVS_INJ1_TIME;
    if(CURRENT_CYLINDER == 1)
    {
        active_inj = ENGDRVS_INJ2_TIME;
    }
    
    pan_set_injection_gpi(CURRENT_CYLINDER,
                          ENGDRVS_INJ_FIRING_ANG,
                          active_inj,
                          ENGDRVS_INJ_DEAD_TIME,
                          ENGDRVS_INJ_DROP_DEAD_ANG,
                          0.5F);
    
}


//Angular task initial
void ENGDRVS_CalcTDC1()
{
    //Temp variable
    BOOL valid;
    
    //Get current cylinder
    pan_get_engine_cyl(&valid,&ENGDRVS_CUR_CYL);
    CURRENT_CYLINDER = ENGDRVS_CUR_CYL;
    
    //Read the ADC
    pan_get_angular_ad_avg_fxd(PIO_AD_GROUP_1,&ENGDRVS_SW_PRI_V);
    
    //Read RPM
    pan_get_engine_speed_per_tooth(&ENGDRVS_SPD);
    pan_get_engine_speed_per_cyl(ENGDRVS_SPD_AVG);
    RPM = ENGDRVS_SPD_AVG;
}

//Init for engine drivers
void ENGDRVS_Init()
{
    //Configure engine
    pan_config_engine(PIO_ENGINE_TYPE_GASOLINE_PORT_INJ,
                      PIO_ENGINE_CYCLE_TYPE_FOUR_STROKE,
                      2,
                      ENGDRVS_TDC_ANGLES,
                      ENGDRVS_SW_CALC_ANGLE);
    
    //Configure crank
    pan_config_crank_wheel_mtg(PIO_CRIN_A8_A9,
                               PIO_CRANK_WHEEL_PRIMARY,
                               PIO_CRANK_WHEEL_SYNC_TMT,
                               ENGDRVS_CRANK_TEETH,
                               ENGDRVS_CRANK_MISS_TEETH,
                               TRUE,
                               PIO_CRANK_TOOTH_EDGE_DEFAULT);
    
    //Configure cam
    //No cam!
    
    //Configure Injectors
    pan_config_injectors(ENGDRVS_INJ_CHANS,
                         2,
                         PIO_INJECTOR_DRIVE_SATURATE,
                         FALSE);
    
    //Configure Sparks
    pan_config_sparks(ENGDRVS_SPK_CHANS,
                      1,
                      PIO_SPARK_TYPE_WASTED_SPARK,
                      FALSE,
                      TRUE);
    
    //Primary AD channel
    pan_config_angular_ad_fxd(ENGDRVS_SW_PRI_CHAN,
                              PIO_AD_GROUP_1,
                              1,
                              ENGDRVS_SW_PRI_ANG);
}