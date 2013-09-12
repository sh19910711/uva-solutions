
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

namespace misc {
  template <typename Type> class SmartPointerSingle {
  public:
    SmartPointerSingle(): pointer(0), reference(0) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointerSingle(Type* value): pointer(value) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointerSingle(const SmartPointer<Type>& sp): pointer(sp.pointer), reference(sp.reference) {
      reference->add();
    }
    ~SmartPointerSingle() {
      if ( reference->release() == 0 ) {
        delete pointer;
        delete reference;
      }
    }
    Type& operator *() { return *pointer; }
    const Type& operator *() const { return *pointer; }
    Type* operator +( const int& x ) { return pointer + x; }
    const Type* operator +( const int& x ) const { return pointer + x; }
    Type* operator ->() { return pointer; }
    SmartPointerSingle<Type>& operator = ( const SmartPointerSingle<Type>& sp ) {
      if ( this != &sp ) {
        if ( reference->release() == 0 ) {
          delete pointer;
          delete reference;
        }
        pointer = sp.pointer;
        reference = sp.reference;
        reference->add();
      }
      return *this;
    }

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
  const Int SEQUENCES = 10 + 1;
  const Int NO_ID = -1;
  const Int NO_TYPE = -1;
  const Int MAX_NODES = 1024 + 11;
  const Int MAX_LENGTH = 100 + 11;
  const Int MAX_TYPES = 4;
  const Int DP_NONE = std::numeric_limits<Int>::max();
  const String TYPE_LETTERS = "ACGT";
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<String, SEQUENCES>::Type Sequences;
  typedef storage::Vector<Int, MAX_NODES, MAX_LENGTH, MAX_TYPES>::Type Table;

  struct Node;
  typedef misc::SmartPointerSingle<Node> NodePointer;
  struct Node {
    NodePointer left;
    NodePointer right;
    Int id;
    Int sequence_id;
    Node(): sequence_id(NO_ID) {}
  };
  
  // storages
  class Storages {
  public:
    Int N;
    Int L;
    Sequences S;
    String E;

    Table dp;
    
    Int result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      Int tmp_node_id = 0;
      Int tmp_index = 0;
      NodePointer tree = generate_tree(s.E, tmp_index, tmp_node_id);
      
      s.dp = init_tree_dp();
      do_tree_dp(s.L, tree, s.S, s.dp);

      s.result = get_minimum_cost(s.L, s.dp);
    }

  protected:
    static Int get_minimum_cost( const Int& n, const Table& dp ) {
      Int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        Int tmp = DP_NONE;
        for ( int j = 0; j < MAX_TYPES; ++ j ) {
          tmp = std::min(tmp, dp[0][i][j]);
        }
        res += tmp;
      }
      return res;
    }

    static Int calc_minimum_cost( const Int& nid, const Int& p, const Int& t, const Table& dp ) {
      Int res = DP_NONE;
      for ( int i = 0; i < MAX_TYPES; ++ i ) {
        res = std::min(res, dp[nid][p][i] + ( t != i ? 1 : 0 ));
      }
      return res;
    }

    static void do_tree_dp( const Int& n, const NodePointer& p, const Sequences& s, Table& dp ) {
      const Node& node = *p;
      if ( node.sequence_id == NO_ID ) {
        do_tree_dp(n, node.left, s, dp);
        do_tree_dp(n, node.right, s, dp);
        const Int& nid = node.id;
        const Int& lid = (*node.left).id;
        const Int& rid = (*node.right).id;
        for ( int i = 0; i < n; ++ i ) {
          for ( int j = 0; j < MAX_TYPES; ++ j ) {
            dp[nid][i][j] = calc_minimum_cost(lid, i, j, dp) + calc_minimum_cost(rid, i, j, dp);
          }
        }
      } else {
        const Int& nid = node.id;
        const Int& sid = node.sequence_id;
        const String& seq = s[sid];
        for ( int i = 0; i < n; ++ i ) {
          for ( int j = 0; j < MAX_TYPES; ++ j ) {
            dp[nid][i][j] = ( seq[i] == TYPE_LETTERS[j] ? 0 : 1 );
          }
        }
      }
    }

    static Table init_tree_dp() {
      Table res;
      for ( int i = 0; i < MAX_NODES; ++ i ) {
        for ( int j = 0; j < MAX_LENGTH; ++ j ) {
          for ( int k = 0; k < MAX_TYPES; ++ k ) {
            res[i][j][k] = DP_NONE;
          }
        }
      }
      return res;
    }

    static NodePointer generate_tree( const String& s, Int& k, Int& id ) {
      NodePointer res = NodePointer(new Node);
      res->id = id ++;
      if ( s[k] == '(' ) {
        res->sequence_id = NO_ID;
        k ++;
        res->left = generate_tree(s, k, id);
        k ++;
        res->right = generate_tree(s, k, id);
        k ++;
      } else if ( std::isdigit(s[k]) ) {
        res->sequence_id = s[k] - '0';
        k ++;
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
      if ( ! ( std::cin >> s.N >> s.L ) )
        return false;
      for ( Int i = 0; i < s.N; ++ i )
        std::cin >> s.S[i];
      std::cin >> s.E;
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



