
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class ISolution {
  public:
    virtual int run() = 0;
    
  protected:
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int NONE = -1;
  const int SIZE = 1000000 + 11;
  // storages
  int N;
  int A[SIZE], B[SIZE];
  int a, b;
  bool P[SIZE];
  int primes[SIZE];
  int primes_cnt;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      a = b = NONE;
      for ( int i = 0; i < primes_cnt && primes[i] <= N; ++ i ) {
        int na = primes[i];
        int nb = N - na;
        if ( P[na] && P[nb] ) {
          a = na;
          b = nb;
          return;
        }
      }
    }

    void pre_calc() {
      if ( pre_calced )
        return;
      pre_calced = true;

      fill(P, P + SIZE, false);
      P[2] = true;
      for ( int i = 3; i < SIZE; i += 2 )
        P[i] = true;
      for ( int i = 3; i < SIZE; i += 2 ) {
        if ( ! P[i] )
          continue;
        for ( int j = i + i; j < SIZE; j += i ) {
          P[j] = false;
        }
      }

      primes_cnt = 0;
      for ( int i = 0; i < SIZE; ++ i )
        if ( P[i] )
          primes[primes_cnt ++] = i;
    }

    Solver() {
      pre_calced = false;
    }
    
  private:
    bool pre_calced;
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      solver.pre_calc();
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }
    
  private:
    Solver solver;

    bool input() {
      if ( ! ( cin >> N ) )
        return false;
      return N > 0;
    }

    void output() {
      cout << N << ":" << endl;
      if ( a != NONE )
        cout << a << "+" << b << endl;
      else
        cout << "NO WAY!" << endl;
    }
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

