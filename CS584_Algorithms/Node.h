#include <vector>
#include <string>

using namespace std;

const string WHITE = "WHITE";
const string GRAY = "GRAY";

class Node {
public:
  Node* parent;
  string color;
  vector<Node*> adj;
  int name;

  Node (int name) {
    parent = NULL;
    color = WHITE;
    this->name = name;
  }
};