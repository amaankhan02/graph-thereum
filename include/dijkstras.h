#pragma once
#include "graph.h"
#include "vertex.h"

/**
 * @brief 
 * 
 * @param g 
 * @return uint64_t 
 */
uint64_t djikstra(Graph* g);

/**
 * @brief 
 * 
 * @param g 
 * @param start 
 * @param end 
 * @return uint64_t 
 */
uint64_t djikstra(Graph* g, Vertex* start, Vertex* end);