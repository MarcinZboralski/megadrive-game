#ifndef _SME_COMPONENT_H_
#define _SME_COMPONENT_H_

#include "genesis.h"
#include "sme_entity.h"

typedef struct
{
    u16 ID;
    u16 AttributesID;
    u16 AttributesSize;
    void (*Destroy)(smeEntity* entity, void* component);
    void (*Update)(smeEntity* entity, void* component);
} smeComponent;

#endif
