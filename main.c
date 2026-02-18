#include <stdint.h>

/* scheduler */
void Scheduler_Run(uint32_t total_ticks);

int main(void)
{
    Scheduler_Run(6000);  // simulate 100ms
    return 0;
}