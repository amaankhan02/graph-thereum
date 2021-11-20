#include "edge.h"

Vertex* Edge::getAdjacentVertex(Vertex* start) const {
  // If the starting vertex of this edge is one of the endpoints, return the other endpont
  return start == source_ ? destination_ : source_;
}
