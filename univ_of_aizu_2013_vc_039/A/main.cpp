
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
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    String S;
  };
  struct Output {
    Int result;
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
    
    void solve() {
      out->result = count(in->S);
    }

    Int count( const String& s ) {
      String table[9] = {
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz",
        " "
      };
      Int res = 0;
      for ( auto c : s ) {
        for ( auto i = 0; i < 9; ++ i ) {
          for ( auto j = 0; j < table[i].size(); ++ j ) {
            if ( c == table[i][j] ) {
              res += j + 1;
              break;
            }
          }
        }
      }
      return res;
    }
    
    bool input() {
      return std::getline(std::cin, in->S);
    }
    
    void output() {
      std::cout << out->result << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) { this->init(); }
    
    int input_number() {
      String line;
      std::getline(std::cin, line);
      std::istringstream iss(line);
      int res;
      iss >> res;
      return res;
    }

    int run() {
      int tests = input_number();
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
      std::cout << "Case #" << ( t_id + 1 ) << ": ";
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


