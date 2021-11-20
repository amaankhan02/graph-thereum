#include "../include/vertex.h"

void Vertex::addEdge(Edge* e) {
  incident_edges_.push_back(e);
}

const std::vector<Edge*>& Vertex::getIncidentEdges() const {
  return incident_edges_;
}

const std::string& Vertex::getAddress() const {
  return address_;
}

