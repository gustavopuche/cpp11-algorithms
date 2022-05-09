#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Entry{
  string name;
  int number;
};

// Define <
bool operator<(const Entry& x, const Entry& y){ // less than.
  return x.name < y.name;
}

// Define ==
bool operator==(const Entry& x, const Entry& y){ // equal than
  return x.name == y.name;
}

// Define output format.
ostream &operator<<(ostream &os, const Entry &e) {
  return os << "{\"" << e.name << "\", " << e.number << "}";
}

// Define input format.
istream &operator>>(istream &is, Entry &e) {
  char c, c2;
  if (is>>c && c=='{' && is>>c2 && c2=='"'){ // starts with a {"
    string name;                             // the default value of a string is the empty string: ""
    while (is.get(c) && c!='"')              // anything before a " is part of the name.
      name+=c;

    if (is>>c && c==','){
      int number = 0;
      if (is>>number>>c && c=='}'){          // read the number and a }
	e = {name,number};                   // assign to the entry
	return is;
      }
    }
  }
  is.setstate(ios_base::failbit); // register the failure in the stream.
  return is;
}

// Print phone book.
void print_book(const vector<Entry>& book)
{
  for (const auto& x : book)
  {
    cout << x << endl;
  }			    
}

// Print phone list.
void print_book_list(const list<Entry> &lst) {
  for (const auto& l : lst)
  {
    cout << l << endl;
  }
}
  
// Insert new element.
void input(vector<Entry>& book) {
  for (Entry e; cin>>e;)
    book.push_back(e);
}

// Function that order vector and place result in a list.
void f(vector<Entry>& vec, list<Entry>& lst){
  sort(vec.begin(),vec.end());                    // use < for order.
  unique_copy(vec.begin(),vec.end(),back_inserter(lst)); // don't copy adjacent equual elements.
}

// Type alias to hide typename C::iterator.
template <typename T>
using Iterator = typename T::iterator;

// Return all occurrences of v in c.
template<typename C, typename V>
vector<Iterator<C>> find_all(C &c, V v) {
  // vector<typename C::iterator> res; // vector provides move semantics.
  vector<Iterator<C>> res; // vector provides move semantics.
  
  for (auto p = c.begin(); p!=c.end(); p++)
  {
    if (*p==v)
      res.push_back(p);
  }
  
  return res;
}


// Define output format for vectors.
template<typename T>
ostream &operator<<(ostream &os, const vector<T>& s) {
  os << "(";
  for (auto const x : s)
    os << x << " ";
  os << ")";
  return os;
}

void iterator_tests() {
  string m {"My name is Gus Eco And I am a robot game."};
  for (auto p : find_all<string,char>(m,'a'))
    if (*p!='a')
      cerr << "a bug!\n";
    else
      cout << "Found: " << *p << endl;

  list<double> ld {1.1,1.2,2.3,4.5,3.4,4.5,6.7,4.5};
  for (auto p : find_all(ld,4.5))
    if (*p!=4.5)
      cerr << "list bug!\n";
    else
      cout << "Found in list: " << *p << endl;

  vector<string> vs {"red","blue","green","orange","red","green","orange","orange","red"};
  for (auto p : find_all(vs,"orange"))
    if (*p!="orange")
      cerr << "vector bug!\n";
    else
      cout << "Found in vector: " << *p << endl;

  for (auto p : find_all(vs,"red"))
    if (*p!="red")
      cerr << "vector bug!\n";
    else
      cout << "Found in vector: " << *p << endl;

  for (auto p : find_all(vs,"green"))
    *p = "vert";

  cout << vs << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
// MAIN FUNCTION
//
////////////////////////////////////////////////////////////////////////////////
int main()
{

  vector<Entry> phone_book = {
    {"Pepe Phone",123456},
    {"Betty Davis",345678},
    {"Iron Man",234567},
    {"Pepe Phone",123456},
    {"Iron Man",234567},
    {"Betty Davis",345678}
  };

  list<Entry> phone_list;

  cout << "Insert order.. " << endl << endl;
  print_book(phone_book);

  f(phone_book,phone_list);

  cout << "Ordered by name..." << endl << endl;
  print_book(phone_book);
  cout << "Ordered print finnished..." << endl;

  cout << "size of phone list:" << phone_list.size() << endl;
  print_book_list(phone_list);
  // input(phone_book);
  // print_book(phone_book);

  iterator_tests();

  return 0;
}
