#include <vector>
#include <iostream>

using namespace std;

template<class T, typename ContainerType>
struct inversion_pairs
{
  unsigned int split;
  ContainerType container;

  inversion_pairs(const ContainerType& nvec) : container(nvec), split (0) {};
  inversion_pairs(inversion_pairs _left, inversion_pairs _right)
    : 
      split(_left.split + _right.split),
      container(_left.container.size() + _right.container.size())
  {
  }

  friend ostream& operator<<(ostream& out, const inversion_pairs<T, ContainerType>& ip)
  {
    out << "split: " << ip.split << endl;
    for (typename ContainerType::const_iterator it = ip.container.begin();
        it != ip.container.end(); 
        ++it)
    {
      out << *it << endl;
    }

    return out;
  }
};

template<class T, typename ContainerType>
inversion_pairs<T, ContainerType> _merge_sort(
    const typename ContainerType::iterator& begin,
    const typename ContainerType::iterator& last
    )
{

  if (last == begin) {
    // Break recursion
    return ContainerType(1, *begin);
  }

  unsigned int m = (distance(begin, last)) / 2;
  inversion_pairs<T, ContainerType> left(_merge_sort<T, ContainerType>(begin, begin + m));
  inversion_pairs<T, ContainerType> right(_merge_sort<T, ContainerType>(begin + m + 1, last));

  // Start merging
  typename ContainerType::const_iterator left_it = left.container.begin();
  typename ContainerType::const_iterator right_it = right.container.begin();

  inversion_pairs<T, ContainerType> pairs(left, right);
  
  typename ContainerType::iterator result_it = pairs.container.begin();
  while (1) {
    if (*right_it < *left_it) {
      *result_it++ = *right_it++;
      pairs.split += distance(left_it, left.container.cend());
    } else {
      *result_it++ = *left_it++;
   }
    if (left_it == left.container.cend()) {
      copy(right_it, right.end_it(), result_it);
      return pairs;
    }
    if (right_it == right.container.cend()) {
      copy(left_it, left.end_it(), result_it);
      return pairs;
    }
  }
}

template<class T, typename ContainerType>
inversion_pairs<T, ContainerType> merge_sort(ContainerType vec) {
  return _merge_sort<T, ContainerType>(vec.begin(), vec.end() - 1);
}

int main()
{
  static const int arr[] = {4, 3, 2, 5}; //{8, 7, 6, 5, 4, 3, 2, 1};
  vector<int> foo(arr, arr + sizeof(arr) / sizeof(arr[0]));
  inversion_pairs<int, vector<int> > pairs = merge_sort<int, vector<int> >(foo);
  cout << pairs << endl;
}
