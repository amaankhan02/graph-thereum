#include <iostream>

#include "include/edge.h"
#include "include/vertex.h"
#include "include/graph.h"

int main(int argc, char* argv[]) {
  Graph* g = Graph::from_file("data/data.csv");

  std::cout << "Edge is " << sizeof(Edge) << "B" << std::endl;
  std::cout << "Vertex is " << sizeof(Vertex) << "B" << std::endl;
  std::cout << "Graph is " << sizeof(Graph) << "B" << std::endl;

  std::cout << "Pointers are " << sizeof(void*) << "B" << std::endl;
  std::cout << "uint64_t is " << sizeof(uint64_t) << "B" << std::endl;

  delete g;
}