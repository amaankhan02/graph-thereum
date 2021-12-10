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
      U = q.top();
      q.pop();
    }

    U->setExplored(true);
    g->pushDistanceOrderedVertex(U);

//    DijkstraResultsContainer& U_container = dr->results_[U->getAddress()];
    for (auto incident_edge : U->getIncidentEdges()) {
      Vertex* V = incident_edge->getAdjacentVertex(U);
      if (!V->wasExplored()) {
        temp_dist = U->getDistance() + incident_edge->getGas();

        if (temp_dist <= V->getDistance()) { // found a new shortest path
          V->setDistance(temp_dist);
          V->setParent(U);
          q.push(V);

          // Betweenness Centrality calculations
          V->incrementCentrality(U->getCentrality());
          V->addCentralityParent(U);
        }
      }
    }
    
    q.pop();
  }
}

uint64_t dijkstra(Graph* g) {
  const unordered_map<string, Vertex*>& temp = g->getVertices();
  vector<uint64_t> outlist;
  auto it = temp.begin();

  Vertex* start = it->second;

//  for (auto it = temp.begin(); it != temp.end(); ++it) {
//    Vertex* end = it->second;
//    DijkstraResults* val = dijkstra(g,start);
//    outlist.push_back(val->results_[end->getAddress()].distance_);
//    std::cout << val << std::endl;
//
//    delete val;
//  }
  
//  return outlist[3];
return 0;
}
