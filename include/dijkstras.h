#pragma once
#include "vertex.h"
#include "graph.h"
#include "edge.h"
#include <iostream>
#include <fstream>


/**
 * @brief Marks all vertices in g with the shortest distance to them, beginning at start
 * 
 * @param g graph upon which the algorithm should be run
 * @param start the start vertex from which we are calculating all distances
 * @return nothing, changes distance_ of g's vertices
 */
void dijkstra(Graph* g, Vertex* start);

/**
 * @brief After running above dijkstra, is used to write all vertex distances into a csv file
 * 
 * @param g 
 */
void saveDistances(Graph* g, std::string distances_filepath);