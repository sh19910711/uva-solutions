
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

    const int SIZE = 100 + 11;
    const string YES = "YES";
    const string NO = "NO";
    const int NONE = -1;
    const char SLUMP = '0';
    const char SLIMP = '1';

    string s;
    int n;

    bool is_slump_char( const char& c ) {
        return c == 'D' || c == 'E';
    }

    bool is_slimp_char( const char& c ) {
        return c == 'A';
    }

    int check_slump( int k, int d ) {
        if ( k >= n )
            return NONE;
        const char& c = s[k];
        if ( d == 0 ) {
            if ( s[k] == 'D' || c == 'E' ) {
                return check_slump(k + 1, 1);
            } else {
                return NONE;
            }
        } else if ( ( d == 1 || d == 2 ) && c == 'F' ) {
            return check_slump(k + 1, 2);
        } else if ( d == 2 && ( c == 'D' || c == 'E' ) ) {
            int ret = check_slump(k, 0);
            return ret == NONE ? NONE : ret;
        } else if ( d == 2 && c == 'G' ) {
            return k;
        }
        return NONE;
    }

    int check_slimp( int k, int d ) {
        if ( k >= n )
            return NONE;
        const char& c = s[k];
        if ( d == 0 && c == 'A' ) {
            return check_slimp(k + 1, 1);
        } else if ( d == 1 ) {
            if ( c == 'H' ) {
                return k;
            } else if ( c == 'B' ) {
                return check_slimp(k + 1, 2);
            } else if ( is_slump_char(c) ) {
                int ret = check_slump(k, 0);
                if ( ret == NONE )
                    return NONE;
                return check_slimp(ret + 1, 3);
            }
        } else if ( d == 2 ) {
            if ( is_slimp_char(c) ) {
                int ret = check_slimp(k, 0);
                if ( ret == NONE )
                    return NONE;
                return check_slimp(ret + 1, 3);
            }
        } else if ( d == 3 && c == 'C' ) {
            return k;
        }
        return NONE;
    }

    bool check_slurpy( string s ) {
        for ( int i = 0; i < n; ++ i ) {
            if ( is_slump_char(s[i]) ) {
                int ret = check_slump(i, 0);
                if ( ret == NONE )
                    continue;
                for ( int j = i; j <= ret; ++ j )
                    s[j] = SLUMP;
            } else if ( is_slimp_char(s[i]) ) {
                int ret = check_slimp(i, 0);
                if ( ret == NONE )
                    continue;
                for ( int j = i; j <= ret; ++ j )
                    s[j] = SLIMP;
            }
        }
        s.erase(unique(s.begin(), s.end()), s.end());
        return s == "10";
    }

    bool solve() {
        n = s.size();
        return check_slurpy(s);
    }

    class Solution: public ISolution {
    public:

        bool input() {
            return cin >> s;
        }

        void output( bool result ) {
            cout << ( result ? YES : NO ) << endl;
        }

        int run() {
            int tests;
            std::cin >> tests;
            cout << "SLURPYS OUTPUT" << endl;
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
                output(solve());
            }
            cout << "END OF OUTPUT" << endl;
            return 0;
        }

    };

}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


