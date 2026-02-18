#include "rte.h"
#include "com.h"


static void EnterExclusiveArea(void) { /* simulate */ }
static void ExitExclusiveArea(void)  { /* simulate */ }

void Rte_Write_VehicleSpeed (uint16_t speed)
{
    Com_SendVehicleSpeed(speed);
}


bool Rte_Read_VehicleSpeed (uint16_t *speed, uint16_t *SpeedTicks)
{
    return Com_ReceiveVehicleSpeed(speed,SpeedTicks);
}