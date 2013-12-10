
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

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 20 + 1;
  const Int TABLE_NONE = -1;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int N;
    Int S;
  };
  
  struct OutputStorage {
    Int result;
  };
  
  struct DataStorage {
    Int table[SIZE][SIZE];
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      init_table(in.N, in.S, data.table);
      out.result = find_value(in.N, data);
      return out;
    }
    
  protected:
    static void init_table( const int& n, const int& start_value, Int table[SIZE][SIZE] ) {
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          table[i][j] = TABLE_NONE;
      table[n][1] = start_value;
    }

    static Int find_value( const int& n, DataStorage& data ) {
      return get_value(1, n, n, data);
    }

    static Int get_value( const int& r, const int& c, const int& n, DataStorage& data ) {
      Int& res = data.table[r][c];
      if ( res != TABLE_NONE ) {
        return res;
      }

      if ( r < c ) {
        res = 0;
        for ( int k = r; k < c; ++ k ) {
          res = std::max(res, get_value(r, k, n, data) + get_value(k + 1, c, n, data));
        }
      } else {
        Int a = 0;
        Int b = 0;
        if ( r < n ) {
          for ( int k = r + 1; k <= n; ++ k ) {
            a = std::max(a, get_value(k, 1, n, data) + get_value(k, c, n, data));
          }
        }
        if ( c > 0 ) {
          for ( int k = 1; k < c; ++ k ) {
            b = std::max(b, get_value(r, k, n, data) + get_value(n, k, n, data));
          }
        }
        res = a + b;
      }

      return res;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.N >> in.S ) )
        return false;
      return true;
    }

    void output( const OutputStorage& out ) const {
      std::cout << out.result << endl;
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif

