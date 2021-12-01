#include "../include/dijkstras.h"
#include "../include/edge.h"
#include <queue>

uint64_t djikstra(Graph* g, Vertex* start, Vertex* end) {
  std::priority_queue<Vertex*> q;

  // set everything to infinity
  for (auto vertex : g->getVertices()) {
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
          temp_dist = incicident_edge->getGas();
        } else {
          temp_dist = U->getDistance() + incicident_edge->getGas();
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
    const std::unordered_map<std::string, Vertex*>& temp = g->getVertices();
    auto it = temp.begin();
    Vertex* start = it->second;
    
    for (int i = 0; i < 200; ++i) ++it;

    Vertex* end = it->second;

    return djikstra_helper(g, start, end);
};
