#include "../include/graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::unordered_map;
using std::stringstream;
using std::make_pair;
using std::fstream;
using std::string;
using std::vector;
using std::pair;

Graph::Graph() { }

Graph::~Graph() {
  for (pair<string, Vertex*> v : vertices_) {
    delete v.second;
  }

  for (Edge* e : edges_) {
    delete e;
  }
}

void Graph::addEdge(Edge* e) {
  edges_.push_back(e);
}

void Graph::addVertex(Vertex* v) {
  vertices_.insert(make_pair(v->getAddress(), v));
}

Vertex* Graph::getVertex(const std::string& address) const {
  /// @todo we can speed this up and remove the NULL check if we trust that address is valid
  auto it = vertices_.find(address);
  return it == vertices_.end() ? NULL : it->second;
}

bool Graph::containsVertex(const std::string& address) const {
  return vertices_.find(address) != vertices_.end();
}

const unordered_map<string, Vertex*>& Graph::getVertices() const {
  return vertices_;
}

const vector<Edge*>& Graph::getEdges() const {
  return edges_;
}

Graph* Graph::from_file(const std::string& path) {
  Graph* g = new Graph();

  std::ifstream infile(path);
  string line;

  if (infile.is_open()) {
    getline(infile, line); // skip the first line containing column names

    while (getline(infile, line)) {
      std::stringstream comma_separated(line);
      string csv_element, to_address, from_address, value, gas, gas_price;

      getline(comma_separated, csv_element, ',');  // discard 0th index element
      getline(comma_separated, from_address, ','); // from_address
      getline(comma_separated, to_address, ',');   // to_address
      getline(comma_separated, value, ',');        // truncated_value
      getline(comma_separated, gas, ',');          // gas
      getline(comma_separated, gas_price, ',');    // gas_price

      Vertex* from = NULL;
      Vertex* to = NULL;

      if (g->containsVertex(from_address)) {
        from = g->getVertex(from_address);
      } else {
        from = new Vertex(from_address);
        g->addVertex(from);
      }

      if (g->containsVertex(to_address)) {
        to = g->getVertex(to_address);
      } else {
        to = new Vertex(to_address);
        g->addVertex(to);
      }

      Edge* transaction = new Edge(
        from, to, std::stod(value), std::stoull(gas), std::stoull(gas_price)
      );

      from->addEdge(transaction);
      to->addEdge(transaction);
      g->addEdge(transaction);
    }
  }

  std::cout << "Loaded " << g->getEdges().size() << " edges and "
            << g->getVertices().size() << " vertices." << std::endl;

  return g;
}
