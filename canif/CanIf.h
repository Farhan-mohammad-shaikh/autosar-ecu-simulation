#ifndef CANIF_H
#define CANIF_H

#include <stdint.h>
#include "../pdur/PduR.h"

void CanIf_Transmit(PduIdType CanIfTxPduId, const PduInfoType* PduInfoPtr);

#endif