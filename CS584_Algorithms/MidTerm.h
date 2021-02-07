#include <vector>

#pragma once

struct Maxes {
  int up;
  int down;
  int max;
  int min;

  Maxes () {
    up = INT_MIN;
    down = INT_MIN;
    max = INT_MAX;
    min = INT_MIN;
  }

  Maxes (int x, int y) {
    up = x;
    down = y;
  }

  Maxes (int x, int y, int n, int m) {
    up = x;
    down = y;
    max = n;
    min = m;
  }
};

class MT {
public:
  int highwayStops (std::vector<int> distance, std::vector<int> cost, int totalDistance);
  Maxes temperatures (std::vector<int> temperatures);
  Maxes DAC (std::vector<int> temperatrues, int l, int r);
  Maxes DACON (std::vector<int> temperatrues, int l, int r);
  Maxes temperaturesON (std::vector<int> temperatures);
  void singlePass (std::vector<int> temperatures);
  void test ();
};