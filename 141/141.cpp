
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

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    typedef set<VVI> Set;

    const int SIZE = 100 + 11;
    const int NONE = -1;

    int n;
    int R[SIZE];
    int C[SIZE];
    char T[SIZE];
    VVI M;
    Set S;

    int winner;
    int move_no;

    void rotate_map() {
        VVI tmp(n, VI(n));
        for ( int i = 0; i < n; ++ i )
            for ( int j = 0; j < n; ++ j )
                tmp[j][n - i - 1] = M[i][j];
        M = tmp;
    }

    bool move( int k ) {
        int r = R[k] - 1;
        int c = C[k] - 1;
        char t = T[k];
        if ( t == '+' ) {
            M[r][c] = 1;
        } else {
            M[r][c] = 0;
        }

        if ( S.count(M) )
            return false;
        for ( int i = 0; i < 4; ++ i ) {
            rotate_map();
            S.insert(M);
        }
        return true;
    }

    void solve() {
        M = VVI(n, VI(n, 0));
        for ( int i = 0; i < 2 * n; ++ i ) {
            if ( ! move(i) ) {
                winner = i % 2 == 0 ? 2 : 1;
                move_no = i + 1;
                return;
            }
        }
    }

    class Solution: public ISolution {
    public:

        void init() {
            winner = NONE;
            S.clear();
        }

        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            if ( n == 0 )
                return false;
            for ( int i = 0; i < 2 * n; ++ i )
                cin >> R[i] >> C[i] >> T[i];
            return true;
        }

        void output() {
            if ( winner == NONE ) {
                cout << "Draw" << endl;
            } else {
                cout << "Player " << winner << " wins on move " << move_no << endl;
            }
        }
        
        int run() {
            while ( init(), input() ) {
                solve();
                output();
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

