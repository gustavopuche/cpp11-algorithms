#include <concepts>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

// // Range concept
// template <BoundedRange R>
// requires Sortable<R>
// void sort(R &r) {
//   return sort(begin(r),end(r));  
// }

template <typename C>
using Value_type = typename C::value_type; // the type of C's elements.

template <typename C>
using Iterator_type = typename C::iterator; // C's iterator type.

template <typename S>
concept Sequence = requires(S a) {
  typename Value_type<S>;                     // S must hava a value type
  typename Iterator_type<S>;                  // S must hava an iterator type

  { begin(a) } -> same_as<Iterator_type<S>>;           // begin(a) must return an iterator
  { end(a) } -> same_as<Iterator_type<S>>;             // end(a) must return an iterator

  requires same_as<Value_type<S>, Value_type<Iterator_type<S>>>;
  requires input_iterator<Iterator_type<S>>;
  requires integral<Value_type<S>>;           // only integral types allowed.
};

template <Sequence Seq, typename Num> Num sum(Seq s, Num v) {
  for (const auto& x : s)
  {
    v+=x;
  }
  return v;
}

////////////////////////////////////////////////////////////////////////////////
//
// MAIN FUNCTION
//
////////////////////////////////////////////////////////////////////////////////
int main()
{
  vector<int> v{2,4,6,8,10};
  // list<double> l{0.5,0.7,1.4,1.7,1.8,2.3};
  // set<string> s{"Gustavo"," is programming"," hard ","in ","c++20"};

  string line = "Gustavo is programming hard in c++20"s;
  auto letter = line[10];
  
  string ini="";
  
  int number = 0;
  double num_float = 0.0;

  cout << "Sum of vector is " << sum(v,number) << endl;
  // cout << "Sum of list is " << sum(l,num_float) << endl;
  // cout << "Sum of set is " << sum(s,ini) << endl;
  cout << "Sum of string is " << sum(line,letter) << endl;
  
  return 0;
}
