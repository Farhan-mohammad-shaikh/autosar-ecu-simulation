#include "com.h"

uint16_t Speed_Buffer;
bool updated_flag;
uint16_t Speed_AgeTicks = 0;
static void EnterExclusiveArea(void) { /* simulate */ }
static void ExitExclusiveArea(void)  { /* simulate */ }

void Com_MainFunction_10ms(void)
{
    EnterExclusiveArea();
    if (Speed_AgeTicks < 0xFFFFu)
    {
        Speed_AgeTicks++;
    }
    ExitExclusiveArea();
}

void Com_SendVehicleSpeed (uint16_t speed)
{
    EnterExclusiveArea();
    Speed_Buffer = speed;
    updated_flag = true;
    Speed_AgeTicks = 0;
    ExitExclusiveArea();
}
bool Com_ReceiveVehicleSpeed (uint16_t *speed, uint16_t *ageTicks)
{
    EnterExclusiveArea();
    *speed = Speed_Buffer;
    bool was_updated = updated_flag;
    *ageTicks = Speed_AgeTicks;
    updated_flag = false; 
    ExitExclusiveArea();

    return was_updated;

}