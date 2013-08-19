
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
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() const {};
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
        std::cout << "Class " << i + 1 << std::endl;
        this->action();
      }
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef ValueType Type;
    VectorClass() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }

    typename std::vector<Type>::iterator at( const int& index ) {
      return data.begin() + index;
    }
    typename std::vector<Type>::const_iterator at_const( const int& index ) const {
      return data.begin() + index;
    }

  private:
    std::vector<Type> data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_X> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_Z> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
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
  struct Result {
    Int max;
    Int min;
    Int gap;
  };
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100 + 11;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef storage::Vector<Int, SIZE>::Type List;

  Int N;
  List A;

  Result result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      A = get_sorted_list(A, N);
      result.max = get_max_element(A, N);
      result.min = get_min_element(A, N);
      result.gap = get_gap(A, N);
    }

    const List get_sorted_list( const List& A, const Int& N ) {
      List res = A;
      std::sort(res.at(0), res.at(N));
      return res;
    }

    const Int get_max_element( const List& A, const Int& N ) {
      return *max_element(A.at_const(0), A.at_const(N));
    }

    const Int get_min_element( const List& A, const Int& N ) {
      return *min_element(A.at_const(0), A.at_const(N));
    }

    const Int get_gap( const List& A, const Int& N ) {
      Int res = std::numeric_limits<Int>::min();
      for ( int i = 0; i + 1 < N; ++ i )
        res = std::max(res, A[i+1] - A[i]);
      return res;
    }

  protected:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input() )
        return false;
      solver.solve();
      this->output();
      return true;
    }

    bool input() {
      if ( ! ( std::cin >> N ) )
        return false;
      for ( int i = 0; i < N; ++ i )
        std::cin >> A[i];
      return true;
    }

    void output() {
      std::cout << "Max " << result.max << ", Min " << result.min << ", Largest gap " << result.gap << std::endl;
    }
    
    Solver solver;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution().run();
}
#endif



