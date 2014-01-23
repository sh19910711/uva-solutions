
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

// @snippet<sh19910711/contest-base:solution/define_classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
  class SolverInterface {
  public:
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    SolverInterface* solver;
    Storages* storages;
  protected:
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

// @snippet<sh19910711/contest-base:solution/solution-base-multi-tests.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
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

// TODO: EDIT
namespace search {
  template <class Node> class BreadthFirstSearchInterface: public SearchInterface<Node> {
  public:
    virtual Node search()                            = 0;
  protected:
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

namespace search {
  template <class Node> class BreadthFirstSearchBase: public BreadthFirstSearchInterface<Node> {
  public:
    Node search() {
      Node res = this->get_none_node();
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

namespace search {
  template <class Node> class BreadthFirstSearch: public BreadthFirstSearchBase<Node> {
  protected:
    bool has_next_node() {
      return ! Q.empty();
    }
    
    Node get_next_node() {
      Node res = Q.front();
      Q.pop();
      return res;
    }
    
  public:
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

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 10000;
  const int NONE = -1;
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::set <Int> Set;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int S[4];
    Int T[4];
    Int N;
    Int F[SIZE][4];
  };
  struct OutputStorage {
    Int result;
  };
}

namespace solution {
  struct Node {
    Int steps;
    Int A[4];
  };


  class Search: public search::BreadthFirstSearch<Node> {
  public:
    void visit_next_node( const Node& node ) {
      for ( int i = 0; i < 4; ++ i ) {
        for ( int d = -1; d <= 1; ++ d ) {
          Node next_node = node;
          next_node.steps += 1;
          next_node.A[i] += d + 10;
          next_node.A[i] %= 10;
          this->push_next_node(next_node);
        }
      }
    }

    bool is_goal_node( const Node& node ) {
      for ( int i = 0; i < 4; ++ i ) {
        if ( node.A[i] != goal_node.A[i] ) {
          return false;
        }
      }
      return true;
    }

    bool& get_visited( const Node& node ) {
      return visited[node.A[0]][node.A[1]][node.A[2]][node.A[3]];
    }

    void set_visited( const Node& node ) {
      get_visited(node) = true;
    }

    bool is_visited_node( const Node& node ) {
      return get_visited(node);
    }

    Node get_none_node() {
      Node node;
      node.steps = NONE;
      return node;
    }

    Node goal_node;
    bool visited[10][10][10][10];
    bool forbidden[10][10][10][10];
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Solver: public SolverInterface {
  public:
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      Search search;
      std::fill((bool*)search.visited, (bool*)search.visited + 10 * 10 * 10 * 10, false);
      for ( int i = 0; i < in->N; ++ i ) {
        search.visited[in->F[i][0]][in->F[i][1]][in->F[i][2]][in->F[i][3]] = true;
      }
      std::copy(in->T, in->T + 4, search.goal_node.A);

      Node start_node;
      start_node.steps = 0;
      std::copy(in->S, in->S + 4, start_node.A);
      search.push_next_node(start_node);

      out->result = search.search().steps;
      return out;
    }
  protected:
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      if ( ! ( input_digits(in->S) && input_digits(in->T) ) ) {
        return false;
      }
      std::cin >> in->N;
      for ( int i = 0; i < in->N; ++ i ) {
        if ( ! ( input_digits(in->F[i]) ) ) {
          return false;
        }
      }
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->result << std::endl;
    }
  private:
    bool input_digits( Int A[4] ) {
      for ( int i = 0; i < 4; ++ i ) {
        if ( ! ( std::cin >> A[i] ) ) {
          return false;
        }
      }
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  static solution::InputStorage in;
  static solution::OutputStorage out;
  static solution::Storages storages;
  static solution::Solution solution;
  static solution::Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif



