#include "sme_world.h"
#include "sme_camera.h"
#include "sme_component_transform.h"

smeMap* smeWorld_Map;
smeEntity* smeWorld_Entities[smeWORLD_MAXIMUM_ENTITY_COUNT];
int smeWorld_EntityCount;
int smeWorld_UpdateIndex;

void smeWORLD_Initialize()
{
    smeSPRITES_Initialize();

    smeWorld_Map = NULL;
    smeWorld_EntityCount = 0;
    smeWorld_UpdateIndex = 0;
}

void smeWORLD_Finalize()
{
    while (smeWorld_EntityCount>0)
        smeWORLD_DestroyEntity(smeWorld_Entities[smeWorld_EntityCount-1]);
   
    if (smeWorld_Map!=NULL)
        smeWORLD_UnloadMap();
    
    smeSPRITES_Finalize();
}

void smeWORLD_Update()
{
    if (smeWorld_Map!=NULL)
    {
        u8 i;
        for (i=0 ; i<smeWorld_EntityCount ; ++i)
            smeENTITY_Update(smeWorld_Entities[i]);
            
        /*
        smeENTITY_Update(smeWorld_Entities[0]);
    
        if (smeWorld_EntityCount>1)
        {
            u8 i;
            for (i=0 ; i<(smeWorld_EntityCount/4)+1 ; ++i)
            {
                ++smeWorld_UpdateIndex;
                smeWorld_UpdateIndex %= smeWorld_EntityCount-1;
                smeENTITY_Update(smeWorld_Entities[smeWorld_UpdateIndex+1]);
            }
        }*/
        
        smeCAMERA_Render();
        smeSPRITES_Render();
    }
}

smeMap* smeWORLD_GetMap()
{
    return smeWorld_Map;
}

void smeWORLD_LoadMap(smeMap* map)
{
    smeWorld_Map = map;
    smeMAP_Load(smeWorld_Map);
    smeCAMERA_Clear();
}

void smeWORLD_UnloadMap()
{
    smeMAP_Unload(smeWorld_Map);
    smeWorld_Map = NULL;
    smeCAMERA_Clear();
}

smeEntity* smeWORLD_CreateEntity()
{
    smeEntity* entity = smeENTITY_Create();
    entity->ID = smeWorld_EntityCount;
    smeWorld_Entities[smeWorld_EntityCount++] = entity;
    return entity;
}

void smeWORLD_DestroyEntity(smeEntity* entity)
{
    --smeWorld_EntityCount;
    int i;
    for (i=entity->ID ; i<smeWorld_EntityCount ; ++i)
    {
        smeWorld_Entities[i] = smeWorld_Entities[i+1];
        smeWorld_Entities[i]->ID = i;
    }
    smeENTITY_Destroy(entity);
}

smeEntity* smeWORLD_FindNearestEntity(fix32* distance, smeEntity* entity)
{
    smeEntity* nearest = NULL;
    *distance = FIX32(9999.0f);
    int i;
    for (i=0 ; i<smeWorld_EntityCount ; ++i)
    {
        if (entity->ID!=i)
        {
            float d = smeTRANSFORM_GetDistance(entity, smeWorld_Entities[i]);
            if (d<*distance)
            {
                nearest = smeWorld_Entities[i];
                *distance = d;
            }
        }
    }
    return nearest;
}
