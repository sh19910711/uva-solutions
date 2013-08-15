
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
  typedef std::pair<bool, Int> Result;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  String S;

  bool result;
  Int depth;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      Result ret = check_number(S);
      result     = ret.first;
      depth      = ret.second;
    }
    
    const Result check_number( const String& s ) const {
      int n = s.size();
      Int sum = 0;
      for ( int i = 0; i < n; ++ i )
        sum += s[i] - '0';
      if ( sum % 9 != 0 )
        return Result(false, -1);
      return Result(true, get_depth(sum));
    }

    const Int get_depth( const Int& x ) const {
      if ( x < 10 )
        return 1;
      Int tmp = x;
      Int next_x = 0;
      while ( tmp >= 10 ) {
        next_x += tmp % 10;
        tmp /= 10;
      }
      next_x += tmp;
      return get_depth(next_x) + 1;
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
      if ( ! ( std::cin >> S ) )
        return false;
      if ( S == "0" )
        return false;
      return true;
    }

    void output() {
      if ( result ) {
        std::cout << S << " is a multiple of 9 and has 9-degree " << depth << "." << std::endl;
      } else {
        std::cout << S << " is not a multiple of 9." << std::endl;
      }
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

