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

void Vertex::setExplored(bool was_explored) { 
  was_explored_ = was_explored; 
}

void Vertex::setDistance(uint64_t distance){
  distance_ = distance;
}

uint64_t Vertex::getDistance(){
  return distance_;
};

bool Vertex::operator>(Vertex*& other){
  return (distance_ > other->getDistance());
}
