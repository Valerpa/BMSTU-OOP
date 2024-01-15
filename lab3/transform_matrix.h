#ifndef TRANSFORM_MATRIX_H
#define TRANSFORM_MATRIX_H
#include "_3d_point.h"
#include "vector"
#define MATRIX_SIZE 4

class Transform_matrix {
private:
    float _matr[MATRIX_SIZE][MATRIX_SIZE];
public:
    Transform_matrix();
    Transform_matrix(const std::vector<std::vector<float>>& matrix);
    Transform_matrix operator*(const Transform_matrix& new_matr);
    Point_3d transform_point(Point_3d& point) const;
};

#endif // TRANSFORM_MATRIX_H
