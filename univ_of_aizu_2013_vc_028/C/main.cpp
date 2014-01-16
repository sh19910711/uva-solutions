
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
  const int MAX_LINES = 10000 + 11;
  const int MAX_TOKENS = 10000 + 11;

  const int BIG_NUMBERS_TYPES = 14;
  const String BIG_NUMBERS_CHAR = "0123456789+-*/";
  const String BIG_NUMBERS[BIG_NUMBERS_TYPES][5] = {
    // 0
    {
      "000",
      "0.0",
      "0.0",
      "0.0",
      "000",
    },
    // 1
    {
      ".0.",
      ".0.",
      ".0.",
      ".0.",
      ".0.",
    },
    // 2
    {
      "000",
      "..0",
      "000",
      "0..",
      "000",
    },
    // 3
    {
      "000",
      "..0",
      "000",
      "..0",
      "000",
    },
    // 4
    {
      "0.0",
      "0.0",
      "000",
      "..0",
      "..0",
    },
    // 5
    {
      "000",
      "0..",
      "000",
      "..0",
      "000",
    },
    // 6
    {
      "0..",
      "0..",
      "000",
      "0.0",
      "000",
    },
    // 7
    {
      "000",
      "..0",
      "..0",
      "..0",
      "..0",
    },
    // 8
    {
      "000",
      "0.0",
      "000",
      "0.0",
      "000",
    },
    // 9
    {
      "000",
      "0.0",
      "000",
      "..0",
      "..0",
    },
    // +
    {
      ".0.",
      ".0.",
      "000",
      ".0.",
      ".0.",
    },
    // -
    {
      "...",
      "...",
      "000",
      "...",
      "...",
    },
    // *
    {
      "0.0",
      "0.0",
      ".0.",
      "0.0",
      "0.0",
    },
    // /
    {
      ".0.",
      "...",
      "000",
      "...",
      ".0.",
    },
  };
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    String lines[MAX_LINES];
  };
  
  struct OutputStorage {
    String result;
  };
  
  struct DataStorage {
    String expr;
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
      data.expr = get_expr(in.lines);
      out.result = get_result(data.expr);
      return out;
    }
    
  protected:
    static String get_result( String expr ) {
      String token[MAX_TOKENS];
      Int tokens = get_tokens(token, expr);

      for ( int i = 0; i < tokens; ++ i ) {
        if ( is_sign(token[i][0]) ) {
          if ( token[i] == "*" ) {
            Int l = to_int(token[i - 1]);
            Int r = to_int(token[i + 1]);
            Int tmp = l * r;
            token[i - 1] = to_string(tmp);
            for ( int k = i; k < tokens; ++ k ) {
              token[k] = token[k + 2];
            }
            tokens -= 2;
            i -= 1;
          } else if ( token[i] == "/" ) {
            Int l = to_int(token[i - 1]);
            Int r = to_int(token[i + 1]);
            Int tmp = l / r;
            token[i - 1] = to_string(tmp);
            for ( int k = i; k < tokens; ++ k ) {
              token[k] = token[k + 2];
            }
            tokens -= 2;
            i -= 1;
          }
        }
      }

      Int res = to_int(token[0]);
      for ( int i = 1; i < tokens; i += 2 ) {
        if ( token[i] == "+" ) {
          res += to_int(token[i + 1]);
        } else {
          res -= to_int(token[i + 1]);
        }
      }
      return to_string(res);
    }

    static bool is_sign( char c ) {
      return c == '+' || c == '-' || c == '*' || c == '/';
    }

    static Int get_tokens( String token[MAX_TOKENS], String expr ) {
      Int res = 0;
      Int len = expr.length();
      String tmp;
      tmp += expr[0];
      for ( int i = 1; i < len; ++ i ) {
        if ( is_sign(expr[i - 1]) == is_sign(expr[i]) ) {
          tmp += expr[i];
        } else {
          token[res ++] = tmp;
          tmp = "";
          tmp += expr[i];
        }
      }
      if ( tmp != "" ) {
        token[res ++] = tmp;
      }
      return res;
    }

    static String to_string( Int x ) {
      std::ostringstream oss;
      oss << x;
      return oss.str();
    }

    static Int to_int( String x ) {
      std::istringstream iss(x);
      Int res;
      iss >> res;
      return res;
    }

    static String get_expr( const String lines[MAX_LINES] ) {
      Int len = lines[0].length() / 4 + 1;
      String res;
      for ( int k = 0; k < len; ++ k ) {
        res += find_big_number_char(lines, k);
      }
      return res;
    }

    static char find_big_number_char( const String lines[MAX_LINES], int k ) {
      for ( int i = 0; i < BIG_NUMBERS_TYPES; ++ i ) {
        if ( find_big_number_char(lines, k, i) ) {
          return BIG_NUMBERS_CHAR[i];
        }
      }
      return '0';
    }

    static bool find_big_number_char( const String lines[MAX_LINES], int k, int t ) {
      for ( int r = 0; r < 5; ++ r ) {
        for ( int c = 0; c < 3; ++ c ) {
          if ( lines[r][k * 4 + c] != BIG_NUMBERS[t][r][c] ) {
            return false;
          }
        }
      }
      return true;
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
      for ( int i = 0; i < 6; ++ i ) {
        std::getline(std::cin, in.lines[i]);
      }
      bool ret = is_terminated(in);
      return ! ret;
    }

    bool is_terminated( const InputStorage& in ) {
      if ( in.lines[0] != "000" || in.lines[4] != "000" )
        return false;
      for ( int i = 1; i < 4; ++ i ) {
        if ( in.lines[i] != "0.0" )
          return false;
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      Int len = out.result.length();
      String buf[5];
      for ( int i = 0; i < 5; ++ i ) {
        buf[i] = String(len * 4 - 1, ' ');
      }
      for ( int i = 0; i < len; ++ i ) {
        draw_big_number(buf, i, (int)(out.result[i] - '0'));
      }
      for ( int i = 0; i < 5; ++ i ) {
        std::cout << buf[i] << std::endl;
      }
      std::cout << std::endl;
    }

    void draw_big_number( String buf[5], int pos, int x ) const {
      for ( int r = 0; r < 5; ++ r ) {
        for ( int c = 0; c < 3; ++ c ) {
          buf[r][pos * 4 + c] = BIG_NUMBERS[x][r][c];
        }
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

