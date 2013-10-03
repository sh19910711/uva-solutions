
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

// @snippet<sh19910711/contest:graph/interface.cpp>
namespace graph {
  template <typename WeightType, typename EdgeType> class GraphInterface {
  public:
    typedef WeightType Weight;
    typedef EdgeType Edge;
    typedef typename misc::SmartPointer<EdgeType> EdgePointer;
    virtual void init( const int& num_vertices ) = 0;
    virtual void add_edge( EdgePointer edge )    = 0;
    virtual ~GraphInterface() {}
  };
}

// @snippet<sh19910711/contest:graph/adjacent_list.cpp>
namespace graph {
  template <typename WeightType, typename EdgeType> class AdjacentList: public GraphInterface<WeightType, EdgeType> {
  public:
    typedef misc::SmartPointer<EdgeType> EdgePointer;
    typedef std::vector<EdgePointer> Edges;
    typedef std::vector<Edges> VertexEdges;

    void init( const int& num_vertices ) {
      this->num_vertices = num_vertices;
      this->vertex_edges = VertexEdges(this->num_vertices);
    }

    void add_edge( EdgePointer edge ) {
      // std::cout << "@edge: " << *(edge+0) << std::endl;
      this->vertex_edges[edge->from].push_back(edge);
    }

    int num_vertices;
    VertexEdges vertex_edges;

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
  const int SIZE = 500 + 11;
  const Int NO_RESULT = -1;
  const Int INF = std::numeric_limits<Int>::max();

}

namespace graph {
  template <int SIZE, class Graph> class MinCostFlow {
  public:
    typedef typename Graph::Weight Weight;
    typedef typename Graph::Edge Edge;
    MinCostFlow(): N(0) {}
    MinCostFlow( const int& num, Graph& graph ): N(num), G(&graph) {}
    Weight get_inf() {
      return std::numeric_limits<Weight>::max();
    }
    Weight get_no_result() {
      return -1;
    }
    Weight find( const int& s, const int& t, Weight f ) {
      Weight res = 0;
      while ( f > 0 ) {
        std::fill(dist, dist + N, get_inf());
        dist[s] = 0;
        bool update = true;
        while ( update ) {
          update = false;
          for ( int v = 0; v < N; ++ v ) {
            if ( dist[v] == get_inf() )
              continue;
            for ( int i = 0; i < G->vertex_edges[v].size(); ++ i ) {
              const Edge& e = *(G->vertex_edges[v][i]);
              if ( e.cap > 0 && dist[e.to] > dist[v] + e.cost ) {
                dist[e.to] = dist[v] + e.cost;
                prev_v[e.to] = v;
                prev_e[e.to] = i;
                update = true;
              }
            }
          }
        }
        if ( dist[t] == get_inf() )
          return get_no_result();
        Weight d = f;
        for ( int v = t; v != s; v = prev_v[v] ) {
          const Edge& e = *(G->vertex_edges[prev_v[v]][prev_e[v]]);
          d = std::min(d, e.cap);
        }
        f -= d;
        res += d * dist[t];
        for ( int v = t; v != s; v = prev_v[v] ) {
          Edge& e = *(G->vertex_edges[prev_v[v]][prev_e[v]]);
          e.cap -= d;
          Edge& e_rev = *(G->vertex_edges[v][e.rev]);
          e_rev.cap += d;
        }
      }
      return res;
    }
  private:
    int N;
    Graph* G;
    Weight dist[SIZE];
    int prev_v[SIZE];
    int prev_e[SIZE];
  };
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<Int, SIZE>::Type List;
  typedef storage::Vector<Int, SIZE, SIZE>::Type EdgeCost;

  struct Edge {
    int from;
    int to;
    Int cap;
    Int cost;
    Int rev;

    friend std::ostream& operator <<( std::ostream& os, const Edge& e ) {
      os << "{";
      os << "from = " << e.from << ", ";
      os << "to = " << e.to << ", ";
      os << "cap = " << e.cap << ", ";
      os << "cost = " << e.cost << ", ";
      os << "rev = " << e.rev << ", ";
      os << "}";
      return os;
    }
  };
  typedef graph::AdjacentList<Int, Edge> Graph;

  // storages
  class Storages {
  public:
    Int N;
    Int M;
    List A;
    List B;
    List C;

    EdgeCost edge_cost;
    Graph graph;

    Int result;
  };

  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      init_edge_cost(s.M, s.A, s.B, s.C, s.edge_cost);
      init_graph(s.N, s.edge_cost, s.graph);
      s.result = find_shortest(s.N, s.graph);
    }

  protected:

    static Int find_shortest( const Int& N, Graph& G ) {
      graph::MinCostFlow<SIZE, Graph> min_cost_flow(N, G);
      return min_cost_flow.find(0, N - 1, 2);
    }

    static void init_graph( const Int& num_vertices, const EdgeCost& edge_cost, Graph& graph ) {
      graph.init(num_vertices);
      for ( int from = 0; from < num_vertices; ++ from ) {
        for ( int to = 0; to < num_vertices; ++ to ) {
          if ( edge_cost[from][to] != INF ) {
            Int cost = edge_cost[from][to];
            Edge edge_from; 
            edge_from.from = from;
            edge_from.to = to;
            edge_from.cap = 1;
            edge_from.cost = cost;
            edge_from.rev = graph.vertex_edges[to].size();
            Edge edge_to;
            edge_to.to = to;
            edge_to.from = from;
            edge_to.cap = 0;
            edge_to.cost = -cost;
            edge_to.rev = graph.vertex_edges[from].size() - 1;
            graph.add_edge(Graph::EdgePointer(new Edge(edge_from)));
            graph.add_edge(Graph::EdgePointer(new Edge(edge_to)));
          }
        }
      }
    }

    static void init_edge_cost( const Int& edges, const List& from_list, const List& to_list, const List& cost, EdgeCost& edge_cost ) {
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          edge_cost[i][j] = INF;
      for ( int i = 0; i < edges; ++ i ) {
        int from = from_list[i] - 1;
        int to = to_list[i] - 1;
        edge_cost[from][to] = edge_cost[to][from] = cost[i];
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
      if ( ! ( std::cin >> s.N && s.N ) )
        return false;
      std::cin >> s.M;
      for ( int i = 0; i < s.M; ++ i ) {
        std::cin >> s.A[i] >> s.B[i] >> s.C[i];
      }
      return true;
    }

    void output( const Storages& s ) const {
      if ( s.result == NO_RESULT )
        std::cout << "Back to jail" << std::endl;
      else
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



