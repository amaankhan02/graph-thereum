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
  unordered_map<string, Vertex*>::const_iterator it = vertices_.find(address);
  return it == vertices_.end() ? NULL : it->second;
}

bool Graph::containsVertex(const std::string& address) const {
  return vertices_.find(address) != vertices_.end();
}

vector<Vertex*> Graph::getAdjacentVertices(Vertex* v) const {
  const vector<Edge*>& incident = v->getIncidentEdges();
  vector<Vertex*> adjacent(incident.size());

  for (size_t i = 0; i < adjacent.size(); ++i) {
    adjacent[i] = incident[i]->getAdjacentVertex(v);
  }

  return adjacent;
}

Graph* Graph::from_file(const std::string& path) {
  Graph* g = new Graph();

  std::ifstream infile(path);
  string line;

  if (infile.is_open()) {
    getline(infile, line); // skip the first line containing column names

    while (getline(infile, line)) {
      std::stringstream comma_separated(line);
      string csv_element;
      string to_address, from_address, value, gas, gas_price;

      getline(comma_separated, csv_element, ',');  // discard 0th element (pandas index)
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

      std::cout << gas << " " << gas_price << " " << value << std::endl; 

      Edge* transaction = new Edge(
        from, to, std::stod(value), std::stoll(gas), std::stoll(gas_price)
      );

      from->addEdge(transaction);
      to->addEdge(transaction);
    }
  }

  return g;
}

/*
,from_address,to_address,truncated_value,gas,gas_price
0,0xc1aced320a22ea96164fb660291900f9630fded5,0x80aa81029df9afdc70a621c86d7a81d7e9ed7e3a,10000000.0,800000,20000000000
1,0x9f6725c5fba117c5f27f5a31cbd902d4b3af6458,0x80aa81029df9afdc70a621c86d7a81d7e9ed7e3a,10000000.0,800000,20000000000
2,0x509c872654a041893531be535fea935e70fdb7ef,0x80aa81029df9afdc70a621c86d7a81d7e9ed7e3a,10000000.0,800000,20000000000
3,0x21d13cc5bc168a51d8469ed223e18d57f0bb9bd1,0x80aa81029df9afdc70a621c86d7a81d7e9ed7e3a,100000000.0,800000,20000000000
4,0xcc8c0432ad2d85991b4f4b5cf6e5209d6aeb2baa,0x80aa81029df9afdc70a621c86d7a81d7e9ed7e3a,10000000.0,800000,20000000000
5,0x026547975a4d16043a9effe63c079bca92087ac6,0x80aa81029df9afdc70a621c86d7a81d7e9ed7e3a,10000000.0,800000,20000000000
*/

// std::stoll, std::stod

/*
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
main() {
   string my_str = "ABC,XYZ,Hello,World,25,C++";
   vector<string> result;
   stringstream s_stream(my_str); //create string stream from the string
   while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      result.push_back(substr);
   }
   for(int i = 0; i<result.size(); i++) {    //print all splitted strings
      cout << result.at(i) << endl;
   }
}
*/

/*
unordered_map<string, size_t> counts;

	string line;
    ifstream infile (filename);

    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (counts.find(line) == counts.end()) counts.insert({line, 1});
            else counts[line] += 1;
        }
    }

    infile.close();
*/