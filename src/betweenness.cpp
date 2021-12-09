#include "../include/betweenness.h"
#include "../include/dijkstras.h"
#include <vector>

using std::unordered_map;
using std::make_pair;
using std::vector;
using std::string;
using std::pair;

unordered_map<string, double>* computeBetweennessCentrality(Graph* graph) {
  auto* centrality = new unordered_map<string, double>();

  for (pair<string, Vertex*> vertexPair : graph->getVertices()) {
//    centrality.insert({vertexPair.second->getAddress(), 0.0});
//    centrality[vertexPair.second->getAddress()] = 0.0;
    centrality->insert(make_pair(vertexPair.second->getAddress(), 0.0));
  }

  for (pair<string, Vertex*> vertexPair : graph->getVertices()) {
    // single-shortest-path
    DijkstraResults* dResult = dijkstra(graph, vertexPair.second);

    // accumulation
    while (!dResult->distance_ordered_vertices_.empty()) {
      Vertex* w = dResult->distance_ordered_vertices_.top();
      dResult->distance_ordered_vertices_.pop();
      DijkstraResultsContainer& wContainer = dResult->results_[w->getAddress()];

      for (Vertex* v : wContainer.parents_) {
        DijkstraResultsContainer& vContainer = dResult->results_[v->getAddress()];
        if (wContainer.centrality_ == 0) {
          std::cout << "Here" << std::endl;

          continue;
        }
        vContainer.dependency_ += (vContainer.centrality_ / wContainer.centrality_) * (1 + wContainer.dependency_);
//        vContainer.dependency_ += (vContainer.centrality_ / wContainer.centrality_) * (1 + wContainer.dependency_);
      }

      if (w != dResult->start_node_) {
        (*centrality)[w->getAddress()] += wContainer.dependency_;
      }
    }

    delete dResult;
  }

  return centrality;
}
