#include "sme.h"
#include "resources.h"
#include "data.h"
#include "player.h"

int main(u16 hard)
{
    sme_Initialize(hard);
    smeWORLD_LoadMap(&city);
    PLAYER_Create();
    
    while (1)
        sme_Update();
    
    smeWORLD_UnloadMap();
    sme_Finalize();    
    return 0;
}
