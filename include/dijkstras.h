#pragma once
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include <iostream>
#include <unordered_map>
#include <stack>

struct DijkstraResultsContainer {
  uint64_t distance_;
  double centrality_;
  std::vector<Vertex*> parents_;
  double dependency_;

  DijkstraResultsContainer() : distance_(0), centrality_(0.0), parents_(), dependency_(0.0) {}
};

struct DijkstraResults {
  Vertex* start_node_;
  std::unordered_map<std::string, DijkstraResultsContainer> results_;
  std::stack<Vertex*> distance_ordered_vertices_;

  DijkstraResults(Vertex* start) 
    : start_node_(start), results_(), distance_ordered_vertices_() { }
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