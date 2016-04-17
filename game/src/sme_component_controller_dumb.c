#include "sme_component_controller_dumb.h"
#include "sme_component_controller.h"
#include "sme_input.h"

void* smeCONTROLLER_DUMB_Create(smeEntity* entity)
{
    return smeCONTROLLER_Create(entity, &smeCONTROLLER_DUMB_Update);
}

void smeCONTROLLER_DUMB_Update(smeEntity* entity, void* component)
{
    //smeController* controller = entity->Controller;
    smePhysics* physics = entity->Physics;
    
    physics->Velocity = fix32Div(intToFix32(random()%100), intToFix32(100));
    physics->Omega = random()/400-100;
}

