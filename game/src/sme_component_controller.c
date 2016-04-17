#include "sme_component_controller.h"

void* smeCONTROLLER_Create(smeEntity* entity, smeENTITY_FUNC_UPDATE)
{
    void* component = smeENTITY_AddComponent(entity, &smeCONTROLLER_Destroy, update);
    smeENTITY_RegisterAttributes(entity, component, sizeof(smeController));
    smeController* controller = (smeController*)smeENTITY_GetAttributes(entity, component);
    entity->Controller = controller;
    return component;
}

void smeCONTROLLER_Destroy(smeEntity* entity, void* component)
{
    entity->Controller = NULL;
}


