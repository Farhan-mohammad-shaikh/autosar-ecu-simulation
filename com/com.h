#ifndef COM_H
#define COM_H

#include <stdint.h>
#include "engine_type.h"
#include <stdbool.h>

void Com_SendVehicleSpeed (uint16_t speed);
bool Com_ReceiveVehicleSpeed (uint16_t *speed, uint16_t *ageTicks);

#endif