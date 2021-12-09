#pragma once
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include <iostream>
#include <unordered_map>

struct DijkstraResultsContainer {
  uint64_t distance_;
  double centrality_;
  std::vector<Vertex*> parents_;

  DijkstraResultsContainer() : distance_(), centrality_(), parents_() { }
};

struct DijkstraResults {
  Vertex* start_node_;
  std::unordered_map<std::string, DijkstraResultsContainer> results_;

  DijkstraResults(Vertex* start) : start_node_(start), results_() { }
};

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
DijkstraResults* dijkstra(Graph* g, Vertex* start);