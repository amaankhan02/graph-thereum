#include <iostream>

#include "include/argument_parser.h"
#include "include/graph.h"
#include "include/utils.h"
#include "include/bfs.h"

using std::string;

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

  Graph* g = Graph::from_file(filepath);
  std::cout << std::endl;

  if (should_run_bfs) {
    run_bfs(g);
  }

  delete g;
}
