
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

    typedef set <LL> Set;

    const int SIZE = 1011;
    
    int n;
    LL X[SIZE];
    LL Y[SIZE];
    LL S[SIZE * SIZE];
    LL SC;

    LL sq( LL x ) {
        return x * x;
    }

    LL get_dist( int a, int b ) {
        return sq(X[a] - X[b]) + sq(Y[a] - Y[b]);
    }
    
    class Solution: public ISolution {
    public:

        void init() {
            SC = 0;
        }

        bool input() {
            cin >> n;
            for ( int i = 0; i < n; ++ i )
                cin >> X[i] >> Y[i];
            return true;
        }

        int solve() {
            S[SC ++] = 0;
            for ( int i = 0; i < n; ++ i )
                for ( int j = i + 1; j < n; ++ j )
                    S[SC ++] = get_dist(i, j);
            sort(S, S + SC);
            return unique(S, S + SC) - S;
        }

        void output( int test_no, int result ) {
            cout << "Case " << test_no << ": " << result << endl;
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


