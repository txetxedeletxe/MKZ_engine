#include "MKZ_Arithmetic.h"
#include "MKZ_Transform.h"
#include <stdio.h>


void MKZ_TRANSFORM_matrix_global(float * transformMat, MKZ_object * obj);

void MKZ_TRANSFORM_matrix_global( float * transformMat, MKZ_object * obj){

	float * temp = MKZ_ARITHMETIC_create_matrix();

	MKZ_ARITHMETIC_matMul(transformMat,obj->l_transform, temp);

	MKZ_ARITHMETIC_copy_matrix(temp, obj->l_transform);
	MKZ_OBJECT_update_children( obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_translate_global(MKZ_object * obj, MKZ_vector3 * v3){

	obj->l_transform[12] += v3->x;
	obj->l_transform[13] += v3->y;
	obj->l_transform[14] += v3->z;
	MKZ_OBJECT_update_children( obj);

}

void MKZ_TRANSFORM_rotate_global(MKZ_object * obj, MKZ_line * axis,  float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotate(axis, rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateX_global(MKZ_object * obj, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateX(rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateY_global(MKZ_object * obj, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateY(rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateZ_global(MKZ_object * obj, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateZ(rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scale_global(MKZ_object * obj, MKZ_vector3 * along, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scale(along, scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleX_global(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleX(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleY_global(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleY(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleZ_global(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleZ(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleUniform_global(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleUniform(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_set_position_global(MKZ_object * obj, MKZ_point3 * position){

	obj->l_transform[12] = position->x;
	obj->l_transform[13] = position->y;
	obj->l_transform[14] = position->z;
	MKZ_OBJECT_update_children(obj);

}


void MKZ_TRANSFORM_set_absolute_scale(MKZ_object * obj, MKZ_vector3 * scaleVector){

	float f = MKZ_ARITHMETIC_eulidean_norm(obj->l_transform);
	float f2 = scaleVector->x/f;
	obj->l_transform[0] *= f2;
	obj->l_transform[1] *= f2;
	obj->l_transform[2] *= f2;

	f = MKZ_ARITHMETIC_eulidean_norm(obj->l_transform+4);
	f2 = scaleVector->y/f;
	obj->l_transform[4] *= f2;
	obj->l_transform[5] *= f2;
	obj->l_transform[6] *= f2;

	f = MKZ_ARITHMETIC_eulidean_norm(obj->l_transform+8);
	f2 = scaleVector->z/f;
	obj->l_transform[8] *= f2;
	obj->l_transform[9] *= f2;
	obj->l_transform[10] *= f2;

	MKZ_OBJECT_update_children(obj);
}

void MKZ_TRANSFORM_look_at(MKZ_object * obj, MKZ_point3 * p3){

	//direct es el vector dirección de la camaŕa al objeto.
		float direct_x = p3->x - obj->l_transform[12];
		float direct_y = p3->y - obj->l_transform[13];
		float direct_z = p3->z - obj->l_transform[14];

		MKZ_vector3 direction;
		direction.x = direct_x;
		direction.y = direct_y;
		direction.z = direct_z;

		MKZ_vector3 vup;
		vup.x = obj->l_transform[4];
		vup.y = obj->l_transform[5];
		vup.z = obj->l_transform[6];

		MKZ_vector3 newX;

		MKZ_ARITHMETIC_normalize_vector(&direction);
		MKZ_ARITHMETIC_normalize_vector(&vup);
		MKZ_ARITHMETIC_corssProduct_vector( &direction, &vup, &newX);
		MKZ_ARITHMETIC_corssProduct_vector( &newX , &direction, &vup);


		float  mod = MKZ_ARITHMETIC_eulidean_norm(obj->l_transform);
		//mod = 1;
		obj->l_transform[0] = newX.x*mod;
		obj->l_transform[1] = newX.y*mod;
		obj->l_transform[2] = newX.z*mod;

		mod = MKZ_ARITHMETIC_eulidean_norm(obj->l_transform+4);
		//mod = 1;
		obj->l_transform[4]= vup.x*mod;
		obj->l_transform[5]= vup.y*mod;
		obj->l_transform[6]= vup.z*mod;

		mod = MKZ_ARITHMETIC_eulidean_norm(obj->l_transform+8);
		//mod = 1;
		obj->l_transform[8] = -direction.x*mod;
		obj->l_transform[9] = -direction.y*mod;
		obj->l_transform[10] = -direction.z*mod;

		MKZ_OBJECT_update_children(obj);
}

/* local transform */
void MKZ_TRANSFORM_matrix_local(float * transformMat, MKZ_object * obj){

	float * temp = MKZ_ARITHMETIC_create_matrix();

	MKZ_ARITHMETIC_matMul( obj->l_transform, transformMat,  temp);

	MKZ_ARITHMETIC_copy_matrix(temp, obj->l_transform);

	MKZ_ARITHMETIC_free_matrix(temp);
	MKZ_OBJECT_update_children(obj);

}

void MKZ_TRANSFORM_translate_local(MKZ_object * obj, MKZ_vector3 * v3){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_translate(v3, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);


}

void MKZ_TRANSFORM_rotate_local(MKZ_object * obj, MKZ_line * axis, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotate(axis, rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateX_local(MKZ_object * obj, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateX(rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateY_local(MKZ_object * obj, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateY(rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateZ_local(MKZ_object * obj, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateZ(rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scale_local(MKZ_object * obj, MKZ_vector3 * along, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scale(along, scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleX_local(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleX( scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleY_local(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleY( scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleZ_local(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleZ( scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleUniform_local(MKZ_object * obj, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleUniform(scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, obj);
	MKZ_ARITHMETIC_free_matrix(temp);

}


