#include "sme_component_controller_pad_human.h"
#include "sme_component_controller.h"
#include "sme_input.h"
#include "sme_maths.h"
#include "sme_camera.h"

void* smeCONTROLLER_PAD_HUMAN_Create(smeEntity* entity)
{
    smeCAMERA_SetSmooth(intToFix32(30));
    return smeCONTROLLER_Create(entity, &smeCONTROLLER_PAD_HUMAN_Update);
}

void smeCONTROLLER_PAD_HUMAN_Update(smeEntity* entity, void* component)
{
    //smeController* controller = entity->Controller;
    smePhysics* physics = entity->Physics;
    smeTransform* transform = entity->Transform;
    
    s8 move_x = 0;
    s8 move_y = 0;

    if (smeINPUT_IsPressed(smeINPUT_UP)) ++move_y;
    if (smeINPUT_IsPressed(smeINPUT_DOWN)) --move_y;
    if (smeINPUT_IsPressed(smeINPUT_LEFT)) --move_x;
    if (smeINPUT_IsPressed(smeINPUT_RIGHT)) ++move_x;

    physics->Velocity = 0;
    
    if (move_x==0 && move_y==0)
    {
        physics->Velocity = 0;
    }
    else
    {
        fix32 angle = 0;
        if (move_x==1 && move_y==0) angle = 0;
        else if (move_x==1 && move_y==1) angle = fPIo4;
        else if (move_x==0 && move_y==1) angle = fPIo2;
        else if (move_x==-1 && move_y==1) angle = fPI34;
        else if (move_x==-1 && move_y==0) angle = fPI;
        else if (move_x==-1 && move_y==-1) angle = -fPI34;
        else if (move_x==0 && move_y==-1) angle = -fPIo2;
        else if (move_x==1 && move_y==-1) angle = fPI74;

        transform->Rotation = clamp_angle(angle);
        physics->Velocity = FIX32(1.8f);
    }
}

