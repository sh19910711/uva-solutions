
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

// @snippet<sh19910711/contest-base:solution/define-classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
}

namespace solution {
  struct SolverInterface {
    // TODO: fix
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

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  // TODO: remove
}

// @snippet<sh19910711/contest-base:solution/solution-base-multi-tests.cpp>
namespace solution {
  struct SolutionBase: public SolutionInterface {
    virtual ~SolutionBase() {}; 
    virtual int run() {
      int tests = 0;
      std::cin >> tests;
      this->before_all_actions();
      for ( int i = 0; i < tests; ++ i ) {
        this->before_action(i);
        this->action();
        this->after_action(i);
      }
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
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  const Int FRIENDS = 3;
  const Int SIZE = 10000 + 11;
  const Int MAX_PROBLEM_ID = 10000 + 11;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int NA[FRIENDS];
    Int A[FRIENDS][SIZE];
  };
  struct OutputStorage {
    Int friends;
    Int NB[FRIENDS];
    Int F[FRIENDS];
    Int B[FRIENDS][SIZE];
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Search {
    const InputStorage* in;

    Int solved_cnt[FRIENDS];
    Int used_cnt[MAX_PROBLEM_ID];

    Int good_friends;
    Int F[FRIENDS];
    Int NB[FRIENDS];
    Int B[FRIENDS][SIZE];

    void run( const InputStorage* in ) {
      this->in = in;

      std::fill(used_cnt, used_cnt + MAX_PROBLEM_ID, 0LL);
      for ( int i = 0; i < FRIENDS; ++ i ) {
        count_used(in->NA[i], in->A[i]);
      }

      std::fill(solved_cnt, solved_cnt + FRIENDS, 0LL);
      for ( int i = 0; i < FRIENDS; ++ i ) {
        count_solved(i, in->NA[i], in->A[i]);
      }

      Int max_solved = *std::max_element(solved_cnt, solved_cnt + FRIENDS);
      good_friends = 0;
      for ( int i = 0; i < FRIENDS; ++ i ) {
        if ( solved_cnt[i] == max_solved ) {
          F[good_friends] = i + 1;
          NB[good_friends] = 0;
          for ( int j = 0; j < in->NA[i]; ++ j ) {
            if ( used_cnt[in->A[i][j]] == 1 )
              B[good_friends][NB[good_friends] ++] = in->A[i][j];
          }
          good_friends ++;
        }
      }

      for ( int i = 0; i < good_friends; ++ i )
        std::sort(B[i], B[i] + NB[i]);
    }

    void count_used( const Int& N, const Int A[SIZE] ) {
      for ( int i = 0; i < N; ++ i )
        used_cnt[A[i]] ++;
    }

    void count_solved( const int& f_id, const Int& N, const Int A[SIZE] ) {
      for ( int i = 0; i < N; ++ i )
        if ( used_cnt[A[i]] == 1 )
          solved_cnt[f_id] ++;
    }
  };

  struct Solver: SolverInterface {
    Search search;
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      search.run(in);
      out->friends = search.good_friends;
      std::copy(search.F, search.F + FRIENDS, out->F);
      std::copy(search.NB, search.NB + FRIENDS, out->NB);
      for ( int i = 0; i < out->friends; ++ i ) {
        std::copy(search.B[i], search.B[i] + search.NB[i], out->B[i]);
      }
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      for ( int i = 0; i < FRIENDS; ++ i ) {
        std::cin >> in->NA[i];
        for ( int j = 0; j < in->NA[i]; ++ j ) {
          std::cin >> in->A[i][j];
        }
      }
      return true;
    }
    void output( const OutputStorage* out ) {
      for ( int i = 0; i < out->friends; ++ i ) {
        std::cout << out->F[i] << " " << out->NB[i];
        if ( out->NB[i] > 0 )
          std::cout << " ";
        for ( int j = 0; j < out->NB[i]; ++ j ) {
          std::cout << out->B[i][j];
          if ( j + 1 < out->NB[i] ) 
            std::cout << " ";
        }
        std::cout << std::endl;
      }
    }
    void before_action( const int& tid ) {
      std::cout << "Case #" << tid + 1 << ":" << std::endl;
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


