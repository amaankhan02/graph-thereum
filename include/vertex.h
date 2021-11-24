#pragma once
#include <string>
#include <vector>
#include "edge.h"

/**
 * Predeclare the Edge class to resolve the circular dependency issue 
 * that arises out of our adjacency list graph implementation. The compiler 
 * needs to know the size of each type contained as members of the Vertex class. 
 * We are only using Edge*, so the exact size of Edge does not matter. This 
 * means we can predeclare the Edge class in the Vertex class header file and 
 * finish the implementation of the Edge class in its own respective header and 
 * implementation files. 
 */
class Edge;

/**
 * @brief This class represents an individual involed in a transaction. An 
 * individual is represented solely by their address on the blockchain and by 
 * the transactions they are involved in. Refer to the Edge class for more 
 * detail on how transactions are represented. 
 */
class Vertex {
  public:
    /**
     * @brief Construct a new Vertex object. By default Vertices are initialized 
     * with an empty list of indicent edges. 
     * 
     * @param address a string indicating the address of the individual that 
     * this Vertex represents. 
     */
    Vertex(const std::string& address);

    /**
     * @brief 
     * 
     * @param e an Edge* 
     */
    void addEdge(Edge* e);

    /**
     * @brief Get
     * 
     * @return const std::vector<Edge*>& 
     */
    const std::vector<Edge*>& getIncidentEdges() const;

    /**
     * @brief 
     * 
     * @return const std::string& 
     */
    const std::string& getAddress() const;

    /**
     * @brief Get whether or not this Vertex has been explored in some iteration 
     * of a graph algorithm. 
     * 
     * @return true if this Vertex HAS been explored in the current iteration of 
     * some graph algorithm.
     * @return false if this Vertex has NOT yet been explored in the current 
     * iteration of some graph algorithm.
     */
    bool wasExplored() const;

    /**
     * @brief Set the whether or not this Vertex has been explored in some 
     * iteration of a graph algorithm. 
     * 
     * @param explored a bool indicating the new exploration state of this 
     * Vertex.
     */
    void setExplored(bool explored);
  private: 
    /**
     * @brief 
     * 
     */
    std::string address_;

    /**
     * @brief 
     * 
     */
    std::vector<Edge*> incident_edges_;

    /**
     * @brief a bool state used by graph algorithms to track whether or not this 
     * Vertex has been explored in the current iteration of the algorithm. 
     */
    bool was_explored_;
};
