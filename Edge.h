#pragma once
#include <string>
#include "vertex.h"

class Vertex; 

class Edge {
  public:
    Edge(Vertex* source, Vertex* destination, uint64_t value, 
         uint64_t gas, uint64_t gas_price) 
      : source_(source), destination_(destination), value_(value), 
        gas_(gas), gas_price_(gas_price) {}

    /**
     * @brief Get a pointer to the Vertex adjacent to the passed Node.
     * 
     * @param start a pointer to a Vertex 
     * @return Vertex* the Vertex adjacent to the passed Vertex such that the 
     * two vertices are connected by this Edge object.
     */
    Vertex* getAdjacentVertex(Vertex* start) const;

    Vertex* getSource() const { return source_; }

    Vertex* getDestination() const { return destination_; }

    uint64_t getValue() const { return value_; }

    uint64_t getGas() const { return gas_; }

    uint64_t getGasPrice() const { return gas_price_; }
  private:
    Vertex* source_;
    Vertex* destination_;
    uint64_t value_;
    uint64_t gas_;
    uint64_t gas_price_;
};