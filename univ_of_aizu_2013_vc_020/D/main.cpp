
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
    virtual bool action() = 0;
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
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
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:math/lcm.cpp>
namespace math {
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
  const int SIZE = 50 + 1;
  const int LCMS_SIZE = 230300 + 11;

}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types

}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int n;
    Int t;
    Int coins[SIZE];
    Int tables[SIZE];
  };

  struct OutputStorage {
    Int tables;
    Int max_length[SIZE];
    Int min_length[SIZE];
  };

  struct DataStorage {
    Int lcms[LCMS_SIZE];
    Int lcms_cnt;
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
      out.tables = in.t;
      generate_lcms(in.n, in.coins, data.lcms, data.lcms_cnt);
      for ( int table_id = 0; table_id < in.t; ++ table_id ) {
        out.max_length[table_id] = find_maximum_length(in.tables[table_id], data.lcms, data.lcms_cnt);
        out.min_length[table_id] = find_minimum_length(in.tables[table_id], data.lcms, data.lcms_cnt);
      }
      return out;
    }

  protected:
    static Int find_maximum_length( const Int& desired, const Int lcms[LCMS_SIZE], const Int lcms_cnt ) {
      Int res = std::numeric_limits<Int>::min();
      for ( int i = 0; i < lcms_cnt; ++ i ) {
        Int lcm = lcms[i];
        Int lb = -1;
        Int ub = 10000;
        while ( ub - lb > 1 ) {
          Int mid = ( lb + ub ) / 2;
          if ( lcm * mid <= desired ) {
            lb = mid;
          } else {
            ub = mid;
          }
        }
        res = std::max(res, lcm * lb);
      }
      return res;
    }

    static Int find_minimum_length( const Int& desired, const Int lcms[LCMS_SIZE], const Int lcms_cnt ) {
      Int res = std::numeric_limits<Int>::max();
      for ( int i = 0; i < lcms_cnt; ++ i ) {
        Int lcm = lcms[i];
        Int lb = -1;
        Int ub = 10000;
        while ( ub - lb > 1 ) {
          Int mid = ( lb + ub ) / 2;
          if ( lcm * mid >= desired ) {
            ub = mid;
          } else {
            lb = mid;
          }
          res = std::min(res, lcm * ub);
        }
      }
      return res;
    }

    static void generate_lcms( const Int& n, const Int coins[SIZE], Int lcms[LCMS_SIZE], Int& lcms_cnt ) {
      lcms_cnt = 0;
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = i + 1; j < n; ++ j ) {
          for ( int k = j + 1; k < n; ++ k ) {
            for ( int l = k + 1; l < n; ++ l ) {
              lcms[lcms_cnt ++] = math::lcm(coins[i], math::lcm(coins[j], math::lcm(coins[k], coins[l])));
            }
          }
        }
      }
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
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.n >> in.t ) ) {
        return false;
      }
      if ( in.n == 0 && in.t == 0 ) {
        return false;
      }
      for ( int i = 0; i < in.n; ++ i ) {
        std::cin >> in.coins[i];
      }
      for ( int i = 0; i < in.t; ++ i ) {
        std::cin >> in.tables[i];
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      for ( int i = 0; i < out.tables; ++ i ) {
        std::cout << out.max_length[i] << " " << out.min_length[i] << endl;
      }
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


