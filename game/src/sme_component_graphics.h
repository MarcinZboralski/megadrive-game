#ifndef _SME_COMPONENT_GRAPHICS_H_
#define _SME_COMPONENT_GRAPHICS_H_

#include "genesis.h"
#include "sme_entity.h"

void* smeGRAPHICS_Create(smeEntity* entity, const SpriteDefinition* sprite_source, u8 width, u8 height, u8 palette);
void smeGRAPHICS_Destroy(smeEntity* entity, void* component);
void smeGRAPHICS_Update(smeEntity* entity, void* component);

#endif
