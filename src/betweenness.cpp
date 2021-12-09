#include "../include/betweenness.h"
#include "../include/dijkstras.h"
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;
using std::string;

std::unordered_map<std::string, double> computeBetweennessCentrality(Graph* graph, Vertex *start, Vertex *end) {
    const std::unordered_map<std::string, Vertex*>& vertices = graph->getVertices();
    const std::vector<Edge*>& edges = graph->getEdges();

    std::unordered_map<string, double> centrality;  

    for (auto vertexPair : vertices) {
        // single-shortest-path
        DijkstraResults* dResult = dijkstra(graph, vertexPair.second);

        // accumulation
        while (!dResult->distance_ordered_vertices_.empty()) {
            Vertex* w = dResult->distance_ordered_vertices_.top();
            dResult->distance_ordered_vertices_.pop();
            DijkstraResultsContainer &wContainer = dResult->results_[w->getAddress()];
            for (Vertex* v : wContainer.parents_) {
                DijkstraResultsContainer &vContainer = dResult->results_[v->getAddress()];
                vContainer.dependency_ += (vContainer.centrality_ / wContainer.centrality_) * (1 + wContainer.dependency_);
            }
            if (w != vertexPair.second) {
                centrality[w->getAddress()] += wContainer.dependency_;
            }
        }
        delete dResult;
    }

    return centrality;
}