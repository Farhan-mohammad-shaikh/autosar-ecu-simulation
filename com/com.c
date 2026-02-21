#include "com.h"
#include "../pdur/PduR.h"

static uint8_t  Com_TxIpduBuf[8]; 
static uint16_t COM_IPDU_LEN = 8u;

uint16_t Speed_Buffer;
bool updated_flag;
uint16_t Speed_AgeTicks = 0;
static void EnterExclusiveArea(void) { /* simulate */ }
static void ExitExclusiveArea(void)  { /* simulate */ }

void Com_Init(void)
{
    EnterExclusiveArea();
    for (int i = 0; i < COM_IPDU_LEN; i++)
    {
        Com_TxIpduBuf[i] = 0u;
    }
    updated_flag = false;
    Speed_AgeTicks = 0;
    ExitExclusiveArea();

}

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
    Com_TxIpduBuf[0]= (uint8_t)(speed & 0xFF);
    Com_TxIpduBuf[1]= (uint8_t)((speed >> 8) & 0xFF);
    updated_flag = true;
    Speed_AgeTicks = 0;
    PduInfoType pdu;
    pdu.SduDataPtr = Com_TxIpduBuf;
    pdu.SduLength = COM_IPDU_LEN;
    ExitExclusiveArea();

    PduR_ComTransmit(0u, &pdu);
}
bool Com_ReceiveVehicleSpeed (uint16_t *speed, uint16_t *ageTicks)
{
    EnterExclusiveArea();
    uint16_t s = (uint16_t)Com_TxIpduBuf[0]
               | ((uint16_t)Com_TxIpduBuf[1] << 8);

    *speed    = s;
    bool was_updated = updated_flag;
    *ageTicks = Speed_AgeTicks;
    updated_flag = false; 
    ExitExclusiveArea();

    return was_updated;

}
