#include "rte.h"
#include <stdio.h>

#define STATE_NORMAL    0
#define STATE_SAFE      1
#define STATE_RECOVERY  2

#define SPEED_TIMEOUT_TICKS     10u   // example: 50 * 10ms = 500ms
#define RECOVERY_OK_REQUIRED     3u   // need 3 good updates to recover
#define SAFE_SPEED_FALLBACK      0u   // safe speed value

uint16_t speed;
uint16_t age;
static uint16_t brakePressure;

static uint8_t myCounter = 0;

static uint8_t BrakeState = STATE_NORMAL;
static uint8_t RecoveryOkCount = 0;
static uint16_t LastValidSpeed = 0;



void Brake_ReadInputs_10ms(void)
{

    bool updated = Rte_Read_VehicleSpeed(&speed, &age);

    // --- STATE: NORMAL ---
    if (BrakeState == STATE_NORMAL)
    {
        if (age > SPEED_TIMEOUT_TICKS)
        {
            printf ("going to state safe /n");
            BrakeState = STATE_SAFE;
            RecoveryOkCount = 0;
        }
        else if (updated)
        {
            LastValidSpeed = speed;
        }
    }

    // --- STATE: SAFE ---
    else if (BrakeState == STATE_SAFE)
    {
        LastValidSpeed = SAFE_SPEED_FALLBACK;

        if (updated && (age <= SPEED_TIMEOUT_TICKS))
        {
            printf("going to state recovery");
            BrakeState = STATE_RECOVERY;
            RecoveryOkCount = 1;
        }
    }

    // --- STATE: RECOVERY ---
    else if (BrakeState == STATE_RECOVERY)
    {
        if (age > SPEED_TIMEOUT_TICKS)
        {
            printf ("going to safe state again"); 
            BrakeState = STATE_SAFE;
            RecoveryOkCount = 0;
        }
        else if (updated)
        {
            LastValidSpeed = speed;
            RecoveryOkCount++;

            if (RecoveryOkCount >= RECOVERY_OK_REQUIRED)
            {
                BrakeState = STATE_NORMAL;
                RecoveryOkCount = 0;
            }
        }
    }

    // default safety
    else
    {
        BrakeState = STATE_SAFE;
        RecoveryOkCount = 0;
        LastValidSpeed = SAFE_SPEED_FALLBACK;
    }
}

void Brake_ComputeAndTransmit_10ms(void)
{
    brakePressure = (uint16_t)(LastValidSpeed * 2u);
    printf("Speed=%u  BrakePressure=%u\n", LastValidSpeed, brakePressure);
}