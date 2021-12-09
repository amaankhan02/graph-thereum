#include "../cs225/catch/catch.hpp"
#include "../include/betweenness.h"
#include "../include/vertex.h"
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/bfs.h"

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

/**
 *          E ---------- A
 *          |            |
 *          |            |
 *          F
 */
TEST_CASE("Simple Betweenness Centrality on Graph with Equal Edge Weights", "[betweenness]") {
  Graph g;

	Vertex* a = g.addVertex("0x1");
  Vertex* b = g.addVertex("0x2");
  Vertex* c = g.addVertex("0x3");
  Vertex* d = g.addVertex("0x4");
  Vertex* e = g.addVertex("0x5");
  Vertex* f = g.addVertex("0x6");

  g.addEdge(a, b, 1, 1, 1);
  g.addEdge(a, c, 1, 1, 1);
  g.addEdge(b, c, 1, 1, 1);
  g.addEdge(c, d, 1, 1, 1);
  g.addEdge(d, e, 1, 1, 1);
  g.addEdge(d, f, 1, 1, 1);
  g.addEdge(e, f, 1, 1, 1);

  unordered_map<string, double>* results = computeBetweennessCentrality(&g);

  REQUIRE( (*results)[c->getAddress()] == 6 );

  delete results;
}

TEST_CASE("Simple Betweenness Centrality 2", "[betweenness]") {
  Graph g;

  Vertex* a = g.addVertex("0x1");
  Vertex* b = g.addVertex("0x2");
  Vertex* c = g.addVertex("0x3");
  Vertex* d = g.addVertex("0x4");
  Vertex* e = g.addVertex("0x5");
  Vertex* f = g.addVertex("0x6");

  g.addEdge(a, b, 1, 1, 1);
  g.addEdge(a, e, 1, 1, 1);
  g.addEdge(e, f, 1, 1, 1);
  g.addEdge(f, c, 1, 1, 1);
  g.addEdge(b, c, 1, 1, 1);
  g.addEdge(b, d, 1, 1, 1);
  g.addEdge(d, c, 1, 1, 1);

  unordered_map<string, double>* results = computeBetweennessCentrality(&g);

  REQUIRE( (*results)[a->getAddress()] == 1.5 );

  delete results;
}
