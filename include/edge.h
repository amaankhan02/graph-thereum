#pragma once
#include <string>
#include "vertex.h"

/**
 * Predeclare the Vertex class to resolve the circular dependency issue 
 * that arises out of our adjacency list graph implementation. The compiler 
 * needs to know the size of each type contained as members of the Edge class. 
 * We are only using Vertex*, so the exact size of Vertex does not matter. This 
 * means we can predeclare the Vertex class in the Edge header file and finish 
 * the implementation of the Vertex class in its own respective header and 
 * implementation files. 
 */
class Vertex; 

/**
 * @brief This class represents a transaction between two individuals. This 
 * class stores the value exchanged in the transaction, the amount spent on gas (transaction fees) 
 * in order to complete the transaction, and the price of gas at the time of 
 * this transaction. Refer to the Vertex class for more details on how 
 * individuals are represented. 
 */
class Edge {
  public:
    /**
     * @brief Construct a new Edge object.
     * 
     * @param source a Vertex* indicating the source of the transaction
     * @param destination a Vertex* indicating the destination of the 
     * transaction
     * @param value a uint64_t indicating the value exchanged in the transaction
     * @param gas a uint64_t indicating the gas used in the transaction
     * @param gas_price a uint64_t indicating the price of gas at the time of 
     * the transaction
     */
    Edge(Vertex* source, Vertex* destination, uint64_t value, 
         uint64_t gas, uint64_t gas_price);

    /**
     * @brief Get a pointer to the Vertex adjacent to the passed Vertex. If the 
     * passed Vertex represents the source of the transaction that this Edge 
     * represents, this function returns a pointer to the Vertex that represents 
     * the destination of the transaction. If the passed Vertex is the 
     * destination of this transaction, the function will return a pointer to 
     * Vertex that represents the source of the transaction. Assumes that the 
     * passed vertex is indeed one of the endpoints of this edge
     * 
     * @param start a pointer to a Vertex 
     * @return a Vertex* representing the Vertex adjacent to the passed Vertex 
     * such that the two vertices are connected by this Edge object.
     */
    Vertex* getAdjacentVertex(Vertex* start) const;

    /**
     * @brief Get the get a pointer to the Vertex representing the source of 
     * this transaction that this Edge represents. 
     * 
     * @return a Vertex* representing the source of this transaction.
     */
    Vertex* getSource() const;

    /**
     * @brief Get the get a pointer to the Vertex representing the destination 
     * of this transaction that this Edge represents. 
     * 
     * @return a Vertex* representing the destination of this transaction.
     */
    Vertex* getDestination() const;

    /**
     * @brief Get the value exhanged as part of the transaction represented by 
     * this Edge.
     * 
     * @return a uint64_t that indicating the value exchanged in this 
     * transaction.
     */
    uint64_t getValue() const;

    /**
     * @brief Get the gas used as part of the transaction represented by 
     * this Edge.
     * 
     * @return a uint64_t indicating the gas used in this transaction.
     */
    uint64_t getGas() const;

    /**
     * @brief Get the gas price at the time that the transaction represented by 
     * this Edge took place.
     * 
     * @return a uint64_t indicating the price of gas at the time of this 
     * transaction.
     */
    uint64_t getGasPrice() const;

    /**
     * @brief Get whether or not this Edge has been explored in some iteration 
     * of a graph algorithm. 
     * 
     * @return true if this Edge HAS been explored in the current iteration of 
     * some graph algorithm.
     * @return false if this Edge has NOT yet been explored in the current 
     * iteration of some graph algorithm.
     */
    bool wasExplored() const;

    /**
     * @brief Set the whether or not this Edge has been explored in some 
     * iteration of a graph algorithm. 
     * 
     * @param explored a bool indicating the new exploration state of this Edge.
     */
    void setExplored(bool explored);
  private:
    /**
     * @brief a Vertex* indicating the source of the transaction that this Edge 
     * represents.
     */
    Vertex* source_;

    /**
     * @brief a Vertex* indicating the destination of the transaction that this 
     * Edge represents.
     */
    Vertex* destination_;

    /**
     * @brief a uint64_t indicating the value exchanged in the transaction that 
     * this Edge represents.
     */
    uint64_t value_;

    /**
     * @brief a uint64_t indicating the amount of gas used in the transaction
     * that this Edge represents.
     */
    uint64_t gas_;

    /**
     * @brief a uint64_t indicating the price of gas at the time of the 
     * transaction that this Edge represents.
     */
    uint64_t gas_price_;

    /**
     * @brief a bool state used by graph algorithms to track whether or not this 
     * Edge has been explored in the current iteration of the algorithm. 
     */
    bool was_explored_;
};
