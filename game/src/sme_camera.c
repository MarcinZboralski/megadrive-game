#include "sme_camera.h"
#include "sme_vdp.h"
#include "sme_world.h"
#include "sme_time.h"

fix32 smeCamera_PositionX;
fix32 smeCamera_PositionY;
fix32 smeCamera_Smooth;
s16 smeCamera_ScrollX;
s16 smeCamera_ScrollY;
s16 smeCamera_ViewportWidth;
s16 smeCamera_ViewportHeight;
s16 smeCamera_ViewportBorder;
u8 smeCamera_ItIsLoaded;
smeEntity* smeCamera_Target;

void smeCAMERA_SetSmooth(fix32 smooth)
{
    smeCamera_Smooth = smooth;
}

void smeCAMERA_Initialize()
{
    smeCamera_ItIsLoaded = 0;
    smeCamera_ViewportBorder = 2;
    smeCamera_ViewportWidth = smeSCREEN_Width8+(smeCamera_ViewportBorder<<1);
    smeCamera_ViewportHeight = smeSCREEN_Height8+(smeCamera_ViewportBorder<<1);
    smeCamera_PositionX = 0;
    smeCamera_PositionY = 0;
    smeCamera_Target = NULL;
    smeCamera_Smooth = intToFix32(30);
}

void smeCAMERA_Finalize()
{
    smeCamera_ItIsLoaded = 0;
}

void smeCAMERA_Clear()
{
    smeCamera_ItIsLoaded = 0;
}

void smeCAMERA_Attach(smeEntity* entity)
{
    smeCamera_Target = entity;
}

void smeCAMERA_Detach()
{
    smeCamera_Target = NULL;
}

void smeCAMERA_Render()
{
    if (smeCamera_ItIsLoaded==0)
    {
        if (smeCamera_Target!=NULL)
        {
            smeCamera_PositionX = smeCamera_Target->Transform->PositionX;
            smeCamera_PositionY = smeCamera_Target->Transform->PositionY;
        }
        
        smeMAP_Render(smeWORLD_GetMap(),
            (fix32ToInt(smeCamera_PositionX)>>3)-smeSCREEN_Width16-smeCamera_ViewportBorder,
            (fix32ToInt(smeCamera_PositionY)>>3)-smeSCREEN_Height16-smeCamera_ViewportBorder,
            smeCamera_ViewportWidth, smeCamera_ViewportHeight);
            
        smeCamera_ItIsLoaded = 1;
    }
    else if (smeCamera_Target!=NULL)
    {
        int old_place_x = fix32ToInt(smeCamera_PositionX)>>3;
        int old_place_y = fix32ToInt(smeCamera_PositionY)>>3;
    
        smeCamera_PositionX += fix32Div(fix32Mul(smeCamera_Target->Transform->PositionX-smeCamera_PositionX, sme_DeltaTime), smeCamera_Smooth);
        smeCamera_PositionY += fix32Div(fix32Mul(smeCamera_Target->Transform->PositionY-smeCamera_PositionY, sme_DeltaTime), smeCamera_Smooth);
        
        int place_x = fix32ToInt(smeCamera_PositionX)>>3;
        int place_y = fix32ToInt(smeCamera_PositionY)>>3;
        int px = place_x-smeSCREEN_Width16-smeCamera_ViewportBorder;
        int py = place_y-smeSCREEN_Height16-smeCamera_ViewportBorder;
        
        if (place_x>old_place_x)
            smeMAP_Render(smeWORLD_GetMap(), px+smeCamera_ViewportWidth-1, py, smeCamera_ViewportBorder, smeCamera_ViewportHeight);
        else if (place_x<old_place_x)
            smeMAP_Render(smeWORLD_GetMap(), px, py, smeCamera_ViewportBorder, smeCamera_ViewportHeight);
        
        if (place_y>old_place_y)
            smeMAP_Render(smeWORLD_GetMap(), px, py+smeCamera_ViewportHeight-1, smeCamera_ViewportWidth, smeCamera_ViewportBorder);
        else if (place_y<old_place_y)
            smeMAP_Render(smeWORLD_GetMap(), px, py, smeCamera_ViewportWidth, smeCamera_ViewportBorder);
    }
    
    smeCamera_ScrollX = smeSCREEN_Width2-fix32ToInt(smeCamera_PositionX);
    smeCamera_ScrollY = fix32ToInt(smeCamera_PositionY)-smeSCREEN_Height2;
    SPR_setScrollPosition(smeSCREEN_Width2-fix32ToInt(smeCamera_PositionX), smeSCREEN_Height2-fix32ToInt(smeCamera_PositionY));
}

void smeCAMERA_UpdateScrolling()
{
    if (smeCamera_ItIsLoaded==1)
    {
        VDP_setHorizontalScroll(PLAN_A, smeCamera_ScrollX);
        VDP_setHorizontalScroll(PLAN_B, smeCamera_ScrollX);
        VDP_setVerticalScroll(PLAN_A, smeCamera_ScrollY);
        VDP_setVerticalScroll(PLAN_B, smeCamera_ScrollY);  
    }
}
