
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

// @snippet<sh19910711/contest:math/extgcd.cpp>
namespace math {
  // 拡張ユークリッド互除法: a*x+b*y=gcd(x,y)
  template <class T> T extgcd( T a, T b, T& x, T& y ) {
    for ( T u = y = 1, v = x = 0; a; ) {
      T q = b / a;
      std::swap( x -= q * u, u );
      std::swap( y -= q * v, v );
      std::swap( b -= q * a, a );
    }
    return b;
  }
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
  
  Int result_x;
  Int result_y;
  Int result_g;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      Int x, y;
      Int d = math::extgcd(a, b, x, y);
      result_x = std::min(x, y);
      result_y = std::max(x, y);
      result_g = d;
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
      std::cout << result_x << " " << result_y << " " << result_g << std::endl;
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




