#include "transform_matrix_builder.h"

Transform_matrix Transform_matrix_builder::create_x_rotation_matrix(const float x) {
    float rad_x = (M_PI / 180) * x;
    std::vector <std::vector<float>> vec_x = {
        {1, 0, 0, 0},
        {0, cos(rad_x), -sin(rad_x), 0},
        {0, sin(rad_x), cos(rad_x), 0},
        {0, 0, 0, 1},
    };
    Transform_matrix res_x = Transform_matrix(vec_x);
    return res_x;
}

Transform_matrix Transform_matrix_builder::create_y_rotation_matrix(const float y) {
    float rad_y = (M_PI / 180) * y;
    std::vector <std::vector<float>> vec_y = {
        {cos(rad_y), 0, sin(rad_y), 0},
        {0, 1, 0, 0},
        {-sin(rad_y), 0, cos(rad_y), 0},
        {0, 0, 0, 1},
    };
    Transform_matrix res_x = Transform_matrix(vec_y);
    return res_x;
}

Transform_matrix Transform_matrix_builder::create_z_rotation_matrix(const float z) {
    float rad_z = (M_PI / 180) * z;
    std::vector <std::vector<float>> vec_z = {
        {cos(rad_z), -sin(rad_z), 0, 0},
        {sin(rad_z), cos(rad_z), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    Transform_matrix res_z = Transform_matrix(vec_z);
    return res_z;
}

Transform_matrix Transform_matrix_builder::create_move_matrix(const float x, const float y, const float z) {
    std::vector <std::vector<float>> vec_move = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1},
    };
    Transform_matrix res = Transform_matrix(vec_move);
    return res;
}

Transform_matrix Transform_matrix_builder::create_scale_matrix(const float x, const float y, const float z) {
    std::vector <std::vector<float>> vec_scale = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    };
    Transform_matrix res = Transform_matrix(vec_scale);
    return res;
}
