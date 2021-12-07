#include "../include/dijkstras.h"
// #include "../include/edge.h"
#include <queue>
// #include <iostream>

uint64_t dijkstra(Graph* g, Vertex* start, Vertex* end) {
  std::priority_queue<vertptr, std::vector<vertptr>, MyComparator> q;

  // set everything to infinity
  // std::cout << "Printing vertices in order now" << std::endl;

  for (auto vertex : g->getVertices()) {

    // std::cout << vertex.second->getAddress() << std::endl;

    // vertex.second is pointer to the vertex
    if (vertex.second==start) {
      vertex.second->setDistance(0);
    }
    else {
      vertex.second->setDistance(0xFFFFFFFFFFFFFFFF); 
    }

    vertex.second->setParent(nullptr);

    // record that we have not yet visited this vertex
    vertex.second->setExplored(false);

    // if (vertex.second != start) {
      // q.push(VertexPointer(vertex.second));
      q.push(vertex.second);
    // }
  }

  // start->setDistance(0);
  uint64_t temp_dist;

  while (!q.empty()) {

    Vertex* U = q.top();
    while (U->wasExplored()){
      U = q.top();
      q.pop();
    }
    // std::cout << "U is " << U->getAddress() << " with current dist " << U->getDistance() << std::endl;
    U->setExplored(true);


    for (auto incicident_edge : U->getIncidentEdges()) {
      Vertex* V = incicident_edge->getAdjacentVertex(U);
      if (!(V->wasExplored())) {

        // std::cout <<"Unexplored neighbor for U is " << V->getAddress() << std::endl;
        temp_dist = U->getDistance() + incicident_edge->getGasPrice();

        if (temp_dist < V->getDistance()) {
          V->setDistance(temp_dist);
          V->setParent(U);
          q.push(V);
          // std::cout << "did relax to " << temp_dist << std::endl;
        }
        else {
          // std::cout << "did not relax" << std::endl;
        }
      }
    }
    
    q.pop();
  }

  return end->getDistance();
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
    auto val = dijkstra(g,start,end);
    outlist.push_back(val);
    std::cout << val << std::endl;
  }
  
  return outlist[3];

};
