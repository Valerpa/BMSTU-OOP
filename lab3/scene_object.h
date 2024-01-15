#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
#include "transform_matrix.h"

class Scene_object {
public:
    virtual void transform(const Transform_matrix& matrix) = 0;
    virtual ~Scene_object() {}
};

#endif // SCENE_OBJECT_H
