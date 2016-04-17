#include "sme_component_transform.h"
#include "sme_maths.h"

void* smeTRANSFORM_Create(smeEntity* entity, fix32 position_x, fix32 position_y, fix32 rotation)
{
    void* component = smeENTITY_AddComponent(entity, &smeTRANSFORM_Destroy, NULL);
    smeENTITY_RegisterAttributes(entity, component, sizeof(smeTransform));
    smeTransform* transform = (smeTransform*)smeENTITY_GetAttributes(entity, component);
    transform->PositionX = position_x;
    transform->PositionY = position_y;
    transform->Rotation = rotation;
    entity->Transform = transform;
    return component;
}

void smeTRANSFORM_Destroy(smeEntity* entity, void* component)
{
    entity->Transform = NULL;
}

fix32 smeTRANSFORM_GetDistance(smeEntity* entity1, smeEntity* entity2)
{
    fix32 square_x = abs(entity1->Transform->PositionX-entity2->Transform->PositionX);
    fix32 square_y = abs(entity1->Transform->PositionY-entity2->Transform->PositionY);
    return square_x+square_y;
}
