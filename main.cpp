#include <iostream>

#include "include/argument_parser.h"
#include "include/graph.h"
#include "include/utils.h"
#include "include/bfs.h"
#include "include/dijkstras.h"

using std::string;

int main(int argc, char* argv[]) {
  string filepath;
  bool should_run_bfs, should_run_betweeness, should_run_dijkstra;

  ArgumentParser ap;

  ap.add_argument("-f", true, &filepath, "The path to the dataset to load as a graph.");
  ap.add_argument("-b", false, &should_run_bfs, "Indicates whether or not to run BFS on the graph.");
  ap.add_argument("-d", false, &should_run_dijkstra, "Indicates whether or not to run Djikstra's on the graph.");
  ap.add_argument("-c", false, &should_run_betweeness, "Indicates whether or not to run betweeness centrality algorithms on the graph.");

  ap.parse(argc, argv);

  Graph* g = Graph::fromFile(filepath);
  std::cout << std::endl;

  if (should_run_bfs) {
    run_bfs(g);
  }

  if (should_run_dijkstra) {
    uint64_t answer = dijkstra(g);
    std::cout << "\n\nShortest path was " << answer << std::endl;
  }

  delete g;
}
