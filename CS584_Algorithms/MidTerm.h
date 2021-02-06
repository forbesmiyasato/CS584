#include <vector>

#pragma once

struct Maxes {
  int up;
  int down;

  Maxes () {
    up = INT_MIN;
    down = INT_MIN;
  }

  Maxes (int x, int y) {
    up = x;
    down = y;
  }
};

class MT {
public:
  int highwayStops (std::vector<int> distance, std::vector<int> cost, int totalDistance);
  Maxes temperatures (std::vector<int> temperatures);
  Maxes DAC (std::vector<int> temperatrues, int l, int r, Maxes maxes);
  void test ();
};