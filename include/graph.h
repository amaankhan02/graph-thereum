#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "vertex.h"
#include "edge.h"

/**
 * @brief A collection of edges and vertices. This class uses an adjacency list
 * graph implementation. Vertices are indexed by their associated blockchain 
 * address in the unordered map used to store all vertices. Edges are simply 
 * stored in a vector with arbitrary ordering.
 */
class Graph {
  public:
    /**
     * @brief Construct a new Graph object. The graph starts with no edges and 
     * no vertices.
     */
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

    /**
     * @brief Adds a vertex to the graph.
     * 
     * @param v a Vertex to add to the graph.
     */
    void addVertex(Vertex* v);

    /**
     * @brief Get the vertex associated with the passed address.
     * 
     * @param address a string indicating the blockchain address with which to 
     * search for the associated vertex in this graph.
     * @return a Vertex* representing the individual associated with the passed 
     * address. If the vertex does not exist in the graph, returns NULL.
     */
    Vertex* getVertex(const std::string& address) const;

    /**
     * @brief Check if the graph contains a vertex associated with the passed 
     * address.
     * 
     * @param address a string indicating the blockchain address with which to 
     * search for the associated vertex in this graph.
     * @return true if this graph CONTAINS a vertex associated with the passed 
     * address.
     * @return false if this graph DOES NOT contain a vertex associated with the
     * passed address.
     */
    bool containsVertex(const std::string& address) const;

    /**
     * @brief Get all the vertices in this graph.
     * 
     * @return a std::unordered_map<std::string, Vertex*> containing all the
     * vertices in this graph, indexed by the associated blockchain addresses.
     */
    const std::unordered_map<std::string, Vertex*>& getVertices() const;

    /**
     * @brief Get all the edges in this graph.
     * 
     * @return a std::vector<Edge*> containing all the edges in this graph, 
     * indexed arbitrarily.
     */
    const std::vector<Edge*>& getEdges() const;

    /**
     * @brief Constructs a Graph with all edges and vertices allocated on the 
     * heap by loading etherium transactions from a CSV file. CSV records are 
     * formatted as follows:
     * 
     * idx,from_address,to_address,truncated_value,gas,gas_price
     * 
     * @param path a string indicating the path to the CSV file to load.
     * @return Graph* a graph constructed from the data in the CSV file.
     */
    static Graph* from_file(const std::string& path);
  private:
    /**
     * @brief A collection of all the edges in this graph in an arbitrary order.
     */
    std::vector<Edge*> edges_;

    /**
     * @brief A collection of all the vertices in this graph ordered by their 
     * associated address in the etherium blockchain.
     */
    std::unordered_map<std::string, Vertex*> vertices_;
};
