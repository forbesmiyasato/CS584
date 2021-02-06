#pragma once
#include "Node.h"

class HW4 {

public:
  void dfsVisit (Node* u, vector<Node*>& sortedNodes);
  vector<Node*> topologicalSort (vector<Node*> G);
  bool checkIfDAGSemiConnected ();
  int longestRepeatedSubString (string str);
  int LFBCS (string str);
  void test ();
};