
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
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
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
  
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
  };
  
  struct OutputStorage {
    Int S2;
    Int R2;
    Int S3;
    Int R3;
    Int S4;
    Int R4;
  };
  
  struct DataStorage {
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
      out.S2 = f2(in.N);
      out.R2 = g2(in.N) - f2(in.N);
      out.S3 = f3(in.N);
      out.R3 = g3(in.N) - f3(in.N);
      out.S4 = f4(in.N);
      out.R4 = g4(in.N) - f4(in.N);
      return out;
    }
    
  protected:
    static Int f2( const int& n ) {
      Int res = 0;
      for ( int i = 0; i <= n; ++ i )
        res += i * i;
      return res;
    }

    static Int f3( const int& n ) {
      Int res = 0;
      for ( int i = 0; i <= n; ++ i )
        res += i * i * i;
      return res;
    }

    static Int f4( const int& n ) {
      Int res = 0;
      for ( int i = 0; i <= n; ++ i )
        res += i * i * i * i;
      return res;
    }

    static Int g2( const int& n ) {
      Int t = n * ( n + 1 ) / 2;
      return t * t;
    }

    static Int g3( const int& n ) {
      Int t = n * ( n + 1 ) / 2;
      return t * t * t;
    }

    static Int g4( const int& n ) {
      Int t = n * ( n + 1 ) / 2;
      return t * t * t * t;
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
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.N ) )
        return false;
      return true;
    }

    void output( const OutputStorage& out ) {
      std::cout << out.S2 << " " << out.R2 << " ";
      std::cout << out.S3 << " " << out.R3 << " ";
      std::cout << out.S4 << " " << out.R4 << endl;
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

