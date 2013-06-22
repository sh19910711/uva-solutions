
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


// @snippet<sh19910711/contest:solution/solution-base-multi-tests.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
      int tests = 0;
      std::cin >> tests;
      for ( int i = 0; i < tests; ++ i )
        action();
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
  const int SIZE = 100 + 11;
  const int NONE = SIZE * SIZE + SIZE * SIZE + 11;

  // storages
  int N;
  int R;
  int U[SIZE];
  int V[SIZE];
  int D[SIZE][SIZE];
  int src, dst;
  int result;
  int test_no;

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = -1;
      test_no ++;

      for ( int i = 0; i < N; ++ i )
        for ( int j = 0; j < N; ++ j )
          D[i][j] = NONE;

      for ( int i = 0; i < N; ++ i )
        D[i][i] = 0;

      for ( int i = 0; i < R; ++ i )
        D[U[i]][V[i]] = D[V[i]][U[i]] = 1;

      for ( int k = 0; k < N; ++ k )
        for ( int i = 0; i < N; ++ i )
          for ( int j = 0; j < N; ++ j )
            D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

      int res = -1;
      for ( int i = 0; i < N; ++ i )
        res = max(res, D[src][i] + D[i][dst]);

      result = res;
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {
      test_no = 0;
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

    bool input() {
      if ( ! ( cin >> N >> R ) )
        return false;
      for ( int i = 0; i < R; ++ i )
        cin >> U[i] >> V[i];
      cin >> src >> dst;
      return true;
    }

    void output() {
      cout << "Case " << test_no << ": " << result << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}


