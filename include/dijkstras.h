#pragma once
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include <queue>


uint64_t djikstra(Graph* g);


uint64_t djikstra_helper(Graph* g, Vertex* start, Vertex* end);