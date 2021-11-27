#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "vertex.h"
#include "edge.h"

class Graph {
  public:
    Graph();

    /**
     * @brief Destroy the Graph object by deleting all of the associated Vertex
     * objects and Edge objects allocated on the heap.
     */
    ~Graph();

    /**
     * @brief Adds an edge to the graph.
     * 
     * @param e an Edge to add to the graph.
     */
    void addEdge(Edge* e);

    void addVertex(Vertex* v);

    Vertex* getVertex(const std::string&) const;

    bool containsVertex(const std::string& address) const;

    const std::unordered_map<std::string, Vertex*>& getVertices() const;

    const std::vector<Edge*>& getEdges() const;

    static Graph* from_file(const std::string& path);
  private:
    std::vector<Edge*> edges_;
    std::unordered_map<std::string, Vertex*> vertices_;
};
