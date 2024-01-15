#ifndef VERTEX_H
#define VERTEX_H
#include "_3d_point.h"
#include "scene_object.h"

class Vertex : public Scene_object {
private:
    Point_3d _position;
public:
    Vertex(const Point_3d& pos);
    Point_3d get_position() const;
    void transform(const Transform_matrix& matrix) override;
};

#endif // VERTEX_H
