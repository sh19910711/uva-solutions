
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
      std::string line;
      std::getline(std::cin, line);
      std::istringstream iss(line);
      int tests = 0;
      iss >> tests;
      for ( int i = 0; i < tests; ++ i ) {
        std::cout << "Roll-call: " << i + 1 << std::endl;
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
  
  struct Pupil {
    String name;
    String submissions[5];
    Int num_submissions;
  };

  struct Result {
    int presents;
    int studies;
    int remedials;
    int absents;

    Result(): presents(0), studies(0), remedials(0), absents(0) {}
  };
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100 + 11; 
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef storage::Vector<Pupil, SIZE>::Type Pupils;
  Int N;
  Pupils P;

  Result result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = check_pupil_submissions(P, N);
    }

    const Result check_pupil_submissions( const Pupils& P, const Int& N ) {
      Result res;
      for ( int i = 0; i < N; ++ i ) {
        if ( check_absent(P[i]) ) {
          res.absents ++;
        } else if ( check_present(P[i]) ) {
          res.presents ++;
        } else if ( check_remedial(P[i]) ) {
          res.remedials ++;
        } else if ( check_study(P[i]) ) {
          res.studies ++;
        }
      }
      return res;
    }

    bool is_wrong_answer( const String& s ) {
      return s == "n" || s == "no";
    }

    bool is_correct_answer( const String& s ) {
      return s == "y" || s == "yes";
    }

    const bool check_absent( const Pupil& P ) {
      return P.num_submissions == 0;
    }

    const bool check_present( const Pupil& P ) {
      for ( int i = 0; i < P.num_submissions; ++ i ) {
        if ( is_wrong_answer(P.submissions[i]) )
          return false;
      }
      return true;
    }

    const bool check_remedial( const Pupil& P ) {
      for ( int i = 0; i < P.num_submissions; ++ i ) {
        if ( is_correct_answer(P.submissions[i]) )
          return false;
      }
      return true;
    }

    const bool check_study( const Pupil& P ) {
      return P.num_submissions > 0 && is_wrong_answer(P.submissions[0]);
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

    bool input_n() {
      string line;
      getline(cin, line);
      ISS iss(line);
      return iss >> N;
    }
    
    Pupil input_pupil() {
      Pupil res;
      string line;
      getline(std::cin, line);
      ISS iss(line);
      iss >> res.name;
      res.num_submissions = 0;
      while ( iss >> res.submissions[res.num_submissions] )
        res.num_submissions ++;
      return res;
    }
    
    bool input() {
      if ( ! ( input_n() ) )
        return false;
      for ( int i = 0; i < N; ++ i ) {
        P[i] = input_pupil();
      }
      return true;
    }

    void output() {
      std::cout << "Present: " << result.presents << " out of " << N << std::endl;
      std::cout << "Needs to study at home: " << result.studies << " out of " << N << std::endl;
      std::cout << "Needs remedial work after school: " << result.remedials << " out of " << N << std::endl;
      std::cout << "Absent: " << result.absents << " out of " << N << std::endl;
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



