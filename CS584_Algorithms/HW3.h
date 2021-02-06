#include "Node.h"
#include <iostream>
#include <cmath>
#include <vector>

#pragma once

using namespace std;

class HW3 {
  float fastSquare (float a, float n);

  int fastSquare2 (int a, int n);

  Node* dfsVisit (Node* u);

  void printCycle (Node* u);

  void DFS (vector<Node*> G);

  void test ();
};