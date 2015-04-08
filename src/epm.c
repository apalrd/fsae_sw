//
// Andrew Palardy
// Engine drivers
//


#include "openecu.h"
#include "fsae_sw.h"
#include "epm.h"
#include "spark.h"

void EPM_Calc5MS()
{
    //Cam sync
    pan_get_cam_wheel_sync(PIO_CAM_WHEEL_PRIMARY,
                           &EPM_SYNC_WITH_CAM);
    //Crank sync
    pan_get_crank_wheel_sync(PIO_CRANK_WHEEL_PRIMARY,
                             &EPM_SYNC_WITH_CRANK);
    
    //Crank moving
    pan_get_crank_wheel_movement(PIO_CRANK_WHEEL_PRIMARY,
                                 &EPM_SYNC_MOVE);
    
    //Crank angle
    pan_get_crank_wheel_angle(PIO_CRANK_WHEEL_PRIMARY,
                              &EPM_SYNC_VALID_CRANK,
                              &EPM_SYNC_ANG_CRANK);
    
    //Engine angle
    pan_get_engine_angle(&EPM_SYNC_VALID_ENG,
                         &EPM_SYNC_ANG_ENG);
    
    //Update ENGINE_POSITION
    ENGINE_POSITION = EPM_SYNC_ANG_ENG;
}


//Angular task final
void EPM_CalcTDC2()
{
    //Set the engine actuators
    F32 active_inj;
    
    //Spark
    EPM_SPK_ANG = SPK_ADV;
    EPM_SPK_DWELL = SPK_DWELL;
    
    //Calculate angular dwell time
#error "Need to calculate angular dwell time"
    
    pan_set_spark(CURRENT_CYLINDER,
                  EPM_SPK_START_ANG,
                  EPM_SPK_ANG);
    
    //Fuel
    EPM_INJ_DEAD_TIME = FUEL_PW_Dead;
    EPM_INJ1_TIME = FUEL_PW_Prim;
    EPM_INJ2_TIME = FUEL_PW_Sec;
    EPM_INJ_FIRING_ANG = FUEL_VIT_Ang;
    EPM_INJ_DROP_DEAD_ANG = FUEL_DropDead_Ang;
    
    //Active injector
    active_inj = EPM_INJ1_TIME;
    if(CURRENT_CYLINDER == 1)
    {
        active_inj = EPM_INJ2_TIME;
    }
    
    pan_set_injection_gpi(CURRENT_CYLINDER,
                          EPM_INJ_FIRING_ANG,
                          active_inj,
                          EPM_INJ_DEAD_TIME,
                          EPM_INJ_DROP_DEAD_ANG,
                          0.5F);
    
}


//Angular task initial
void EPM_CalcTDC1()
{
    //Temp variable
    BOOL valid;
    
    //Get current cylinder
    pan_get_engine_cyl(&valid,&EPM_CUR_CYL);
    CURRENT_CYLINDER = EPM_CUR_CYL;
    
    //Read the ADC
    pan_get_angular_ad_avg_fxd(PIO_AD_GROUP_1,&EPM_SW_PRI_V);
    
    //Read RPM
    pan_get_engine_speed_per_tooth(&EPM_SPD);
    pan_get_engine_speed_per_cyl(EPM_SPD_AVG);
    RPM = EPM_SPD_AVG;
}

//Init for engine drivers
void EPM_Init()
{
    //Configure engine
    pan_config_engine(PIO_ENGINE_TYPE_GASOLINE_PORT_INJ,
                      PIO_ENGINE_CYCLE_TYPE_FOUR_STROKE,
                      2,
                      EPM_TDC_ANGLES,
                      EPM_SW_CALC_ANGLE);
    
    //Configure crank
    pan_config_crank_wheel_mtg(PIO_CRIN_A8_A9,
                               PIO_CRANK_WHEEL_PRIMARY,
                               PIO_CRANK_WHEEL_SYNC_TMT,
                               EPM_CRANK_TEETH,
                               EPM_CRANK_MISS_TEETH,
                               TRUE,
                               PIO_CRANK_TOOTH_EDGE_DEFAULT);
    
    //Configure cam
    //No cam!
    
    //Configure Injectors
    pan_config_injectors(EPM_INJ_CHANS,
                         2,
                         PIO_INJECTOR_DRIVE_SATURATE,
                         FALSE);
    
    //Configure Sparks
    pan_config_sparks(EPM_SPK_CHANS,
                      1,
                      PIO_SPARK_TYPE_WASTED_SPARK,
                      FALSE,
                      TRUE);
    
    //Primary AD channel
    pan_config_angular_ad_fxd(EPM_SW_PRI_CHAN,
                              PIO_AD_GROUP_1,
                              1,
                              EPM_SW_PRI_ANG);
}