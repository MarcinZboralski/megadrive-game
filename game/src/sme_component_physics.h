#ifndef _SME_COMPONENT_PHYSICS_H_
#define _SME_COMPONENT_PHYSICS_H_

#include "genesis.h"
#include "sme_entity.h"

void* smePHYSICS_Create(smeEntity* entity, smeENTITY_FUNC_UPDATE);
void smePHYSICS_Destroy(smeEntity* entity, void* component);

void smePHYSICS_Reflect(smeEntity* entity, fix32* position_x, fix32* position_y, fix32 velocity_x, fix32 velocity_y, fix32 normal);

#endif
