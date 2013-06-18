
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
  const int SIZE = 8;
  const string LINE = "**********************************************************";
  // storages
  int N;
  double X[SIZE];
  double Y[SIZE];
  int test_no;
  double tmp_x[SIZE], tmp_y[SIZE];
  int id[SIZE];

  double min_sum;

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      test_no ++;

      for ( int i = 0; i < N; ++ i )
        id[i] = i;

      min_sum = std::numeric_limits<double>::max();
      double min_x[SIZE];
      double min_y[SIZE];
      do {
        for ( int i = 0; i < N; ++ i ) {
          tmp_x[i] = X[id[i]];
          tmp_y[i] = Y[id[i]];
        }

        double sum = get_sum(tmp_x, tmp_y);
        if ( sum < min_sum ) {
          min_sum = sum;
          for ( int i = 0; i < N; ++ i ) {
            min_x[i] = tmp_x[i];
            min_y[i] = tmp_y[i];
          }
        }

      } while ( next_permutation(id, id + N) );

      for ( int i = 0; i < N; ++ i ) {
        X[i] = min_x[i];
        Y[i] = min_y[i];
      }

    }

    double get_sum( double* x, double* y ) {
      double res = 0.0;
      for ( int i = 0; i + 1 < N; ++ i )
        res += get_dist(x[i], y[i], x[i + 1], y[i + 1]);
      return res;
    }

    double get_dist( double x1, double y1, double x2, double y2 ) {
      return sqrt(( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ));
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
    
  private:
    Solver solver;

    void init() {
    }

    bool input() {
      if ( ! ( cin >> N && N ) )
        return false;
      for ( int i = 0; i < N; ++ i )
        cin >> X[i] >> Y[i];
      return true;
    }

    void output() {
      cout << LINE << endl;
      cout << "Network #" << test_no << endl;
      for ( int i = 0; i + 1 < N; ++ i ) {
        printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
            (int)X[i], (int)Y[i], (int)X[i + 1], (int)Y[i + 1], solver.get_dist(X[i], Y[i], X[i + 1], Y[i + 1]) + 16);
      }
      printf("Number of feet of cable required is %.2f.\n", min_sum + 16 * ( N - 1 ));
    }
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

