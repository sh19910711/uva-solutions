
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
  const int SIZE      = 26 * 26 + 11;
  const int VERTICES  = 26;
  const int WAYS_NONE = -1;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::vector<String> Queries;
  typedef std::vector<int> QueryResults;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int N;
    int M;
    String paths[SIZE];
    int Q;
    Queries queries;
  };
  
  struct OutputStorage {
    int Q;
    Queries queries;
    QueryResults results;
  };
  
  struct DataStorage {
    bool G[VERTICES][VERTICES];
    int ways[VERTICES];
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
      out.Q = in.Q;
      out.queries = in.queries;
      out.results = QueryResults(in.Q, -1);
      std::fill(data.ways, data.ways + VERTICES, WAYS_NONE);
      init_graph(in.M, in.paths, data.G);
      for ( int i = 0; i < in.Q; ++ i ) {
        out.results[i] = find_lexicographical_index(in.queries[i], data.G, data.ways);
      }
      return out;
    }
    
  protected:
    static int count_ways( const int& from, const bool G[VERTICES][VERTICES], int ways[VERTICES] ) {
      int& res = ways[from];
      if ( res != WAYS_NONE ) {
        return res;
      }
      bool flag = false;
      res = 0;
      for ( int to = 0; to < VERTICES; ++ to ) {
        if ( ! G[from][to] ) {
          continue;
        }
        res += count_ways(to, G, ways);
        flag |= true;
      }
      if ( ! flag ) {
        res = 1;
      }
      return res;
    }

    static int find_lexicographical_index( const String& query, const bool G[VERTICES][VERTICES], int ways[VERTICES] ) {
      int res = 0;
      int len = query.size();
      for ( int i = 1; i < len; ++ i ) {
        int from = query[i - 1] - 'A';
        int next_v = query[i] - 'A';
        for ( int lower = 0; lower < next_v; ++ lower ) {
          if ( ! G[from][lower] ) {
            continue;
          }
          res += count_ways(lower, G, ways);
        }
      }
      return res + 1;
    }

    static void init_graph( const int& num_vertices, const String edges[SIZE], bool G[VERTICES][VERTICES] ) {
      for ( int i = 0; i < VERTICES; ++ i ) {
        for ( int j = 0; j < VERTICES; ++ j ) {
          G[i][j] = false;
        }
      }
      for ( int i = 0; i < num_vertices; ++ i ) {
        int from = edges[i][0] - 'A';
        int to = edges[i][1] - 'A';
        G[from][to] = true;
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
      if ( ! ( std::cin >> in.N >> in.M ) ) {
        return false;
      }
      for ( int i = 0; i < in.M; ++ i ) {
        std::cin >> in.paths[i];
      }
      std::cin >> in.Q;
      in.queries = Queries(in.Q);
      for ( int i = 0; i < in.Q; ++ i ) {
        std::cin >> in.queries[i];
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      for ( int i = 0; i < out.Q; ++ i ) {
        std::cout << out.queries[i] << ": " << out.results[i] << endl;
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


