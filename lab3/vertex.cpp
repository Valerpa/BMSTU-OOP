#include "vertex.h"

Vertex::Vertex(const Point_3d& pos) : _position(pos) {}

void Vertex::transform(const Transform_matrix& matrix) {
    Point_3d tempPoint;
    tempPoint = matrix.transform_point(_position);
    _position = tempPoint;
}

Point_3d Vertex::get_position() const {
    return _position;
}
