#include "sme_component_physics.h"
#include "sme_component_physics_human.h"
#include "sme_component_transform.h"
#include "sme_world.h"
#include "sme_time.h"
#include "sme_maths.h"

void* smePHYSICS_HUMAN_Create(smeEntity* entity)
{
    return smePHYSICS_Create(entity, &smePHYSICS_HUMAN_Update);
}

void smePHYSICS_HUMAN_Update(smeEntity* entity, void* component)
{
    smePhysics* physics = entity->Physics;
    smeTransform* transform = entity->Transform;
    smeGraphics* graphics = entity->Graphics;
        
    fix32 velocity_x = fix32Mul(cos(transform->Rotation), physics->Velocity);
    fix32 velocity_y = -fix32Mul(sin(transform->Rotation), physics->Velocity);
    
    fix32 position_x = transform->PositionX+fix32Mul(velocity_x, sme_DeltaTime);
    fix32 position_y = transform->PositionY+fix32Mul(velocity_y, sme_DeltaTime);
    int iposition_x = fix32ToInt(position_x);
    int iposition_y = fix32ToInt(position_y);
    
    u8 solid = smeMAP_SOLID_Block;
    fix32 normal;
    if (physics->Switch)
    {
        smeMAP_GetSolidInfo(&solid, &normal, smeWORLD_GetMap(), smeWORLD_GetMap()->PlaneB, iposition_x, iposition_y);
        
        if (solid==smeMAP_SOLID_Block)
        {
            fix32 px = position_x;
            fix32 py = position_y;
            smePHYSICS_Reflect(entity, &px, &py, velocity_x, velocity_y, normal);
            iposition_x = fix32ToInt(px);
            iposition_y = fix32ToInt(py);
            smeMAP_GetSolidInfo(&solid, &normal, smeWORLD_GetMap(), smeWORLD_GetMap()->PlaneB, iposition_x, iposition_y);
            
            if (solid!=smeMAP_SOLID_Empty)
            {
                iposition_x = fix32ToInt(position_x);
                iposition_y = fix32ToInt(position_y);
            }
            else
            {
                position_x = px;
                position_y = py;
            }
        }

        if (solid==smeMAP_SOLID_Empty)
        {
            physics->Plane = 1;
            
            if (graphics!=NULL)
                graphics->Sprite->Priority = 1;
        }
    }
    
    if (solid==smeMAP_SOLID_Block)
    {
        smeMAP_GetSolidInfo(&solid, &normal, smeWORLD_GetMap(), smeWORLD_GetMap()->PlaneA, iposition_x, iposition_y);
        
        if (solid==smeMAP_SOLID_Block)
        {
            smePHYSICS_Reflect(entity, &position_x, &position_y, velocity_x, velocity_y, normal);
            iposition_x = fix32ToInt(position_x);
            iposition_y = fix32ToInt(position_y);
            smeMAP_GetSolidInfo(&solid, &normal, smeWORLD_GetMap(), smeWORLD_GetMap()->PlaneA, iposition_x, iposition_y);
        }
    
        if (solid==smeMAP_SOLID_Special)
            solid = smeMAP_SOLID_Empty;
        
        if (solid==smeMAP_SOLID_SwitchHuman || solid==smeMAP_SOLID_SwitchVehicle)
        {
            if (physics->Plane)
            {
                physics->Plane = 0;
            }
            
            if (graphics!=NULL)
                graphics->Sprite->Priority = 1;
        
            physics->Switch = 1;
            solid = smeMAP_SOLID_Empty; 
        }
        else
        {
            if (graphics!=NULL)
                graphics->Sprite->Priority = 0;
                
            if (physics->Plane)
            {
                solid = smeMAP_SOLID_Block;
            }
            else
            {
                physics->Switch = 0;
            }
        }
    }
    
    if (solid!=smeMAP_SOLID_Block)
    {
        transform->PositionX = position_x;
        transform->PositionY = position_y;
    }
}

