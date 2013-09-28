#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
  
int A[1000];

int get_number() {
  string line;
  getline(cin, line);
  std::istringstream iss(line);
  int res;
  iss >> res;
  return res;
}

bool input_edge( int& a, int& b ) {
  string line;
  getline(cin, line);
  std::istringstream iss(line);
  return iss >> a >> b;
}

int main() {
  int tests = get_number();
  string dummy;
  getline(cin, dummy);
  for ( int i = 0; i < tests; ++ i ) {
    int max_a = 0;
    int a, b;
    while ( input_edge(a, b) ) {
      max_a = std::max(max_a, std::max(a, b));
      for ( int j = 0; j < max_a * max_a * max_a; ++ j )
        A[j] = 0;
    }
    cout << "Put guards in room 3." << endl;
  }
}

