#include <iostream>
#include <string>
#include "include/vertex.h"
#include "include/graph.h"
#include "include/edge.h"
#include "include/bfs.h"

using std::string;
using std::pair;

void run_bfs(Graph* g);

int main(int argc, char* argv[]) {
  Graph* g = Graph::from_file("data/data.csv");

  run_bfs(g);

  delete g;
}

void run_bfs(Graph* g) {
  // Check if all vertices HAVE NOT been explored before BFS
  bool vertices_explored = false;
  for (pair<string, Vertex*> p : g->getVertices()) {
    vertices_explored |= p.second->wasExplored();
  }

  if (!vertices_explored)
    std::cout << "No vertex has been explored." << std::endl;
  else
    std::cerr << "One or more vertices has been explored." << std::endl;

  // Check if all edges HAVE NOT been explored before BFS
  bool edges_explored = false;
  for (Edge* e : g->getEdges()) {
    edges_explored |= e->wasExplored();
  }

  if (!edges_explored)
    std::cout << "No edge has been explored." << std::endl;
  else
    std::cerr << "One or more edges has been explored." << std::endl;

  // Run BFS on graph
  std::cout << "Running BFS..." << std::endl;
  bfs(g);

  // Ensure all vertices HAVE been explored after BFS
  vertices_explored = true;
  for (pair<string, Vertex*> p : g->getVertices()) {
    vertices_explored &= p.second->wasExplored();
  }

  if (vertices_explored)
    std::cout << "All vertices have been explored." << std::endl;
  else
    std::cerr << "One or more vertices has not been explored." << std::endl;

  // Ensure all edges HAVE been explored after BFS
  edges_explored = true;
  for (Edge* e : g->getEdges()) {
    edges_explored &= e->wasExplored();
  }

  if (edges_explored)
    std::cout << "All edges have been explored." << std::endl;
  else
    std::cerr << "One or more edges has not been explored." << std::endl;
}
