
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

    typedef double Double;

    const Double NONE = 0.00;
    const int SIZE = 10000 + 11;

    int n;
    Double S[SIZE];

    int get_number() {
        string s;
        getline(cin, s);
        ISS iss(s);
        int res;
        iss >> res;
        return res;
    }

    bool test( Double a, Double b, Double c ) {
        return a + b >= c && b + c >= a && c + a >= b;
    }

    Double calc_area( Double a, Double b, Double c ) {
        Double s = ( a + b + c ) / 2.0;
        return sqrt(s * ( s - a ) * ( s - b ) * ( s - c ));
    }

    Double solve() {
        sort(S, S + n, greater<Double>());

        Double res = NONE;
        for ( int i = 0; i + 2 < n; ++ i ) {
            Double a = S[i], b = S[i + 1], c = S[i + 2];
            if ( test(a, b, c) )
                res = max(res, calc_area(a, b, c));
        }

        return res;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            string s;
            if ( ! getline(cin, s) )
                return false;
            ISS iss(s);
            iss >> n;
            for ( int i = 0; i < n; ++ i )
                iss >> S[i];
            return true;
        }

        void output( Double result ) {
            cout.setf(ios::fixed);
            cout << setprecision(2) << result << endl;
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


