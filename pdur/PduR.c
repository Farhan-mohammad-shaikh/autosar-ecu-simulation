#include "PduR.h"
#include "../canif/CanIf.h"

void PduR_ComTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    CanIf_Transmit(TxPduId, PduInfoPtr);
}