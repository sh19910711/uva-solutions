
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif

// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const String YES = "S";
  const String NO = "T";
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    String S;
  };
  struct Output {
    bool result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-multi-tests.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    void init() {
    }

    Int get_sum( const String& s ) {
      Int res = 0;
      for ( auto c : s ) {
        res += c - '0';
      }
      return res;
    }

    String to_string( const Int& x ) {
      std::ostringstream oss;
      oss << x;
      return oss.str();
    }
    
    void solve() {
      out->result = check(in->S);
    }

    bool check( const String& s ) {
      Int cnt[3] = {0, 0, 0};
      Int sum = 0;
      for ( auto c : s ) {
        cnt[(c - '0') % 3] ++;
        sum += ( c - '0' );
        sum %= 3;
      }
      if ( sum == 0 ) {
        return cnt[0] % 2 == 1;
      }
      return ! ( cnt[0] % 2 == 1 && cnt[sum] > 0 ) && ! ( cnt[sum] == 0 );
    }
    
    bool input() {
      return std::cin >> in->S;
    }
    
    void output() {
      std::cout << ( out->result ? YES : NO ) << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) { this->init(); }
    
    int run() {
      int tests = 0;
      std::cin >> tests;
      for ( int i = 0; i < tests; ++ i ) {
        this->before_action(i);
        this->action();
        this->after_action(i);
      }
      return 0;
    }
    
    bool action() {
      if ( ! this->input() ) {
        return false;
      }
      this->solve();
      this->output();
      return true;
    }
    
    void before_action( const int& t_id ) {
      std::cout << "Case " << ( t_id + 1 ) << ": ";
    }
    
    void after_action( const int& t_id ) {}
    
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using namespace solution;
  static Input in;
  static Output out;
  static Solution sol(&in, &out);
  return sol.run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>


