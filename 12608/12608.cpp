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

    const int SIZE = 1011;
    int L, N;
    int X[SIZE];
    int W[SIZE];

    class Solution: public ISolution {
    public:
        bool input() {
            cin >> L >> N;
            for ( int i = 0; i < N; ++ i )
                cin >> X[i] >> W[i];
            return true;
        }

        LL solve() {
            LL res = 0;
            int sum = 0;
            for ( int i = 0; i < N; ++ i ) {
                if ( sum + W[i] > L ) {
                    res += X[i] * 2;
                    sum = 0;
                }
                res += X[i];
                sum += W[i];
                if ( i - 1 >= 0 )
                    res -= X[i-1];
            }
            res += X[N-1];
            return res;
        }

        void output( LL result ) {
            cout << result << endl;
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



