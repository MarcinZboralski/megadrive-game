#include "sme_component_controller_pad_vehicle.h"
#include "sme_component_controller.h"
#include "sme_input.h"
#include "sme_camera.h"

void* smeCONTROLLER_PAD_VEHICLE_Create(smeEntity* entity)
{
    smeCAMERA_SetSmooth(intToFix32(10));
    return smeCONTROLLER_Create(entity, &smeCONTROLLER_PAD_VEHICLE_Update);
}

void smeCONTROLLER_PAD_VEHICLE_Update(smeEntity* entity, void* component)
{
    //smeController* controller = entity->Controller;
    smePhysics* physics = entity->Physics;
    
    fix32 acceleration = FIX32(0.015f);
    fix32 deceleration = FIX32(0.020f);
    fix32 maximum_forward_speed = FIX32(6.0f);
    fix32 maximum_backward_speed = FIX32(2.6f);
    
    if (smeINPUT_IsPressed(smeINPUT_UP)) physics->Velocity += acceleration;
    if (smeINPUT_IsPressed(smeINPUT_DOWN)) physics->Velocity -= acceleration;
    
    if (physics->Velocity!=0 && !smeINPUT_IsPressed(smeINPUT_UP) && !smeINPUT_IsPressed(smeINPUT_DOWN))
    {
        if (physics->Velocity>0) { physics->Velocity -= deceleration; if (physics->Velocity<0) physics->Velocity = 0; }
        else { physics->Velocity += deceleration; if (physics->Velocity>0) physics->Velocity = 0; }
    }
    
    if (physics->Velocity>maximum_forward_speed) physics->Velocity = maximum_forward_speed;
    if (physics->Velocity<-maximum_backward_speed) physics->Velocity = -maximum_backward_speed;
    
    fix32 speed = 0;
    if (physics->Velocity>0) speed = fix32Div(physics->Velocity, maximum_forward_speed);
    else speed = fix32Div(physics->Velocity, maximum_backward_speed);
    
    speed = fix32Div(speed, FIX32(14.0f));
    
    physics->Omega = 0;
    if (smeINPUT_IsPressed(smeINPUT_LEFT)) physics->Omega += speed;
    if (smeINPUT_IsPressed(smeINPUT_RIGHT)) physics->Omega -= speed;
}

