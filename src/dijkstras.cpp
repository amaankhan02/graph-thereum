#include "../include/dijkstras.h"
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::vector;
using std::string;
using std::stack;

void dijkstra(Graph* g, Vertex* start) {
  priority_queue<Vertex*, vector<Vertex*>, MyComparator> q; // creates a priority queue based on distance of vertices

  g->resetDistanceOrderedVertices();
  for (auto vertex : g->getVertices()) {
    vertex.second->reset();
  }

  start->incrementCentrality(1.0);
  start->setDistance(0);
  q.push(start);

  uint64_t temp_dist;

  while (!q.empty()) {
    Vertex* U = q.top(); // vertex marked with shortest distance rn
    while (U->wasExplored()) {
      if (q.empty()) return; // error checking
      q.pop(); 
      U = q.top(); // keep going until we find vertex we haven't marked as visited (bc we constantly repush verteces to keep the queue updated)
    }

    g->pushDistanceOrderedVertex(U);
    U->setExplored(true); // after with this iteration, this will have been explored
    q.pop();

    for (auto incident_edge : U->getIncidentEdges()) {
      Vertex* V = incident_edge->getAdjacentVertex(U); // for every adjacent vertex to this one
      if (!V->wasExplored()) {
        temp_dist = U->getDistance() + incident_edge->getGas(); // calculate total cost of path from here to that adjacent V

        if (temp_dist <= V->getDistance()) { // found a new shortest path, bc this path shorter than other distance
          V->setDistance(temp_dist); // relax the vertex distance
          V->setParent(U); //record that the parent for this adjacent vertex is us
          q.push(V); // to reorder the priority queue with this new weighting

          // Betweenness Centrality calculations
          V->incrementCentrality(U->getCentrality());
          V->addCentralityParent(U);
        }
      }
    }
  }
}

/**
 * @brief after running dijkstra, save all the shortest distances into a file
 * 
 * @param g graph post dijkstra
 * @param distances_filepath file to save everything into
 */
void saveDistances(Graph* g, std::string distances_filepath) {
  std::ofstream of;
  of.open(distances_filepath);

  for (auto v : g->getVertices()) {
    if (v == *(g->getVertices().begin())) {
      continue;
    }
    of << v.second -> getDistance() << std::endl;
  }
}