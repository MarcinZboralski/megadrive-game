#include "sme_entity.h"
#include "sme_component.h"

void smeENTITY_OnRealloc(smeEntity* entity, void* old_attributes)
{
    if (entity->Transform!=NULL) entity->Transform = (smeTransform*)(entity->Attributes+((void*)entity->Transform-old_attributes));
    if (entity->Graphics!=NULL) entity->Graphics = (smeGraphics*)(entity->Attributes+((void*)entity->Graphics-old_attributes));
    if (entity->Physics!=NULL) entity->Physics = (smePhysics*)(entity->Attributes+((void*)entity->Physics-old_attributes));
    if (entity->Controller!=NULL) entity->Controller = (smeController*)(entity->Attributes+((void*)entity->Controller-old_attributes));
}

void smeENTITY_OnMoveAttributes(smeEntity* entity, void* new_attributes, void* old_attributes)
{
    if (entity->Transform==old_attributes) entity->Transform = (smeTransform*)new_attributes;
    else if (entity->Graphics==old_attributes) entity->Graphics = (smeGraphics*)new_attributes;
    else if (entity->Physics==old_attributes) entity->Physics = (smePhysics*)new_attributes;
    else if (entity->Controller==old_attributes) entity->Controller = (smeController*)new_attributes;
}

smeEntity* smeENTITY_Create()
{
    smeEntity* entity = (smeEntity*)MEM_alloc(sizeof(smeEntity));
    entity->Components = NULL;
    entity->ComponentCount = 0;
    entity->Attributes = NULL;
    entity->AttributesSize = 0;
    entity->Transform = NULL;
    entity->Graphics = NULL;
    entity->Physics = NULL;
    entity->Controller = NULL;
    return entity;
}

void smeENTITY_Destroy(smeEntity* entity)
{
    while (entity->ComponentCount>0)
        smeENTITY_RemoveComponent(entity, entity->Components[entity->ComponentCount-1]);
    MEM_free(entity);
}

void smeENTITY_Update(smeEntity* entity)
{
    u8 i;
    for (i=0 ; i<entity->ComponentCount ; ++i)
    {
        smeComponent* component = (smeComponent*)entity->Components[i];
        if (component->Update!=NULL)
            component->Update(entity, component);
    }
}

void* smeENTITY_AddComponent(smeEntity* entity, smeENTITY_FUNC_DESTROY, smeENTITY_FUNC_UPDATE)
{
    smeComponent* component = (smeComponent*)MEM_alloc(sizeof(smeComponent));
    component->ID = entity->ComponentCount;
    component->AttributesID = entity->AttributesSize;
    component->AttributesSize = 0;
    component->Destroy = destroy;
    component->Update = update;
    
    entity->Components = (void**)MEM_realloc(entity->Components, sizeof(void*)*entity->ComponentCount, sizeof(void*)*(entity->ComponentCount+1));
    entity->Components[entity->ComponentCount] = component;
    ++entity->ComponentCount;
    return (void*)component;
}

smeComponent* smeENTITY_GetComponent(smeEntity* entity, void* component_element)
{
    u8 i;
    for (i=0 ; i<entity->ComponentCount ; ++i)
    {
        smeComponent* component = (smeComponent*)entity->Components[i];
        void* attributes = entity->Attributes+component->AttributesID;
        if (attributes==component_element)
            return component;
    }
    return component_element;
}

void smeENTITY_RemoveComponent(smeEntity* entity, void* component)
{
    smeComponent* comp = smeENTITY_GetComponent(entity, component);
       
    if (comp->Destroy!=NULL)
        comp->Destroy(entity, comp);
    
    --entity->ComponentCount;
    u16 attributes = comp->AttributesID;    
    u8 i;
    for (i=comp->ID ; i<entity->ComponentCount ; ++i)
    {
        smeComponent* move_comp = (smeComponent*)entity->Components[i+1];
        move_comp->ID = i;
        entity->Components[i] = move_comp;
        
        if (comp->AttributesSize>0 && move_comp->AttributesSize>0)
        {
            void* old_attributes = entity->Attributes+move_comp->AttributesID;
            void* new_attributes = entity->Attributes+attributes;
            smeENTITY_OnMoveAttributes(entity, new_attributes, old_attributes);
            memcpy_bytes(new_attributes, old_attributes, move_comp->AttributesSize);
            move_comp->AttributesID = attributes;
            attributes += move_comp->AttributesSize;
        }
    }
    
    entity->Components = (void**)MEM_realloc(entity->Components, sizeof(void*)*(entity->ComponentCount+1), sizeof(void*)*(entity->ComponentCount));
    
    void* old_attributes = entity->Attributes;
    entity->Attributes = MEM_realloc(entity->Attributes, entity->AttributesSize, entity->AttributesSize-comp->AttributesSize);
    entity->AttributesSize -= comp->AttributesSize;
    smeENTITY_OnRealloc(entity, old_attributes);
    
    MEM_free(comp);
}

void* smeENTITY_GetAttributes(smeEntity* entity, void* component)
{
    return ((char*)entity->Attributes)+((smeComponent*)component)->AttributesID;
}

void* smeENTITY_RegisterAttributes(smeEntity* entity, void* component, u16 size)
{
    smeComponent* comp = (smeComponent*)component;    
    comp->AttributesSize = size;
    
    void* old_attributes = entity->Attributes;
    entity->Attributes = MEM_realloc(entity->Attributes, entity->AttributesSize, entity->AttributesSize+size);
    entity->AttributesSize += size;
    smeENTITY_OnRealloc(entity, old_attributes);
    
    return smeENTITY_GetAttributes(entity, component);
}

