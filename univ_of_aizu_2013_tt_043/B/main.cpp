
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

// @snippet<sh19910711/contest:search/search_interface.cpp>
namespace search {
  template <class Node> class SearchInterface {
  public:
    virtual Node search() = 0;
  };
}

namespace search {
  template <class Node> class BreadthFirstSearchInterface: public SearchInterface<Node> {
  public:
    virtual Node search()                            = 0;
  protected:
    virtual void init()                              = 0;
    virtual bool has_next_node()                     = 0;
    virtual void visit_next_node( const Node& node ) = 0;
    virtual void push_next_node( const Node& node )  = 0;
    virtual Node get_next_node()                     = 0;
    virtual Node get_none_node()                     = 0;
    virtual bool is_visited_node( const Node& node ) = 0;
    virtual void set_visited( const Node& node )     = 0;
    virtual bool is_goal_node( const Node& node )    = 0;
  };
}

namespace search {
  template <class Node> class BreadthFirstSearchBase: public BreadthFirstSearchInterface<Node> {
  public:
    Node search() {
      Node res = this->get_none_node();
      this->init();
      while ( this->has_next_node() ) {
        Node node = this->get_next_node();
        if ( this->is_goal_node(node) )
          res = node;
        this->visit_next_node(node);
      }
      return res;
    }
    
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search.cpp>
namespace search {
  template <class Node> class BreadthFirstSearch: public BreadthFirstSearchBase<Node> {
  protected:
    virtual void init() {}
    
    bool has_next_node() {
      return ! Q.empty();
    }
    
    Node get_next_node() {
      Node res = Q.front();
      Q.pop();
      return res;
    }
    
    void push_next_node( const Node& node ) {
      if ( this->is_visited_node(node) )
        return;
      Q.push(node);
      this->set_visited(node);
    }
    
  protected:
    std::queue <Node> Q;
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
  const Int SIZE = 20 + 1;
  const Int INF = std::numeric_limits<Int>::max();
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<Int, SIZE, SIZE>::Type Grid;
  typedef storage::Vector<Int, SIZE, SIZE, SIZE>::Type Dist;

  // storages
  class Storages {
  public:
    Int H;
    Int W;
    Int K;
    Grid G;
    
    Int result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.result = find_minimum_steps(s);
    }

  protected:
    static Int find_minimum_steps( const Storages& s ) {
      MyBFS bfs(s);
      Node ret = bfs.search();
      return ret.dist;
    }

    struct Node {
      Int dist;
      Int r;
      Int c;
      Int cnt;
    };

    class MyBFS: public search::BreadthFirstSearch<Node> {
    public:
      MyBFS( const Storages& s ): s(&s) {}

      void init() {
        for ( int i = 0; i < SIZE; ++ i )
          for ( int j = 0; j < SIZE; ++ j )
            for ( int k = 0; k < SIZE; ++ k )
              dist[i][j][k] = INF;
        Node start_node = {0, 0, 0};
        push_next_node(start_node);
      }

      void visit_next_node( const Node& node ) {
        const int dr[4] = {1, -1, 0, 0};
        const int dc[4] = {0, 0, 1, -1};
        for ( int k = 0; k < 4; ++ k ) {
          Int nr = node.r + dr[k];
          Int nc = node.c + dc[k];
          if ( nr < 0 || nr >= s->H || nc < 0 || nc >= s->W )
            continue;
          Int dist = node.dist + 1;
          Int cnt = node.cnt;
          if ( s->G[nr][nc] )
            cnt ++;
          else
            cnt = 0;
          if ( cnt > s->K )
            continue;
          Node next = {dist, nr, nc, cnt};
          push_next_node(next);
        }
      }

      Node get_none_node() {
        Node res = {-1, -1, -1};
        return res;
      }

      bool is_goal_node( const Node& node ) {
        return node.r == s->H - 1 && node.c == s->W - 1;
      }

      bool is_visited_node( const Node& node ) {
        return node.dist >= dist[node.r][node.c][node.cnt];
      }

      void set_visited( const Node& node ) {
        dist[node.r][node.c][node.cnt] = node.dist;
      }

    private:
      Dist dist;
      const Storages* s;
    };
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
      std::cin >> s.K;
      for ( int i = 0; i < s.H; ++ i )
        for ( int j = 0; j < s.W; ++ j )
          std::cin >> s.G[i][j];
      return true;
    }
    
    void output( const Storages& s ) const {
      std::cout << s.result << std::endl;
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




