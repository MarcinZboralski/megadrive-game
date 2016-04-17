#include "sme_sprite.h"
#include "sme_world.h"

#define VISIBILITY_ALWAYS_FLAG  0x40000000
#define VISIBILITY_ALWAYS_ON    (VISIBILITY_ALWAYS_FLAG | 0x3FFFFFFF)
#define VISIBILITY_ALWAYS_OFF   (VISIBILITY_ALWAYS_FLAG | 0x00000000)

Sprite smeGraphicsSprites[smeWORLD_MAXIMUM_ENTITY_COUNT];
smeSprite* smeSprites[smeWORLD_MAXIMUM_ENTITY_COUNT];
int smeSpritesCount;
s16 smeSpritesScrollX = 0;
s16 smeSpritesScrollY = 0;

void smeSPRITES_Initialize()
{
    SPR_init(0);
    
    u8 i;
    for (i=0 ; i<smeWORLD_MAXIMUM_ENTITY_COUNT ; ++i)
        smeGraphicsSprites[i].visibility = VISIBILITY_ALWAYS_OFF;
        
    smeSpritesCount = 0;
}

void smeSPRITES_Finalize()
{
    while (smeSpritesCount>0)
        smeSPRITE_Destroy(smeSprites[smeSpritesCount-1]);
        
    SPR_end();
}

void smeSPRITES_Render()
{
    SPR_update(smeGraphicsSprites, smeWORLD_MAXIMUM_ENTITY_COUNT);
}

void smeSPRITES_SetScrollPosition(s16 x, s16 y)
{
	smeSpritesScrollX = x;
	smeSpritesScrollY = y;
}

smeSprite* smeSPRITE_Create(const SpriteDefinition* source, u8 palette)
{
    if (smeSpritesCount>=smeWORLD_MAXIMUM_ENTITY_COUNT)
        return NULL;
    
    smeSprite* sprite = (smeSprite*)MEM_alloc(sizeof(smeSprite));
    
    sprite->ID = smeSpritesCount;
    
    sprite->GraphicsID = 0;
    while (smeGraphicsSprites[sprite->GraphicsID].visibility!=VISIBILITY_ALWAYS_OFF)
        ++sprite->GraphicsID;
    
    sprite->PositionX = smeSpritesScrollX;
    sprite->PositionY = smeSpritesScrollY;
    sprite->Source = (SpriteDefinition*)source;
    sprite->Palette = palette;
    sprite->Animation = 0;
    sprite->Mirrored = FALSE;
    sprite->Priority = 0;
    
    SPR_initSprite(smeGraphicsSprites+sprite->GraphicsID, sprite->Source, 0, 0, TILE_ATTR(palette, 0, FALSE, 0));

    smeSprites[smeSpritesCount++] = sprite;
    return sprite;
}

void smeSPRITE_Destroy(smeSprite* sprite)
{
    //--smeSpritesCount;
    smeGraphicsSprites[sprite->GraphicsID].visibility = VISIBILITY_ALWAYS_OFF;
    /*u8 i;
    for (i=sprite->ID ; i<smeSpritesCount ; ++i)
    {
        smeSprites[i] = smeSprites[i+1];
        smeSprites[i]->ID = i;
    }
    MEM_free(sprite);*/
}

void smeSPRITE_Update(smeSprite* sprite)
{
    Sprite* graphics = smeGraphicsSprites+sprite->GraphicsID;
    SPR_setAttribut(graphics, TILE_ATTR(sprite->Palette, sprite->Priority, FALSE, sprite->Mirrored));
    SPR_setAnim(graphics, sprite->Animation);        
    SPR_setPosition(graphics, sprite->PositionX+smeSpritesScrollX, sprite->PositionY+smeSpritesScrollY);
}
