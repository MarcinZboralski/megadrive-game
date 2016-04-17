#include "sme_component_controller_pad.h"
#include "sme_component_controller.h"
#include "sme_input.h"

void* smeCONTROLLER_PAD_Create(smeEntity* entity)
{
    return smeCONTROLLER_Create(entity, &smeCONTROLLER_PAD_Update);
}

void smeCONTROLLER_PAD_Update(smeEntity* entity, void* component)
{
    //smeController* controller = entity->Controller;
    smePhysics* physics = entity->Physics;
    
    physics->Velocity = 0;
    if (smeINPUT_IsPressed(smeINPUT_UP)) physics->Velocity += FIX32(1.1f);
    if (smeINPUT_IsPressed(smeINPUT_DOWN)) physics->Velocity -= FIX32(1.1f);
    
    physics->Omega = 0;
    if (smeINPUT_IsPressed(smeINPUT_LEFT)) physics->Omega += FIX32(0.1f);
    if (smeINPUT_IsPressed(smeINPUT_RIGHT)) physics->Omega -= FIX32(0.1f);
}

