
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
  typedef map<int, int> Map;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 30 + 11;
  // storages
  int N;
  int result;
  Map memo1;
  Map memo2;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = rec1(N);
    }

    int rec1( int N ) {
      if ( N < 0 )
        return 0;
      if ( memo1.count(N) )
        return memo1[N];
      if ( N == 0 )
        return memo1[N] = 1;
      if ( N == 1 )
        return memo1[N] = 0;
      return memo1[N] = rec1(N - 2) + rec2(N - 1) + rec2(N - 1);
    }

    int rec2( int N ) {
      if ( N < 0 )
        return 0;
      if ( memo2.count(N) )
        return memo2[N];
      if ( N == 0 )
        return memo2[N] = 0;
      if ( N == 1 )
        return memo2[N] = 1;
      return memo2[N] = rec1(N - 1) + rec2(N - 2);
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {
      memo1.clear();
      memo2.clear();
    }

  protected:
    virtual bool action() {
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
      if ( ! ( cin >> N && N != -1 ) )
        return false;
      return true;
    }

    void output() {
      cout << result << endl;
    }
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

