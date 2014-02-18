
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
  const Int SIZE = 3;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<IntArray, SIZE> IntMatrix;
  typedef std::map<IntMatrix, Int> IntMatrixMap;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    IntMatrix mat;
  };
  struct Output {
    Int result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    IntMatrixMap table;
    IntMatrix mat;
    IntMatrix zero;

    void init() {
      for ( auto i = 0; i < SIZE; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          zero[i][j] = 0;
        }
      }
      rec(0, 0);
    }

    void print_matrix( const IntMatrix& mat ) {
      for ( auto i = 0; i < SIZE; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

    IntMatrix f( const IntMatrix& mat ) {
      IntMatrix res;
      for ( auto i = 0; i < SIZE; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          res[i][j] = 0;
        }
      }
      for ( auto i = 0; i < SIZE; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          const int dr[4] = {1, -1, 0, 0};
          const int dc[4] = {0, 0, 1, -1};

          for ( int k = 0; k < 4; ++ k ) {
            int nr = i + dr[k];
            int nc = j + dc[k];
            if ( nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE )
              continue;
            res[i][j] += mat[nr][nc];
            res[i][j] %= Int(2);
          }
        }
      }
      return res;
    }

    void rec( const Int& r, const Int& c ) {
      if ( r >= SIZE ) {
        // print_matrix(mat);
        if ( mat == zero ) {
          table[mat] = -1;
        } else {
          Int cnt = 0;
          IntMatrix cur = mat;
          while ( cur != zero ) {
            cur = f(cur);
            cnt += 1;
          }
          table[mat] = cnt - 1;
        }
        return;
      }
      if ( c >= SIZE ) {
        return rec(r + 1, 0);
      }
      for ( int i = 0; i < 2; ++ i ) {
        mat[r][c] = i;
        rec(r, c + 1);
      }
    }
    
    void solve() {
      out->result = table[in->mat];
    }
    
    bool input() {
      for ( auto i = 0; i < SIZE; ++ i ) {
        String s;
        std::cin >> s;
        for ( auto j = 0; j < SIZE; ++ j ) {
          in->mat[i][j] = s[j] - '0';
        }
      }
      return true;
    }
    
    void output() {
      std::cout << out->result << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) { this->init(); }
    
    int run() {
      int tests;
      std::cin >> tests;
      for ( int i = 0; i < tests; ++ i ) {
        this->before_action(i);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(i);
      };
      return 0;
    }
    
    bool action() {
      if ( ! this->input() ) return false;
      this->solve();
      this->output();
      return true;
    }
    
    void before_action( const int& t_id ) {}
    
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

