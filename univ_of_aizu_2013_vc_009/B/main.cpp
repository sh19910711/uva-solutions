
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
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( Storages& s ) { return false; };
    virtual void output( const Storages& s ) const {};
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
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
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
  const Int SIZE = 30 + 1;
  const Int ORDER_SIZE = 5;
  const char ANY = '*';
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  class Storages {
  public:
    Int H, W;
    String M[SIZE];

    String result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.result = find_order(s.H, s.W, s.M);
    }

  protected:
    static String find_order( const Int& H, const Int& W, const String* M ) {
      String order = "ABCDE";
      String tmp[SIZE];
      do {
        for ( int i = 0; i < H; ++ i )
          tmp[i] = M[i];
        if ( check_order(order, 0, H, W, tmp) )
          return order;
      } while ( std::next_permutation(order.begin(), order.end()) );
      return "NONE";
    }

    static bool check_order( const String& order, const Int& id, const Int& H, const Int& W, String* M ) {
      if ( id >= ORDER_SIZE )
        return true;
      const char& c = order[ORDER_SIZE - id - 1];
      const int fw_[5] = {4, 4, 3, 6, 6};
      const int fh_[5] = {4, 5, 4, 5, 8};
      const int fw = fw_[c - 'A'];
      const int fh = fh_[c - 'A'];
      for ( int sr = 0; sr + fh - 1 < H; ++ sr ) {
        for ( int sc = 0; sc + fw - 1 < W; ++ sc ) {
          if ( M[sr][sc] == c ) {
            if ( check_frame(M, sr, sc, c, fh, fw) ) {
              fill_frame(sr, sc, fh, fw, M);
              if ( check_order(order, id + 1, H, W, M) )
                return true;
            }
            return false;
          }
        }
      }
      return false;
    }

    static bool is_valid_cell( const char& a, const char& b ) {
      return a == b || a == ANY;
    }

    static bool check_frame( const String* M, const Int& sr, const Int& sc, const char& c, const Int& fh, const Int& fw ) {
      for ( int i = 0; i < fw; ++ i )
        if ( ! is_valid_cell(M[sr][sc + i], c) )
          return false;
      for ( int i = 0; i < fw; ++ i )
        if ( ! is_valid_cell(M[sr + fh - 1][sc + i], c) )
          return false;
      for ( int i = 0; i < fh; ++ i )
        if ( ! is_valid_cell(M[sr + i][sc + fw - 1], c) )
          return false;
      for ( int i = 0; i < fh; ++ i )
        if ( ! is_valid_cell(M[sr + i][sc], c) )
          return false;
      return true;
    }

    static void fill_frame( const Int& sr, const Int& sc, const Int& fh, const Int& fw, String* M )  {
      for ( int i = 0; i < fw; ++ i )
        M[sr][sc + i] = ANY;
      for ( int i = 0; i < fw; ++ i )
        M[sr + fh - 1][sc + i] = ANY;
      for ( int i = 0; i < fh; ++ i )
        M[sr + i][sc + fw - 1] = ANY;
      for ( int i = 0; i < fh; ++ i )
        M[sr + i][sc] = ANY;
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
      this->init();
      if ( ! this->input(*this->storages) )
        return false;
      solver.solve(*this->storages);
      this->output(*this->storages);
      return true;
    }

    bool input( Storages& s ) {
      if ( ! ( std::cin >> s.H >> s.W ) )
        return false;
      for ( int i = 0; i < s.H; ++ i )
        std::cin >> s.M[i];
      return true;
    }

    void output( const Storages& s ) const {
      std::cout << s.result << endl;
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

