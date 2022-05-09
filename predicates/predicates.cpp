#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>

using namespace std;

struct Greater_than {
  int val;
  Greater_than(int v) : val(v) {}
  bool operator()(const pair<string, int>& r) const { return r.second > val;}
};

void f(map<string, int> &m) {
  auto p = find_if(m.begin(),m.end(),Greater_than{42});
}

////////////////////////////////////////////////////////////////////////////////
///
// Predicate.
//
// Looks for an element that fulfills a specific requirement, a predicate.
// 
////////////////////////////////////////////////////////////////////////////////
void f_with_lambda(map<string, int> &m) {
  auto p = find_if(m.begin(),m.end(),[](const auto& r){return r.second > 42;});
  
  cout << "Found: " << p->first << " , " <<p->second << endl;
}

template<typename T1,typename T2>
ostream &operator<<(ostream &os, const map<T1,T2>& s) {
  os << "(";
  for (auto const& x : s)
    os << "{" << x.first << "," << x.second << "}";
  os << ")";
  return os;
}

////////////////////////////////////////////////////////////////////////////////
//
// MAIN FUNCTION
//
////////////////////////////////////////////////////////////////////////////////
int main()
{
  map<string,int> m{pair{"Gus",43},pair{"Maylen",15},pair{"Delphine",26},pair{"Caelys",4}};

  cout << m << endl;
  
  f_with_lambda(m);
  
  return 0;
}
