#include "../include/bfs.h"
#include <queue>

using std::string;
using std::vector;
using std::queue;
using std::pair;

void bfs(Graph* g) {
  for (pair<string, Vertex*> p : g->getVertices()) {
    p.second->setExplored(false);
  }

  for (Edge* e : g->getEdges()) {
    e->setExplored(false);
  }

  for (pair<string, Vertex*> p : g->getVertices()) {
    if (!p.second->wasExplored()) {
      bfs(g, p.second);
    }
  }
}

void bfs(Graph* g, Vertex* start) {
  queue<Vertex*> q;
  start->setExplored(true);
  q.push(start);

  while (!q.empty()) {
    Vertex* v = q.front();
    q.pop();

    for (Edge* indicent : v->getIncidentEdges()) {
      Vertex* adjacent = indicent->getAdjacentVertex(v);
      if (!adjacent->wasExplored()) {
        // set indicent as discovery edge
        adjacent->setExplored(true);
        q.push(adjacent);
      } /*else if (indicent->wasExplored()) {
        // set indicent as cross edge
      } */
    }
  }
}