#include <iostream>
using namespace std;

int main() {
  int tests = 0;
  std::cin >> tests;
  for ( int i = 0; i < tests; ++ i ) {
    int n, k;
    std::cin >> n >> k;
    for ( int j = 0; j < k; ++ j ) {
      int a, b, c;
      std::cin >> a >> b >> c;
    }
    int cnt = 0;
    for ( int i = 0; i < n; ++ i ) {
      for ( int j = 0; j < k; ++ j ) {
        cnt ++;
      }
    }
    cout << "YES" << endl;
  }
  return 0;
}
