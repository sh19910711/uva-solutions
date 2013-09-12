
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

// @snippet<sh19910711/contest:solution/solution-base-multi-tests.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      int tests = 0;
      std::cin >> tests;
      for ( int i = 0; i < tests; ++ i ) {
        this->before_action(i);
        this->action();
        this->after_action(i);
      }
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer_reference_count.cpp>
namespace misc {
  class SmartPointerReferenceCount {
  public:
    void add() { count ++; }
    int release() { return -- count; }
  private:
    int count;
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer.cpp>
namespace misc {
  template <typename Type> class SmartPointer {
  public:
    SmartPointer(): pointer(0), reference(0) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(Type* value): pointer(value) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(const SmartPointer<Type>& sp): pointer(sp.pointer), reference(sp.reference) {
      reference->add();
    }
    ~SmartPointer() {
      if ( reference->release() == 0 ) {
        delete[] pointer;
        delete[] reference;
      }
    }
    Type& operator *() { return *pointer; }
    const Type& operator *() const { return *pointer; }
    Type* operator +( const int& x ) { return pointer + x; }
    const Type* operator +( const int& x ) const { return pointer + x; }
    Type* operator ->() { return pointer; }
    SmartPointer<Type>& operator = ( const SmartPointer<Type>& sp ) {
      if ( this != &sp ) {
        if ( reference->release() == 0 ) {
          delete[] pointer;
          delete[] reference;
        }
        pointer = sp.pointer;
        reference = sp.reference;
        reference->add();
      }
      return *this;
    }
  private:
    Type* pointer;
    misc::SmartPointerReferenceCount* reference;
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef misc::SmartPointer<ValueType> Pointer;
    VectorClass() { data = Pointer(new ValueType[SIZE]); }
    ValueType& operator [] ( const int& index ) { return *(data + index); }
    const ValueType& operator [] ( const int& index ) const { return *(data + index); }
  private:
    Pointer data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_Z> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
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
  const Int SIZE = 1000 + 11;
  const Int MAX_NODES = 2 * SIZE + 11;
  const char CELL_WHITE = 'W';
  const String YES = "YES";
  const String NO = "NO";
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<String, SIZE>::Type Grid;
  typedef storage::Vector<Int, MAX_NODES>::Type Nodes;
  typedef storage::Vector<Nodes, MAX_NODES>::Type ConnectedNodes;
  typedef storage::Vector<Int, MAX_NODES>::Type ConnectedNodesNums;
  typedef storage::Vector<bool, MAX_NODES, MAX_NODES>::Type Edges;
  typedef storage::Vector<bool, MAX_NODES>::Type Used;

  // storages
  class Storages {
  public:
    Int N;
    Grid grid;

    ConnectedNodes cons;
    ConnectedNodesNums cons_nums;
    Edges edges;
    Used used;

    bool result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.edges = init_edges();
      generate_graph(s.N, s.grid, s.cons, s.cons_nums, s.edges);
      s.result = match(s.cons, s.cons_nums, s.edges, s.used) == s.N;
    }

  protected:
    static Int match( const ConnectedNodes& cons, const ConnectedNodesNums& cons_nums, Edges& edges, Used& used ) {
      Int res = 0;
      for ( int i = 0; i < MAX_NODES; ++ i ) {
        init_dfs(used);
        if ( dfs(0, cons, cons_nums, edges, used) ) {
          res ++;
        }
      }
      return res;
    }

    static bool dfs( const Int& cur, const ConnectedNodes& cons, const ConnectedNodesNums& cons_nums, Edges& edges, Used& used ) {
      if ( cur == goal_id() )
        return true;
      used[cur] = true;
      int num_vertices = cons_nums[cur];
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = cons[cur][i];
        if ( ! edges[cur][to] || used[to] )
          continue;
        if ( dfs(to, cons, cons_nums, edges, used) ) {
          edges[cur][to] = false;
          edges[to][cur] = true;
          return true;
        }
      }
      return false;
    }

    static void init_dfs( Used& used ) {
      for ( int i = 0; i < MAX_NODES; ++ i )
        used[i] = false;
    }

    static Edges init_edges() {
      Edges res;
      for ( int i = 0; i < MAX_NODES; ++ i )
        for ( int j = 0; j < MAX_NODES; ++ j )
          res[i][j] = false;
      return res;
    }

    static Int start_id() {
      return 0;
    }

    static Int goal_id() {
      return MAX_NODES - 1;
    }

    static Int row_id( const Int& row ) {
      return row + 1;
    }

    static Int col_id( const Int& col ) {
      return SIZE + col + 1;
    }

    static void add_edge( const Int& a, const Int& b, ConnectedNodes& cons, ConnectedNodesNums& cons_nums, Edges& edges ) {
      edges[a][b] = true;
      edges[b][a] = false;
      cons[a][cons_nums[a] ++] = b;
      cons[b][cons_nums[b] ++] = a;
    }

    static void generate_graph( const Int& N, const Grid& grid, ConnectedNodes& cons, ConnectedNodesNums& cons_nums, Edges& edges ) {
      for ( int i = 0; i < N; ++ i ) {
        for ( int j = 0; j < N; ++ j ) {
          if ( grid[i][j] == CELL_WHITE ) {
            add_edge(row_id(i), col_id(j), cons, cons_nums, edges);
          }
        }
      }
      for ( int i = 0; i < N; ++ i ) {
        add_edge(start_id(), row_id(i), cons, cons_nums, edges);
      }
      for ( int i = 0; i < N; ++ i ) {
        add_edge(col_id(i), goal_id(), cons, cons_nums, edges);
      }
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
      if ( ! ( std::cin >> s.N ) )
        return false;
      for ( int i = 0; i < s.N; ++ i )
        std::cin >> s.grid[i];
      return true;
    }

    void output( const Storages& s ) const {
      std::cout << ( s.result ? YES : NO ) << std::endl;
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



