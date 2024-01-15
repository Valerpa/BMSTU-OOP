#ifndef FACADE_H
#define FACADE_H

#include <memory>
#include "base_file_reader.h"
#include "file_reader.h"
#include "scene_drawer_base.h"
#include "qt_scene_drawer.h"
#include "facade_operation_result.h"
#include "normalization_parameters.h"
#include "transform_matrix_builder.h"

class Facade {
private:
    std::shared_ptr<Base_file_reader> _file_reader;
    std::shared_ptr<Scene_drawer_base> _scene_drawer;
    std::shared_ptr<Scene> _scene;
public:
    Facade(QPicture pix);
    Facade_operation_result draw_scene();
    Facade_operation_result load_scene(const std::string& path, Normalization_parameters& parameters);
    Facade_operation_result move_scene(const float x, const float y, const float z);
    Facade_operation_result rotate_scene(const float x, const float y, const float z);
    Facade_operation_result scale_scene(const float x, const float y, const float z);
};

#endif // FACADE_H
