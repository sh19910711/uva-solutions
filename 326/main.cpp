
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
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef ValueType Type;
    VectorClass() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
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
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 10 + 11;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storage types
  typedef storage::Vector<int, SIZE, SIZE>::Type Table;
  typedef storage::Vector<int, SIZE>::Type List;

  // storages
  Int N;
  Int K;
  List A;

  Table init_table;
  List B;

  Int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      init_table = get_init_table(A, N);
      B = get_b(init_table, N);

      List last_b = do_operations(B, N, K);
      result = last_b[0];
    }

    List do_operations( const List& B, const Int& N, const Int& K ) {
      List res = B;
      for ( int i = 0; i < K; ++ i ) {
        res = do_operation(res, N);
      }
      return res;
    }

    List do_operation( const List& B, const Int& N ) {
      List res;
      res[N - 1] = B[N - 1];
      for ( int i = N - 2; i >= 0; -- i ) {
        res[i] = B[i] + res[i + 1];
      }
      return res;
    }

    List get_b( const Table& table, const Int& N ) {
      List res;
      for ( int i = 0; i < N; ++ i ) {
        res[i] = table[N - i - 1][i];
      }
      return res;
    }

    Table get_init_table( const List& A, const Int& N ) {
      Table res;
      for ( int i = 0; i < N; ++ i ) {
        res[i][0] = A[i];
      }
      for ( int i = 1; i < N; ++ i ) {
        for ( int j = 0; j < N - i; ++ j ) {
          res[j][i] = res[j+1][i-1] - res[j][i-1];
        }
      }
      return res;
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
      if ( ! ( std::cin >> N ) )
        return false;
      if ( N == 0 )
        return false;
      for ( int i = 0; i < N; ++ i )
        std::cin >> A[i];
      std::cin >> K;
      return true;
    }

    void output() {
      std::cout << "Term " << N + K << " of the sequence is " << result << std::endl;
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


