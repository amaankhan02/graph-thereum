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
     * @brief Construct a new Graph object by making a deep copying of the 
     * passed Graph object. This deep copy includes making deep copies of all 
     * owned Edge and Vertex objects.
     * 
     * @param other a Graph to take a deep copy of.
     */
    Graph(const Graph& other);

    /**
     * Assignment operator for a Graph.
     *
     * @param rhs The right hand side of the assignment statement.
     * @return A reference for performing chained assignments.
     */
    const Graph& operator=(const Graph& rhs);

    /**
     * @brief Destroy the Graph object by deleting all of the associated Vertex
     * objects and Edge objects allocated on the heap.
     */
    ~Graph();

    /**
     * @brief Construct a new Edge object and adds it to the graph. Adds the 
     * edge to both the source and destination's incident edges list.
     * 
     * @param source a Vertex* indicating the source of the transaction.
     * @param destination a Vertex* indicating the destination of the 
     * transaction.
     * @param value a double indicating the value exchanged in the transaction 
     * in the trillions (multiply by 10^12 to get the actual value).
     * @param gas a uint64_t indicating the gas used in the transaction.
     * @param gas_price a uint64_t indicating the price of gas at the time of 
     * the transaction.
     * @return an Edge* pointing to the newly created Edge.
     */
    Edge* addEdge(Vertex* source, Vertex* destination, double value, 
                  uint64_t gas, uint64_t gas_price); 

    /**
     * @brief Construct a new Vertex object and adds it to the graph. By default 
     * Vertices are initialized with an empty list of indicent edges. 
     * 
     * @param address a string indicating the address of the individual that 
     * this Vertex represents. 
     * @return a Vertex* pointing to the newly created Vertex.
     */
    Vertex* addVertex(const std::string& address);

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
    static Graph* fromFile(const std::string& path);
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

    /**
     * @brief Delete all of the associated Vertex objects and Edge objects 
     * that are allocated on the heap.
     */
    void _delete();

    /**
     * @brief Create a deep copy of the passed Graph object and of all of the 
     * associated Vertex objects and Edge objects allocated on the heap.
     * 
     * @param other a Graph to take a deep copy of.
     */
    void _copy(const Graph& other);
};
