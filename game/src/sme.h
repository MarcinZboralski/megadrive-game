#ifndef _SME_H_
#define _SME_H_

#include "sme_maths.h"
#include "sme_vdp.h"
#include "sme_sound.h"
#include "sme_input.h"
#include "sme_time.h"
#include "sme_bitmap.h"
#include "sme_map.h"
#include "sme_camera.h"
#include "sme_entity.h"
#include "sme_world.h"

#include "sme_component_transform.h"
#include "sme_component_graphics.h"
#include "sme_component_physics.h"
#include "sme_component_physics_human.h"
#include "sme_component_physics_vehicle.h"
#include "sme_component_controller_pad.h"
#include "sme_component_controller_pad_human.h"
#include "sme_component_controller_pad_vehicle.h"
#include "sme_component_controller_dumb.h"


void sme_Initialize(int hard);
void sme_Finalize();
void sme_Update();

void* MEM_realloc(void* ptr, u16 old_size, u16 new_size);
void memcpy_bytes(void *to, const void *from, int len);

#endif
