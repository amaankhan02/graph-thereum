#include "../cs225/catch/catch.hpp"
#include "../include/vertex.h"
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/bfs.h"
#include "../include/dijkstras.h"

#include <iostream>
#include <string>
#include <list>

using std::string;
using std::pair;
using std::list;

TEST_CASE("V small dijkstra", "[dijkstras]") {
  Graph g;

  Vertex* v1 = g.addVertex("0x1");
  Vertex* v2 = g.addVertex("0x2");
  Vertex* v3 = g.addVertex("0x3");
  Vertex* v4 = g.addVertex("0x4");

  g.addEdge(v1, v2, 1, 1, 2);
  g.addEdge(v1, v3, 1, 1, 12);
  g.addEdge(v2, v3, 1, 1, 3);
  g.addEdge(v3, v4, 1, 1, 2);

  uint64_t distance = dijkstra(&g, v1, v4);
  REQUIRE(distance == 7);
}


TEST_CASE("dijkstras simple 2, dist only", "[dijkstras]") {
  Graph g;

  Vertex* v1 = g.addVertex("0x1");
  Vertex* v2 = g.addVertex("0x2");
  Vertex* v3 = g.addVertex("0x3");
  Vertex* v4 = g.addVertex("0x4");
  Vertex* v5 = g.addVertex("0x5");
  Vertex* v6 = g.addVertex("0x6");
  Vertex* v7 = g.addVertex("0x7");
  Vertex* v8 = g.addVertex("0x8");

  g.addEdge(v1, v2, 1, 1, 1);
  g.addEdge(v1, v3, 1, 1, 1);
  g.addEdge(v2, v4, 1, 1, 1);
  g.addEdge(v3, v5, 1, 1, 1);
  g.addEdge(v4, v5, 1, 1, 1);
  g.addEdge(v4, v6, 1, 1, 1);
  g.addEdge(v4, v7, 1, 1, 1);
  g.addEdge(v5, v7, 1, 1, 1);
  g.addEdge(v6, v7, 1, 1, 1);
  g.addEdge(v7, v8, 1, 1, 1);

  uint64_t distance = dijkstra(&g, v1, v8);
  REQUIRE(distance == 4);
}

TEST_CASE("Simple dijkstras path is accurate on Graph with 1 Connected Component and 8 nodes", "[dijkstras]") {
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

  list<Vertex*> correct_path = list<Vertex*> {v8, v7, v4, v2, v1};
  list<Vertex*> output_path = list<Vertex*> {};

  Vertex* current = v8;
  while(current != NULL) {
    output_path.push_back(current);
    current = current->getParent();
  }

  REQUIRE(correct_path == output_path);
}


