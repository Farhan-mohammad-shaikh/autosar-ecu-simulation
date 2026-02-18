#ifndef RTE_H
#define RTE_H

#include <stdint.h>
#include "engine_type.h"
#include <stdbool.h>

void Rte_Write_VehicleSpeed (uint16_t speed);
bool Rte_Read_VehicleSpeed (uint16_t *speed, uint16_t *SpeedTicks);

#endif