
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
  const int SIZE = 10000 + 11;
  const int MAX_CUTS = 1000 + 11;
  const int MAX_LETTER_TYPES = 26;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef storage::Vector<Int, MAX_CUTS>::Type Cuts;
  typedef storage::Vector<Int, SIZE>::Type Count;
  typedef storage::Vector<Count, MAX_LETTER_TYPES>::Type Counts;

  struct Range {
    Int l;
    Int r;
    Range() {}
    Range(Int l, Int r): l(l), r(r) {}
  };
  typedef storage::Vector<Range, MAX_CUTS>::Type Ranges;

  // storages
  class Storages {
  public:
    Int K;
    Cuts A;
    String S;

    Counts C;
    Ranges R;

    Int result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.C = get_counts(s.S);
      s.R = get_ranges(s.A, s.K, s.S);
      s.result = get_total_cost(s.C, s.A, s.K, s.R, s.S.size());
    }

  protected:

    static Ranges get_ranges( const Cuts& cuts, const Int& cuts_num, const String& s ) {
      Ranges res;
      for ( int i = 0; i < cuts_num; ++ i )
        res[i] = Range(1, s.size());
      for ( int i = 0; i < cuts_num; ++ i ) {
        for ( int j = i + 1; j < cuts_num; ++ j ) {
          if ( cuts[j] < cuts[i] ) {
            res[j].r = std::min(res[j].r, cuts[i]);
          }
          if ( cuts[i] < cuts[j] ) {
            res[j].l = std::max(res[j].l, cuts[i] + 1);
          }
        }
      }
      return res;
    }

    static void print_counts( const Counts& c, const Int& n ) {
      cout << "# counts" << endl;
      for ( int i = 0; i < MAX_LETTER_TYPES; ++ i ) {
        cout << (char)('a' + i) << ": ";
        for ( int j = 0; j < n; ++ j ) {
          cout << c[i][j] << ", ";
        }
        cout << endl;
      }
      cout << endl;
    }

    static Counts get_counts( const String& s ) {
      Counts res;
      for ( int i = 0; i < MAX_LETTER_TYPES; ++ i ) {
        res[i] = get_count(s, 'a' + i);
      }
      return res;
    }

    static Count get_count( const String& s, const char& c ) {
      Count res;
      int n = s.size();
      int cnt = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( s[i] == c )
          cnt ++;
        res[i] = cnt;
      }
      return res;
    }

    static Int get_total_cost( const Counts& counts, const Cuts& cuts, const Int& cuts_num, const Ranges& ranges, const Int& N ) {
      Int res = 0;
      for ( Int i = 0; i < cuts_num; ++ i ) {
        const Range& r = ranges[i];
        const Int& p = cuts[i];
        for ( Int j = 0; j < MAX_LETTER_TYPES; ++ j ) {
          Int l_sum = counts[j][p - 1];
          if ( r.l - 2 >= 0 )
            l_sum -= counts[j][r.l - 2];
          Int r_sum = counts[j][r.r - 1];
          if ( p - 1 >= 0 )
            r_sum -= counts[j][p - 1];

          bool fl = l_sum > 0;
          bool fr = r_sum > 0;
          if ( fl ^ fr )
            res ++;
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
      if ( ! ( std::cin >> s.K ) )
        return false;
      for ( int i = 0; i < s.K; ++ i )
        std::cin >> s.A[i];
      std::cin >> s.S;
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



