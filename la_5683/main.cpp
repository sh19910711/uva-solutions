
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <iomanip>
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
        this->action();
      }
      return 0;
    }
    
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
  const String NONE = "--:--";
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  String A, B, C;

  String result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = to_string(find_correct_time(to_int(A), to_int(B), to_int(C)));
    }

    const Int to_int( const String& s ) {
      String t = s;
      replace(t.begin(), t.end(), ':', ' ');
      ISS iss(t);
      Int hh, mm;
      iss >> hh >> mm;
      return hh * 60 + mm;
    }

    const String to_string( const Int& t ) {
      if ( t == -1 )
        return NONE;
      Int hh, mm;
      hh = t / 60;
      mm = t % 60;
      OSS oss;
      oss << setw(2) << setfill('0') << hh << ":" << setw(2) << setfill('0') << mm;
      return oss.str();
    }

    const Int find_correct_time( const Int& A, const Int& B, const Int& C ) {
      int state = 0;
      if ( check_correct_time(A, B, C) )
        state |= 1 << 1;
      if ( check_correct_time(B, C, A) )
        state |= 1 << 2;
      if ( check_correct_time(C, A, B) )
        state |= 1 << 3;
      if ( check_correct_time(A, C, B) )
        state |= 1 << 4;
      if ( check_correct_time(B, A, C) )
        state |= 1 << 5;
      if ( check_correct_time(C, B, A) )
        state |= 1 << 6;
      if ( __builtin_popcount(state) <= 2 ) {
        if ( check_correct_time(A, B, C) )
          return A;
        if ( check_correct_time(B, C, A) )
          return B;
        if ( check_correct_time(C, A, B) )
          return C;
        if ( check_correct_time(A, C, B) )
          return A;
        if ( check_correct_time(B, A, C) )
          return B;
        if ( check_correct_time(C, B, A) )
          return C;
      }
      return -1;
    }

    const bool check_correct_time( const Int& A, const Int& B, const Int& C ) {
      for ( int x = 0; x <= 480; ++ x ) {
        if ( normalize(A) == normalize(B - x) )
          if ( normalize(A) == normalize(C + x) )
            return true;
      }
      return false;
    }

    const Int normalize( const Int& t ) {
      if ( t < 0 )
        return 12 * 60 - t;
      if ( t >= 12 * 60 )
        return t - 12 * 60;
      return t;
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
      return std::cin >> A >> B >> C;
    }

    void output() {
      if ( result != NONE ) {
        std::cout << "The correct time is " << result << std::endl;
      } else {
        std::cout << "Look at the sun" << std::endl;
      }
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


