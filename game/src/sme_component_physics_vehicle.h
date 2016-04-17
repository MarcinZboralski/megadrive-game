#ifndef _SME_COMPONENT_PHYSICS_VEHICLE_H_
#define _SME_COMPONENT_PHYSICS_VEHICLE_H_

#include "genesis.h"
#include "sme_entity.h"

void* smePHYSICS_VEHICLE_Create(smeEntity* entity);
void smePHYSICS_VEHICLE_Update(smeEntity* entity, void* component);

#endif
