#include "HW3.h"

using namespace std;

float HW3::fastSquare (float a, float n) {
  if (n == 1) {
    return a * a;
  }
  else {
    float a1 = (int)(a / (pow (10, n / 2)));
    float a2 = fmod (a, (pow (10, n / 2)));
    float x = fastSquare (a1, n / 2);
    float y = fastSquare (a2, n / 2);
    float z = fastSquare (a1 - a2, n / 2);
    float m = x + y - z;
    return x * pow (10, n) + m * pow (10, n / 2) + y;
  }
}

int HW3::fastSquare2 (int a, int n) {
  if (n == 1) {
    return a * a;
  }
  else {
    int m = n / 3;
    int a1 = a / (pow (10, 2 * m));
    int a2 = a % (int)(pow (10, 2 * m)) / (int)(pow (10, m));
    int a3 = a % (int)(pow (10, 2 * m)) % (int)(pow (10, m));
    int x = fastSquare2 (a1, m);
    int y = fastSquare2 (a2, m);
    int z = fastSquare2 (a3, m);
    int u = fastSquare2 (a1 - a2, m);
    int v = fastSquare2 (a1 - a3, m);
    int w = fastSquare2 (a2 - a3, m);
    int r = x + y - u;
    int s = x + y + z - v;
    int t = y + z - w;

    return x * (int)(pow (10, 4 * m)) + r * (int)(pow (10, 3 * m)) + s * (int)(pow (10, 2 * m)) + t * (int)(pow (10, m)) + z;
  }
}

Node* HW3::dfsVisit (Node* u) {
  u->color = GRAY;
  for (auto v : u->adj) {
    if (v->color == WHITE) {
      v->parent = u;
      Node* repeatNode = dfsVisit (v);
      if (repeatNode != NULL) {
        return repeatNode;
      }
    }
    else if (v->color == GRAY && u->parent != v) {
      v->parent = u;
      return v;
    }
  }
  return NULL;
}

void HW3::printCycle (Node* u) {
  Node* traverse = u;
  cout << u->name << " ";
  traverse = u->parent;
  while (traverse != u) {
    cout << traverse->name << " ";
    traverse = traverse->parent;
  }
  cout << u->name << endl;
}

void HW3::DFS (vector<Node*> G) {
  for (auto u : G) {
    if (u->color == WHITE) {
      Node* repeatNode = dfsVisit (u);
      if (repeatNode != NULL) {
        printCycle (repeatNode);
        break;
      }
    }
  }
}

void HW3::test () {
  cout << "1234^2 = " << fastSquare (111.111, 4) << endl;
  cout << "123^2 = " << fastSquare2 (578, 3) << endl;

  vector<Node*> G;

  Node* n1 = new Node (1);
  Node* n2 = new Node (2);
  Node* n3 = new Node (3);
  Node* n4 = new Node (4);
  Node* n5 = new Node (5);
  Node* n6 = new Node (6);
  Node* n7 = new Node (7);
  Node* n8 = new Node (8);
  Node* n9 = new Node (9);
  Node* n10 = new Node (10);

  n1->adj.push_back (n2);
  n1->adj.push_back (n3);
  n2->adj.push_back (n1);
  n3->adj.push_back (n1);
  n3->adj.push_back (n4);
  n3->adj.push_back (n7);
  n4->adj.push_back (n8);
  n4->adj.push_back (n3);
  n4->adj.push_back (n5);
  n5->adj.push_back (n4);
  n5->adj.push_back (n6);
  n6->adj.push_back (n5);
  n6->adj.push_back (n7);
  n6->adj.push_back (n9);
  n6->adj.push_back (n10);
  n7->adj.push_back (n6);
  n7->adj.push_back (n3);
  n8->adj.push_back (n4);

  G.push_back (n1);
  G.push_back (n2);
  G.push_back (n3);
  G.push_back (n4);
  G.push_back (n8);
  G.push_back (n5);
  G.push_back (n6);
  G.push_back (n7);

  DFS (G);
}