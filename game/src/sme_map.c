#include "sme_map.h"
#include "sme_maths.h"
#include "sme_vdp.h"

void smeMAP_Slice(u16* ms, u16* ps, u16* count, u16 mx, u16 px, u16 s, u16 m_max, u16 p_max);

void smeMAP_Load(smeMap* map)
{
    VDP_setPalette(0, map->PlaneA->Palette);
    VDP_loadTileSet(map->PlaneA->Tiles, TILE_USERINDEX, 0);
    map->PlaneA->Data = (Map*)MEM_alloc(sizeof(Map));
    map->PlaneA->Data->compression = 0;
    map->PlaneA->Data->w = map->Width;
    map->PlaneA->Data->h = map->Height;
    map->PlaneA->Data->tilemap = map->PlaneA->Graphics;

    VDP_setPalette(1, map->PlaneB->Palette);
    VDP_loadTileSet(map->PlaneB->Tiles, TILE_USERINDEX+map->PlaneA->Tiles->numTile, 0);
    map->PlaneB->Data = (Map*)MEM_alloc(sizeof(Map));
    map->PlaneB->Data->compression = 0;
    map->PlaneB->Data->w = map->Width;
    map->PlaneB->Data->h = map->Height;
    map->PlaneB->Data->tilemap = map->PlaneB->Graphics;
}

void smeMAP_Unload(smeMap* map)
{
    MEM_free(map->PlaneB->Tiles);
    map->PlaneB->Tiles = NULL;
    MEM_free(map->PlaneA->Tiles);
    map->PlaneA->Tiles = NULL;
}

void smeMAP_Render(smeMap* map, s16 x, s16 y, u16 w, u16 h)
{
    u16 mx = smeMOD(x, map->Width);
    u16 my = smeMOD(y, map->Height);
    u16 px = smeMOD(x, smePLAN_WIDTH);
    u16 py = smeMOD(y, smePLAN_HEIGHT);
    
    u16 mxs[6];
    u16 pxs[6];    
    u16 nx = 0;
    smeMAP_Slice(mxs, pxs, &nx, mx, px, w, map->Width, smePLAN_WIDTH);
    
    u16 mys[6];
    u16 pys[6];    
    u16 ny = 0;
    smeMAP_Slice(mys, pys, &ny, my, py, h, map->Height, smePLAN_HEIGHT);
    
    u16 i, j;
    for (j=0 ; j<ny ; j+=2)
    {
        u16 hs = pys[j+1];
        for (i=0 ; i<nx ; i+=2)
        {
            u16 ws = pxs[i+1];
            VDP_setMapEx(VDP_PLAN_A, map->PlaneA->Data, TILE_ATTR(0, 0, 0, 0), pxs[i], pys[j], mxs[i], mys[j], ws, hs); 
            VDP_setMapEx(VDP_PLAN_B, map->PlaneB->Data, TILE_ATTR(1, 1, 0, 0), pxs[i], pys[j], mxs[i], mys[j], ws, hs); 
        }
    }
}

void smeMAP_Slice(u16* ms, u16* ps, u16* count, u16 mx, u16 px, u16 s, u16 m_max, u16 p_max)
{
    // check breaks with each maximum
    u16 breaks[3];
    u16 breaks_count = 0;
    
    {
        // check map maximum
        s16 out = mx+s-m_max;
        if (out>0)
        {
            breaks[0] = s-out;
            ++breaks_count;
        }
    
        // check plan maximum
        out = px+s-p_max;
        if (out>0)
        {
            s16 b = s-out;
            if (breaks_count==0 || breaks[0]<b)
            {
                breaks[breaks_count] = b;
                ++breaks_count;
            }
            else if (breaks[0]!=b)
            {
                u16 t = breaks[0];
                breaks[0] = b;
                breaks[1] = t;
                ++breaks_count;
            }        
        }
    
        // add final break if required
        if (breaks_count==0 || breaks[breaks_count-1]!=s)
        {
            breaks[breaks_count] = s;
            ++breaks_count;
        }
    }
    
    // create drawing points
    u16 i;
    *count = breaks_count*2;
    
    ms[0] = mx;
    ps[0] = px;
    ms[1] = breaks[0];
    ps[1] = breaks[0];
    
    for (i=1 ; i<breaks_count ; ++i)
    {
        ms[i*2] = smeMOD(mx+breaks[i-1], m_max);
        ps[i*2] = smeMOD(px+breaks[i-1], p_max);
        ms[i*2+1] = breaks[i]-breaks[i-1];
        ps[i*2+1] = breaks[i]-breaks[i-1];
    }
}

void smeMAP_GetSolidInfo(u8* solid, fix32* normal, smeMap* map, smePlane* plane, s16 x, s16 y)
{
    x = smeMOD(x, map->Width*8);
    y = smeMOD(y, map->Height*8);
    
    s16 map_x = x/8;
    s16 map_y = y/8;
    s16 tile_x = x-map_x*8;
    s16 tile_y = y-map_y*8;
    
    u16 tile_id = plane->Physics[map_y*map->Width+map_x];
    *normal = map->SolidNormals[tile_id];
    *solid = map->Solids[tile_id*(8*4)+tile_y*4+tile_x/2]&15;

    if (*solid>=smeMAP_SOLID_Count)
        *solid = smeMAP_SOLID_Empty;
    
    if (plane==map->PlaneB)
        *solid = (*solid==smeMAP_SOLID_Empty?smeMAP_SOLID_Block:smeMAP_SOLID_Empty);
}
