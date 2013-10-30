#include <iostream>
#include <cstdio>
using namespace std;

int f( int n ) {
  if ( n % 10 > 0 )
    return n % 10;
  if ( n == 0 )
    return 0;
  return f( n / 10 );
}

int main() {
  for ( int i = 0; i < 1000; ++ i )
    printf("%d\t%d\n", i, f(i));
  return 0;
}
