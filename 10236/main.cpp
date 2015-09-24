#include <bits/stdc++.h>
using namespace std;

typedef long long Int;
const int LIMIT = 300000 + 11;
Int primes[LIMIT];
Int p[LIMIT];
double fib[LIMIT];

Int solve(Int n) {
  return fib[p[n]];
}

int main() {
  fill(primes, primes + LIMIT, 1);
  primes[0] = primes[1] = 0;
  for (int i = 2; i * i < LIMIT; ++ i) {
    // if (!primes[i]) continue;
    for (int j = i * i; j < LIMIT; j += i) {
      primes[j] = 0;
    }
  }
  primes[1] = true;

  int cnt = 0;
  for (int i = 0; i < LIMIT; ++i) {
    if (primes[i]) {
      p[cnt] = i;
      ++cnt;
    }
  }
  p[1] = 3;
  p[2] = 4;

  fib[1] = 1;
  fib[2] = 1;
  bool flag = false;
  for (int i = 3; i < LIMIT; ++i) {
    fib[i] = fib[i-1] + (flag ? fib[i-2] / 10LL : fib[i-2]);
    flag = false;
    while (fib[i] >= 1000000000LL) {
      fib[i] /= 10LL;
      flag = true;
    }
  }

  Int n;
  while (cin >> n) {
    cout << solve(n) << endl;
  }

  return 0;
}
