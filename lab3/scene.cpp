#include "scene.h"

Scene::Scene(std::vector<Figure>& figure) : _figures(figure) {}

std::vector<Figure> Scene::get_figures() const {
    return _figures;
}

void Scene::transform_figures(Transform_matrix& matrix) {
    for (Figure& figure : _figures) {
        figure.transform(matrix);
    }
}
