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
using std::vector;
using std::string;
using std::pair;
using std::sort;

int main(int argc, char* argv[]) {
  string dataset_filepath, cc_addresses_filepath;
  bool should_run_bfs, should_run_dijkstra, verbose;
  int num_betweenness_to_print, num_threads;

  ArgumentParser ap;

  ap.add_argument("-f", true, &dataset_filepath, "The path to the dataset to load as a graph.");
  ap.add_argument("-b", false, &should_run_bfs, "Indicates whether or not to run BFS on the graph.");
  ap.add_argument("-d", false, &should_run_dijkstra, "Indicates whether or not to run Djikstra's on the graph.");
  ap.add_argument("-c", false, &num_betweenness_to_print, "Indicates the number of nodes to print the betweeness centrality of. Prints the BC of the k nodes with the largest BC.");
  ap.add_argument("-l", false, &cc_addresses_filepath, "The path to save addresses of the largest connected component. Does nothing if not specified.");
  ap.add_argument("-t", false, &num_threads, "The number of threads to use when computing betweenness centrality. Does nothing if not specified or if not running BC.");
  ap.add_argument("-v", false, &verbose, "Whether or not to print thread status when running code on multiple threads.");

  ap.parse(argc, argv);

  Graph* g = Graph::fromFile(dataset_filepath);
  Graph* largest_connected_component = NULL;
  std::cout << std::endl;

  // Run BFS if the CLI argument to do so was given
  if (should_run_bfs) {
    run_bfs(g);
  }

  // Find the largest connected component if the CLI argument to do so was given
  if (cc_addresses_filepath != "") {
    vector<Vertex*> cc = find_largest_component(g);

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

  // Compute betweenness centrality if the CLI argument to do so was given
  if (num_betweenness_to_print > 0) {
    std::cout << YELLOW << "Computing betweenness centrality on graph..." 
              << RESET << std::endl;
    unordered_map<string, double> bc = compute_betweenness_centrality(g, num_threads, verbose);
    std::cout << YELLOW << "Finished computing betweenness centrality on graph..." 
              << RESET << std::endl;

    vector<pair<string, double>> bc_heap;
    bc_heap.reserve(bc.size());

    for (pair<string, double> p : bc)
      bc_heap.push_back(p);
    sort(bc_heap.begin(), bc_heap.end(), compare_bc_pair);

    num_betweenness_to_print = 
      std::min(num_betweenness_to_print, static_cast<int>(bc_heap.size()));

    for (int i = 0; i < num_betweenness_to_print; ++i) {
      Vertex* node = g->getVertex(bc_heap[i].first);
      std::cout << BLUE << "Betweenness Centrality of Address "
                << bc_heap[i].first << " (" << node->getIncidentEdges().size()
                << " incident edges): " << bc_heap[i].second << RESET << std::endl;
    }

    std::ofstream of;
    string base_filepath = dataset_filepath.substr(0, dataset_filepath.size()-4);

    of.open(base_filepath +  + "_betweenness_centrality.csv");
    of << "address,incident_edges,betweenness_centrality" << std::endl;

    for (pair<string, double>& p : bc_heap) {
      Vertex* v = g->getVertex(p.first);
      of << v->getAddress() << "," << v->getIncidentEdges().size()
         << "," << p.second << std::endl;
    }
    
    of.close();
  }

  // Run Dijkstra's algorithm if the CLI argument to do so was given
  if (should_run_dijkstra) {
    Vertex* start = g->getVertices().begin()->second;
    std::cout << YELLOW << "Running Dijkstra's algorithm starting at vertex " 
              << "with address " << start->getAddress() << RESET << std::endl;
    dijkstra(g, start);
    std::cout << YELLOW << "Finished running Dijkstra's algorithm." << RESET << std::endl;
    saveDistances(g,"results/dijsktra_output.csv");
    std::cout << "Saved all shortest paths to results/dijsktra_output.csv" << std::endl;
  }

  if (largest_connected_component != NULL) {
    delete largest_connected_component;
  }

  delete g;
}
