#pragma once

#include <iostream>
#include <future>
#include <map>

#include "graph.h"
#include "edge.h"
#include "vertex.h"

/**
 * @brief 
 * 
 * @param graph 
 * @return std::unordered_map<std::string, double> 
 */
std::unordered_map<std::string, double> compute_betweenness_centrality(Graph* graph, int num_threads, bool verbose);

/**
 * @brief 
 * 
 * @param graph 
 * @return std::unordered_map<std::string, double> 
 */
std::unordered_map<std::string, double> compute_betweenness_centrality(Graph* graph);

/**
 * @brief
 *
 * @param graph
 * @return std::unordered_map<std::string, double>
 */
std::unordered_map<std::string, double> compute_betweenness_centrality_parallel(
    Graph* graph, int num_threads=4, bool verbose=false);

/**
 * @brief
 *
 * @param thread_result
 * @param graph
 * @param thread_index
 * @param num_threads
 */
void compute_betweenness_centrality_parallel_helper(
    std::promise<std::unordered_map<std::string, double>> thread_result,
    Graph* graph, int thread_index, int num_threads, bool verbose);
