
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
    const int dr2[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    const int dc2[8] = {1, -1, 0, 0, 1, -1, 1, -1};

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

    bool check_filled() {
        fill_init();
        for ( int i = 0; i < D; ++ i ) {
            int ret = fill(R[i], C[i]);
            if ( ret != N[i] )
                return false;
        }
        return true;
    }

    void calc_shaded_init() {
        for ( int i = 0; i < H; ++ i )
            for ( int j = 0; j < W; ++ j )
                V[i][j] = false;
    }

    int calc_shaded( int r, int c ) {
        if ( V[r][c] )
            return 0;
        V[r][c] = true;
        int res = 1;
        for ( int k = 0; k < 4; ++ k ) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if ( ! check_pos(nr, nc) )
                continue;
            if ( M[nr][nc] == EMPTY )
                continue;
            if ( V[nr][nc] )
                continue;
            res += calc_shaded(nr, nc);
        }
        return res;
    }

    bool check_shaded() {
        int shaded = 0;
        for ( int i = 0; i < H; ++ i )
            for ( int j = 0; j < W; ++ j )
                if ( M[i][j] != EMPTY )
                    shaded ++;
        calc_shaded_init();
        for ( int i = 0; i < H; ++ i )
            for ( int j = 0; j < W; ++ j )
                if ( M[i][j] != EMPTY ) {
                    int ret = calc_shaded(i, j);
                    return ret == shaded;
                }
        return shaded == 0;
    }

    bool check_2x2( int r, int c ) {
        for ( int i = 0; i < 2; ++ i )
            for ( int j = 0; j < 2; ++ j )
                if ( M[r + i][c + j] == EMPTY )
                    return true;
        return false;
    }

    bool check_2x2() {
        for ( int i = 0; i + 1 < H; ++ i )
            for ( int j = 0; j + 1 < W; ++ j )
                if ( ! check_2x2(i, j) )
                    return false;
        return true;
    }

    void dfs_init() {
        for ( int i = 0; i < H; ++ i )
            for ( int j = 0; j < W; ++ j )
                V[i][j] = false;
    }

    bool dfs( int r, int c ) {
        if ( V[r][c] )
            return false;
        V[r][c] = true;
        if ( r == 0 || r == H - 1 || c == 0 || c == W - 1 )
            return true;
        for ( int k = 0; k < 8; ++ k ) {
            int nr = r + dr2[k];
            int nc = c + dc2[k];
            if ( ! check_pos(nr, nc) )
                continue;
            if ( V[nr][nc] )
                continue;
            if ( M[nr][nc] != EMPTY )
                continue;
            if ( dfs(nr, nc) )
                return true;
        }
        return false;
    }

    bool check_reached() {
        for ( int i = 0; i < D; ++ i ) {
            dfs_init();
            if ( ! V[R[i]][C[i]] && ! dfs(R[i], C[i]) )
                return false;
        }
        return true;
    }

    bool check_sum() {
        int empties = 0;
        for ( int i = 0; i < H; ++ i )
            for ( int j = 0; j < W; ++ j )
                if ( M[i][j] == EMPTY )
                    empties ++;
        int sum = 0;
        for ( int i = 0; i < D; ++ i )
            sum += N[i];
        return empties == sum;
    }

    bool check_2x2_small() {
        for ( int i = 0; i < min(2, H); ++ i )
            for ( int j = 0; j < min(2, W); ++ j )
                if ( M[i][j] == EMPTY )
                    return true;
        return false;
    }

    bool has_zero() {
        return count(N, N + D, 0) > 0;
    }

    bool solve() {
        if ( has_zero() )
            return false;
        if ( ! check_sum() )
            return false;
        if ( ! check_filled() )
            return false;
        if ( ! check_shaded() )
            return false;
        if ( ! check_2x2() )
            return false;
        if ( ! check_2x2_small() )
            return false;
        if ( ! check_reached() )
            return false;
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


