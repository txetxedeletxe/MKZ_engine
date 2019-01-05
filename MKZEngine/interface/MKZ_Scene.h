#ifndef __MKZ_SCENE_IMPORTED__
#define __MKZ_SCENE_IMPORTED__

#include "MKZ_Objects.h"
#include "MKZ_Draw.h"
/** SCENE **/
void MKZ_SCENE_add(MKZ_object * obj);
void MKZ_SCENE_set_camera(MKZ_object * ca);

MKZ_object *  MKZ_SCENE_get_object(int id);

MKZ_object * MKZ_SCENE_get_camera();
MKZ_object * MKZ_SCENE_get_default_camera();

void MKZ_SCENE_remove(int id);

void MKZ_SCENE_set_global_mask(unsigned int g_mask);
unsigned int MKZ_SCENE_get_global_mask();
#endif
