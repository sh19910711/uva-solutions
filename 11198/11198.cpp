
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

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
      while ( action() );
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
  typedef set<int> Set;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 8;
  const int NONE = -1;
  // storages
  int A[SIZE];
  int B[SIZE];
  int test_no;
  int result;
  bool P[SIZE + SIZE + 1];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {

  class Node {
  public:
    int state[SIZE];
    int depth;

    Node( const int data[SIZE], const int& depth ): depth(depth) {
      for ( int i = 0; i < SIZE; ++ i )
        state[i] = data[i];
    }
 
    int getHash() {
      int res = 0;
      for ( int i = 0; i < SIZE; ++ i ) {
        res *= 10;
        res += abs(state[i]);
      }
      return res;
    }

    friend ostream& operator <<( ostream& os, const Node& node ) {
      for ( int i = 0; i < SIZE; ++ i )
        os << node.state[i] << ", ";
      return os;
    }
  };

  typedef queue <Node> Queue;

  bool comparator( const int &a, const int& b ) {
    return abs(a) < abs(b);
  }

  class Solver {
  public:

    void solve() {
      test_no ++;

      for ( int i = 0; i < SIZE; ++ i )
        B[i] = A[i];
      sort(B, B + SIZE, comparator);

      result = bfs();
    }

    bool is_goal( const Node& node ) {
      for ( int i = 0; i < SIZE; ++ i )
        if ( node.state[i] != B[i] )
          return false;
      return true;
    }

    void dance( const int src[SIZE], int dst[SIZE], int from, int to ) {
      for ( int i = 0; i < to; ++ i )
        dst[i] = src[i];
      dst[to] = src[from];
      dst[to + 1] = src[to + 1];
      for ( int i = to + 1; i <= from; ++ i )
        dst[i] = src[i - 1];
      for ( int i = from + 1; i < SIZE; ++ i )
        dst[i] = src[i]; 
    }

    int bfs() {
      Queue Q;
      Set visited;
      Node node(A, 0);
      visited.insert(node.getHash());
      Q.push(node);

      while ( ! Q.empty() ) {
        Node node = Q.front();
        Q.pop();

        int* state = node.state;
        int depth = node.depth;

        if ( is_goal(node) )
          return node.depth;

        for ( int i = 0; i < SIZE; ++ i ) {
          for ( int j = 0; j < SIZE; ++ j ) {
            if ( state[i] < 0 && state[j] > 0 ) {
              int sum = abs(state[i]) + abs(state[j]);
              if ( P[sum] ) {
                int next_depth = depth + 1;
                int next_state[SIZE];
                dance(state, next_state, i, j);
                Node next_node(next_state, next_depth);
                int hash = next_node.getHash();
                if ( visited.count(hash) )
                  continue;
                visited.insert(hash);
                Q.push(next_node);
              }
            }
          }
        }
      }

      return NONE;
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {
      test_no = 0;
      fill(P, P + SIZE + SIZE + 1, false);
      for ( int i = 3; i < SIZE; i += 2 )
        P[i] = true;
      P[2] = true;
      for ( int i = 3; i < SIZE; i += 2 ) {
        if ( ! P[i] )
          continue;
        for ( int j = i + i; j < SIZE; j += i ) {
          P[j] = false;
        }
      }
    }

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
      if ( ! ( cin >> A[0] && A[0] != 0 ) )
        return false;
      for ( int i = 1; i < 8; ++ i )
        cin >> A[i];
      return true;
    }

    void output() {
      cout << "Case " << test_no << ": " << result << endl;
    }

  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

