#include "MKZ_Objects.h"
#include "MKZ_Arithmetic.h"
#include "MKZ_Definitions.h"

#include <stdlib.h>

int MKZ_next_obj_id = 0;

MKZ_object * MKZ_OBJECT_create_empty(){

	MKZ_object * obj = (MKZ_object *) malloc(sizeof(MKZ_object));
	obj->active = 1;
	obj->children = 0;
	obj->id = MKZ_next_obj_id++;
	obj->l_transform = MKZ_ARITHMETIC_create_matrix();
	obj->g_transform = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_identityMatrix(obj->g_transform);
	MKZ_ARITHMETIC_identityMatrix(obj->l_transform);
	obj->type_id = MKZ_GENERIC_ID_EMPTY;
	obj->object = 0;
	return obj;
}

MKZ_object * MKZ_OBJECT_create_mesh(){

	MKZ_object * obj = MKZ_OBJECT_create_empty();
	MKZ_mesh * m = (MKZ_mesh *) malloc(sizeof(MKZ_mesh));
	m->material = 0;
	m->mesh = 0;
	obj->type_id = MKZ_GENERIC_ID_MESH;
	obj->object = m;
	return obj;

}

MKZ_object * MKZ_OBJECT_create_light(){

	MKZ_object * obj = MKZ_OBJECT_create_empty();
	MKZ_light * mlo = (MKZ_light *) malloc(sizeof(MKZ_light));
	mlo->color.r = 1;
	mlo->color.g = 1;
	mlo->color.b = 1;
	mlo->intensityAmbient = 1;
	mlo->intensityDifuse = 1;
	mlo->intensitySpecular = 1;

	mlo->atenuationConstant = 1;
	mlo->atenuationLinear = 1;
	mlo->atenuationQuadratic = 1;

	mlo->spotExponent = 0;

	mlo->light_type = 0;

	obj->type_id = MKZ_GENERIC_ID_LIGHT;
	obj->object = mlo;
	return obj;
}

MKZ_object * MKZ_OBJECT_create_camera(){

	MKZ_object * obj = MKZ_OBJECT_create_empty();

	MKZ_camera * mc = (MKZ_camera *) malloc(sizeof(MKZ_camera));
	mc->projection_mode = MKZ_PROJECTIONMODE_PARALLEL;
	mc->polygon_mode = MKZ_POLYGONMODE_FILLED;
	MKZ_GEOMETRY_reset_to_black(&mc->skybox);
	mc->lighting_enable = 0;
	mc->lighting_mode = 0;
	mc->culling_enabled = 1;
	mc->v_x = 2;
	mc->v_y = 2;
	mc->v_near = 1;
	mc->v_far = 1000;

	obj->type_id = MKZ_GENERIC_ID_CAMERA;
	obj->object = mc;
	return obj;

}


void MKZ_OBJECT_free_mesh(MKZ_mesh * mo){

	free(mo);
}

void MKZ_OBJECT_free_light(MKZ_light* lo){

	free(lo);

}
void MKZ_OBJECT_free_camera(MKZ_camera * ca){

	free(ca);
}

void __obj_free_tool(void * obj , int t_id) {

	if (t_id == 0){

		MKZ_OBJECT_free((MKZ_object *) obj);

	}else{
		free(obj);
	}
}


void MKZ_OBJECT_free(MKZ_object * obj){

	MKZ_ARITHMETIC_free_matrix(obj->l_transform);
	MKZ_ARITHMETIC_free_matrix(obj->g_transform);
	switch(obj->type_id){
	case MKZ_GENERIC_ID_MESH:
		MKZ_OBJECT_free_mesh((MKZ_mesh*)obj->object);
		break;

	case MKZ_GENERIC_ID_LIGHT:
		MKZ_OBJECT_free_light((MKZ_light*)obj->object);
		break;

	case MKZ_GENERIC_ID_CAMERA:
		MKZ_OBJECT_free_camera((MKZ_camera*)obj->object);
		break;
	}
	MKZ_DATASTRUCT_free_linkedList(obj->children,__obj_free_tool);
	free(obj);

}


void MKZ_OBJECT_get_absolute_transform(MKZ_object * obj , float * mat){

	MKZ_ARITHMETIC_matMul(obj->g_transform,obj->l_transform , mat);
}


void MKZ_OBJECT_update_children(MKZ_object * obj){

	MKZ_linkedList * aux = obj->children;

	while (aux != 0){

			if (aux->type_id == 0){

				MKZ_object * o = (MKZ_object *) aux->object;
				MKZ_OBJECT_get_absolute_transform(obj, o->g_transform);
				MKZ_OBJECT_update_children(o);

			}

			aux = aux->ll;

		}


}

void MKZ_OBJECT_add_child(MKZ_object * parent, MKZ_object * child){
	MKZ_OBJECT_get_absolute_transform(parent,child->g_transform);
	MKZ_OBJECT_update_children(child);
	MKZ_DATASTRUCT_linkedList_add(&parent->children,child,MKZ_GENERIC_ID_OBJECT,child->id);
}


