//
// Andrew Palardy
// Spark
//


#include "openecu.h"
#include "fsae_sw.h"
#include "spark.h"
#include "epm.h"
#include "gasflows.h"
#include "com_idx.h"

void Spark_Calc40MS()
{
    //Calculate dwell at 40ms
    put_cal_map_1d_f32((F32)SENS_VBatt,
                       17,
                       IDX_VBatt,
                       SPK_DWELL_Tbl,
                       &SPK_DWELL);
    
    if(DIAL_SPK_DWELL_Sel)
    {
        SPK_DWELL = DIAL_SPK_DWELL;
    }
}


//Angular task
void Spark_CalcTDC()
{
    //Spark Mode
    if(ETRQ_Open_Pdl_Req && ETRQ_ENG_MODE >= 2)
    {
        put_cal_map_2d_f32((F32)RPM,
                       GF_Charge,
                       17,
                       17,
                       IDX_RPM,
                       IDX_Charge,
                       SPK_ADV_PowerOn_Surf,
                       &SPK_ADV_Base);
    }
    else if(ETRQ_ENG_MODE >= 2);
    {
        put_cal_map_2d_f32((F32)RPM,
                       GF_Charge,
                       17,
                       17,
                       IDX_RPM,
                       IDX_Charge,
                       SPK_ADV_PowerOff_Surf,
                       &SPK_ADV_Base);
    }
    else
    {
        //Not in run mode, must be in crank mode
        put_cal_map_1d_f32(SENS_ECT,
                            17,
                            IDX_ECT,
                            SPK_ADV_Start_Tbl,
                            &SPK_ADV_Base);
    }
    
    //Set final spark to base spark
    SPK_ADV = SPK_ADV_Base;
    
    //Dial override for spark
    if(DIAL_SPK_ADV_Sel)
    {
        SPK_ADV = DIAL_SPK_ADV;
    }
    
}

//Init for engine drivers
void Spark_Init()
{
    //Set start spark based on ECT
    //Not in run mode, must be in crank mode
    put_cal_map_1d_f32(SENS_ECT,
                        17,
                        IDX_ECT,
                        SPK_ADV_Start_Tbl,
                        &SPK_ADV);
                       
    //Calculate dwell (run a 40ms iteration)
    Spark_Calc40MS();
                       
}