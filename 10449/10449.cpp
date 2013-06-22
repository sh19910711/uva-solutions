
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
  const int SIZE = 200 + 11;
  const int INF = std::numeric_limits<int>::max() / 2;
  
  // storages
  int test_no;
  int N;
  LL B[SIZE];
  int R;
  int U[SIZE], V[SIZE];
  int queries;
  int Q[SIZE];
  int A[SIZE];
  int T[SIZE];

  LL D[SIZE][SIZE];
  bool G[SIZE][SIZE];

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      test_no ++;
      adjust();
      calc();
      for ( int i = 0; i < queries; ++ i )
        A[i] = T[Q[i]];
    }

    void adjust() {
      for ( int i = 0; i < N; ++ i ) {
        Q[i] --;
      }
      for ( int i = 0; i < R; ++ i ) {
        U[i] --;
        V[i] --;
      }
    }

    void calc() {
      for ( int i = 0; i < N; ++ i ) {
        for ( int j = 0; j < N; ++ j ) {
          D[i][j] = INF;
        }
      }
      for ( int i = 0; i < N; ++ i ) {
        for ( int j = 0; j < N; ++ j ) {
          G[i][j] = INF;
        }
      }
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
      if ( ! ( cin >> N ) )
        return false;
      for ( int i = 0; i < N; ++ i )
        cin >> B[i];
      cin >> R;
      for ( int i = 0; i < N; ++ i )
        cin >> U[i] >> V[i];
      cin >> queries;
      for ( int i = 0; i < queries; ++ i )
        cin >> Q[i];
      return true;
    }

    void output() {
      cout << "Set #" << test_no << endl;
      for ( int i = 0; i < queries; ++ i )
        cout << A[i] << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

