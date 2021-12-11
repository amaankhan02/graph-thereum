#include "catch.hpp"
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
 * All Edge Weights are 1:
 * 
 *        A               E
 *        | \           / |
 *        |  \         /  | 
 *        |   C ----- D   |
 *        |  /         \  |
 *        | /           \ |
 *        B               F
 * 
 * Betweenness Centrality of Each Vertex and Amount Each Path Contributes:
 *      - A: 0.0
 *          - A is not a central node in any shortest paths
 *      - B: 0.0
 *          - B is not a central node in any shortest paths
 *      - C: 6.0
 *          - A --> C --> D --> E (+1.0)
 *          - A --> C --> D --> F (+1.0)
 *          - A --> C --> D       (+1.0)
 *          - B --> C --> D --> E (+1.0)
 *          - B --> C --> D --> F (+1.0)
 *          - B --> C --> D       (+1.0)
 *      - D: 6.0
 *          - A --> C --> D --> E (+1.0)
 *          - A --> C --> D --> F (+1.0)
 *          - A --> C --> D       (+1.0)
 *          - B --> C --> D --> E (+1.0)
 *          - B --> C --> D --> F (+1.0)
 *          - B --> C --> D       (+1.0)
 *      - E: 0.0
 *          - E is not a central node in any shortest paths
 *      - F: 0.0
 *          - F is not a central node in any shortest paths
 *
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

  unordered_map<string, double> results = compute_betweenness_centrality(&g);

  REQUIRE( results[a->getAddress()] == 0.0 );
  REQUIRE( results[b->getAddress()] == 0.0 );
  REQUIRE( results[c->getAddress()] == 6.0 );
  REQUIRE( results[d->getAddress()] == 6.0 );
  REQUIRE( results[e->getAddress()] == 0.0 );
  REQUIRE( results[f->getAddress()] == 0.0 );
}

/**
 * All Edge Weights are 1:
 *
 *         E ---- A
 *         |      |
 *         |      |
 *         F      B
 *          \   /   \
 *           \ /     \
 *            C ----- D
 *
 * Betweenness Centrality of Each Vertex and Amount Each Path Contributes:
 *      - A: 1.5
 *          - E --> A --> B --> D (+0.5)
 *          - E --> F --> C --> D (+0.0)
 *          - E --> A --> B       (+1.0)
 *      - B: 2.5
 *          - E --> A --> B --> D (+0.5)
 *          - E --> F --> C --> D (+0.0)
 *          - A --> B --> C       (+1.0)
 *          - A --> B --> D       (+1.0)
 *      - C: 2.5
 *          - E --> F --> C --> D (+0.5)
 *          - E --> A --> B --> D (+0.0)
 *          - F --> C --> D       (+1.0)
 *          - F --> C --> B       (+1.0)
 *      - D: 0.0
 *          - D is not a central node in any shortest paths
 *      - E: 1.0
 *          - F --> E --> A       (+1.0)
 *      - F: 1.5
 *          - E --> F --> C       (+1.0)
 *          - E --> F --> C --> D (+0.5)
 *          - E --> A --> B --> D (+0.0)
 *
 */
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

  unordered_map<string, double> results = compute_betweenness_centrality(&g);

  REQUIRE( results[a->getAddress()] == 1.5 );
  REQUIRE( results[b->getAddress()] == 2.5 );
  REQUIRE( results[c->getAddress()] == 2.5 );
  REQUIRE( results[d->getAddress()] == 0.0 );
  REQUIRE( results[e->getAddress()] == 1.0 );
  REQUIRE( results[f->getAddress()] == 1.5 );
}

/**       4
 *    E ----- A
 *    |       |
 *  8 |       | 6
 *    |       |
 *    F       B
 *    \     /  \
 *  16 \ 12/    \ 1
 *      \ /      \
 *       C ------ D
 *           1
 */
TEST_CASE("Betweenness Centrality on Weighted Graph (unequal edge weights)", "[betweenness]") {
  Graph g;

  Vertex* a = g.addVertex("0x1");
  Vertex* b = g.addVertex("0x2");
  Vertex* c = g.addVertex("0x3");
  Vertex* d = g.addVertex("0x4");
  Vertex* e = g.addVertex("0x5");
  Vertex* f = g.addVertex("0x6");

  g.addEdge(a, b, 1, 6, 1);
  g.addEdge(a, e, 1, 4, 1);
  g.addEdge(e, f, 1, 8, 1);
  g.addEdge(f, c, 1, 16, 1);
  g.addEdge(b, c, 1, 12, 1);
  g.addEdge(b, d, 1, 1, 1);
  g.addEdge(d, c, 1, 1, 1);

  unordered_map<string, double> results = compute_betweenness_centrality(&g);

  REQUIRE( results[a->getAddress()] == 3.5);
  REQUIRE( results[b->getAddress()] == 4.0 );
  REQUIRE( results[c->getAddress()] == 1.5 );
  REQUIRE( results[d->getAddress()] == 3.5 );
  REQUIRE( results[e->getAddress()] == 1.5 );
  REQUIRE( results[f->getAddress()] == 0.0 );
}
