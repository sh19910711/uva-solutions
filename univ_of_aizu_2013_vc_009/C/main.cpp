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
  const int SIZE = 26 + 1;
  const int NO_TYPE = -1;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<String, SIZE>::Type Lines;

  struct Edge {
    int from;
    int to;

    Edge() {}
    Edge(int from, int to): from(from), to(to) {}
  };
  typedef graph::AdjacentList<Int, Edge> Graph;

  typedef storage::Vector<Int, SIZE>::Type VertexTypes;
  
  // storages
  class Storages {
  public:
    Int N;
    Lines S;

    Graph G;
    
    Int result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.G = init_graph(s.N, s.S);
      s.result = find_minimum_types(s.N, s.G);
    }

  protected:
    static bool check_types( const Int& N, const VertexTypes& V ) {
      for ( int i = 0; i < N; ++ i )
        if ( V[i] == NO_TYPE )
          return false;
      return true;
    }

    static bool find_type( const Int& from, const Int& channels, const Graph& G, VertexTypes& V ) {
      bool used[channels];
      std::fill(used, used + channels, false);

      const Graph::Edges& edges = G.vertex_edges[from];
      for ( Graph::Edges::const_iterator it_i = edges.begin(); it_i != edges.end(); ++ it_i ) {
        const Graph::Edge& edge = *((*it_i)+0);
        const Int& to = edge.to;
        if ( V[to] != NO_TYPE )
          used[V[to]] = true;
      }

      for ( int channel = 0; channel < channels; ++ channel ) {
        if ( used[channel] )
          continue;
        V[from] = channel;
        bool ok = true;
        for ( Graph::Edges::const_iterator it_i = edges.begin(); it_i != edges.end(); ++ it_i ) {
          const Graph::Edge& edge = *((*it_i)+0);
          const Int& to = edge.to;
          if ( V[to] != NO_TYPE )
            continue;
          ok &= find_type(to, channels, G, V);
        }
        if ( ok )
          return true;
        V[from] = NO_TYPE;
      }

      return false;
    }

    static bool check_channels( const Int& channels, const Int& N, const Graph& G, VertexTypes& V ) {
      for ( int i = 0; i < N; ++ i )
        find_type(i, channels, G, V);
      return check_types(N, V);
    }

    static Int find_minimum_types( const Int& N, const Graph& G ) {
      for ( Int channels = 1; channels <= 4; ++ channels ) {
        VertexTypes V = init_vertex();
        if ( check_channels(channels, N, G, V) ) {
          return channels;
        }
      }
      return -1;
    }

    static VertexTypes init_vertex() {
      VertexTypes res;
      for ( int i = 0; i < SIZE; ++ i ) {
        res[i] = NO_TYPE;
      }
      return res;
    }

    static Graph init_graph( const Int& N, const Lines& lines ) {
      Graph res;
      res.init(SIZE);
      for ( int i = 0; i < N; ++ i ) {
        string s = lines[i];
        replace(s.begin(), s.end(), ':', ' ');
        ISS iss(s);
        char c;
        string t;
        iss >> c >> t;
        int from = c - 'A';
        int len = t.size();
        for ( int j = 0; j < len; ++ j ) {
          char c = t[j];
          int to = c - 'A';
          res.add_edge(Graph::EdgePointer(new Edge(from, to)));
        }
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
      if ( ! this->input(*this->storages) )
        return false;
      solver.solve(*this->storages);
      this->output(*this->storages);
      return true;
    }
    
    bool input( Storages& s ) {
      if ( ! ( std::cin >> s.N && s.N ) )
        return false;
      for ( int i = 0; i < s.N; ++ i )
        std::cin >> s.S[i];
      return true;
    }
    
    void output( const Storages& s ) const {
      if ( s.result <= 1 ) {
        std::cout << s.result << " channel needed." << endl;
      } else {
        std::cout << s.result << " channels needed." << endl;
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



