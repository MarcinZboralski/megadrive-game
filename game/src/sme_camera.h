#ifndef _SME_CAMERA_H_
#define _SME_CAMERA_H_

#include "genesis.h"
#include "sme_map.h"
#include "sme_entity.h"

void smeCAMERA_Initialize();
void smeCAMERA_Finalize();
void smeCAMERA_Clear();
void smeCAMERA_Attach(smeEntity* entity);
void smeCAMERA_Detach();
void smeCAMERA_Render();
void smeCAMERA_UpdateScrolling();
void smeCAMERA_SetSmooth(fix32 smooth);

#endif
