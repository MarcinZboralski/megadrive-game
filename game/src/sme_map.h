#ifndef _SME_MAP_H_
#define _SME_MAP_H_

#include "genesis.h"

#define smeMAP_SOLID_Empty          0   // empty tile
#define smeMAP_SOLID_Block          1   // blocking tile
#define smeMAP_SOLID_Special        2   // special tile, ex: sidewalks
#define smeMAP_SOLID_SwitchHuman    3   // switch plane tile, for human
#define smeMAP_SOLID_SwitchVehicle  4   // switch plane tile, for vehicle
#define smeMAP_SOLID_Water          5   // water tile
#define smeMAP_SOLID_Count          6

typedef struct
{
    u16* Physics;
    u16* Graphics;
    u16* Palette;
    TileSet* Tiles;
    Map* Data;
} smePlane;

typedef struct
{
    u16 Width;
    u16 Height;
    u8* Solids;
    fix32* SolidNormals;
    smePlane* PlaneA;
    smePlane* PlaneB;    
} smeMap;

void smeMAP_Load(smeMap* map);
void smeMAP_Unload(smeMap* map);
void smeMAP_Render(smeMap* map, s16 x, s16 y, u16 w, u16 h);

void smeMAP_GetSolidInfo(u8* solid, fix32* normal, smeMap* map, smePlane* plane, s16 x, s16 y); 

#endif
