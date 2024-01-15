#ifndef TRANSFORM_MATRIX_BUILDER_H
#define TRANSFORM_MATRIX_BUILDER_H
#include "transform_matrix.h"
#include "math.h"
#include "vector"

class Transform_matrix_builder {
public:
    static Transform_matrix create_x_rotation_matrix(const float x);
    static Transform_matrix create_y_rotation_matrix(const float y);
    static Transform_matrix create_z_rotation_matrix(const float z);
    static Transform_matrix create_move_matrix(const float x, const float y, const float z);
    static Transform_matrix create_scale_matrix(const float x, const float y, const float z);
};


#endif // TRANSFORM_MATRIX_BUILDER_H
