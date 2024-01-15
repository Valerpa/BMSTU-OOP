#include "edge.h"

Edge::Edge(Vertex& begin, Vertex& end) : _begin(begin), _end(end) {}

Vertex Edge::get_begin() const {
    return _begin;
}

Vertex Edge::get_end() const {
    return _end;
}
