
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

    const int T_SIZE = 5;
    const int A_SIZE = 75;
    const int BOMBED = -1;
    const int NONE = -1;

    int T[T_SIZE][T_SIZE];
    int A[A_SIZE];

    void bomb( int x ) {
        for ( int i = 0; i < T_SIZE; ++ i )
            for ( int j = 0; j < T_SIZE; ++ j )
                if ( T[i][j] == x )
                    T[i][j] = BOMBED;
    }

    bool check_diag_1() {
        for ( int i = 0; i < T_SIZE; ++ i )
            if ( T[i][i] != BOMBED )
                return false;
        return true;
    }

    bool check_diag_2() {
        for ( int i = 0; i < T_SIZE; ++ i )
            if ( T[T_SIZE - i - 1][i] != BOMBED )
                return false;
        return true;
    }

    bool check_column( int c ) {
        for ( int i = 0; i < T_SIZE; ++ i )
            if ( T[i][c] != BOMBED )
                return false;
        return true;
    }

    bool check_row( int r ) {
        for ( int i = 0; i < T_SIZE; ++ i )
            if ( T[r][i] != BOMBED )
                return false;
        return true;
    }

    bool is_bingo() {
        if ( check_diag_1() )
            return true;
        if ( check_diag_2() )
            return true;
        for ( int i = 0; i < T_SIZE; ++ i )
            if ( check_column(i) )
                return true;
        for ( int i = 0; i < T_SIZE; ++ i )
            if ( check_row(i) )
                return true;
        return false;
    }

    int solve() {
        for ( int i = 0; i < A_SIZE; ++ i ) {
            bomb(A[i]);
            if ( is_bingo() )
                return i + 1;
        }
        return NONE;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            for ( int i = 0; i < T_SIZE; ++ i ) {
                for ( int j = 0; j < T_SIZE; ++ j ) {
                    if ( i == 2 && j == 2 ) {
                        T[i][j] = BOMBED;
                    } else {
                        cin >> T[i][j];
                    }
                }
            }
            for ( int i = 0; i < A_SIZE; ++ i )
                cin >> A[i];
            return true;
        }

        void output( int result ) {
            cout << "BINGO after " << result << " numbers announced" << endl;
        }
        
        int run() {
            int tests;
            std::cin >> tests;
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


