#include <iostream>
#include <ctime>

#include "include/graph.h"
#include "include/utils.h"
#include "include/bfs.h"
#include "include/cli.h"

using std::string;

int main(int argc, char* argv[]) {
  CLI arguments(argc, argv, {{"-f", CLI::DataType::STRING},
                             {"-b", CLI::DataType::BOOL}});
  clock_t c1, c2;

  std::cout << "Loading graph..." << std::endl;
  c1 = clock();
  Graph* g = Graph::from_file(*static_cast<string*>(arguments.get("-f")));
  c2 = clock();
  print_elapsed(c1, c2, "loading graph from csv");

  std::cout << std::endl;

  if (*static_cast<bool*>(arguments.get("-b"))) {
    run_bfs(g);
  }

  delete g;
}
