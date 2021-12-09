#include "../include/dijkstras.h"
#include <queue>

using std::priority_queue;
using std::vector;

DijkstraResults* dijkstra(Graph* g, Vertex* start) {
  DijkstraResults* dr = new DijkstraResults(start);
  std::priority_queue<Vertex*, vector<Vertex*>, MyComparator> q;

  for (auto vertex : g->getVertices()) {
    vertex.second->setDistance(0xFFFFFFFFFFFFFFFF); 
    vertex.second->setParent(NULL);

    // record that we have not yet visited this vertex
    vertex.second->setExplored(false);
    // q.push(vertex.second);

    dr->results_[vertex.second->getAddress()];
  }

  DijkstraResultsContainer& start_container = dr->results_[start->getAddress()];
  start_container.centrality_ = 1;

  start->setDistance(0);
  q.push(start);
  uint64_t temp_dist;

  while (!q.empty()) {
    Vertex* U = q.top();
    while (U->wasExplored()) {
      if (q.empty()) {
        return dr;
      }
      U = q.top();
      q.pop();
    }
    // std::cout << "U is " << U->getAddress() << " with current dist " << U->getDistance() << std::endl;
    U->setExplored(true);
    dr->distance_ordered_vertices_.push(U);

    DijkstraResultsContainer& U_container = dr->results_[U->getAddress()];
    for (auto incident_edge : U->getIncidentEdges()) {
      Vertex* V = incident_edge->getAdjacentVertex(U);
      if (!V->wasExplored()) {

        std::cout <<"Unexplored neighbor for " << U->getAddress() << " is " << V->getAddress() << std::endl;
        temp_dist = U->getDistance() + incident_edge->getGas();

        if (temp_dist <= V->getDistance()) { // found a new shortest path
          V->setDistance(temp_dist);
          V->setParent(U);
          q.push(V);
          // Betweenness Centrality calculations
          DijkstraResultsContainer& V_container = dr->results_[V->getAddress()];
          V_container.centrality_ += U_container.centrality_;
          V_container.parents_.push_back(U);
          V_container.distance_ = temp_dist;
        }
      }
    }
    
    q.pop();
  }

  // return end->getDistance();
  return dr;
}

// uint64_t dijkstra(Graph* g) {

//     const std::unordered_map<std::string, Vertex*>& temp = g->getVertices();
//     auto it = temp.begin();

//     Vertex* start = it->second;

//     // std::cout << "Start vertex is " << start->getAddress() << std::endl;
    
//     for (int i = 0; i < 1; ++i) ++it;

//     Vertex* end = it->second;
//     // std::cout << "End vertex is " << end->getAddress() << std::endl;


//     return dijkstra(g, start, end);
// };

uint64_t dijkstra(Graph* g) {

  const std::unordered_map<std::string, Vertex*>& temp = g->getVertices();
  std::vector<uint64_t> outlist;
  auto it = temp.begin();

  Vertex* start = it->second;

  // std::cout << "Start vertex is " << start->getAddress() << std::endl;
  
  for (auto it = temp.begin(); it != temp.end(); ++it) {
    Vertex* end = it->second;
    DijkstraResults* val = dijkstra(g,start);
    outlist.push_back(val->results_[end->getAddress()].distance_);
    std::cout << val << std::endl;

    delete val;
  }
  
  return outlist[3];
};
