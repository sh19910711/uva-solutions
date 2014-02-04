
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
  const Int BOXES = 4;
  const Int SIZE = 6;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::string String;
  typedef std::array<String, SIZE> StringArray;
  typedef std::array<StringArray, BOXES> StringTable;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
    StringTable T;
  };
  
  struct Output {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  int box_id_list[24][6] = {
    {0, 1, 2, 3, 4, 5}, 
    {0, 2, 4, 1, 3, 5}, 
    {0, 3, 1, 4, 2, 5}, 
    {0, 4, 3, 2, 1, 5}, 
    {1, 0, 3, 2, 5, 4}, 
    {1, 2, 0, 5, 3, 4}, 
    {1, 3, 5, 0, 2, 4}, 
    {1, 5, 2, 3, 0, 4}, 
    {2, 0, 1, 4, 5, 3}, 
    {2, 1, 5, 0, 4, 3}, 
    {2, 4, 0, 5, 1, 3}, 
    {2, 5, 4, 1, 0, 3}, 
    {3, 0, 4, 1, 5, 2}, 
    {3, 1, 0, 5, 4, 2}, 
    {3, 4, 5, 0, 1, 2}, 
    {3, 5, 1, 4, 0, 2}, 
    {4, 0, 2, 3, 5, 1}, 
    {4, 2, 5, 0, 3, 1}, 
    {4, 3, 0, 5, 2, 1}, 
    {4, 5, 3, 2, 0, 1}, 
    {5, 1, 3, 2, 4, 0}, 
    {5, 2, 1, 4, 3, 0}, 
    {5, 3, 4, 1, 2, 0}, 
    {5, 4, 2, 3, 1, 0}
  };

  template <class FaceType> struct Box {
    int cur;
    FaceType faces[6];

    Box(): cur(0) {}

    void set_face( const int& x, const FaceType& type ) {
      this->faces[x] = type;
    }

    FaceType* get_faces() {
      FaceType next[6];
      for ( int i = 0; i < 6; ++ i )
        next[i] = faces[box_id_list[cur][i]];
      for ( int i = 0; i < 6; ++ i )
        this->faces[i] = next[i];
      return this->faces;
    }

    bool next() {
      if ( this->cur + 1 >= 0 && this->cur + 1 < 24 ) {
        this->cur += 1;
        this->get_faces();
        return true;
      }
      return false;
    }

    FaceType& operator[]( const int& x ) {
      return faces[x];
    }

    friend std::ostream& operator <<( std::ostream& os, Box<FaceType>& box ) {
      for ( int i = 0; i < 6; ++ i )
        os << box.faces[i] << ", ";
      return os;
    }
  };

  struct Counter {
    typedef Box<int> IntBox;
    typedef std::array<IntBox, BOXES> IntBoxArray;
    typedef std::map<String, Int> StringMap;

    StringMap color;
    IntBoxArray boxes;
    Int best;

    void init() {
      init_boxes();
      best = std::numeric_limits<Int>::max();
    }

    void init_boxes() {
      Int cnt = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          if ( color.count(in->T[i][j]) ) {
            boxes[i][j] = color[in->T[i][j]];
          } else {
            color[in->T[i][j]] = cnt;
            boxes[i][j] = cnt;
            cnt += 1;
          }
        }
      }
    }

    void rotate( const Int& cur ) {
      if ( cur >= in->N ) {
        update();
        return;
      }
      for ( auto i = 0; i < 24; ++ i ) {
        boxes[cur].cur = i;
        boxes[cur].get_faces();
        rotate(cur + 1);
      }
    }

    void update() {
      Int sum = 0;
      for ( auto i = 0; i < SIZE; ++ i ) {
        Int best_cnt = std::numeric_limits<Int>::max();
        for ( auto t = 0; t < in->N; ++ t ) {
          Int cnt = 0;
          for ( auto j = 0; j < in->N; ++ j ) {
            if ( boxes[t][i] != boxes[j][i] )
              cnt ++;
          }
          min(best_cnt, cnt);
        }
        sum += best_cnt;
      }
      min(best, sum);
    }

    Int count() {
      rotate(0);
      return best;
    }

    const Input* in;
    Counter(const Input* in): in(in) { init(); }
  };
  typedef std::unique_ptr<Counter> CounterPointer;

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      auto counter = CounterPointer(new Counter(in));
      out->result = counter->count();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N && in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          if ( ! ( std::cin >> in->T[i][j] ) )
            return false;
        }
      }
      return true;
    }
    void output( const Output* out ) {
      std::cout << out->result << std::endl;
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

