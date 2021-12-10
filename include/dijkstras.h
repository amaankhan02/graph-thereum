#pragma once
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include <iostream>
#include <unordered_map>
#include <stack>

/**
 * @brief 
 * 
 * @param g 
 * @return uint64_t 
 */
uint64_t dijkstra(Graph* g);

/**
 * @brief 
 * 
 * @param g 
 * @param start 
 * @param end 
 * @return uint64_t 
 */
void dijkstra(Graph* g, Vertex* start);
