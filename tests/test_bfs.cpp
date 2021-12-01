#include "../cs225/catch/catch.hpp"
#include "../include/vertex.h"
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/bfs.h"

#include <iostream>
#include <string>

using std::string;
using std::pair;

void wasEntireGraphWasVisited(Graph* g, bool visited) {
  for (Edge* e : g->getEdges()) {
    REQUIRE( e->wasExplored() == visited );
  }

  for (pair<string, Vertex*> p : g->getVertices()) {
    REQUIRE( p.second->wasExplored() == visited );
  }
}

TEST_CASE("Simple BFS on Graph with 1 Connected Component", "[bfs]")
{
  Graph g;

	Vertex* v1 = g.addVertex("0x1");
  Vertex* v2 = g.addVertex("0x2");
  Vertex* v3 = g.addVertex("0x3");
  Vertex* v4 = g.addVertex("0x4");

  g.addEdge(v1, v2, 1, 1, 1);
  g.addEdge(v1, v3, 1, 1, 1);
  g.addEdge(v2, v4, 1, 1, 1);
  g.addEdge(v3, v4, 1, 1, 1);

  wasEntireGraphWasVisited(&g, false);

  int num_connected_components = bfs(&g);
  REQUIRE( num_connected_components == 1 );

  wasEntireGraphWasVisited(&g, true);
}

TEST_CASE("Simple BFS on Graph with 2 Connected Components", "[bfs]")
{
  Graph g;

	Vertex* v1 = g.addVertex("0x1");
  Vertex* v2 = g.addVertex("0x2");
  Vertex* v3 = g.addVertex("0x3");
  Vertex* v4 = g.addVertex("0x4");

  g.addEdge(v1, v2, 1, 1, 1);
  g.addEdge(v3, v4, 1, 1, 1);

  wasEntireGraphWasVisited(&g, false);

  int num_connected_components = bfs(&g);
  REQUIRE( num_connected_components == 2 );

  wasEntireGraphWasVisited(&g, true);
}

TEST_CASE("Simple BFS on Graph with 4 Connected Components", "[bfs]")
{
  Graph g;

	Vertex* v1 = g.addVertex("0x1");
  Vertex* v2 = g.addVertex("0x2");
  Vertex* v3 = g.addVertex("0x3");
  Vertex* v4 = g.addVertex("0x4");

  wasEntireGraphWasVisited(&g, false);

  int num_connected_components = bfs(&g);
  REQUIRE( num_connected_components == 4 );

  wasEntireGraphWasVisited(&g, true);
}