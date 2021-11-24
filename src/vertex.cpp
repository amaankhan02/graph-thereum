#include "../include/vertex.h"

Vertex::Vertex(const std::string& address) 
  : address_(address), was_explored_(false) {}

void Vertex::addEdge(Edge* e) {
  incident_edges_.push_back(e);
}

const std::vector<Edge*>& Vertex::getIncidentEdges() const {
  return incident_edges_;
}

const std::string& Vertex::getAddress() const {
  return address_;
}

bool Vertex::wasExplored() const { 
  return was_explored_; 
}

void Vertex::setExplored(bool explored) { 
  was_explored_ = explored; 
}
