#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "edge.h"
#include "vertex.h"

class Graph {
  public:
    Graph();

    /**
     * @brief Destroy the Graph object by deleting all of the associated Vertex
     * objects and Edge objects allocated on the heap.
     */
    ~Graph();

    /**
     * @brief Adds an edge to the graph. If either the source Vertex of the Edge
     * does not already exist in the graph, the source Vertex is added. If the 
     * destination Vertex of the Edge does not already exist in the graph, the 
     * destination Vertex is added.  
     * 
     * @param e an Edge to add to the graph
     */
    void addEdge(Edge* e);

    std::vector<Vertex*> getAdjacentVertices(Vertex* v) const;

    const std::unordered_map<std::string, Vertex*>& getVertices() const { return vertices_; }

    const std::vector<Edge*>& getEdges() const { return edges_; }
  private:
    std::vector<Edge*> edges_;
    std::unordered_map<std::string, Vertex*> vertices_;
};