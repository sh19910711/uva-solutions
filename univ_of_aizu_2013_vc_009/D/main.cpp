
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

    int get_number() {
      std::string line;
      std::getline(std::cin, line);
      std::istringstream iss(line);
      int res;
      iss >> res;
      return res;
    }

    virtual int run() {
      int tests = get_number();
      get_number();
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
  const Int SIZE = 1000 + 11;
  const int NO_ROOM = -1;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef std::vector<int> List;

  struct Result {
    int room_id;
    int max_visited_rooms;
  };

  // storages
  class Storages {
  public:
    int N;
    int ET;
    List G[SIZE];

    Result result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      Result tmp = {NO_ROOM, -1};
      s.result = tmp;
      for ( int i = 0; i < s.N; ++ i ) {
        if ( i == s.ET )
          continue;
        bool V[s.N];
        std::fill(V, V + s.N, false);
        int visited_rooms = 0;
        if ( check_guards(0, i, s.ET, s.G, V, visited_rooms) ) {
          if ( visited_rooms > s.result.max_visited_rooms ) {
            s.result.room_id = i;
            s.result.max_visited_rooms = visited_rooms;
          }
        }
      }
    }

  protected:
    static bool check_guards( const int& from, const int& guards, const int& et, const List* G, bool* V, int& visited_rooms ) {
      if ( from == et )
        return false;
      V[from] = true;
      visited_rooms ++;
      for ( List::const_iterator it_i = G[from].begin(); it_i != G[from].end(); ++ it_i ) {
        const int& to = *it_i;
        if ( V[to] )
          continue;
        if ( to == guards )
          continue;
        if ( ! check_guards(to, guards, et, G, V, visited_rooms) )
          return false;
      }
      return true;
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

    bool get_edge( int& a, int& b ) {
      string line;
      std::getline(cin, line);
      ISS iss(line);
      return iss >> a >> b;
    }

    bool input( Storages& s ) {
      int from, to;
      for ( int i = 0; i < SIZE; ++ i )
        s.G[i].clear();
      get_edge(s.N, s.ET);
      while ( get_edge(from, to) ) {
        s.G[from].push_back(to);
      }
      return true;
    }

    void output( const Storages& s ) const {
      std::cout << "Put guards in room " << s.result.room_id << "." << endl;
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


