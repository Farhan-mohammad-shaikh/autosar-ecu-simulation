#include "rte.h"
#include "engine_type.h"

EngineData enginestate;
uint8_t i = 0;

void Engine_ReadSensor_1ms(void){

    enginestate.raw++;
}

void Engine_Compute_10ms(void){

    enginestate.speed = enginestate.raw;
    enginestate.rpm = enginestate.raw * 10u;
}

void Engine_Transmit_10ms(void){
    
    i++;
    if (i < 7)
    {Rte_Write_VehicleSpeed(enginestate.speed);}

    
}