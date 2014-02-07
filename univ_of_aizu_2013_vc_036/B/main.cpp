
// @snippet<sh19910711/contest-base:headers.cpp>
#define __THIS_IS_CPP11__
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

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest:utils/collection_prototype.cpp>
namespace utils {
  // collection
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value );
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t );
  template <class T> void copy( const T& s, const int& n, T& t );
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v );
  template <class T> void sort( T& v, const int& n );
#endif
}

// @snippet<sh19910711/contest:utils/misc_prototype.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b );
  template <class T> void min( T& a, const T& b );
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v );
  template <class T> T to_type( const std::string& s );
  
}

// @snippet<sh19910711/contest:utils_prototypes.cpp>

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct Input;
  struct Output;
  struct Storages {
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const Output* solve( const Input* in, Output* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    virtual int run()                             = 0;
    virtual bool action()                         = 0;
    virtual bool input( Input* s )         = 0;
    virtual void output( const Output* s ) = 0;
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    SolverInterface* solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    
    int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
    
    bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100;
  
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::set<Int> IntSet;
  typedef std::array<bool, SIZE> BoolArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
  };
  
  struct Output {
    bool is_perfect;
    bool is_prime;
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    BoolArray is_prime;
    BoolArray is_perfect;

    Solver() {
      fill(is_prime, SIZE, true);
      fill(is_perfect, SIZE, false);

      for ( Int i = 0; i <= 31; ++ i ) {
        for ( Int j = 2; j < i; ++ j ) {
          if ( i % j == 0 )
            is_prime[i] = false;
        }
      }

      for ( Int i = 1; i <= 31 ; ++ i ) {
        is_perfect[i] = is_relative_perfect(i);
      }
    }

    const Output* solve( const Input* in, Output* out ) {
      out->is_prime = is_prime[in->N];
      if ( is_perfect[in->N] ) {
        out->is_perfect = true;
        out->result = calc(in->N);
      } else {
        out->is_perfect = false;
      }
      return out;
    }

    static IntSet generate_factors_right( const Int& x ) {
      IntSet factors;
      Int tmp = get_number_right(x);
      factors.insert(tmp);
      for ( Int i = 3; i * i <= tmp; ++ i ) {
        if ( tmp % i == 0 )
          factors.insert(i);
      }
      return factors;
    }

    static IntSet generate_factors_left( const Int& x ) {
      IntSet factors;
      Int tmp = 1;
      for ( Int i = 0; i < x; ++ i ) {
        factors.insert(tmp);
        tmp *= 2;
      }
      return factors;
    }

    static Int calc( const Int& k ) {
      return get_number_left(k) * get_number_right(k);
    }

    static Int get_number_left( const Int& k ) {
      return std::pow(Int(2), k - 1);
    }

    static Int get_number_right( const Int& k ) {
      return std::pow(Int(2), k) - 1;
    }

    static bool is_relative_perfect( const Int& x ) {
      auto factors_left = generate_factors_left(x);
      auto factors_right = generate_factors_right(x);
      IntSet factors;
      factors.insert(std::begin(factors_left), std::end(factors_left));
      factors.insert(std::begin(factors_right), std::end(factors_right));
      Int tmp = calc(x);
      for ( auto f1 : factors_left ) {
        for ( auto f2 : factors_right ) {
          if ( f1 * f2 < tmp )
            factors.insert(f1 * f2);
        }
      }
      Int sum = std::accumulate(std::begin(factors), std::end(factors), Int(0));
      return sum == tmp;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N && in->N ) )
        return false;
      return true;
    }
    void output( const Output* out ) {
      if ( out->is_perfect ) {
        std::cout << "Perfect: " << out->result << "!" << std::endl;
      } else {
        if ( out->is_prime ) {
          std::cout << "Given number is prime. But, NO perfect number is available." << std::endl;
        } else {
          std::cout << "Given number is NOT prime! NO perfect number is available." << std::endl;
        }
      }
    }
  };
}

// @snippet<sh19910711/contest-base:main_func.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // desc: http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html#id18
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  // 
  using namespace solution;
  static Input in;
  static Output out;
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

// @snippet<sh19910711/contest:utils/collection.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value ) { std::fill(std::begin(v), std::begin(v) + n, value); }
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t ) { std::copy(std::begin(s), std::end(s), std::begin(t)); }
  template <class T> void copy( const T& s, const int& n, T& t ) { std::copy(std::begin(s), std::begin(s) + n, std::begin(t)); }
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v ) { std::sort(std::begin(v), std::end(v)); }
  template <class T> void sort( T& v, const int& n ) { std::sort(std::begin(v), std::begin(v) + n); }
#endif
}

// @snippet<sh19910711/contest:utils/misc.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b ) { a = std::max(a, b); }
  template <class T> void min( T& a, const T& b ) { a = std::min(a, b); }
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v ) { std::ostringstream oss; oss << v; return oss.str(); }
  template <class T> T to_type( const std::string& s ) { std::istringstream iss(s); T res; iss >> res; return res; }
  
}

// @snippet<sh19910711/contest:utils.cpp>

// @snippet<sh19910711/contest-base:main.cpp>

