/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: angular_g850.c 43639 2015-02-18 14:13:14Z cwartnaby $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/branches/integration-m670-rb2/examples/c_api/angular_demo/src/angular_g850.c $
 *  Description:    Implementation of the C-API 'angular' example, completed.
 *                  Taken from section 3 of the OpenECU C-API User Guide.
 *
 *  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 *
 *****************************************************************************
 */

/********* Includes *********/

#include "openecu.h"
#include "angular_g850_api.h"

/********* These macros can be changed *********/

/* This macro defines the number of cylinders in the engine */
#define ANG_NUM_CYLINDERS       4u

/********* These macros must not be changed *********/

/* None */

/********* Static Structure Definitions *********/

/* None */

/********* Static Prototypes *********/

/* None */

/********* Global Variable Instantiations *********/

/* Calibrateable engine parameters */

/* This array defines the the firing TDC angle for each cylinder.
 * The firing order defined by these default values is 1-3-4-2.
 * Range: [0, 720)
 */
OE_CAL F32  angm_tdc_angles[ANG_NUM_CYLINDERS] =
{
    90.0,
    630.0,
    270.0,
    450.0
};

/* This array defines the injector channel to use for each cylinder.
 * Cylinder 1 uses pin E52, cylinder 2 uses pin E35, and so on.
 */
OE_CAL PDX_LCHAN_T angm_injector_chs[ANG_NUM_CYLINDERS] =
{
    PIO_INJOT_E52,
    PIO_INJOT_E35,
    PIO_INJOT_E53,
    PIO_INJOT_E55
};

/* This array defines the coil channels to use.
 * The default values use two channels in a "wasted spark" mode.
 */
OE_CAL PDX_LCHAN_T angm_coil_chs[ANG_NUM_CYLINDERS / 2] =
{
    PIO_IGNOT_E17,
    PIO_IGNOT_E12,
};

/* This scalar defines the number of teeth on the toothed crankshaft
 * wheel, (including missing teeth).
 * Range: [36,60] teeth
 */
OE_CAL U8   angc_crank_teeth = 60U;

/* This scalar defines the number of missing teeth on the toothed
 * crankshaft wheel.
 * Range: [1, 2] teeth
 */
OE_CAL U8   angc_crank_missing = 2U;

/* This scalar specifies the angle in degrees relative to firing TDC
 * when the angular task for each cylinder should be executed
 * Range: [-360, 360]
 */
OE_CAL F32  angc_calculation_angle = -120.0;

/* This scalar specifies the start angle of the cam window
 * Range: [0, 720)
 */
OE_CAL F32  angc_cam_start_angle = 40.0;

/* This scalar specifies the end angle of the cam window
 * Range: [0, 720)
 */
OE_CAL F32  angc_cam_end_angle = 120.0;

/* This Boolean specifies that a camshaft wheel is fitted
 */
OE_CAL BOOL angc_cam_wheel_fitted = TRUE;

/* This scalar defines the angle at which to stop coil charge from
 * TDC firing of cylinder.
 * It is important to remember that with coil-related parameters,
 * a positive angle is before TDC firing.
 * Range: [-360, 360] degrees
 */
OE_CAL F32  angc_coil_off_angle = 20.0;

/* This scalar defines the angle at which to stop coil charge from
 * TDC firing of cylinder.
 * It is important to remember that with coil-related parameters,
 * a positive angle is before TDC firing.
 * Range: [-360, 360] degrees
 */
OE_CAL F32  angc_coil_on_angle = 30.0;

/* This scalar defines the injector dead-time (i.e., the duration
 * between starting the injector pulse to when fuel flows
 * from the injector).
 * Range: [0, 349.5] ms
 */
OE_CAL F32  angc_inj_deadtime = 0.5;

/* This scalar defines the duration of injection flow time
 * Range: [0, 349.5] ms
 */
OE_CAL F32  angc_inj_flowtime = 10.0;

/* This scalar defines the angle from TDC to turn the injector on.
 * It is important to remember that with injector-related parameters,
 * a positive angle is after TDC firing.
 * Range: [-360, 360] degrees
 */
OE_CAL F32  angc_inj_on_angle = 280.0;

/* This scalar defines the angle from TDC to turn the injector off.
 * It is important to remember that with injector-related parameters,
 * a positive angle is after TDC firing.
 * Range: [-360, 360] degrees
 */
OE_CAL F32  angc_inj_end_of_intake = 540.0;

/* This scalar defines the length of the initial fuel pulse
 * (flow time).
 * Range: [0, 500] ms
 */
OE_CAL F32  angc_initial_fuel_pulse_ft = 14.5;

/* This scalar defines the length of the initial fuel pulse
 * (dead time).
 * Range: [0, 500] ms
 */
OE_CAL F32  angc_initial_fuel_pulse_dt = 0.5;

/********* Static Variables *********/

/* These constants define the primary and secondary angular
 * sample channels.
 */
static const PAX_LCHAN_T ang_pri_channel = PIO_AIN_G1_E18;
static const PAX_LCHAN_T ang_sec_channel = PIO_AIN_G2_E19;

/* These arrays configure the primary and secondary angular
 * sample angles.
 */
static F32      ang_pri_angles[1] = { -140.0 };
static F32      ang_sec_angles[1] = { -140.0 };

/* This Boolean is TRUE if crankshaft movement is occuring and
 * FALSE otherwise.
 */
static BOOL     ang_crank_movement;

/* This Boolean is TRUE if crankshaft synchronisation has occured
 * and FALSE otherwise.
 */
static BOOL     ang_synced_with_crank;

/* This Boolean is TRUE if camshaft synchronisation has occured,
 * and FALSE otherwise.
 */
static BOOL     ang_synced_with_cam;

/* This Boolean is TRUE if crankshaft angle is valid (the software
 * has achieved synchronisation with the crank trigger wheel), FALSE
 * otherwise.
 */
static BOOL     ang_crank_angle_valid;

/* This is the current angle as decoded from the crank trigger wheel.
 * Use in conjunction with ang_crank_angle_valid.
 * Range: [0, 360) degrees
 */
static F32     ang_crank_angle;

/* This Boolean is TRUE if crankshaft angle is valid (the software
 * has achieved synchronisation with the crank trigger wheel), FALSE
 * otherwise.
 */
static BOOL     ang_engine_angle_valid;

/* This is the current engine angle as decoded from the crank and cam
 * trigger wheels. Use in conjunction with ang_engine_angle_valid.
 * Note that while only crank synchronisation has been achieved, the
 * angle continues to range between 0 and 720 degrees. When cam synchronisation
 * occurs, the angle may be adjusted by 360 degrees to account for the
 * engine cycle.
 * Range: [0, 720) degrees
 */
static F32     ang_engine_angle;

/* This scalar holds the engine speed calculated since the last TDC 720° ago.
 * If 720° has not passed, the populated value will be the same as
 * ang_engine_speed
 * Range: [0, 10000] RPM
 */
static F32      ang_avg_engine_speed;

/* This scalar holds the engine speed calculated since the last TDC event
 * occurred. If there has not been a previous TDC calculation event, then
 * a value of zero will be populated.
 * Range: [0, 10000] RPM
 */
static F32      ang_engine_speed;

/* This scalar holds the averaged primary angular sensor A/D counts taken
 * during each angular event.
 * Range: [0, 4096] A/D counts
 */
static S16      ang_pri_sensor_counts;

/* This scalar holds the averaged secondary angular sensor A/D counts taken
 * during each angular event.
 * Range: [0, 4096] A/D counts
 */
static S16      ang_sec_sensor_counts;

/*
 *****************************************************************************
 *  Purpose: Initialise the application. Called by the library between
 *           pre and post initialisation.
 *  Returns: None.
 *  Notes:   None.
 *****************************************************************************
 */
void psc_initialise_app
(
    void
)
{
    U8 cyl;

    /* Call the library to initialise the CAN ports. The example uses CCP to
     * communicate with a calibration tool, so the configuration must occur.
     * For this example, the return value from the function is ignored to keep
     * the code simple.
     */
    (void) pcx_config(PIO_CAN_C23_C11, PIO_CBAUD_500_KBPS);
    (void) pcx_config(PIO_CAN_T26_T14, PIO_CBAUD_500_KBPS);

    /* Configure the G850 to process the cam trigger wheel input as
     * a Hall effect (other options are default).
     */
    pcfg_setup_g850(PIO_CFG_HEGO_FILTER_160HZ,
                    PIO_CFG_TYPE_VRS_SINGLE_ENDED,
                    PIO_CFG_TYPE_VRS_SINGLE_ENDED,
                    PIO_CFG_TYPE_VRS_SINGLE_ENDED,
                    PIO_CFG_TYPE_HALL,
                    PIO_CFG_TYPE_VRS_SINGLE_ENDED,
                    PIO_CFG_HYST_302MV,
                    PIO_CFG_HYST_302MV,
                    PIO_CFG_HYST_302MV,
                    PIO_CFG_HYST_302MV,
                    PIO_CFG_HYST_302MV,
                    PIO_CFG_NOM_3A,
                    PIO_CFG_MAX_9_5A);

    /* Configure core engine parameters */
    (void) pan_config_engine(PIO_ENGINE_TYPE_GASOLINE_PORT_INJ,
                             PIO_ENGINE_CYCLE_TYPE_FOUR_STROKE,
                             ANG_NUM_CYLINDERS,
                             angm_tdc_angles,
                             angc_calculation_angle);

    /* Configure the CRANK wheel trigger source, always available */
    (void) pan_config_crank_wheel_mtg(PIO_CRIN_E47_E46,
                                      PIO_CRANK_WHEEL_PRIMARY,
                                      PIO_CRANK_WHEEL_SYNC_TMT,
                                      angc_crank_teeth,
                                      angc_crank_missing,
                                      TRUE,
                                      PIO_CRANK_TOOTH_EDGE_DEFAULT);

    /* Configure the CAM wheel trigger source, if required */
    if (angc_cam_wheel_fitted)
    {
        (void) pan_config_cam_wheel_st(PIO_CAIN_E45,
                                       PIO_CAM_WHEEL_PRIMARY,
                                       angc_cam_start_angle,
                                       angc_cam_end_angle);
    }

    /* Configure the injector channels to use */
    (void) pan_config_injectors(angm_injector_chs,
                                ANG_NUM_CYLINDERS,
                                PIO_INJECTOR_DRIVE_SATURATE,
                                FALSE);

    /* Configure the coil channels to use in wasted-spark mode
     * (thus only half the channels are specified).
     */
    (void) pan_config_sparks(angm_coil_chs,
                             ANG_NUM_CYLINDERS / 2,
                             PIO_SPARK_TYPE_WASTED_SPARK,
                             FALSE,
                             TRUE);

    /* Program initial fuel pulse */
    (void) pan_set_initial_injection_gpi(angc_initial_fuel_pulse_ft,
                                         angc_initial_fuel_pulse_dt);

    /* Configure primary angular sample channel */
    (void) pan_config_angular_ad_fxd(ang_pri_channel,
                                     PIO_AD_GROUP_1,
                                     1,
                                     ang_pri_angles);

    /* Configure secondary angular sample channel */
    (void) pan_config_angular_ad_fxd(ang_sec_channel,
                                     PIO_AD_GROUP_2,
                                     1,
                                     ang_sec_angles);

    /* Call the library to enable the output control switch. This enables
     * numerous output drivers, including the injector and coil output
     * drivers.
     */
    pss_set_safety_switch(TRUE);
}

/*
 *****************************************************************************
 *  Purpose: An application task to process various angular parameters.
 *           Called by the library every tdc for each cylinder.
 *  Returns: None.
 *  Notes:   None.
 *****************************************************************************
 */
void ang_task_angular
(
    void
)
{
    BOOL valid;    /* whether the API has provided valid data during a call,
                    * largely ignored in this example.
                    */
    U8   cylinder; /* the cylinder that triggered this task */

    /* get current cylinder */
    (void) pan_get_engine_cyl(&valid, &cylinder);

    /* primary counts */
    (void) pan_get_angular_ad_avg_fxd(PIO_AD_GROUP_1, &ang_pri_sensor_counts);

    /* secondary counts */
    (void) pan_get_angular_ad_avg_fxd(PIO_AD_GROUP_2, &ang_sec_sensor_counts);

    /* engine speed + avg engine speed */
    (void) pan_get_engine_speed_per_tooth(&ang_engine_speed);
    (void) pan_get_engine_speed_per_cyl(&ang_avg_engine_speed);

    /* set coil drive */
    (void) pan_set_spark(cylinder,
                         angc_coil_on_angle,
                         angc_coil_off_angle);

    /* set injector drive */
    (void) pan_set_injection_gpi(cylinder,
                                 angc_inj_on_angle,
                                 angc_inj_flowtime,
                                 angc_inj_deadtime,
                                 angc_inj_end_of_intake,
                                 0.5F);
}

/*
 *****************************************************************************
 *  Purpose: An application task to process various angular parameters.
 *           Called by the library every 10ms as defined by the interface file.
 *  Returns: None.
 *  Notes:   None.
 *****************************************************************************
 */
void ang_task_10ms
(
    void
)
{
    /* synced with cam */
    (void) pan_get_cam_wheel_sync(PIO_CAM_WHEEL_PRIMARY,
                                  &ang_synced_with_cam);

    /* synced with crank */
    (void) pan_get_crank_wheel_sync(PIO_CRANK_WHEEL_PRIMARY,
                                    &ang_synced_with_crank);

    /* crank moving */
    (void) pan_get_crank_wheel_movement(PIO_CRANK_WHEEL_PRIMARY,
                                        &ang_crank_movement);

    /* current crank angle */
    (void) pan_get_crank_wheel_angle(PIO_CRANK_WHEEL_PRIMARY,
                                     &ang_crank_angle_valid,
                                     &ang_crank_angle);

    /* current engine angle */
    (void) pan_get_engine_angle(&ang_engine_angle_valid,
                                &ang_engine_angle);
}

/*
 *****************************************************************************
 *  Purpose: Called by the library while the processor is not running
 *           any tasks. Can be used for background processing.
 *  Returns: None.
 *  Notes:   None.
 *****************************************************************************
 */
void psc_background_app
(
    void
)
{
    /* Nothing to do */
}
