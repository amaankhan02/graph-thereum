#include <iostream>
#include "include/graph.h"
#include "include/bfs.h"

int main(int argc, char* argv[]) {
  Graph* g = Graph::from_file("data/data.csv");

  run_bfs(g);

  delete g;
}
