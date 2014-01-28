
// @snippet<sh19910711/contest-base:headers.cpp>
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

// TODO: add snippet
#include <memory>
#include <array>

// @snippet<sh19910711/contest-base:solution/define-classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    SolverInterface* solver;
    Storages* storages;
    virtual int run() = 0;
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
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
  };
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100000 + 11;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Int S[SIZE];
    Int T[SIZE];
    Int P[SIZE];
  };
  struct OutputStorage {
    Int result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Search {
    enum PointIndex { POINT_POS, POINT_TYPE, POINT_ID, POINT_REV };
    enum PointType { TYPE_P, TYPE_S, TYPE_T, TYPE_NONE };
    typedef std::tuple <Int, PointType, Int, bool> Point; // pos, type, id, rev
    const InputStorage* in;
    static const Int MAX_N = 3 * 100000 + 11;

    Int N;
    Int P_v[MAX_N];
    Point P[MAX_N];
    Int sum_p[MAX_N];

    Int run() {
      N = 0;
      init_points();
      init_sum_p();

      for ( auto i = 0; i < N; ++ i ) {
        if ( std::get<POINT_TYPE>(P[i]) == TYPE_S ) {
          auto l_id = std::get<POINT_ID>(P[i]);
          auto l = std::lower_bound(P_v, P_v + N, in->S[l_id]) - P_v;
          auto r = std::lower_bound(P_v, P_v + N, in->T[l_id]) - P_v;
          if ( in->S[l_id] > in->T[l_id] ) {
            std::get<POINT_TYPE>(P[l]) = TYPE_T;
            std::get<POINT_TYPE>(P[r]) = TYPE_S;
            std::get<POINT_REV>(P[l]) = true;
            std::get<POINT_REV>(P[r]) = true;
          }
        }
      }

      Int res = 0;
      Int a = 0;
      Int b = 0;
      for ( auto i = 0; i + 1 < N; ++ i ) {
        if ( std::get<POINT_TYPE>(P[i]) == TYPE_P ) {
          std::swap(a, b);
        } else if ( std::get<POINT_TYPE>(P[i]) == TYPE_S ) {
          auto l_id = std::get<POINT_ID>(P[i]);
          auto l = std::lower_bound(P_v, P_v + N, in->S[l_id]) - P_v;
          auto r = std::lower_bound(P_v, P_v + N, in->T[l_id]) - P_v;
          auto s = get_sum(l, r);
          if ( std::get<POINT_REV>(P[i]) ) {
            if ( s % 2 == 0 ) {
              a ++;
            } else {
              b ++;
            }
          } else {
            a ++;
          }
        } else if ( std::get<POINT_TYPE>(P[i]) == TYPE_T ) {
          auto l_id = std::get<POINT_ID>(P[i]);
          auto l = std::lower_bound(P_v, P_v + N, in->S[l_id]) - P_v;
          auto r = std::lower_bound(P_v, P_v + N, in->T[l_id]) - P_v;
          auto s = get_sum(l, r);
          if ( std::get<POINT_REV>(P[i]) ) {
            if ( s % 2 == 0 ) {
              b --;
            } else {
              a --;
            }
          } else {
            if ( s % 2 == 0 ) {
              a --;
            } else {
              b --;
            }
          }
        }
        if ( i + 1 < N ) {
          res += a * ( P_v[i + 1] - P_v[i]);
        } else {
          res += a;
        }
        // cout << P_v[i] << ": inc = " << a << ", no inc = " << b << ", res = " << res << endl;
      }
      return res;
    }

    // [l, r]
    Int get_sum( const Int& l, const Int& r ) {
      Int mi = std::min(l, r);
      Int ma = std::max(l, r);
      return sum_p[ma] - sum_p[mi - 1];
    }

    void init_sum_p() {
      Int sum = 0;
      for ( auto i = 0; i < N; ++ i ) {
        if ( std::get<POINT_TYPE>(P[i]) == TYPE_P ) {
          sum ++;
        }
        sum_p[i] = sum;
      }
    }

    void init_points() {
      for ( auto i = 0; i < in->N; ++ i )
        P[N ++] = Point(in->S[i], TYPE_S, i, false);
      for ( auto i = 0; i < in->N; ++ i )
        P[N ++] = Point(in->T[i], TYPE_T, i, false);
      for ( auto i = 0; i < in->M; ++ i )
        P[N ++] = Point(in->P[i], TYPE_P, i, false);
      std::sort(P, P + N);
      for ( int i = 0; i < N; ++ i )
        P_v[i] = std::get<POINT_POS>(P[i]);
    }
  };

  struct Solver: SolverInterface {
    Search search;
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      this->search.in = in;
      out->result = this->search.run();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        std::cin >> in->S[i] >> in->T[i];
      for ( auto i = 0; i < in->M; ++ i )
        std::cin >> in->P[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->result << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  using namespace solution;
  std::cin.sync_with_stdio(false);
  static InputStorage in;
  static OutputStorage out;
  static Storages storages;
  static Solution solution;
  static Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

