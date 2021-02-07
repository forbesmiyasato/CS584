#include "MidTerm.h"
#include <algorithm>
#include <numeric>
#include <iostream>

int MT::highwayStops (std::vector<int> distance, std::vector<int> cost, int totalDistance)
{
  int size = distance.size ();
  std::vector<std::pair<int, int>> dp (size, std::make_pair (INT_MAX, -1)); //pair - cost up to this stop and previous stop

  for (int i = 0; i < size; i++) {
    int curDistance = distance[i];
    if (curDistance > 30) {
      int j = i - 1;
      while (j >= 0 && curDistance - distance[j] <= 30) {
        int costToPrevStop = cost[i] + dp[j].first;
        if (costToPrevStop < dp[i].first) {
          dp[i].first = costToPrevStop;
          dp[i].second = j;
        }
        j--;
      }
    }
    else {
      dp[i].first = cost[i];
    }
  }

  if (dp[0].first == INT_MAX) {
    return -1; //no rest stop within 30 miles of start
  }

  //find optimal end stop
  int index = dp.size () - 1;
  int endStopMinCost = INT_MAX;
  for (int i = size - 1; i >= 0; i--) {
    if (totalDistance - distance[i] > 30) {
      break;
    }

    if (dp[i].first < endStopMinCost) {
      index = i;
      endStopMinCost = dp[i].first;
    }
  }

  if (endStopMinCost == INT_MAX) {
    return -1; //no rest stop within 30 miles of end
  }


  return endStopMinCost;
}

Maxes MT::DAC (std::vector<int> temperatures, int l, int r) {
  if (l < r) {
    if (l == r - 1) {
      return Maxes (temperatures[r] - temperatures[l], temperatures[l] - temperatures[r]);
    }

    int mid = mid = static_cast <int> (floor ((l + r) / 2));
    Maxes maxesLeft = DAC (temperatures, l, mid);
    Maxes maxesRight = DAC (temperatures, mid + 1, r);

    //Find min and max in the left hand side
    int leftMaxNum = INT_MIN;
    int leftMinNum = INT_MAX;
    for (int i = l; i <= mid; i++) {
      leftMaxNum = std::max (leftMaxNum, temperatures[i]);
      leftMinNum = std::min (leftMinNum, temperatures[i]);
    }

    //Find min and max in the right hand side
    int rightMaxNum = INT_MIN;
    int rightMinNum = INT_MAX;
    for (int j = mid + 1; j <= r; j++) {
      rightMaxNum = std::max (rightMaxNum, temperatures[j]);
      rightMinNum = std::min (rightMinNum, temperatures[j]);
    }

    Maxes maxes;
    maxes.up = std::max (std::max (maxesLeft.up, maxesRight.up), rightMaxNum - leftMinNum);
    maxes.down = std::max (std::max (maxesLeft.down, maxesRight.down), leftMaxNum - rightMinNum);

    return maxes;
  }
}

Maxes MT::DACON (std::vector<int> temperatures, int l, int r) {
  if (l == r) {
    return Maxes (0, 0, temperatures[l], temperatures[r]);
  }
  if (l < r) {
    if (l == r - 1) {
      int right = temperatures[r];
      int left = temperatures[l];
      return Maxes (right - left, left - right, std::max(left, right), std::min(left, right));
    }

    int mid = mid = static_cast <int> (floor ((l + r) / 2));
    Maxes maxesLeft = DACON (temperatures, l, mid);
    Maxes maxesRight = DACON (temperatures, mid + 1, r);

    Maxes maxes;
    maxes.up = std::max (std::max (maxesLeft.up, maxesRight.up), maxesRight.max - maxesLeft.min);
    maxes.down = std::max (std::max (maxesLeft.down, maxesRight.down), maxesLeft.max - maxesRight.min);
    maxes.max = std::max (maxesLeft.max, maxesRight.max);
    maxes.min = std::min (maxesLeft.min, maxesRight.min);
    return maxes;
  }
}

Maxes MT::temperatures (std::vector<int> temperatures)
{
  int high = temperatures.size ();
  return DAC (temperatures, 0, high - 1);
}

Maxes MT::temperaturesON (std::vector<int> temperatures)
{
  int high = temperatures.size ();
  return DACON (temperatures, 0, high - 1);
}

void MT::test () {
  std::vector<int> distance ({ 15, 20, 25, 45, 50, 70, 80 });
  std::vector<int> cost ({ 2, 2, 1, 21, 4, 7, 3 });

  std::cout << highwayStops (distance, cost, 100) << std::endl;

  Maxes maxes = temperatures ({ 10, 0, 1, 2, 3, 4, -1 });
  std::cout << maxes.up << " " << maxes.down << std::endl;

  Maxes maxesON = temperaturesON ({ 10, 0, 1, 2, 3, 4, -1 });
  std::cout << maxesON.up << " " << maxesON.down << std::endl;
}