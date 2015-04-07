//
// Andrew Palardy
// Engine drivers
//


#include "openecu.h"
#include "fsae_sw.h"
#include "epm.h"
#include "spark.h"
#include "gasflows.h"
#include "sensors.h"
#include "fuel.h"

//5MS task
void Task_5MS()
{
    //Sensors
    Sensors_Calc5MS();
    //EPM
    EPM_Calc5MS();
}

//10MS task
void Task_10MS()
{
    //Gas Flows
    GF_Calc10MS();
}

//TDC task
void Task_TDC()
{
    //EPM initial
    EPM_CalcTDC1();
    
    //Gas Flows
    GF_CalcTDC();
    
    //Spark
    Spark_CalcTDC();
    
    //Fuel
    
    //EPM final
    EPM_CalcTDC2();
    
}

//320MS task

void Task_320MS()
{
    //Sensors
    Sensors_Calc320MS();
    
    //Gas Flows
    GF_Calc320MS();
}

//40MS task
void Task_40MS()
{
    //Spark
    Spark_Calc40MS();
}

//Init
void psc_initialize_app()
{
    //EPM
    EPM_Init();
    //Sensors
    Sensors_Init();
    //Gas Flows
    GF_Init();
    //Spark
    Spark_Init();
    //fuel
  
}

//Background
void psc_background_app()
{
    return;
}