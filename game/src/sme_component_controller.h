#ifndef _SME_COMPONENT_CONTROLLER_H_
#define _SME_COMPONENT_CONTROLLER_H_

#include "genesis.h"
#include "sme_entity.h"

void* smeCONTROLLER_Create(smeEntity* entity, smeENTITY_FUNC_UPDATE);
void smeCONTROLLER_Destroy(smeEntity* entity, void* component);
void smeCONTROLLER_Update(smeEntity* entity, void* component);

#endif
