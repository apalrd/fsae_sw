//
// Andrew Palardy
// Spark
//


#include "openecu.h"
#include "fsae_sw.h"
#include "spark.h"

void SPK_Calc40MS()
{
    //Calculate dwell at 40ms
    
}


//Angular task
void SPK_CalcTDC()
{
    //Power On vs Power Off base spark
    if(POWER ON SPARK)
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
    else
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
    
    //Set final spark to base spark
    SPK_ADV = SPK_ADV_Base;
    
    //Dial override for spark
    if(DIAL_SPK_ADV_Sel)
    {
        SPK_ADV = DIAL_SPK_ADV;
    }
    
}

//Init for engine drivers
void EPM_Init()
{
    //Set start spark based on ECT
}