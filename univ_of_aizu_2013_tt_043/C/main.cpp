
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
        delete pointer;
        delete reference;
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
          delete pointer;
          delete reference;
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
  const Int RELATIONS = 20000 + 11;
  const Int TASKS = 500 + 11;
  const Int INF = std::numeric_limits<Int>::max() >> 2LL;
  const String YES = "YES";
  const String NO = "NO";
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<Int, RELATIONS>::Type List;
  typedef storage::Vector<Int, TASKS>::Type Times;

  struct Relation {
    Int X;
    Int Y;
    Int D;
  };
  typedef storage::Vector<Relation, RELATIONS>::Type Relations;

  // storages
  class Storages {
  public:
    Int N;
    Int K;
    Relations R;

    Times T;

    bool result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.T = init_times(s.N);
      s.T = update_times(s.K, s.R, s.T);
      s.result = check_times(s.K, s.R, s.T);
    }
  protected:

    static bool check_times( const Int& relations, const Relations& R, const Times& T ) {
      for ( int i = 0; i < relations; ++ i ) {
        const Int& x = R[i].X;
        const Int& y = R[i].Y;
        const Int& d = R[i].D;
        if ( T[x] + d < T[y] )
          return false;
      }
      return true;
    }

    static Times update_times( const Int& relations, const Relations& R, const Times& T ) {
      Times res = T;
      for ( int i = 0; i < TASKS && update_time(relations, R, res); ++ i );
      return res;
    }

    static bool update_time( const Int& relations, const Relations& R, Times& T ) {
      bool res = false;
      for ( Int i = 0; i < relations; ++ i ) {
        const Int& x = R[i].X;
        const Int& y = R[i].Y;
        const Int& d = R[i].D;
        if ( T[x] + d < T[y] ) {
          T[y] = std::min(T[y], T[x] + d);
          res = true;
        }
      }
      return res;
    }

    static Times init_times( const Int& N ) {
      Times res;
      for ( Int i = 0; i < N; ++ i )
        res[i] = INF;
      res[0] = 0;
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
      if ( ! ( std::cin >> s.N >> s.K ) )
        return false;
      for ( Int i = 0; i < s.K; ++ i ) {
        Int x, y, d;
        std::cin >> x >> y >> d;
        if ( d >= 0 ) {
          s.R[i].X = x;
          s.R[i].Y = y;
          s.R[i].D = d;
        } else {
          s.R[i].X = y;
          s.R[i].Y = x;
          s.R[i].D = d;
        }
      }
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



