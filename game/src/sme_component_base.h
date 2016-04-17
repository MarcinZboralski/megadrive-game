#ifndef _SME_COMPONENT_BASE_H_
#define _SME_COMPONENT_BASE_H_

#include "genesis.h"
#include "sme_input.h"
#include "sme_sprite.h"

typedef struct
{
    fix32 PositionX;
    fix32 PositionY;
    fix32 Rotation;
} smeTransform;

typedef struct
{
    smeSprite* Sprite;
    u8 Width;
    u8 Height;
} smeGraphics;

typedef struct
{
    fix32 Velocity;     
    fix32 Omega;
    u8 Plane;            // 0:PLANE_A 1:PLANE_B
    u8 Switch;           // is on other plane and/or able to switch
} smePhysics;

typedef struct
{
    int Empty;
} smeController;

#endif
