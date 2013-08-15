#include <iostream>
#include <cstdio>
using namespace std;

int f( int x ) {
  if ( x % 10 > 0 )
    return x % 10;
  if ( x == 0 )
    return 0;
  return f( x / 10 );
}

int main() {
  for ( int i = 1; i < 1000; ++ i ) {
    if ( i % 10 == 0 )
      printf("f(%d) = %d\n", i, f(i));
  }
  return 0;
}

