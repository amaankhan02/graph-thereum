#pragma once
#include "vertex.h"
#include "graph.h"
#include "edge.h"

/**
 * @brief 
 * 
 * @param g 
 * @param start 
 * @param end 
 * @return uint64_t 
 */
void dijkstra(Graph* g, Vertex* start);
