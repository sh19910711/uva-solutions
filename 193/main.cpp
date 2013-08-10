
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
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base-multi-tests.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
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
  const int SIZE = 100 * 100 + 11;
  const int COLOR_BLACK = 1;
  const int COLOR_WHITE = 2;
  const int COLOR_EMPTY = 0;
  // storages
  int n, k;
  int A[SIZE];
  int B[SIZE];

  int G[SIZE][SIZE];
  int GC[SIZE];
  int color[SIZE];

  int result_num;
  int result[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      generate_graph();

      std::fill(color, color + SIZE, COLOR_EMPTY);
      find_good_coloring(0, 0);
    }

    void normalize() {
      for ( int i = 0; i < k; ++ i ) {
        A[i] --;
        B[i] --;
      }
    }

    void add_edge( int from, int to ) {
      G[from][GC[from] ++] = to;
      G[to][GC[to] ++] = from;
    }

    void generate_graph() {
      for ( int i = 0; i < k; ++ i ) {
        int a = A[i], b = B[i];
        add_edge(a, b);
      }
    }

    void find_good_coloring( int x, int black_num ) {
      if ( x >= n ) {
        if ( black_num > result_num ) {
          result_num = 0;
          for ( int i = 0; i < n; ++ i ) {
            if ( color[i] == COLOR_BLACK ) {
              result[result_num ++] = i;
            }
          }
        }
        return;
      }

      if ( ! has_adjacent_black_node(x) ) {
        color[x] = COLOR_BLACK;
        find_good_coloring(x + 1, black_num + 1);
        color[x] = COLOR_EMPTY;
      }

      color[x] = COLOR_WHITE;
      find_good_coloring(x + 1, black_num);
      color[x] = COLOR_EMPTY;
    }

    bool has_adjacent_black_node( int from ) {
      int num_vertices = GC[from];
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = G[from][i];
        if ( color[to] == COLOR_BLACK )
          return true;
      }
      return false;
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void init() {
      result_num = 0;
      for ( int i = 0; i < SIZE; ++ i ) {
        GC[i] = 0;
      }
    }
    
    bool input() {
      if ( ! ( cin >> n >> k ) )
        return false;
      for ( int i = 0; i < k; ++ i )
        cin >> A[i] >> B[i];
      return true;
    }

    void output() {
      cout << result_num << endl;
      for ( int i = 0; i < result_num; ++ i ) {
        cout << result[i] + 1;
        if ( i + 1 < result_num )
          cout << ' ';
      }
      cout << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif


