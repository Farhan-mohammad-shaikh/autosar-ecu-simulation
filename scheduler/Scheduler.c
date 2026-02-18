#include <stdint.h>

/* function pointer type */
typedef void (*Runnable)(void);

/* runnables */
void Engine_ReadSensor_1ms(void);
void Engine_Compute_10ms(void);
void Engine_Transmit_10ms(void);

void Brake_ReadInputs_10ms(void);
void Brake_ComputeAndTransmit_10ms(void);
void Com_MainFunction_10ms(void);

/* tables */
static Runnable runnables_1ms[] = {
    Engine_ReadSensor_1ms
};

static Runnable runnables_10ms[] = {
    Engine_Compute_10ms,
    Com_MainFunction_10ms,
    Engine_Transmit_10ms,
    Brake_ReadInputs_10ms,
    Brake_ComputeAndTransmit_10ms
};

static void run_table(Runnable *table, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        table[i]();
}

void Scheduler_Run(uint32_t total_ticks)
{
    for (uint32_t tick = 1; tick <= total_ticks; tick++)
    {
        run_table(runnables_1ms, sizeof(runnables_1ms)/sizeof(runnables_1ms[0]));

        if ((tick % 10u) == 0u)
        {
            run_table(runnables_10ms, sizeof(runnables_10ms)/sizeof(runnables_10ms[0]));
        }
    }
}
