#include "sme.h"

void sme_Initialize(u16 hard)
{
    if (hard==0)
    {
        // handle reset
    }
    
    smeVDP_Initialize();
    smeWORLD_Initialize();
    smeCAMERA_Initialize();
    smeINPUTS_Initialize();
}

void sme_Finalize()
{
    smeCAMERA_Finalize();
    smeWORLD_Finalize();
    smeVDP_Finalize();
}

void sme_Update()
{
    smeTIME_Update();
    smeINPUTS_Update();
    smeWORLD_Update();
    VDP_showFPS(1);
}
