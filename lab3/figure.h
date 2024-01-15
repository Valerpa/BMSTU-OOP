#ifndef FIGURE_H
#define FIGURE_H
#include "vertex.h"
#include "edge.h"
#include "transform_matrix.h"
#include "scene_object.h"
#include "vector"

class Figure : public Scene_object {
private:
    std::vector<Vertex>* _vertices;
    std::vector<Edge>* _edges;
public:
    Figure() = default;
    Figure(std::vector<Vertex>* vertices, std::vector<Edge>* edges);
    std::vector<Vertex>* get_vertices() const;
    std::vector<Edge>* get_edges() const;
    void transform(const Transform_matrix& matrix) override;
};

#endif // FIGURE_H
