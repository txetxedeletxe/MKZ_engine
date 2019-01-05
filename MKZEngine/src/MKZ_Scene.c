#include "MKZ_Definitions.h"
#include "MKZ_Datastruct.h"
#include "MKZ_Objects.h"
#include "MKZ_Draw.h"

#include <stdlib.h>
#include <unistd.h>

/** Internal state **/
/** camera **/
MKZ_object * default_camera;
MKZ_object * camera;

/** objects **/
MKZ_linkedList * objectList;

unsigned int global_mask;
/** Exported **/
/* Init */

void MKZ_SCENE_init(){


		objectList = 0;
		global_mask = 0;

		default_camera = MKZ_OBJECT_create_camera();
		camera = default_camera;

		MKZ_DRAW_init();

}

void __add_lights(MKZ_linkedList * ll){

	MKZ_linkedList * aux = ll;

	while (aux != 0){

		if (aux->type_id == MKZ_GENERIC_ID_OBJECT){

			MKZ_object * obj = (MKZ_object *)aux->object;
			if (obj->active){
				MKZ_DRAW_push_modelview(obj->l_transform);
				if (obj->type_id == MKZ_GENERIC_ID_LIGHT){
					MKZ_light * l = (MKZ_light *)obj->object;
					MKZ_DRAW_add_light(l);
				}

				__add_lights(obj->children);
				MKZ_DRAW_pop_modelview(obj->l_transform);
			}

		}
		aux = aux->ll;
	}

}

void __add_mesh(MKZ_linkedList * ll){

	MKZ_linkedList * aux = ll;

	while (aux != 0){

		if (aux->type_id == MKZ_GENERIC_ID_OBJECT){

			MKZ_object * obj = (MKZ_object *)aux->object;
			if (obj->active){
				MKZ_DRAW_push_modelview(obj->l_transform);
				if (obj->type_id == MKZ_GENERIC_ID_MESH){
					MKZ_mesh * m = (MKZ_mesh *)obj->object;
					MKZ_DRAW_add_mesh(m);
				}

				__add_mesh(obj->children);
				MKZ_DRAW_pop_modelview(obj->l_transform);
			}

		}
		aux = aux->ll;
	}

}

void MKZ_SCENE_draw(){

		float tra_mat[16];

		MKZ_camera * aux_camera = 0;
		MKZ_object * aux_object = 0;

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_background_color(&aux_camera->skybox);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_projectionMode(aux_camera->projection_mode);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_poligonMode(aux_camera->polygon_mode);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_culling(aux_camera->culling_enabled);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_OBJECT_get_absolute_transform(aux_object,tra_mat);
		MKZ_DRAW_set_cameraMat(tra_mat);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_lighting(aux_camera->lighting_enable);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_lighting_mode(aux_camera->lighting_mode);

		aux_object = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		aux_camera = (MKZ_camera *)aux_object->object;
		MKZ_DRAW_set_renderVolume(-aux_camera->v_x/2,aux_camera->v_x/2,
				-aux_camera->v_y/2,aux_camera->v_y/2,
				aux_camera->v_near,aux_camera->v_far);

		MKZ_DRAW_clear();
		MKZ_DRAW_start();

		MKZ_DRAW_clear_lights();

		__add_lights(objectList);
		__add_mesh(objectList);

		MKZ_DRAW_end();
}

void MKZ_SCENE_add(MKZ_object * o){

	MKZ_DATASTRUCT_linkedList_add(&objectList , o , MKZ_GENERIC_ID_OBJECT , o->id);
}


void MKZ_SCENE_set_camera(MKZ_object * ca){
	if (ca->type_id == MKZ_GENERIC_ID_CAMERA)
		camera = ca;
}

MKZ_object *  MKZ_SCENE_get_object(int id){

	void * p = 0;
	int t_id;
	MKZ_DATASTRUCT_linkedList_get(objectList,id,&p,&t_id);

	if (t_id != MKZ_GENERIC_ID_OBJECT)
		return 0;
	else
		return (MKZ_object *) p;
}



MKZ_object * MKZ_SCENE_get_camera(){
	return camera;
}

MKZ_object * MKZ_SCENE_get_default_camera(){

	return default_camera;

}

void MKZ_SCENE_remove(int id){

	MKZ_DATASTRUCT_linkedList_remove(&objectList,id,0);

}


void MKZ_SCENE_restore_camera(){

	camera = default_camera;

}

void MKZ_SCENE_set_global_mask(unsigned int g_mask){
	global_mask = g_mask;
}

unsigned int MKZ_SCENE_get_global_mask(){
	return global_mask;
}

