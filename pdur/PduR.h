#ifndef PDUR_H
#define PDUR_H

#include <stdint.h>

typedef uint16_t PduIdType;
typedef uint16_t PduLengthType;

typedef struct {
    uint8_t*      SduDataPtr;   // pointer to payload bytes
    PduLengthType SduLength;    // payload length in bytes
}PduInfoType;

void PduR_ComTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

#endif