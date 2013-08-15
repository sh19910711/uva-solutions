
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
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class Vector {
  public:
    typedef ValueType Type;
    Vector() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
    void fill( Type value ) { std::fill(data.begin(), data.end(), value); }
  private:
    std::vector<Type> data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  template <typename Type, int SIZE_X = 0, int SIZE_Y = 0, int SIZE_Z = 0> struct VectorTypes {
    typedef storage::Vector<Type   , SIZE_X> Type1D;
    typedef storage::Vector<Type1D , SIZE_Y> Type2D;
    typedef storage::Vector<Type2D , SIZE_Z> Type3D;
  };
  template <int SIZE_X = 0, int SIZE_Y = 0, int SIZE_Z = 0> struct BasicVectors {
    typedef VectorTypes<int    , SIZE_X , SIZE_Y , SIZE_Z> IntVectors;
    typedef VectorTypes<double , SIZE_X , SIZE_Y , SIZE_Z> DoubleVectors;
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
  const Int SIZE = 1000 + 11;
  const Int TESTS = 30 + 11;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages types
  typedef storage::VectorTypes<Int, SIZE>::Type1D Neighbours;
  typedef storage::VectorTypes<Neighbours, SIZE>::Type1D Places;
  typedef storage::VectorTypes<Places, TESTS>::Type1D TestPlaces;
  typedef storage::VectorTypes<Int, SIZE>::Type1D PlacesNum;
  typedef storage::VectorTypes<Int, SIZE>::Type1D PlaceCount;
  typedef storage::VectorTypes<PlaceCount, TESTS>::Type1D PlacesCount;
  typedef storage::VectorTypes<Int, SIZE>::Type1D TestResult;
  typedef storage::VectorTypes<Int, TESTS>::Type1D TestResultNum;
  typedef storage::VectorTypes<TestResult, TESTS>::Type1D TestResults;
  typedef std::pair<TestResult, int> Result;

  // storages
  Int tests;
  PlacesNum places_num;
  PlacesCount places_count;
  TestPlaces places;

  TestResultNum test_result_num;
  TestResults test_results;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 0; i < tests; ++ i ) {
        Result ret = do_test(places_num[i], places_count[i], places[i]);
        test_result_num[i] = ret.second;
        test_results[i] = ret.first;
      }
    }

    Result do_test( const Int& place_num, const PlaceCount& place_count, Places places ) {
      Int minimum_number = find_minimum_numbers(place_num, place_count);
      TestResult list;
      int cnt = 0;
      for ( int i = 0; i < place_num; ++ i ) {
        if ( place_count[i] == minimum_number ) {
          list[cnt ++] = i + 1;
        }
      }
      return Result(list, cnt);
    }

    const Int find_minimum_numbers( const Int& places_num, const PlaceCount& place_count ) const {
      Int res = std::numeric_limits<Int>::max();
      for ( int i = 0; i < places_num; ++ i ) {
        res = std::min(res, place_count[i]);
      }
      return res;
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void init() {
      for ( int i = 0; i < TESTS; ++ i ) {
        test_result_num.fill(Int(0));
      }
    }

    bool input_tests() {
      std::string line;
      std::getline(std::cin, line);
      ISS iss(line);
      return iss >> tests;
    }

    bool input_places_num( int test ) {
      std::string line;
      std::getline(std::cin, line);
      ISS iss(line);
      return iss >> places_num[test];
    }

    bool input_places( int test, int place_id ) {
      std::string line;
      std::getline(std::cin, line);
      ISS iss(line);
      int neighbour_id;
      places_count[test][place_id] = 0;
      while ( iss >> neighbour_id ) {
        places[test][place_id][places_count[test][place_id] ++] = neighbour_id;
      }
      return true;
    }

    bool input() {
      if ( ! input_tests() )
        return false;
      for ( int test = 0; test < tests; ++ test ) {
        input_places_num(test);
        for ( int i = 0; i < places_num[test]; ++ i ) {
          input_places(test, i);
        }
        std::string dummy;
        std::getline(std::cin, dummy);
      }
      return true;
    }

    void output() const {
      for ( int test = 0; test < tests; ++ test ) {
        for ( int i = 0; i < test_result_num[test]; ++ i ) {
          std::cout << test_results[test][i];
          if ( i + 1 < test_result_num[test] )
            std::cout << " ";
        }
        std::cout << endl;
      }
    }
    
    Solver solver;
    
  private:
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

