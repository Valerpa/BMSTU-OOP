#ifndef SCENE_H
#define SCENE_H
#include "figure.h"
#include "iostream"
#include "transform_matrix.h"
#include "vector"

class Scene {
private:
    std::vector<Figure> _figures;
public:
    Scene() = default;
    Scene(std::vector<Figure>& figure);
    std::vector<Figure> get_figures() const;
    void transform_figures(Transform_matrix& matrix);
};

#endif // SCENE_H
