#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "include/argument_parser.h"
#include "include/betweenness.h"
#include "include/dijkstras.h"
#include "include/graph.h"
#include "include/utils.h"
#include "include/bfs.h"

using std::priority_queue;
using std::unordered_map;
using std::make_heap;
using std::vector;
using std::string;
using std::pair;

int main(int argc, char* argv[]) {
  string dataset_filepath, cc_addresses_filepath;
  bool should_run_bfs, should_run_dijkstra;
  int num_betweenness_to_print;

  ArgumentParser ap;

  ap.add_argument("-f", true, &dataset_filepath, "The path to the dataset to load as a graph.");
  ap.add_argument("-b", false, &should_run_bfs, "Indicates whether or not to run BFS on the graph.");
  ap.add_argument("-d", false, &should_run_dijkstra, "Indicates whether or not to run Djikstra's on the graph.");
  ap.add_argument("-c", false, &num_betweenness_to_print, "Indicates the number of nodes to print the betweeness centrality of. Prints the BC of the k nodes with the largest BC.");
  ap.add_argument("-l", false, &cc_addresses_filepath, "The path to save addresses of the largest connected component. Does nothing if not specified.");

  ap.parse(argc, argv);

  Graph* g = Graph::fromFile(dataset_filepath);
  Graph* largest_connected_component = NULL;
  std::cout << std::endl;

  if (should_run_bfs) {
    run_bfs(g);
  }

  if (cc_addresses_filepath != "") {
    vector<Vertex*> cc = get_largest_component(g);

    std::cout << YELLOW << "The largest connected component contains " 
              << cc.size() << " vertices." << RESET << std::endl;

    largest_connected_component = Graph::fromVertexList(cc);

    std::cout << YELLOW << "The new graph produced using the largest connected" 
              << " component consists of " 
              << largest_connected_component->getVertices().size() 
              << " vertices and "
              << largest_connected_component->getEdges().size() << " egdes."
              << RESET << std::endl;

    std::ofstream of;
    of.open(cc_addresses_filepath);
    of << ",from_address,to_address,truncated_value,gas,gas_price" << std::endl;

    for (Edge* e : largest_connected_component->getEdges()) {
      of << "," << *e << std::endl;
    }

    std::cout << GREEN << "Saved the largest connected component as a CSV to " 
              << cc_addresses_filepath << "." << RESET << std::endl;

    of.close();
  }

  if (num_betweenness_to_print > 0) {
    std::cout << YELLOW << "Computing betweenness centrality on graph..." 
              << RESET << std::endl;
    unordered_map<string, double> bc = compute_betweenness_centrality(g);
    std::cout << YELLOW << "Finished computing betweenness centrality on graph..." 
              << RESET << std::endl;

    vector<pair<string, double>> bc_heap;
    for (pair<string, double> p : bc)
      bc_heap.push_back(p);

    make_heap(bc_heap.begin(), bc_heap.end(), compare_bc_heap); 

    for (int i = 0; i < num_betweenness_to_print; ++i) {
      std::cout << BLUE << "Betweenness Centrality of Address " 
                << bc_heap[i].first << ": " << bc_heap[i].second << RESET << std::endl;
    }
  }

  if (should_run_dijkstra) {
//    uint64_t answer = dijkstra(g);
    uint64_t answer = 0;
    std::cout << "\n\nShortest path was " << answer << std::endl;
  }

  if (largest_connected_component != NULL) {
    delete largest_connected_component;
  }

  delete g;
}
