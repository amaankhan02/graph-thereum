#include <iostream>
#include <ctime>

#include "include/argument_parser.h"
#include "include/graph.h"
#include "include/utils.h"
#include "include/bfs.h"

using std::string;
using std::vector;

int main(int argc, char* argv[]) {
  string filepath;
  bool should_run_bfs, should_run_betweeness;

  ArgumentParser ap;

  ap.add_argument("-f", ArgumentParser::DataType::STRING, true, &filepath, 
                  "The path to the dataset to load as a graph.");
  ap.add_argument("-b", ArgumentParser::DataType::BOOL, false, &should_run_bfs,
                  "Indicates whether or not to run BFS on the graph.");
  ap.add_argument("-c", ArgumentParser::DataType::BOOL, false, &should_run_betweeness,
                  "Indicates whether or not to run betweeness centrality algorithms on the graph.");

  ap.parse(argc, argv);
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
