#include "../include/dijkstras.h"
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::vector;
using std::string;
using std::stack;

void dijkstra(Graph* g, Vertex* start) {
  priority_queue<Vertex*, vector<Vertex*>, MyComparator> q;

  g->resetDistanceOrderedVertices();
  for (auto vertex : g->getVertices()) {
    vertex.second->reset();
  }

  start->incrementCentrality(1.0);
  start->setDistance(0);
  q.push(start);

  uint64_t temp_dist;

  while (!q.empty()) {
    Vertex* U = q.top();
    while (U->wasExplored()) {
      if (q.empty()) return;
      q.pop();
      U = q.top();
    }

    g->pushDistanceOrderedVertex(U);
    U->setExplored(true);
    q.pop();

    for (auto incident_edge : U->getIncidentEdges()) {
      Vertex& V = *incident_edge->getAdjacentVertex(U);
      if (!V.wasExplored()) {
        temp_dist = U->getDistance() + incident_edge->getGas();

        if (temp_dist <= V.getDistance()) { // found a new shortest path
          V.setDistance(temp_dist);
          V.setParent(U);
          q.push(&V);

          // Betweenness Centrality calculations
          V.incrementCentrality(U->getCentrality());
          V.addCentralityParent(U);
        }
      }
    }
  }
}
