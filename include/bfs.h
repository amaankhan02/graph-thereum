#pragma once
#include "graph.h"
#include "vertex.h"

/**
 * @brief Perform breadth first search upon all connected compontents within the
 * passed graph. 
 * 
 * @param g a Graph* to perform the search upon
 * @return an int indicating the number of connected components in the graph.
 */
int bfs(Graph* g);

/**
 * @brief Perform breadth first search upon all connected compontents within the
 * passed graph starting at the passed Vertex.
 * 
 * @param g a Graph* to perform the search upon
 * @param start the Vertex* to begin the search from
 */
void bfs(Graph* g, Vertex* start);

/**
 * @brief Perform breadth first search upon all connected compontents within the
 * passed graph and print out the CPU running time of the algorithm along with
 * sanity checks to indicate that the search visits all vertices and edges.
 * 
 * @param g a Graph* to perform the search upon
 */
void run_bfs(Graph* g);
