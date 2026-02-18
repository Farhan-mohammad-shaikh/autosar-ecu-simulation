#ifndef ENGINE_TYPE_H
#define ENGINE_TYPE_H

#include <stdint.h>

/* data */
typedef struct 
{
   uint16_t raw;
   uint16_t speed;
   uint16_t rpm; 
} EngineData;

#endif