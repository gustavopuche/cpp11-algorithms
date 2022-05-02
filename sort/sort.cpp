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
  
  return 0;
}
