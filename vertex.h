#pragma once
#include <string>
#include <vector>
#include "edge.h"

class Edge;

class Vertex {
  public:
    Vertex();

    const std::vector<Edge*>& getIncidentEdges() const;

    const std::string& getAddress() const;
  private: 
    std::string address_;
    std::vector<Edge*> incident_edges_;
};

// std::stoll

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