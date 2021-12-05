#pragma once
#include "graph.h"
#include "edge.h"
#include "vertex.h"
// #include "vertexp.h"
#include <iostream>


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
uint64_t dijkstra(Graph* g, Vertex* start, Vertex* end);