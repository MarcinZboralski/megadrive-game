#ifndef _SME_WORLD_H_
#define _SME_WORLD_H_

#include "genesis.h"
#include "sme_map.h"
#include "sme_entity.h"
#include "sme_sprite.h"

#define smeWORLD_MAXIMUM_ENTITY_COUNT   60

void smeWORLD_Initialize();
void smeWORLD_Finalize();
void smeWORLD_Update();

smeMap* smeWORLD_GetMap();
void smeWORLD_LoadMap(smeMap* map);
void smeWORLD_UnloadMap();

smeEntity* smeWORLD_CreateEntity();
void smeWORLD_DestroyEntity(smeEntity* entity);

smeEntity* smeWORLD_FindNearestEntity(fix32* distance, smeEntity* entity);

#endif
