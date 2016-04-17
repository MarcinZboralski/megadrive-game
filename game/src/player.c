#include "player.h"
#include "resources.h"

void TAKE_VEHICLES_BEHAVIOUR_Update(smeEntity* entity, void* component);

void SpawnZombie(int x, int y)
{
    smeEntity* zombie = smeWORLD_CreateEntity();
    smeTRANSFORM_Create(zombie, intToFix32(x), intToFix32(y), 0);
    smeGRAPHICS_Create(zombie, &man, 16, 16, PAL2);
    smePHYSICS_HUMAN_Create(zombie);
    smeCONTROLLER_DUMB_Create(zombie);
}

void PLAYER_Create()
{
    VDP_setPalette(PAL2, man.palette->data);
    VDP_setPalette(PAL3, truck.palette->data);

    smeEntity* player = smeWORLD_CreateEntity();
    smeTRANSFORM_Create(player, FIX32(800.0f), FIX32(800.0f), 0);
    smeGRAPHICS_Create(player, &man, 16, 16, PAL2);
    smePHYSICS_HUMAN_Create(player);
    smeCONTROLLER_PAD_HUMAN_Create(player);
    smeENTITY_AddComponent(player, NULL, &TAKE_VEHICLES_BEHAVIOUR_Update);
    
    smeCAMERA_Attach(player);
        
    smeEntity* car = smeWORLD_CreateEntity();
    smeTRANSFORM_Create(car, FIX32(915.0f), FIX32(850.0f), PI*3.0f/4.0f);
    smeGRAPHICS_Create(car, &truck, 32, 32, PAL3);
    smePHYSICS_VEHICLE_Create(car);
        
    //int i;
    //for (i=0 ; i<30 ; ++i)
    //    SpawnZombie(700+random()%200, 700+random()%200);
}

void TAKE_VEHICLES_BEHAVIOUR_Update(smeEntity* entity, void* component)
{
    if (smeINPUT_IsJustPressed(smeINPUT_A))
    {
        if (entity->Graphics->Sprite->Source==&man)
        {
            fix32 distance;
            smeEntity* target = smeWORLD_FindNearestEntity(&distance, entity);
            if (distance<FIX32(30.0f) && target->Graphics->Sprite->Source==&truck)
            {
                entity->Transform->PositionX = target->Transform->PositionX;
                entity->Transform->PositionY = target->Transform->PositionY;
                entity->Transform->Rotation = target->Transform->Rotation;
                
                smeENTITY_RemoveComponent(entity, entity->Physics);
				smeENTITY_RemoveComponent(entity, entity->Controller);
				smeENTITY_RemoveComponent(entity, entity->Graphics);

                smePHYSICS_VEHICLE_Create(entity);
                smeCONTROLLER_PAD_VEHICLE_Create(entity);
                smeGRAPHICS_Create(entity, target->Graphics->Sprite->Source, target->Graphics->Width, target->Graphics->Height, PAL3);
                
				smeWORLD_DestroyEntity(target);
				//smeENTITY_RemoveComponent(target, target->Graphics);
            }
        }
        else
        {
            smeEntity* car = smeWORLD_CreateEntity();
            smeTRANSFORM_Create(car, entity->Transform->PositionX, entity->Transform->PositionY, entity->Transform->Rotation);
            smeGRAPHICS_Create(car, entity->Graphics->Sprite->Source, entity->Graphics->Width, entity->Graphics->Height, PAL3);
            smePHYSICS_VEHICLE_Create(car);
            
            smeENTITY_RemoveComponent(entity, entity->Physics);
			smeENTITY_RemoveComponent(entity, entity->Controller);
			smeENTITY_RemoveComponent(entity, entity->Graphics);

			smePHYSICS_HUMAN_Create(entity);
            smeCONTROLLER_PAD_HUMAN_Create(entity);
            smeGRAPHICS_Create(entity, &man, 16, 16, PAL2);
        }
    }
}

