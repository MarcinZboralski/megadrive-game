#include "sme_component_graphics.h"
#include "sme_component_transform.h"
#include "sme_maths.h"

void* smeGRAPHICS_Create(smeEntity* entity, const SpriteDefinition* sprite_source, u8 width, u8 height, u8 palette)
{
    void* component = smeENTITY_AddComponent(entity, &smeGRAPHICS_Destroy, &smeGRAPHICS_Update);
    smeENTITY_RegisterAttributes(entity, component, sizeof(smeGraphics));
    smeGraphics* graphics = (smeGraphics*)smeENTITY_GetAttributes(entity, component);
    graphics->Sprite = smeSPRITE_Create(sprite_source, palette);
    graphics->Width = width;
    graphics->Height = height;
    entity->Graphics = graphics;    
    return component;
}

void smeGRAPHICS_Destroy(smeEntity* entity, void* component)
{
    smeSPRITE_Destroy(entity->Graphics->Sprite);
    entity->Graphics = NULL;
}

void smeGRAPHICS_Update(smeEntity* entity, void* component)
{
    smeGraphics* graphics = entity->Graphics;
    smeTransform* transform = entity->Transform;
    
    u8 animation_count = graphics->Sprite->Source->numAnimation;
    u8 animation = fix32ToInt(fix32Div(fix32Mul(clamp_angle2(transform->Rotation), intToFix32(animation_count+1)), fPI2));
    graphics->Sprite->Animation = smeMOD(animation, animation_count);
    graphics->Sprite->PositionX = fix32ToInt(transform->PositionX)-graphics->Width/2;
    graphics->Sprite->PositionY = fix32ToInt(transform->PositionY)-graphics->Height*3/4;
    smeSPRITE_Update(graphics->Sprite);
}
