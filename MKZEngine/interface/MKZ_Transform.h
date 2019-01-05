#ifndef __MKZ_TRANSFORM_IMPORTED__
#define __MKZ_TRANSFORM_IMPORTED__

#include "MKZ_Geometry.h"
#include "MKZ_Objects.h"


/** Transforms **/
/* global transform */
void MKZ_TRANSFORM_matrix_global( float * transformMat , MKZ_object * obj);
void MKZ_TRANSFORM_translate_global(MKZ_object * obj, MKZ_vector3 * v3);
void MKZ_TRANSFORM_rotate_global(MKZ_object * obj, MKZ_line * axis,  float rads);
void MKZ_TRANSFORM_rotateX_global(MKZ_object * obj, float rads);
void MKZ_TRANSFORM_rotateY_global(MKZ_object * obj, float rads);
void MKZ_TRANSFORM_rotateZ_global(MKZ_object * obj, float rads);
void MKZ_TRANSFORM_scale_global(MKZ_object * obj, MKZ_vector3 * along, float scalar);
void MKZ_TRANSFORM_scaleX_global(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_scaleY_global(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_scaleZ_global(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_scaleUniform_global(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_set_position_global(MKZ_object * obj, MKZ_point3 * position);
void MKZ_TRANSFORM_set_absolute_scale(MKZ_object * obj, MKZ_vector3 * scaleVector);

void MKZ_TRANSFORM_look_at(MKZ_object * obj, MKZ_point3 * p3);


/* local transform */
void MKZ_TRANSFORM_matrix_local( float * transformMat, MKZ_object * obj);
void MKZ_TRANSFORM_translate_local(MKZ_object * obj, MKZ_vector3 * v3);
void MKZ_TRANSFORM_rotate_local(MKZ_object * obj, MKZ_line * axis, float rads);
void MKZ_TRANSFORM_rotateX_local(MKZ_object * obj, float rads);
void MKZ_TRANSFORM_rotateY_local(MKZ_object * obj, float rads);
void MKZ_TRANSFORM_rotateZ_local(MKZ_object * obj, float rads);
void MKZ_TRANSFORM_scale_local(MKZ_object * obj, MKZ_vector3 * along, float scalar);
void MKZ_TRANSFORM_scaleX_local(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_scaleY_local(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_scaleZ_local(MKZ_object * obj, float scalar);
void MKZ_TRANSFORM_scaleUniform_local(MKZ_object * obj, float scalar);


#endif
