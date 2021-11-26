#include "../include/bfs.h"
#include "../include/utils.h"

#include <iostream>
#include <queue>

using std::string;
using std::vector;
using std::queue;
using std::pair;

int bfs(Graph* g) {
  // Set all vertices as unexplored to start
  for (pair<string, Vertex*> p : g->getVertices()) {
    p.second->setExplored(false);
  }

  // Set all edges as unexplored to start
  for (Edge* e : g->getEdges()) {
    e->setExplored(false);
  }

  int num_connected_components = 0;

  // Run BFS on each connected component of the graph
  for (pair<string, Vertex*> p : g->getVertices()) {
    if (!p.second->wasExplored()) {
      bfs(g, p.second);
      ++num_connected_components;
    }
  }

  return num_connected_components;
}

void bfs(Graph* g, Vertex* start) {
  queue<Vertex*> q;
  start->setExplored(true);
  q.push(start);

  while (!q.empty()) {
    Vertex* v = q.front();
    q.pop();

    for (Edge* indicent : v->getIncidentEdges()) {
      indicent->setExplored(true);
      Vertex* adjacent = indicent->getAdjacentVertex(v);
      if (!adjacent->wasExplored()) {
        // set indicent as discovery edge
        adjacent->setExplored(true);
        q.push(adjacent);
      } /*else if (indicent->wasExplored()) {
        // set indicent as cross edge
      } */
    }
  }
}

void run_bfs(Graph* g) {
  //////////////////////////////////////////////////////////////////////////////
  ///         Ensure all vertices HAVE NOT been explored BEFORE BFS          ///
  //////////////////////////////////////////////////////////////////////////////
  bool vertices_explored = false;
  for (pair<string, Vertex*> p : g->getVertices()) {
    vertices_explored |= p.second->wasExplored();
  }

  if (!vertices_explored)
    std::cout << "No vertex has been explored." << std::endl;
  else
    std::cerr << "One or more vertices has been explored." << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  ///           Ensure all edges HAVE NOT been explored BEFORE BFS           ///
  //////////////////////////////////////////////////////////////////////////////
  bool edges_explored = false;
  for (Edge* e : g->getEdges()) {
    edges_explored |= e->wasExplored();
  }

  if (!edges_explored)
    std::cout << "No edge has been explored." << std::endl;
  else
    std::cerr << "One or more edges has been explored." << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  ///                            Run BFS on graph                            ///
  //////////////////////////////////////////////////////////////////////////////
  std::cout << "\nRunning BFS..." << std::endl;
  clock_t c1, c2;
  c1 = clock();
  int num_connected_components = bfs(g);
  c2 = clock();
  print_elapsed(c1, c2, "BFS");
  std::cout << "There are " << num_connected_components
            << " connected components in the graph.\n" << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  ///            Ensure all vertices HAVE been explored AFTER BFS            ///
  //////////////////////////////////////////////////////////////////////////////
  vertices_explored = true;
  for (pair<string, Vertex*> p : g->getVertices()) {
    vertices_explored &= p.second->wasExplored();
  }

  if (vertices_explored)
    std::cout << "All vertices have been explored." << std::endl;
  else
    std::cerr << "One or more vertices has not been explored." << std::endl;

  //////////////////////////////////////////////////////////////////////////////
  ///             Ensure all edges HAVE been explored AFTER BFS              ///
  //////////////////////////////////////////////////////////////////////////////
  edges_explored = true;
  for (Edge* e : g->getEdges()) {
    edges_explored &= e->wasExplored();
  }

  if (edges_explored)
    std::cout << "All edges have been explored." << std::endl;
  else
    std::cerr << "One or more edges has not been explored." << std::endl;
}
