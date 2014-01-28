
// @snippet<sh19910711/contest-base:headers.cpp>
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

// @snippet<sh19910711/contest-base:solution/define-classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    SolverInterface* solver;
    Storages* storages;
    virtual int run() = 0;
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}


// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
}

// @snippet<sh19910711/contest-base:solution/solution-base-multi-tests.cpp>
namespace solution {
  struct SolutionBase: public SolutionInterface {
    virtual ~SolutionBase() {}; 
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
  };
}

// @snippet<sh19910711/contest:search/search_interface.cpp>
namespace search {
  template <class Node> class SearchInterface {
  public:
    virtual Node search() = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_interface.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchInterface: public SearchInterface<Node> {
  public:
    virtual Node search()                            = 0;
    virtual void init()                              = 0;
    virtual bool has_next_node()                     = 0;
    virtual void visit_next_node( const Node& node ) = 0;
    virtual void push_next_node( const Node& node )  = 0;
    virtual Node get_next_node()                     = 0;
    virtual Node get_none_node()                     = 0;
    virtual bool is_visited_node( const Node& node ) = 0;
    virtual void set_visited( const Node& node )     = 0;
    virtual bool is_goal_node( const Node& node )    = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_base.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchBase: public BreadthFirstSearchInterface<Node> {
  public:
    Node search() {
      Node res = this->get_none_node();
      this->init();
      while ( this->has_next_node() ) {
        Node node = this->get_next_node();
        if ( this->is_goal_node(node) )
          res = node;
        this->visit_next_node(node);
      }
      return res;
    }
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search.cpp>
namespace search {
  template <class Node> class BreadthFirstSearch: public BreadthFirstSearchBase<Node> {
  public:
    virtual void init() {}
    
    bool has_next_node() {
      return ! Q.empty();
    }
    
    Node get_next_node() {
      Node res = Q.front();
      Q.pop();
      return res;
    }
    
    void push_next_node( const Node& node ) {
      if ( this->is_visited_node(node) )
        return;
      Q.push(node);
      this->set_visited(node);
    }
    
  protected:
    std::queue <Node> Q;
  };
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100 + 11;
  const Int NONE = -1;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int H;
    Int W;
    string G[SIZE];
  };
  struct OutputStorage {
    Int result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Node {
    Int r;
    Int c;
    Int s;
  };

  struct Search: public search::BreadthFirstSearch<Node> {
    const InputStorage* in;
    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const Node NODE_NONE = {NONE, NONE, NONE};

    int gr;
    int gc;
    bool visited[SIZE][SIZE];
    string grid[SIZE];

    void visit_next_node( const Node& node ) {
      for ( int k = 0; k < 8; ++ k ) {
        Node next_node = node;
        next_node.r = node.r + dr[k];
        next_node.c = node.c + dc[k];
        next_node.s = node.s + 1;
        if ( ! check_in_grid(next_node) )
          continue;
        if ( grid[next_node.r][next_node.c] != '.' )
          continue;
        push_next_node(next_node);
      }
    }

    bool check_in_grid( const Node& node ) {
      return ! ( node.r < 0 || node.r >= in->H || node.c < 0 || node.c >= in->W );
    }

    Node get_none_node() {
      return NODE_NONE;
    }

    bool is_visited_node( const Node& node ) {
      return visited[node.r][node.c];
    }

    void set_visited( const Node& node ) {
      visited[node.r][node.c] = true;
    }

    bool is_goal_node( const Node& node ) {
      return node.r == gr && node.c == gc;
    }
  };

  struct Solver: SolverInterface {
    const InputStorage* in;
    Search search;
    Int sr;
    Int sc;
    string grid[SIZE];

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      this->in = in;
      search.in = in;
      std::fill((bool*)search.visited, (bool*)search.visited + SIZE * SIZE, false);
      init_grid();
      Node start_node = {sr, sc, 0};
      search.push_next_node(start_node);
      Node ret = search.search();
      out->result = ret.s;
      return out;
    }

    void init_grid() {
      for ( auto i = 0; i < in->H; ++ i ) {
        search.grid[i] = in->G[i];
      }

      const int dr[8] = {1, 2, 1, 2, -1, -2, -1, -2};
      const int dc[8] = {2, 1, -2, -1, 2, 1, -2, -1};
      for ( auto i = 0; i < in->H; ++ i ) {
        for ( auto j = 0; j < in->W; ++ j ) {
          if ( search.grid[i][j] == 'Z' ) {
            for ( auto k = 0; k < 8; ++ k ) {
              int nr = i + dr[k];
              int nc = j + dc[k];
              if ( nr < 0 || nr >= in->H || nc < 0 || nc >= in->W )
                continue;
              if ( search.grid[nr][nc] == '.' )
                search.grid[nr][nc] = 'Y';
            }
          }
        }
      }

      for ( auto i = 0; i < in->H; ++ i ) {
        for ( auto j = 0; j < in->W; ++ j ) {
          if ( search.grid[i][j] == 'A' ) {
            sr = i;
            sc = j;
            search.grid[i][j] = '.';
          } else if ( search.grid[i][j] == 'B' ) {
            search.gr = i;
            search.gc = j;
            search.grid[i][j] = '.';
          }
        }
      }
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->H >> in->W ) )
        return false;
      for ( int i = 0; i < in->H; ++ i )
        std::cin >> in->G[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      if ( out->result == NONE ) {
        std::cout << "King Peter, you can't go now!" << std::endl;
      } else {
        std::cout << "Minimal possible length of a trip is " << out->result << std::endl;
      }
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  using namespace solution;
  std::cin.sync_with_stdio(false);
  static InputStorage in;
  static OutputStorage out;
  static Storages storages;
  static Solution solution;
  static Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif



