
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
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
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
    virtual bool action() = 0;
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
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
      this->before_all_actions();
      for ( int i = 0; i < tests; ++ i ) {
        this->before_action(i);
        this->action();
        this->after_action(i);
      }
      this->after_all_actions();
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE       = 100 + 11;
  const int START_NODE = 0;
  const int NODE_NONE  = -1;
  const String YES     = "Y";
  const String NO      = "N";
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int N;
    int T[SIZE][SIZE];
  };
  
  struct OutputStorage {
    int N;
    bool relations[SIZE][SIZE];
  };
  
  struct DataStorage {
    bool visited[SIZE][SIZE];
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.N = in.N;
      init_table(out.relations);
      init_table(data.visited);
      check_relations(in, out.relations, data.visited);
      return out;
    }
    
  protected:
    static void check_relations( const InputStorage& in, bool relations[SIZE][SIZE], bool visited[SIZE][SIZE] ) {
      bool visited2[SIZE];
      std::fill(visited2, visited2 + SIZE, false);
      visit(in, START_NODE, NODE_NONE, visited2);
      for ( int ignore_node = 0; ignore_node < in.N; ++ ignore_node ) {
        visit(in, START_NODE, ignore_node, visited[ignore_node]);
        for ( int i = 0; i < in.N; ++ i ) {
          relations[ignore_node][i] = visited2[i] && ! visited[ignore_node][i];
        }
      }
    }

    static void visit( const InputStorage& in, const int& from, const int& ignore_node, bool visited[SIZE] ) {
      if ( from == ignore_node ) {
        return;
      }
      if ( visited[from] ) {
        return;
      }
      visited[from] = true;
      for ( int i = 0; i < in.N; ++ i ) {
        if ( i == ignore_node ) {
          continue;
        }
        if ( ! in.T[from][i] ) {
          continue;
        }
        visit(in, i, ignore_node, visited);
      }
    }

    static void init_table( bool table[SIZE][SIZE] ) {
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          table[i][j] = false;
        }
      }
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
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.N ) )
        return false;
      for ( int i = 0; i < in.N; ++ i ) {
        for ( int j = 0; j < in.N; ++ j ) {
          std::cin >> in.T[i][j];
        }
      }
      return true;
    }

    void before_action( const int& test_id ) const {
      std::cout << "Case " << test_id + 1 << ":" << endl;
    }

    void output( const OutputStorage& out ) const {
      for ( int i = 0; i < out.N; ++ i ) {
        draw_line(out.N);
        for ( int j = 0; j < out.N; ++ j ) {
          std::cout << "|" << ( out.relations[i][j] ? YES : NO );
        }
        std::cout << "|" << endl;
      }
      draw_line(out.N);
    }

    static void draw_line( const int& num_vertices ) {
      std::cout << "+" << String(num_vertices * 2 - 1, '-') << "+" << endl;
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


