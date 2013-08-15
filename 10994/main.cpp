
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
    virtual void output() const {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class Vector {
  public:
    typedef ValueType Type;
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
  private:
    Type data[SIZE];
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  Int P;
  Int Q;

  Int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = calc_s(P, Q);
    }

    const Int calc_s( const Int& p, const Int& q ) const {
      return calc_g(q) - calc_g(p - 1);
    }

    const Int calc_g( const Int& x ) const {
      if ( x <= 0 )
        return 0;
      Int t = x % 10;
      Int s = x / 10;
      return 45 * s + t * ( t + 1 ) / 2 + calc_g(s);
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

    bool input() {
      if ( ! ( std::cin >> P >> Q ) )
        return false;
      if ( P < 0 && Q < 0 )
        return false;
      return true;
    }

    void output() const {
      std::cout << result << std::endl;
    } 
    
    Solver solver;
    
  private:
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

