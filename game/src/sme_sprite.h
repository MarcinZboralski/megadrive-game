#ifndef _SME_SPRITE_H_
#define _SME_SPRITE_H_

#include "genesis.h"

typedef struct
{
    u16 ID;
    u16 GraphicsID;
    s16 PositionX;
    s16 PositionY;
    SpriteDefinition* Source;
    u8 Palette;
    u8 Animation;
    u8 Mirrored;
    u8 Priority;
} smeSprite;

void smeSPRITES_Initialize();
void smeSPRITES_Finalize();
void smeSPRITES_Render();
void smeSPRITES_SetScrollPosition(s16 x, s16 y);

smeSprite* smeSPRITE_Create(const SpriteDefinition* source, u8 palette);
void smeSPRITE_Destroy(smeSprite* sprite);
void smeSPRITE_Update(smeSprite* sprite);

#endif
