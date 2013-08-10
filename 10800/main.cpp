
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
      for ( int i = 0; i < tests; ++ i ) {
        std::cout << "Case #" << i + 1 << ":" << std::endl;
        action();
        std::cout << std::endl;
      }
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
  const int SIZE = 200;
  const int RESULT_OFFSET = SIZE / 2;
  const char TYPE_R = 'R';
  const char TYPE_F = 'F';
  const char TYPE_C = 'C';
  const char GRAPH_R = '/';
  const char GRAPH_F = '\\';
  const char GRAPH_C = '_';

  // storages
  string s;
  int max_r;
  int min_r;

  string result[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      do_draw();
      do_trim();
    }

    void do_trim() {
      for ( int i = min_r; i <= max_r; ++ i )
        mapping(i) = trim(mapping(i));
    }

    string trim( string s ) {
      std::reverse(s.begin(), s.end());
      while ( ! s.empty() && s[0] == ' ' )
        s = s.substr(1);
      std::reverse(s.begin(), s.end());
      return s;
    }

    void do_draw() {
      int n = s.size();
      int r = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( s[i] == TYPE_R ) {
          mapping(r)[i] = GRAPH_R;
          r ++;
        } else if ( s[i] == TYPE_F ) {
          r --;
          mapping(r)[i] = GRAPH_F;
        } else if ( s[i] == TYPE_C ) {
          mapping(r)[i] = GRAPH_C;
        }
        max_r = std::max(max_r, r);
        min_r = std::min(min_r, r);
      }
    }

    string& mapping( int r ) {
      return result[RESULT_OFFSET + r];
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
      max_r = 0;
      min_r = 0;
      std::fill(result, result + SIZE, string(SIZE, ' '));
    }

    bool input() {
      return cin >> s;
    }

    void output() {
      for ( int i = max_r; i >= min_r; -- i ) {
        if ( solver.mapping(i) == "" )
          continue;
        cout << "| " << solver.mapping(i) << endl;
      }
      cout << "+" << string(s.size() + 2, '-') << endl;
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


