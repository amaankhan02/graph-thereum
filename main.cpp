#include <iostream>

#include "edge.h"
#include "vertex.h"
#include "graph.h"

int main(int argc, char* argv[]) {
  Graph g;

  std::cout << "Edge is " << sizeof(Edge) << "B" << std::endl;
  std::cout << "Vertex is " << sizeof(Vertex) << "B" << std::endl;
  std::cout << "Graph is " << sizeof(Graph) << "B" << std::endl;

  std::cout << "Pointers are " << sizeof(void*) << "B" << std::endl;
  std::cout << "uint64_t is " << sizeof(uint64_t) << "B" << std::endl;
}