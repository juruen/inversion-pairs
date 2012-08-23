#include <vector>
#include <iostream>

using namespace std;

struct inversion_pairs
{
  inversion_pairs(vector<int> nvec) : vec(nvec), left(0), right(0), split (0) {};
  inversion_pairs(inversion_pairs _left, inversion_pairs _right)
    : 
      left(0),
      right(0),
      split(0),
      vec(_left.vec.size() + _right.vec.size())
  {
    left += _left.left + _left.right + _left.split;
    right += _right.left + _right.right + _right.split;
  }
  unsigned int left;
  unsigned int right;
  unsigned int split;
  vector<int> vec;
  vector<int>::const_iterator end_it() { return vec.end(); }
};

inversion_pairs _merge_sort(
    const vector<int>::iterator& begin,
    const vector<int>::iterator& last
    )
{

  if (last == begin) {
    // Break recursion
    return vector<int>(1, *begin);
  }

  unsigned int m = (distance(begin, last)) / 2;
  inversion_pairs left(_merge_sort(begin, begin + m));
  inversion_pairs right(_merge_sort(begin + m + 1, last));

  // Start merging
  vector<int>::const_iterator left_it = left.vec.begin();
  vector<int>::const_iterator right_it = right.vec.begin();

  inversion_pairs pairs(left, right);
  
  pairs.vec.resize(left.vec.size() + right.vec.size());
  vector<int>::iterator result_it = pairs.vec.begin();
  while (1) {
    if (*right_it < *left_it) {
      *result_it++ = *right_it++;
      pairs.split += distance(left_it, left.end_it());
    } else {
      *result_it++ = *left_it++;
   }
    if (left_it == left.vec.end()) {
      copy(right_it, right.end_it(), result_it);
      return pairs;
    }
    if (right_it == right.vec.end()) {
      copy(left_it, left.end_it(), result_it);
      return pairs;
    }
  }
}

inversion_pairs merge_sort(vector<int> vec) {
  return _merge_sort(vec.begin(), vec.end() - 1);
}

int main()
{
  static const int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
  vector<int> foo(arr, arr + sizeof(arr) / sizeof(arr[0]));
  inversion_pairs pairs = merge_sort(foo);
  cout << "left: " << pairs.left << " right: " << pairs.right << " split: " << pairs.split << endl;
  for (vector<int>::iterator it = pairs.vec.begin(); it != pairs.vec.end(); it++) {
    cout << *it << endl;
  }
}
