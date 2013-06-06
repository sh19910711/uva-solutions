
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


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;

    const int SIZE = 100 * 100 + 11;
    const int GRID_SIZE = 100 + 11;
    const string YES = "solved";
    const string NO = "not solved";
    const char EMPTY = '.';

    int H, W, D;
    int R[SIZE];
    int C[SIZE];
    int N[SIZE];
    string M[GRID_SIZE];
    bool V[GRID_SIZE][GRID_SIZE];

    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};

    int get_number() {
        string s;
        getline(cin, s);
        ISS iss(s);
        int res;
        iss >> res;
        return res;
    }

    void fill_init() {
        for ( int i = 0; i < H; ++ i )
            for ( int j = 0; j < W; ++ j )
                V[i][j] = false;
    }

    bool check_pos( int r, int c ) {
        return r >= 0 && r < H && c >= 0 && c < W;
    }

    int fill( int r, int c ) {
        if ( V[r][c] )
            return 0;
        V[r][c] = true;
        int res = 1;
        for ( int k = 0; k < 4; ++ k ) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if ( ! check_pos(nr, nc) )
                continue;
            if ( M[nr][nc] != EMPTY )
                continue;
            if ( V[nr][nc] )
                continue;
            res += fill(nr, nc);
        }
        return res;
    }

    bool solve() {
        fill_init();
        for ( int i = 0; i < D; ++ i ) {
            int ret = fill(R[i], C[i]);
            cout << R[i] << ", " << C[i] << ": " << ret << " ? " << N[i] << endl;
            if ( ret != N[i] )
                return false;
        }
        return true;
    }

    class Solution: public ISolution {
    public:

        void input_hwd() {
            string s;
            getline(cin, s);
            ISS iss(s);
            iss >> H >> W >> D;
        }

        void input_numbered( int k ) {
            string s;
            getline(cin, s);
            ISS iss(s);
            iss >> R[k] >> C[k] >> N[k];
        }

        void input_grid() {
            for ( int i = 0; i < H; ++ i )
                getline(cin, M[i]);
        }

        bool input() {
            string blank;
            if ( ! getline(cin, blank) )
                return false;
            input_hwd();
            for ( int i = 0; i < D; ++ i ) {
                input_numbered(i);
            }
            input_grid();
            return true;
        }

        void output( bool result ) {
            cout << ( result ? YES : NO ) << endl;
        }
        
        int run() {
            int tests = get_number();
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
                output(solve());
            }
            return 0;
        }
        
    };
    
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


