#ifndef _SME_COMPONENT_CONTROLLER_DUMB_H_
#define _SME_COMPONENT_CONTROLLER_DUMB_H_

#include "genesis.h"
#include "sme_entity.h"

void* smeCONTROLLER_DUMB_Create(smeEntity* entity);
void smeCONTROLLER_DUMB_Update(smeEntity* entity, void* component);

#endif
