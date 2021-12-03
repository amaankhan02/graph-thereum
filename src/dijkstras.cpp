#include "../include/dijkstras.h"
#include "../include/edge.h"
#include <queue>
#include <iostream>

uint64_t dijkstra(Graph* g, Vertex* start, Vertex* end) {
  std::priority_queue<Vertex*> q;

  // set everything to infinity
  std::cout << "Printing vertices in order now" << std::endl;

  for (auto vertex : g->getVertices()) {

    std::cout << vertex.second->getAddress() << std::endl;

    // vertex.second is pointer to the vertex
    vertex.second->setDistance(0xFFFFFFFFFFFFFFFF); 

    // record that we have not yet visited this vertex
    vertex.second->setExplored(false);

    if (vertex.second != start) {
      q.push(vertex.second);
    }
  }

  start->setDistance(0);
  uint64_t temp_dist;

  while (!q.empty()) {
    Vertex* U = q.top();
    q.pop();

    for (auto incicident_edge : U->getIncidentEdges()) {
      if (!incicident_edge->getAdjacentVertex(U)->wasExplored()) {
        if (U->getDistance() == 0xFFFFFFFFFFFFFFFF) {
          temp_dist = incicident_edge->getGasPrice();
        } else {
          temp_dist = U->getDistance() + incicident_edge->getGasPrice();
        }

        if (temp_dist < incicident_edge->getAdjacentVertex(U)->getDistance()) {
          incicident_edge->getAdjacentVertex(U)->setDistance(temp_dist);
        }
      }
    }
    
    U->setExplored(true);
  }

  return end->getDistance();
}

uint64_t dijkstra(Graph* g) {
    // std::cout << "Entered dijkstra helper function " << std::endl;

    const std::unordered_map<std::string, Vertex*>& temp = g->getVertices();
    auto it = temp.begin();

    // std::cout << "About to identify start vertex " << std::endl;
    Vertex* start = it->second;

    std::cout << "Start vertex is " << start->getAddress() << std::endl;
    
    for (int i = 0; i < 1; ++i) ++it;

    Vertex* end = it->second;
    std::cout << "End vertex is " << end->getAddress() << std::endl;

    // std::cout << "Segfault even before calling dijkstra helper function " << std::endl;

    return dijkstra(g, start, end);
};
