#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

class Edge {
private:
    Vertex& _begin;
    Vertex& _end;
public:
    Edge(Vertex& begin, Vertex& end);
    Vertex get_begin() const;
    Vertex get_end() const;
};


#endif // EDGE_H
