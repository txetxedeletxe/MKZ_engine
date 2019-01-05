#ifndef __MKZ_OBJECTS_IMPORTED__
#define __MKZ_OBJECTS_IMPORTED__

#include "MKZ_Geometry.h"
#include "MKZ_Datastruct.h"


typedef struct{

	float* l_transform;
	float* g_transform;

	int active;
	int id;

	void * object;
	int type_id;

	MKZ_linkedList * children;

}MKZ_object;

typedef struct {

	MKZ_geometry * mesh;
	MKZ_material * material;

}MKZ_mesh;


typedef struct {

	int light_type;

	float intensityAmbient;
	float intensityDifuse;
	float intensitySpecular;

	MKZ_color3 color;

	float atenuationConstant;
	float atenuationLinear;
	float atenuationQuadratic;

	float spotExponent;

}MKZ_light;

typedef struct{

	MKZ_color3 skybox;

	int projection_mode;

	double v_x, v_y, v_near, v_far;

	int polygon_mode;
	int culling_enabled;

	int lighting_enable;
	int lighting_mode;


}MKZ_camera;

/** Objects **/
MKZ_object * MKZ_OBJECT_create_mesh();
MKZ_object * MKZ_OBJECT_create_light();
MKZ_object * MKZ_OBJECT_create_camera();
MKZ_object * MKZ_OBJECT_create_empty();

void MKZ_OBJECT_free(MKZ_object * obj);

void MKZ_OBJECT_add_child(MKZ_object * parent, MKZ_object * child);

void MKZ_OBJECT_update_children(MKZ_object * obj);

void MKZ_OBJECT_get_absolute_transform(MKZ_object * obj , float * mat);


#endif
