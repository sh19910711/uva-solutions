
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

    const int SIZE = 10000 + 11;
    const int TYPES = 26;

    int n;
    string S[SIZE];
    int remains;

    int get_number() {
        string s;
        getline(cin, s);
        ISS iss(s);
        int res;
        iss >> res;
        return res;
    }

    int get_state( string s ) {
        int res = 0;
        int ns = s.size();
        for ( int i = 0; i < ns; ++ i )
            res |= 1 << ( s[i] - 'a' );
        return res;
    }

    bool have_common( int a, int b ) {
        return a & b;
    }

    bool check( string s ) {
        int state = get_state(s);
        if ( ! have_common(remains, state) ) {
            remains = state;
            return true;
        }
        remains &= state;
        return false;
    }

    int solve() {
        int res = 0;
        remains = get_state(S[0]);
        for ( int i = 1; i < n; ++ i ) {
            if ( check(S[i]) ) {
                res ++;
            }
        }
        return res;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            n = get_number();
            for ( int i = 0; i < n; ++ i )
                getline(cin, S[i]);
            return true;
        }

        void output( int result ) {
            cout << result << endl;
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


