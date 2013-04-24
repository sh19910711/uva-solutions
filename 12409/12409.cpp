
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
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
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


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;
    
    const int SIZE = 50011;
    const string YES = "win";
    const string NO = "lose";

    int H, W;
    int A[SIZE];

    inline int mapping( int r, int c ) {
        return r * W + c;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            if ( ! ( cin >> H >> W ) )
                return false;
            for ( int i = 0; i < H; ++ i )
                for ( int j = 0; j < W; ++ j )
                    cin >> A[mapping(i, j)];
            return true;
        }

        bool solve() {
            int nim = 0;
            for ( int i = 0; i < H; ++ i )
                for ( int j = 0; j < W; ++ j )
                    if ( ( H - i + W - j ) % 2 == 1 )
                        nim ^= A[mapping(i, j)];
            return nim > 0;
        }

        void output( int test_no, bool result ) {
            cout << "Case " << test_no << ": " << ( result ? YES : NO ) << endl;
        }

        int run() {
            int tests;
            std::cin >> tests;
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
                output(i + 1, solve());
            }
            return 0;
        }

    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


