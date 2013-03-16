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

    const string YES = "nice";
    const string NO = "not nice";

    string s;

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> s;
        }
        int get_first( string s ) {
            reverse( s.begin(), s.end() );
            int n = s.size();
            int res = 0;
            int base = 1;
            for ( int i = 0; i < n; ++ i ) {
                res += base * ( s[i] - 'A' );
                base *= 26;
            }
            return res;
        }
        int get_second( string s ) {
            reverse( s.begin(), s.end() );
            int n = s.size();
            int res = 0;
            int base = 1;
            for ( int i = 0; i < n; ++ i ) {
                res += base * ( s[i] - '0' );
                base *= 10;
            }
            return res;
        }
        bool solve() {
            replace( s.begin(), s.end(), '-', ' ' );
            ISS iss(s);
            string f, s;
            iss >> f >> s;
            return abs( get_first(f) - get_second(s) ) <= 100;
        }
        void output( bool result ) {
            cout << ( result ? YES : NO ) << endl;
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



