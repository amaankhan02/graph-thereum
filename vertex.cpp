#include "vertex.h"

const std::vector<Edge*>& Vertex::getIncidentEdges() const {
  return incident_edges_;
}

const std::string& Vertex::getAddress() const {
  return address_;
}