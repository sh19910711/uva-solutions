
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
        std::cout << i + 1 << " ";
        action();
      }
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

// @snippet<sh19910711/contest:math/gcd.cpp>
namespace math {
  // @desc 最大公約数を求める
  template <class T> T gcd( T a, T b ) {
    T i, j;
    for ( i = 0; ! ( a & 1 ); ++ i ) a >>= 1;
    for ( j = 0; ! ( b & 1 ); ++ j ) b >>= 1;
    while ( b != a ) {
      b -= a;
      if ( b < 0 ) a += b, b = -b;
      while ( ! ( b & 1 ) ) b >>= 1;
    }
    return a << std::min( i, j );
  }
}

// @snippet<sh19910711/contest:math/lcm.cpp>
namespace math {
  // @desc 最小公倍数を求める
  template <class T> T lcm( T a, T b ) {
    T larger = a > b ? a : b;
    T smaller = a > b ? b : a;
    T res = larger;
    while ( res % smaller != 0 )
      res += larger;
    return res;
  }
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
  template <typename Type, int SIZE_X, int SIZE_Y, int SIZE_Z> struct VectorTypes {
    typedef storage::Vector<Type   , SIZE_X> Type1D;
    typedef storage::Vector<Type1D , SIZE_Y> Type2D;
    typedef storage::Vector<Type2D , SIZE_Z> Type3D;
  };
  template <int SIZE_X, int SIZE_Y, int SIZE_Z> struct BasicVectors {
    typedef VectorTypes<Int    , SIZE_X , SIZE_Y , SIZE_Z> IntVectors;
    typedef VectorTypes<Double , SIZE_X , SIZE_Y , SIZE_Z> DoubleVectors;
    typedef VectorTypes<String , SIZE_X , SIZE_Y , SIZE_Z> StringVectors;
  };
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
  Int a;
  Int b;
  
  Int result_lcm;
  Int result_gcd;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result_gcd = math::gcd(a, b);
      result_lcm = math::lcm(a, b);
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
      return std::cin >> a >> b;
    }
    
    void output() {
      std::cout << result_lcm << " " << result_gcd << std::endl;
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




