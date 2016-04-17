#include "sme_component_physics.h"
#include "sme_component_transform.h"
#include "sme_world.h"
#include "sme_time.h"
#include "sme_maths.h"

void* smePHYSICS_Create(smeEntity* entity, smeENTITY_FUNC_UPDATE)
{
    void* component = smeENTITY_AddComponent(entity, &smePHYSICS_Destroy, update);
    smeENTITY_RegisterAttributes(entity, component, sizeof(smePhysics));
    smePhysics* physics = (smePhysics*)smeENTITY_GetAttributes(entity, component);
    physics->Velocity = 0;
    physics->Omega = 0;
    physics->Plane = 0;
    physics->Switch = 0;
    entity->Physics = physics;
    return component;
}

void smePHYSICS_Destroy(smeEntity* entity, void* component)
{
    entity->Physics = NULL;
}

void smePHYSICS_Reflect(smeEntity* entity, fix32* position_x, fix32* position_y, fix32 velocity_x, fix32 velocity_y, fix32 normal)
{
    fix32 nx = cos(normal);
    fix32 ny = sin(normal);
    fix32 dot = fix32Mul(velocity_x, nx)+fix32Mul(velocity_y, ny);
    velocity_x -= fix32Mul(fix32Mul(dot, nx), intToFix32(2));
    velocity_y -= fix32Mul(fix32Mul(dot, ny), intToFix32(2));
    *position_x = entity->Transform->PositionX+fix32Mul(fix32Mul(velocity_x, intToFix32(2)), sme_DeltaTime);
    *position_y = entity->Transform->PositionY+fix32Mul(fix32Mul(velocity_y, intToFix32(2)), sme_DeltaTime); 
}

