
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

#include <memory>
#include <array>

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

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
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
  const string YES = "STABLE";
  const string NO = "UNSTABLE";
  const char EMPTY_CELL = '.';
  const Int NONE = -1;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int W;
    Int H;
    string grid[SIZE];
  };
  struct OutputStorage {
    bool result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  typedef std::tuple <Int, Int> Pos;

  struct Piece;
  typedef std::unique_ptr<Piece> UP_Piece;
  typedef std::vector <UP_Piece> Pieces;
  struct Piece {
    Double x_l;
    Double x_r;
    Double m_sum;
    Int blocks;
    Pieces childrens;
    // Int childrens_num;

    Piece() {
      x_l = std::numeric_limits<Double>::max();
      x_r = std::numeric_limits<Double>::min();
      m_sum = 0.0;
      blocks = 0;
    }

    Piece* add_child() {
      childrens.push_back(UP_Piece(new Piece()));
      return this->childrens.back().get();
    }

    Int get_child_blocks() const {
      Double res = blocks;
      for ( const auto& child : childrens ) {
        res += child->get_child_blocks();
      }
      return res;
    }

    Double get_child_sum() const {
      Double res = m_sum;
      for ( const auto& child : childrens ) {
        res += child->get_child_sum();
      }
      return res;
    }

    bool check_balance() const {
      // cout << "@check_balance: " << get_child_sum() << " / " << get_child_blocks() << endl;
      Double m = get_child_sum() / get_child_blocks();
      // cout << "@check_balance: l = " << x_l << " < " << m << " < " << x_r << endl;
      return x_l < m && m < x_r;
    }

    friend ostream& operator <<( ostream& os, const Piece& p ) {
      return os << "{l = " << p.x_l << ", r = " << p.x_r << ", m_sum = " << p.m_sum << ", childs = " << p.childrens.size() << ", blocks = " << p.blocks << "}";
    }
  };

  const Int dr[4] = {1, -1, 0, 0};
  const Int dc[4] = {0, 0, 1, -1};

  struct Search {
    const InputStorage* in;

    Int W;
    Int H;
    string G[SIZE];

    Int sr;
    Int sc;
    bool visited[SIZE][SIZE];
    bool visited_childrens[SIZE][SIZE];

    bool run() {
      this->W = in->W;
      this->H = in->H;
      std::copy(in->grid, in->grid + SIZE, G);
      find_start();

      std::fill((bool*)visited, (bool*)visited + SIZE * SIZE, false);
      std::fill((bool*)visited_childrens, (bool*)visited_childrens + SIZE * SIZE, false);
      UP_Piece root = UP_Piece(new Piece());
      find_pieces(sr, sc, root.get());
      // cout << "Debug: " << endl; print_tree(root.get()); cout << endl;
      // Int connected_blocks = 0;
      // for_each_node(root.get(), [&connected_blocks](const Piece* p) { connected_blocks += p->blocks; });
      // Int total_blocks = count_cell([this](const Int& r, const Int& c) { return G[r][c] != '.'; });
      
      return check_tree(root.get());
    }

    bool check_tree( const Piece* cur ) {
      if ( ! cur->check_balance() )
        return false;
      for ( const auto& child : cur->childrens ) {
        if ( ! check_tree(child.get()) )
          return false;
      }
      return true;
    }

    template <class Func> Int count_cell( Func func ) {
      Int res = 0;
      for ( auto r = 0; r < H; ++ r ) {
        for ( auto c = 0; c < W; ++ c ) {
          if ( func(r, c) )
            res ++;
        }
      }
      return res;
    }

    template <class Func> void for_each_node( const Piece* p, Func func ) {
      func(p);
      for ( const auto& child : p->childrens ) {
        for_each_node(child.get(), func);
      }
    }

    void print_tree( const Piece* p, const Int& depth = 0 ) {
      // cout << string(depth * 2, ' ') << *p << " | " << p << endl;
      // for ( auto i = 0; i < p->childrens_num; ++ i ) {
      for ( const auto& child : p->childrens ) {
        print_tree(child.get(), depth + 1);
      }
    }

    void find_pieces( const Int& sr, const Int& sc, Piece* cur ) {
      find_blocks(G[sr][sc], sr, sc, cur);
      find_childrens(G[sr][sc], sr, sc, cur);
    }

    void find_childrens( const char& color, const Int& sr, const Int& sc, Piece* parent_piece ) {
      if ( visited_childrens[sr][sc] )
        return;
      visited_childrens[sr][sc] = true;
      for ( auto i = 0; i < 1; ++ i ) {
        Int nr = sr - 1;
        Int nc = sc;
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
          continue;
        if ( color == G[nr][nc] || G[nr][nc] == '.' )
          continue;
        if ( visited[nr][nc] )
          continue;
        Piece* child = parent_piece->add_child();
        find_pieces(nr, nc, child);
      }
      for ( auto k = 0; k < 4; ++ k ) {
        Int nr = sr + dr[k];
        Int nc = sc + dc[k];
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
          continue;
        if ( color != G[nr][nc] )
          continue;
        find_childrens(color, nr, nc, parent_piece);
      }
    }

    bool is_bottom( const Int& r, const Int& c ) {
      if ( r + 1 >= H )
        return true;
      if ( G[r + 1][c] == '.' )
        return false;
      return G[r + 1][c] != G[r][c];
    }

    void find_blocks( const char& color, const Int& sr, const Int& sc, Piece* p ) {
      if ( visited[sr][sc] )
        return;
      visited[sr][sc] = true;

      // update
      Double x = sc;
      if ( is_bottom(sr, sc) ) {
        p->x_l = std::min(p->x_l, x);
        p->x_r = std::max(p->x_r, x + 1.0);
      }
      p->m_sum += x + 0.5;
      p->blocks += 1;

      for ( Int k = 0; k < 4; ++ k ) {
        Int nr = sr + dr[k];
        Int nc = sc + dc[k];
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
          continue;
        if ( color != G[nr][nc] )
          continue;
        find_blocks(color, nr, nc, p);
      }
    }

    void find_start() {
      auto ret = find_cell([this](Int r, Int c){ return r == H - 1 && G[r][c] != EMPTY_CELL; });
      sr = get<0>(ret);
      sc = get<1>(ret);
    }

    template <class Func> Pos find_cell( Func f ) {
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          if ( f(i, j) )
            return Pos(i, j);
        }
      }
      return Pos(NONE, NONE);
    }
  };

  struct Solver: SolverInterface {
    Search search;

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      search.in = in;
      out->result = search.run();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->W >> in->H ) )
        return false;
      if ( in->W == 0 && in->H == 0 )
        return false;
      for ( int i = 0; i < in->H; ++ i )
        std::cin >> in->grid[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << ( out->result ? YES : NO ) << std::endl;
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

