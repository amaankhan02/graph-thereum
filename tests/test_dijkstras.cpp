#include "../cs225/catch/catch.hpp"
#include "../include/vertex.h"
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/bfs.h"
#include "../include/dijkstras.h"

#include <iostream>
#include <string>

using std::string;
using std::pair;

TEST_CASE("Simple dijkstras distance is accurate on Graph with 1 Connected Component and 8 nodes", "[dijkstras]") {
  Graph g;

  Vertex* v1 = g.addVertex("0x1");
  Vertex* v2 = g.addVertex("0x2");
  Vertex* v3 = g.addVertex("0x3");
  Vertex* v4 = g.addVertex("0x4");
  Vertex* v5 = g.addVertex("0x5");
  Vertex* v6 = g.addVertex("0x6");
  Vertex* v7 = g.addVertex("0x7");
  Vertex* v8 = g.addVertex("0x8");

  g.addEdge(v1, v2, 50, 1, 1);
  g.addEdge(v1, v3, 21, 1, 1);
  g.addEdge(v2, v4, 42, 1, 1);
  g.addEdge(v3, v5, 57, 1, 1);
  g.addEdge(v4, v5, 53, 1, 1);
  g.addEdge(v4, v6, 57, 1, 1);
  g.addEdge(v4, v7, 40, 1, 1);
  g.addEdge(v5, v7, 63, 1, 1);
  g.addEdge(v6, v7, 51, 1, 1);
  g.addEdge(v7, v8, 1, 1, 1);

  uint64_t distance = dijkstra(&g, v1, v8);
  REQUIRE(distance == 4);
}


