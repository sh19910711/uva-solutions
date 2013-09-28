
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
  const Int CONTACTS = 200 + 11;
  const Int STOCKBROKERS = 100 + 11;
  const Int INF = std::numeric_limits<Int>::max() / 2;
  const Int NO_ID = -1;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<Int, CONTACTS>::Type Contacts;
  typedef storage::Vector<Contacts, STOCKBROKERS>::Type InputList;
  typedef storage::Vector<Int, STOCKBROKERS>::Type InputListNum;
  typedef storage::Vector<Int, STOCKBROKERS, STOCKBROKERS>::Type Costs;

  struct Result {
    Int id;
    Int cost;
  };

  // storages
  class Storages {
  public:
    Int N;
    InputList list;
    InputListNum list_num;

    Costs cost;

    Result result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.cost = init_cost(s.N, s.list, s.list_num);
      update_cost(s.N, s.cost);
      s.result = get_result(s.N, s.cost);
    }

  protected:
    static Costs init_cost( const Int& N, const InputList& list, const InputListNum& list_num ) {
      Costs res;
      for ( int i = 0; i < STOCKBROKERS; ++ i )
        for ( int j = 0; j < STOCKBROKERS; ++ j )
          res[i][j] = INF;
      for ( int i = 0; i < N; ++ i ) {
        for ( int j = 0; j < list_num[i]; ++ j ) {
          int to = list[i][j * 2] - 1;
          Int cost = list[i][j * 2 + 1];
          res[i][to] = std::min(res[i][to], cost);
        }
      }
      return res;
    }

    static void update_cost( const Int& N, Costs& cost ) {
      for ( int k = 0; k < N; ++ k ) {
        for ( int i = 0; i < N; ++ i ) {
          for ( int j = 0; j < N; ++ j ) {
            if ( i == j || j == k || k == i )
              continue;
            if ( cost[i][k] == INF || cost[k][j] == INF )
              continue;
            cost[i][j] = std::min(cost[i][j], cost[i][k] + cost[k][j]);
          }
        }
      }
    }

    static Result get_result( const Int& N, const Costs& cost ) {
      Result res = {NO_ID, INF};
      for ( int i = 0; i < N; ++ i ) {
        Int num = 0;
        Int max_cost = std::numeric_limits<Int>::min();
        for ( int j = 0; j < N; ++ j ) {
          if ( cost[i][j] != INF ) {
            num ++;
            max_cost = std::max(max_cost, cost[i][j]);
          }
        }
        if ( num == N - 1 && max_cost < res.cost ) {
          res.id = i;
          res.cost = max_cost;
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
      for ( int i = 0; i < s.N; ++ i ) {
        std::cin >> s.list_num[i];
        for ( int j = 0; j < s.list_num[i]; ++ j ) {
          std::cin >> s.list[i][j * 2] >> s.list[i][j * 2 + 1];
        }
      }
      return true;
    }

    void output( const Storages& s ) const {
      if ( s.result.id == NO_ID ) {
        std::cout << "disjoint" << endl;
      } else {
        std::cout << s.result.id + 1 << " " << s.result.cost << endl;
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


