#include <iostream>
#include <ctime>

#include "include/graph.h"
#include "include/utils.h"
#include "include/bfs.h"
#include "include/cli.h"

using std::string;
using std::vector;

int main(int argc, char* argv[]) {
  string filepath;
  bool should_run_bfs;

  vector<CLI::ArgumentConfig> acs = {
      CLI::ArgumentConfig("-f", CLI::DataType::STRING, true, &filepath,
                          "The path to the dataset to load as a graph."),
      CLI::ArgumentConfig("-b", CLI::DataType::BOOL, false, &should_run_bfs,
                          "Indicates whether or not to run BFS on the graph."),
  };

  CLI::parse_args(argc, argv, acs);
  clock_t c1, c2;

  std::cout << "Loading graph..." << std::endl;
  c1 = clock();
  Graph* g = Graph::from_file(filepath);
  c2 = clock();
  print_elapsed(c1, c2, "loading graph from csv");

  std::cout << std::endl;

  if (should_run_bfs) {
    run_bfs(g);
  }

  delete g;
}
