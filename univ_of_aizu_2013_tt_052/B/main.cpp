
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
  protected:
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

namespace storage {
  template <class Storage> class Collection: public Storage {
  public:
    void input( std::istream& is, const int& begin, const int& end ) {
      for ( int i = begin; i < end; ++ i )
        is >> (this->operator[](i));
    }
    template <typename Func> bool each( const int& begin, const int& end, Func func ) {
      for ( int i = begin; i < end; ++ i )
        if ( ! func(this->operator[](i)) )
          return false;
      return true;
    }
    template <typename Func> bool each( const int& begin, const int& end, Func func ) const {
      for ( int i = begin; i < end; ++ i )
        if ( ! func(this->operator[](i)) )
          return false;
      return true;
    }
    template <typename Func, class Result> Result reduce( const int& begin, const int& end, Func func, Result init_value ) const {
      Result res = init_value;
      for ( int i = begin; i < end; ++ i )
        res = func(res, this->operator[](i));
      return res;
    }
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
  const int SIZE = 30000 + 11;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct Student {
    string name;
    int money;

    friend ostream& operator << ( ostream& os, const Student& si ) {
      return os << "{" << si.name << ", " << si.money << "}";
    }
    
    friend istream& operator >> ( istream& is, Student& si ) {
      is >> si.name;
      int x, y, z;
      is >> x >> y >> z;
      si.money = x * 5 + y * 10 + z * 20;
      return is;
    }

    friend bool operator < ( const Student& a, const Student& b ) {
      return a.money < b.money;
    }
  };
  typedef storage::Collection<storage::Vector<Student, SIZE>::Type> Students;
  
  struct InputStorages {
    int N;
    Students S;
  };
  
  struct OutputStorages {
    Student most;
    Student least;
  };
  
  struct DataStorages {
  };
  
  struct Storages {
    InputStorages in;
    OutputStorages out;
    DataStorages data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    OutputStorages& solve( const InputStorages& in, OutputStorages& out, DataStorages& data ) {
      out.most = find_max_student(in.N, in.S);
      out.least = find_min_student(in.N, in.S);
      return out;
    }

  protected:
    static Student find_max_student( const int& n, const Students& S ) {
      Student identity = {"max", std::numeric_limits<int>::min()};
      return S.reduce(0, n, std::max<Student>, identity);
    }

    static Student find_min_student( const int& n, const Students& S ) {
      Student identity = {"min", std::numeric_limits<int>::max()};
      return S.reduce(0, n, std::min<Student>, identity);
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

    bool input( InputStorages& s ) {
      if ( ! ( std::cin >> s.N && s.N != -1 ) )
        return false;
      s.S.input(std::cin, 0, s.N);
      return true;
    }

    void output( OutputStorages& out ) {
      if ( out.most.money == out.least.money ) {
        std::cout << "All have the same amount." << endl;
      } else {
        std::cout << out.most.name << " has most, " << out.least.name << " has least money." << endl;
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


