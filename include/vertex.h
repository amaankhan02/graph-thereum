#pragma once
#include <string>
#include <vector>
#include "edge.h"

/**
 * @brief Predeclare the Edge class to resolve the circular dependency issue
 * that arises out of our adjacency list graph implementation. The compiler 
 * needs to know the size of each type contained as members of the Vertex class. 
 * We are only using Edge*, so the exact size of Edge does not matter. This 
 * means we can predeclare the Edge class in the Vertex class header file and 
 * finish the implementation of the Edge class in its own respective header and 
 * implementation files. 
 */
class Edge;

/**
 * @brief This class represents an individual involved in a transaction. An 
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
     * @brief Adds a new edge to the list of incident edges. Assumed to be used 
     * safely (edge should border this vertex, and not already exist).
     * 
     * @param e an Edge* to be added as an incident edge to this vertex.
     */
    void addEdge(Edge* e);

    /**
     * @brief Gets all incident edges to this vertex. Each indicent edge 
     * represents a transaction that the person represented by this Vertex was
     * involved in.
     * 
     * @return const std::vector<Edge*>& the edges indicident to this Vertex.
     */
    const std::vector<Edge*>& getIncidentEdges() const;

    /**
     * @brief Returns the blockchain address of the person represented by this 
     * Vertex.
     * 
     * @return a const std::string& indicating the address of the person that 
     * this Vertex represents.
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

    /**
     * @brief Set the distance from some other arbitary Vertex. Used in the 
     * implementation of Dijkstra's algorithm to find the shortest path between
     * two vertices. 
     * 
     * @param distance a uint64_t with which to update the distance.
     */
    void setDistance(uint64_t distance);

    /**
     * @brief Get the distance from some other arbitary Vertex. Used in the 
     * implementation of Dijkstra's algorithm to find the shortest path between
     * two vertices. 
     * 
     * @return a uint64_t used in the implementation of Dijkstra's algorithm to 
     * find the shortest path between two vertices.
     */
    uint64_t getDistance() const;

    Vertex* getParent() const;

    void setParent(Vertex* parent);

    void addCentralityParent(Vertex* parent);

    void incrementCentrality(double amount);

    double getCentrality() const;

    void incrementDependency(double amount);

    double getDependency() const;

    const std::vector<Vertex*>& getCentralityParents() const;

    void reset();
  private: 
    /**
     * @brief The blockchain address of the person represented by this 
     * Vertex.
     */
    std::string address_;

    /**
     * @brief All of the edges that are indicident to this Vertex. Each indicent 
     * edge represents a transaction that the person represented by this Vertex 
     * was involved in.
     */
    std::vector<Edge*> incident_edges_;

    /**
     * @brief A bool state used by graph algorithms to track whether or not this 
     * Vertex has been explored in the current iteration of the algorithm. 
     */
    bool was_explored_;

    /**
     * @brief A uint64_t used in the implementation of Dijkstra's algorithm to 
     * find the shortest path between two vertices.
     */
    uint64_t distance_; 

    /**
     * @brief
     */
    Vertex* parent_;

    /**
     * @brief
     */
    std::vector<Vertex*> centrality_parents_;

    /**
     * @brief
     */
    double centrality_;

    /**
     * @brief
     */
    double dependency_;
};

/**
 * @brief
 */
struct MyComparator {
  /**
   * @brief Compares the distance parameters of two Vertex objects. This
   * operator is used by the priority queue in the implementation of
   * Dijkstra's algorithm to find the shortest path between two vertices.
   *
   * @param arg1 one of the Vertex objects with which to compare distances with.
   * @param arg2 the other Vertex object with which to compare distances with.
   *
   * @return true if arg1 has a larger distance than arg2.
   * @return false if arg1 has a smaller distance than arg2.
   */
  bool operator() (Vertex* arg1, Vertex* arg2) {
    return (arg1->getDistance() > arg2->getDistance());
  }
};
