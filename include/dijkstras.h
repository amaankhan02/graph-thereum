#pragma once
#include "vertex.h"
#include "graph.h"
#include <string>

/**
 * @brief Run Dijkstra's algorithm to find the shortest path from a single 
 * source vertex. This function will mark all of the vertices in the passed 
 * graph with the shortest distance to the vertex from the given starting 
 * vertex. It will also save each vertex' predecessor in the shortest path to 
 * the vertex so that the shortest path to some arbitary vertex may be recovered 
 * by backtracking to the starting vertex.
 * 
 * @param g a Graph* indicating the graph with which to find the shortest path 
 * from the given starting vertex to all other vertices in the graph.
 * @param start a Vertex* indicating the start vertex from which we are find all 
 * of the shortest paths to all other nodes in the given graph.
 */
void dijkstra(Graph* g, Vertex* start);

/**
 * @brief Saves the distance to each vertex in the given graph to the file 
 * indicated in the second parameter. This function assumes that Dijkstra's 
 * algorithm to comute the shortest path from one vertex to all other vertices
 * in a graph has been run upon the passed graph.
 * 
 * @param g a Graph* indicating the graph with which, for all vertices in the 
 * graph, to save the distances from some starting vertex to the current vertex.
 */
void saveDistances(Graph* g, std::string distances_filepath);