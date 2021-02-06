#include "HW4.h"
#include <iostream>
#include <algorithm>

using namespace std;

void HW4::dfsVisit (Node* u, vector<Node*> &sortedNodes) {
  u->color = GRAY;
  for (auto v : u->adj) {
    if (v->color == WHITE) {
      dfsVisit (v, sortedNodes);
    }
  }
  sortedNodes.push_back (u);
}

vector<Node*> HW4::topologicalSort (vector<Node*> G) {
  vector<Node*> sortedNodes;

  for (auto u : G) {
    if (u->color == WHITE) {
      dfsVisit (u, sortedNodes);
    }
  }

  return sortedNodes;
}

int HW4::longestRepeatedSubString (string str) {
  int n = str.length ();
  vector<vector<int>> dp (n + 1, vector<int> (n + 1, 0));
  int max = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (str[i - 1] == str[j - 1] && dp[i - 1][j - 1] < (j - i)) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        max = std::max(dp[i][j], max);
      }
    }
  }

  return max;
}

int HW4::LFBCS (string str) {
  int n = str.length ();
  vector<vector<int>> dp (n + 1, vector<int> (n + 1, 0));
  int max = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = n - 1; j >= i; j--) {
      if (str[i - 1] == str[j]) {
        dp[i][j] = dp[i - 1][j + 1] + 1;
        max = std::max (dp[i][j], max);
      }
    }
  }

  return max;
}

bool HW4::checkIfDAGSemiConnected ()
{
  vector<Node*> G;
  vector<Node*> sortedNodes;

  Node* n0 = new Node (0);
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

  n0->adj.push_back (n1);
  n0->adj.push_back (n3);
  n0->adj.push_back (n4);
  n1->adj.push_back (n2);
  n1->adj.push_back (n3);
  n2->adj.push_back (n3);
  n3->adj.push_back (n4);
  n3->adj.push_back (n5);
  n4->adj.push_back (n5);
  n5->adj.push_back (n0);

  G.push_back (n0);
  G.push_back (n1);
  G.push_back (n2);
  G.push_back (n3);
  G.push_back (n4);
  G.push_back (n5);

  sortedNodes = topologicalSort (G);

  reverse (sortedNodes.begin (), sortedNodes.end ());
  for (auto it : sortedNodes) {
    cout << it->name << " ";
  }
  cout << endl;

  for (int i = 0; i < sortedNodes.size () - 1; i++) {
    vector<Node*> adjVertices = sortedNodes[i]->adj;
    int name = sortedNodes[i]->name;
    if (std::find (adjVertices.begin (), adjVertices.end (), sortedNodes[i + 1]) == adjVertices.end ()) {
      return false;
    }
  }

  return true;
}

void HW4::test () {
  cout << longestRepeatedSubString ("abcdefg") << endl;
  cout << longestRepeatedSubString ("restbe") << endl;
  cout << longestRepeatedSubString ("testfortest") << endl;

  cout << LFBCS ("ALGORITHM") << endl;
  cout << LFBCS ("RECURSION") << endl;
  cout << LFBCS ("REDIVIDE") << endl;
  cout << LFBCS ("DYNAMICPROGRAMMINGMANYTIMES") << endl;
  cout << LFBCS ("REER") << endl;
  cout << LFBCS ("SAMETESTEMAS") << endl;
  cout << LFBCS ("AA") << endl;
  cout << LFBCS ("A") << endl;
}