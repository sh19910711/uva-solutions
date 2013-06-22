
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
  const string YES = "tautology";
  const string NO = "not";
  const int VARIABLES = 5;
  const int STATES = 1 << VARIABLES;
  const int NONE_TYPE = -1;
  
  // storages
  string exp;
  bool result;
  int state;
  int p;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = check();
    }

    bool check() {
      for ( state = 0; state < STATES; ++ state ) {
        p = 0;
        if ( ! eval() )
          return false;
      }
      return true;
    }

    int get_type( char c ) {
      string t = "pqrst";
      int n = t.size();
      for ( int i = 0; i < n; ++ i )
        if ( t[i] == c )
          return i;
      return NONE_TYPE;
    }

    bool eval() {
      char c = exp[p ++];
      int type = get_type(c);
      
      if ( type != NONE_TYPE ) {
        int bit_type = 1 << type;
        return ( state & bit_type ) > 0;
      }

      if ( c == 'N' ) {
        return ! eval();
      }

      bool l = eval(), r = eval();

      if ( c == 'K' )
        return l & r;

      if ( c == 'A' )
        return l | r;

      if ( c == 'C' )
        return ! ( l & ( ! r ) );

      if ( c == 'E' )
        return l == r;

      return true;
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
    }
    
    bool input() {
      if ( ! ( cin >> exp ) )
        return false;
      return exp != "0";
    }
    
    void output() {
      cout << ( result ? YES : NO ) << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}



