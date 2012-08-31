#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

template<class T>
struct inversion_pairs
{
  unsigned int split;
  T container;

  inversion_pairs(const T& nvec) : container(nvec), split (0) {};
  inversion_pairs(inversion_pairs _left, inversion_pairs _right)
    : 
      split(_left.split + _right.split),
      container(_left.container.size() + _right.container.size())
  {
  }

  friend ostream& operator<<(ostream& out, const inversion_pairs<T>& pairs)
  {
    out << "Number of inversion pairs: " << pairs.split << endl;
    out << "Sorted vector: " << endl;

    copy(
        pairs.container.begin(),
        pairs.container.end(),
        ostream_iterator<typename T::value_type>(out, "\n")
      );

    return out;
  }
};

template<class T>
inversion_pairs<T> _merge_sort(
    const class T::iterator& begin,
    const class T::iterator& last
    )
{

  if (last == begin) {
    // Break recursion
    return T(1, *begin);
  }

  unsigned int m = (distance(begin, last)) / 2;
  inversion_pairs<T> left(_merge_sort<T>(begin, begin + m));
  inversion_pairs<T> right(_merge_sort<T>(begin + m + 1, last));

  // Start merging
  auto left_it = left.container.cbegin();
  auto right_it = right.container.cbegin();

  inversion_pairs<T> pairs(left, right);
  
  auto result_it = pairs.container.begin();
  while (1) {
    if (*right_it < *left_it) {
      *result_it++ = *right_it++;
      pairs.split += distance(left_it, left.container.cend());
    } else {
      *result_it++ = *left_it++;
   }
    if (left_it == left.container.cend()) {
      copy(right_it, right.container.cend(), result_it);
      return pairs;
    }
    if (right_it == right.container.cend()) {
      copy(left_it, left.container.cend(), result_it);
      return pairs;
    }
  }
}

template<class T>
inversion_pairs<T> compute_inversion_pairs(T vec) {
  return _merge_sort<T>(vec.begin(), vec.end() - 1);
}

int main()
{
  cout << compute_inversion_pairs<vector<int> >(vector<int>({4,3,2,5})) << endl;
}
