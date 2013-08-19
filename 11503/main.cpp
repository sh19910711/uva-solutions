
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

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef ValueType Type;
    VectorClass() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
    
    void fill( Type value ) {
      std::fill(data.begin(), data.end(), value);
    }
    
  private:
    std::vector<Type> data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_X> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_Z> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
}

// @snippet<sh19910711/contest:io/pair.cpp>
namespace io {
  template <class A, class B> std::ostream& operator<<( std::ostream& os, const std::pair<A,B>& p ) {
    return os << "(" << p.first << "," << p.second << ")";
  }
  template <class A, class B> std::istream& operator>>( std::istream& is, std::pair<A,B>& p ) {
    return is >> p.first >> p.second;
  }
}

// @snippet<sh19910711/contest:setlib/disjoints_set.cpp>
namespace setlib {
  class DisjointSets {
  public:
    std::vector<int> data;
    DisjointSets( int size ): data(size, -1) {};
    void init( int size ) { data.resize(size); std::fill( data.begin(), data.end(), -1 ); }
    bool merge( int x, int y ) {
      x = root(x), y = root(y);
      if ( x != y ) {
        if ( data[y] < data[x] ) std::swap( x, y );
        data[x] += data[y], data[y] = x;
      }
      return x != y;
    }
    bool same( int x, int y ) { return root(x) == root(y); }
    int root( int x ) { return data[x] < 0 ? x : data[x] = root(data[x]); }
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
  using namespace io;

  typedef setlib::DisjointSets UnionFind;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef std::pair<String, String> Friendship;
  typedef storage::Vector<Friendship, SIZE>::Type Friendships;
  typedef storage::Vector<Int, SIZE>::Type List;
  typedef storage::Vector<String, SIZE * 2>::Type Names;
  
  Int N;
  Friendships F;

  std::map<String, Int> name_to_id;
  std::map<Int, Int> group_size;
  Names names;
  Int person_id;

  List results;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      UnionFind uf(2 * N);
      add_name("Fred");
      Int fred_id = get_id("Fred");
      for ( int i = 0; i < 2 * N; ++ i )
        group_size[i] = 1;
      for ( int i = 0; i < N; ++ i ) {
        add_name(F[i].first);
        add_name(F[i].second);
        Int a = get_id(F[i].first);
        Int b = get_id(F[i].second);
        if ( uf.same(fred_id, a) || uf.same(fred_id, b) ) {
          if ( ! uf.same(a, b) ) {
            if ( uf.root(fred_id) == uf.root(a) ) {
              group_size[uf.root(fred_id)] += group_size[uf.root(b)];
            } else {
              group_size[uf.root(fred_id)] += group_size[uf.root(a)];
            }
            uf.merge(a, b);
          }
        } else {
          int new_size = group_size[uf.root(a)] + group_size[uf.root(b)];
          uf.merge(a, b);
          group_size[uf.root(a)] = new_size;
        }
        results[i] = group_size[uf.root(fred_id)];
      }
    }

    static const Int get_id( const String& name ) {
      return name_to_id[name];
    }

    static const void add_name( const String& name ) {
      if ( name_to_id.count(name) )
        return;
      name_to_id[name] = person_id ++;
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
    
    void init() {
      name_to_id.clear();
      group_size.clear();
      results.fill(0);
      person_id = 0;
    }
    
    bool input() {
      if ( ! ( std::cin >> N ) )
        return false;
      for ( int i = 0; i < N; ++ i )
        std::cin >> F[i];
      return true;
    }
    
    void output() {
      for ( int i = 0; i < N; ++ i ) {
        std::cout << results[i] << std::endl;
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





