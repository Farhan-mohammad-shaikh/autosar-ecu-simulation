#include "CanIf.h"
#include <stdio.h>

static uint32_t CanIf_GetCanIdFromPduId(PduIdType pduId)
{
    // In real AUTOSAR, CAN ID comes from CanIf configuration
    // Here, we just map one PDU to one CAN ID for demo
    (void)pduId;
    return 0x123u;
}

void CanIf_Transmit(PduIdType CanIfTxPduId, const PduInfoType* PduInfoPtr)
{
    uint32_t canId = CanIf_GetCanIdFromPduId(CanIfTxPduId);

    printf("[CanIf] CAN-ID=0x%03X DLC=%u Data=",
           (unsigned)canId, (unsigned)PduInfoPtr->SduLength);

    for (PduLengthType i = 0; i < PduInfoPtr->SduLength; i++) {
        printf("%02X ", PduInfoPtr->SduDataPtr[i]);
    }
    printf("\n");
}