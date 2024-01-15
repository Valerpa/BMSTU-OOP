#include "facade.h"

Facade::Facade(QPicture pix) {
    _file_reader = std::make_shared<File_reader>();
    _scene_drawer = std::make_shared<Qt_scene_drawer>(pix);
    _scene = std::make_shared<Scene>();
}

Facade_operation_result Facade::draw_scene() {
    Facade_operation_result _result;
    _scene_drawer->draw_scene(_scene);
    return _result;
}

Facade_operation_result Facade::load_scene(const std::string& path, Normalization_parameters& parameters) {
    Facade_operation_result result;
    _scene = _file_reader->read_scene(path, parameters);
    if (_scene == nullptr) {
        result.set_error_message("Scene was not drew!");
    }
    return result;
}

Facade_operation_result Facade::move_scene(const float x, const float y, const float z) {
    Facade_operation_result result;
    if (x == 0 && y == 0 && z == 0) {
        result.set_error_message("Wrong values for movement!");
        return result;
    }
    Transform_matrix matrix = Transform_matrix_builder::create_move_matrix(x, y, z);
    _scene->transform_figures(matrix);
    return result;
}

Facade_operation_result Facade::rotate_scene(const float x, const float y, const float z) {
    Facade_operation_result result;
    if (x == 0 && y == 0 && z == 0) {
        result.set_error_message("Wrong values for rotation!");
        return result;
    }
    Transform_matrix matr;
    if (x != 0) {
        matr = Transform_matrix_builder::create_x_rotation_matrix(x);
    }
    if (y != 0) {
        matr = Transform_matrix_builder::create_y_rotation_matrix(y);
    }
    if (z != 0) {
        matr = Transform_matrix_builder::create_z_rotation_matrix(z);
    }
    _scene->transform_figures(matr);
    return result;
}

Facade_operation_result Facade::scale_scene(const float x, const float y, const float z) {
    Facade_operation_result result;
    if (x <= 0 || y <= 0 || z <= 0) {
        result.set_error_message("Wrong coordinates!");
        return result;
    }
    Transform_matrix matrix = Transform_matrix_builder::create_scale_matrix(x, y, z);
    _scene->transform_figures(matrix);
    return result;
}
