#include "MidTerm.h"
#include <algorithm>
#include <numeric>
#include <iostream>

int MT::highwayStops (std::vector<int> distance, std::vector<int> cost, int totalDistance)
{
  int size = distance.size ();
  std::vector<std::pair<int, int>> dp (size, std::make_pair(INT_MAX, -1)); //pair - cost up to this stop and previous stop

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

  int minCostSet = 0;
  while (index != -1) {
    minCostSet += cost[index];
    index = dp[index].second;
  }

  return minCostSet;
}

void MT::test () {
  std::vector<int> distance ({ 15, 20, 25, 45, 50, 70, 80 });
  std::vector<int> cost ({ 2, 2, 1, 21, 4, 7, 3 });

  std::cout << highwayStops (distance, cost, 100) << std::endl;
}