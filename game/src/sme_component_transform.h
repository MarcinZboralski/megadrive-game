#ifndef _SME_COMPONENT_TRANSFORM_H_
#define _SME_COMPONENT_TRANSFORM_H_

#include "genesis.h"
#include "sme_entity.h"

void* smeTRANSFORM_Create(smeEntity* entity, fix32 position_x, fix32 position_y, fix32 rotation);
void smeTRANSFORM_Destroy(smeEntity* entity, void* component);

fix32 smeTRANSFORM_GetDistance(smeEntity* entity1, smeEntity* entity2);

#endif
