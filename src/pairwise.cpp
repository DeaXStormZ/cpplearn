#include "pairwise.h"
#include <algorithm>
#include <vector>

template<class InputIterator, class Function>
Function for_each_pairwise(InputIterator first, InputIterator last, Function f) {
//    allows to iterate on pair elements, ie
// 1,2,3,4 => 1,2 2,3 3,4
  for (; first != last; ++first) {
    InputIterator nextIter = std::next(first);
    if (nextIter == last) {
      f(*first, *last);
      break;
    }

    f(*first, *nextIter);
  }
  return f;
}

int main() {
  std::vector<int> vec{1,2,3,4,5};
//  for_each_(vec.begin(), vec.end(), [](int &a){ a=a*2;});
  for_each_pairwise(vec.begin(), vec.end(), [](int &a, int &b){a = a + b;});
  // todo can we remove the last one in for_each_pairwise (only if f has side effects ?)
  return 0;
}