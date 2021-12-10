#include "../include/betweenness.h"
#include "../include/dijkstras.h"
#include <vector>

using std::unordered_map;
using std::make_pair;
using std::vector;
using std::string;
using std::pair;

unordered_map<string, double> compute_betweenness_centrality(Graph* graph) {
  unordered_map<string, double> betweenness_centrality;

  for (pair<string, Vertex*> vertexPair : graph->getVertices()) {
    betweenness_centrality.insert({vertexPair.second->getAddress(), 0.0});
  }

  int i = -1;
  for (pair<string, Vertex*> vertexPair : graph->getVertices()) {
    // single-shortest-path
    dijkstra(graph, vertexPair.second);

    // accumulation
    while (graph->hasDistanceOrderedVertices()) {
      Vertex* w = graph->popDistanceOrderedVertex();

      for (Vertex* v : w->getCentralityParents()) {
        if (w->getCentrality() == 0) continue;

        v->incrementDependency((v->getCentrality() / w->getCentrality()) * (1 + w->getDependency()));
      }

      // only add centrality to paths that do not start/end at the starting vertex
      if (w != vertexPair.second) {
        // divide by because its an undirected graph so each edge is counted
        // twice (since algo is for directed graphs)
        betweenness_centrality[w->getAddress()] += w->getDependency() / 2.0;
      }
    }
  }

  return betweenness_centrality;
}
