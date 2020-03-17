#pragma once
#include <vector>
#include <set>

std::vector<int>appendUnique(std::vector<int> left, std::vector<int> right) {
    left.insert(left.end(), right.begin(), right.end());
    std::set<int> aux(left.begin(), left.end());
    std::vector<int> result;
    result.assign(aux.begin(), aux.end());
    return result;
}

 class State {
 public:
     int position;
     std::vector<int>followPos;
     

     virtual bool isNullable() = 0;
     virtual std::vector<int> firstPos() = 0;
     virtual std::vector<int> lastPos() = 0;
     virtual void calculateFollowers(std::vector<std::vector<int>> &followers) {};

};