
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
  class ISolution {
  public:
    virtual int run() = 0;
    
  protected:
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
  };
}


// @snippet<sh19910711/contest:solution/solution-base-multi-tests.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
      int tests = 0;
      std::cin >> tests;
      for ( int i = 0; i < tests; ++ i )
        action();
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 3;
  const int LETTERS = 'L' - 'A' + 1;
  const string TYPE_EVEN = "even";
  const string TYPE_UP = "up";
  const string TYPE_DOWN = "down";
  const int WEIGHT_HEAVY = 3;
  const int WEIGHT_NORMAL = 2;
  const int WEIGHT_LIGHT = 1;

  // storages
  string L[SIZE];
  string R[SIZE];
  string T[SIZE];
  int counterfeit_letter;
  int counterfeit_weight;
  
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      rec(0, 0);
    }

    void rec( int letter, int weight ) {
      if ( letter >= LETTERS )
        return rec(0, weight + 1);
      if ( weight >= 2 )
        return;

      if ( check_counterfeit(letter, weight) ) {
        counterfeit_letter = letter;
        counterfeit_weight = weight;
        return;
      }

      return rec(letter + 1, weight);
    }

    bool check_counterfeit( int letter, int weight ) {
      for ( int i = 0; i < SIZE; ++ i ) {
        int left_sum = calc_sum(L[i], letter, weight);
        int right_sum = calc_sum(R[i], letter, weight);
        if ( T[i] == TYPE_EVEN && ! ( left_sum == right_sum ) )
          return false;
        if ( T[i] == TYPE_UP && ! ( left_sum > right_sum ) )
          return false;
        if ( T[i] == TYPE_DOWN && ! ( left_sum < right_sum ) )
          return false;
      }
      return true;
    }

    int calc_sum( string s, int letter, int weight ) {
      int sum = 0;
      int n = s.size();
      for ( int i = 0; i < n; ++ i ) {
        int t = s[i] - 'A';
        if ( t == letter ) {
          sum += weight == 1 ? WEIGHT_HEAVY : WEIGHT_LIGHT;
        } else {
          sum += WEIGHT_NORMAL;
        }
      }
      return sum;
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
    
  private:
    Solver solver;

    bool input() {
      for ( int i = 0; i < SIZE; ++ i )
        cin >> L[i] >> R[i] >> T[i];
      return true;
    }

    void output() {
      char letter = 'A' + counterfeit_letter;
      string weight = ( counterfeit_weight == 1 ? "heavy" : "light" );
      cout << letter << " is the counterfeit coin and it is " << weight << "." << endl;
    }
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}


