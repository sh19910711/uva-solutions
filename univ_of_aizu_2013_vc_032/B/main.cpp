
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

// @snippet<sh19910711/contest-base:solution/solution-base-queries.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    int queries;
    virtual ~SolutionBase() {};
    virtual bool input_query( InputStorage* in ) { return false; }
    virtual bool action() {
      if ( ! this->input(this->storages->in) )
        return false;
      for ( int i = 0; i < queries; ++ i ) {
        this->input_query(this->storages->in);
        this->output(this->solver->solve(this->storages->in, this->storages->out));
      }
      return true;
    }
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
  const string YES = "theorem";
  const string NO = "no-theorem";
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    string S;
  };
  struct OutputStorage {
    bool result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = check(in->S);
      return out;
    }

    static bool check( const string& s ) {
      if ( ! has_invalid_char(s) )
        return false;
      if ( ! check_order(s) )
        return false;
      if ( ! check_questions(s) )
        return false;
      return true;
    }

    static bool check_questions( const string& s ) {
      auto a = std::distance(begin(s), std::find(begin(s), end(s), 'M'));
      auto b = std::distance(std::find(begin(s), end(s), 'M'), std::find(begin(s), end(s), 'E')) - 1;
      auto c = std::distance(std::find(begin(s), end(s), 'E'), end(s)) - 1;
      return a >= 1 && b >= 1 && c >= 2 && a + b == c;
    }

    static bool check_order( const string& s ) {
      bool has_m = false;
      bool has_e = false;
      int n = s.size();
      for ( auto i = 0; i < n; ++ i ) {
        if ( s[i] == 'M' ) {
          if ( has_e )
            return false;
          if ( has_m )
            return false;
          has_m = true;
        } else if ( s[i] == 'E' ) {
          if ( ! has_m )
            return false;
          if ( has_e )
            return false;
          has_e = true;
        }
      }
      return has_m & has_e;
    }

    static bool has_invalid_char( const string& s ) {
      int n = s.size();
      for ( int i = 0; i < n; ++ i ) {
        if ( s[i] != '?' && s[i] != 'M' && s[i] != 'E' )
          return false;
      }
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      return std::cin >> this->queries;
    }
    bool input_query( InputStorage* in ) {
      return std::cin >> in->S;
    }
    void output( const OutputStorage* out ) {
      std::cout << ( out->result ? YES : NO ) << std::endl; 
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


