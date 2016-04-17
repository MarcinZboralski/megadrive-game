#ifndef _SME_ENTITY_H_
#define _SME_ENTITY_H_

#include "genesis.h"
#include "sme_component_base.h"

#define smeENTITY_FUNC_DESTROY      void (*destroy)(smeEntity*, void* component)
#define smeENTITY_FUNC_UPDATE       void (*update)(smeEntity*, void* component)

typedef struct
{
    u16 ID;
    void** Components;
    u8 ComponentCount;
    void* Attributes;
    u16 AttributesSize;
    smeTransform* Transform;
    smeGraphics* Graphics;
    smePhysics* Physics;
    smeController* Controller;
} smeEntity;

smeEntity* smeENTITY_Create();
void smeENTITY_Destroy(smeEntity* entity);
void smeENTITY_Update(smeEntity* entity);

void* smeENTITY_AddComponent(smeEntity* entity, smeENTITY_FUNC_DESTROY, smeENTITY_FUNC_UPDATE);
void smeENTITY_RemoveComponent(smeEntity* entity, void* component);

void* smeENTITY_GetAttributes(smeEntity* entity, void* component);
void* smeENTITY_RegisterAttributes(smeEntity* entity, void* component, u16 size);

#endif
