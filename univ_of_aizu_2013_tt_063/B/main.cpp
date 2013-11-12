
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

namespace setlib {
  template <typename KeyType> class DisjointSets {
  public:
    std::vector<int> data;
    std::map<KeyType, int> keys;
    DisjointSets( int size ): data(size + 10, -1) {};
    bool merge( KeyType key_x, KeyType key_y ) {
      int x = root(key_x), y = root(key_y);
      if ( x != y ) {
        if ( data[y] < data[x] ) std::swap( x, y );
        data[x] += data[y], data[y] = x;
      }
      return x != y;
    }
    int get_key( KeyType key ) {
      if ( ! keys.count(key) )
        return keys[key] = keys.size();
      return keys[key];
    }
    bool same( KeyType x, KeyType y ) { return root(x) == root(y); }
    int root( KeyType x ) {
      int key = get_key(x);
      return data[key] < 0 ? key : data[key] = root(data[key]);
    }
    int root( int key ) {
      return data[key] < 0 ? key : data[key] = root(data[key]);
    }
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
  const int SIZE = 1000 + 11;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef setlib::DisjointSets<std::string> UnionFind;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int n;
    int m;
    string from[SIZE];
    string to[SIZE];
  };
  
  struct OutputStorage {
    int result;
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
      out.result = get_faces(in.n, in.m, in.from, in.to);
      return out;
    }
    
  protected:
    static int get_faces( const int& n, const int& m, const string from[SIZE], const string to[SIZE] ) {
      int res = 1;
      UnionFind uf(n);
      for ( int i = 0; i < m; ++ i ) {
        if ( uf.same(from[i], to[i]) ) {
          res ++;
        }
        uf.merge(from[i], to[i]);
      }
      return res;
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
      if ( ! ( std::cin >> in.n >> in.m ) )
        return false;
      for ( int i = 0; i < in.m; ++ i )
        std::cin >> in.from[i] >> in.to[i];
      return true;
    }
    
    void output( const OutputStorage& out ) {
      std::cout << out.result << endl;
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


