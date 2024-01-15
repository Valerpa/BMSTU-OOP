#include "transform_matrix.h"

Transform_matrix::Transform_matrix() {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            _matr[i][j] = 0;
        }
    }
}

Transform_matrix::Transform_matrix(const std::vector<std::vector<float>>& matrix) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            _matr[i][j] = matrix[i][j];
        }
    }
}

Transform_matrix Transform_matrix::operator*(const Transform_matrix& new_matr) {
    Transform_matrix res;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                res._matr[i][j] += _matr[i][k] * new_matr._matr[k][j];
            }
        }
    }
    return res;
}

Point_3d Transform_matrix::transform_point(Point_3d& point) const {
    Point_3d res;
    res.X = _matr[0][0] * point.X + _matr[0][1] * point.Y + _matr[0][2] * point.Z + _matr[0][3];
    res.Y = _matr[1][0] * point.X + _matr[1][1] * point.Y + _matr[1][2] * point.Z + _matr[1][3];
    res.Z = _matr[2][0] * point.X + _matr[2][1] * point.Y + _matr[2][2] * point.Z + _matr[2][3];
    return res;
}


