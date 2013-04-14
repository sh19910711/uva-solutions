
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

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    const int NONE = -1;
    string s1, s2;

    bool is_alphabet( char c ) {
        return ( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' );
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return getline(cin, s1) && getline(cin, s2);
        }

        string replace( string s ) {
            int n = s.size();
            for ( int i = 0; i < n; ++ i )
                if ( ! is_alphabet(s[i]) )
                    s[i] = ' ';
            return s;
        }

        VS convert( string s ) {
            VS res;
            ISS iss(s);
            string word;
            while ( iss >> word )
                res.push_back(word);
            return res;
        }

        bool has_only_spaces( string s ) {
            int n = s.size();
            for ( int i = 0; i < n; ++ i )
                if ( s[i] != ' ' )
                    return false;
            return true;
        }
        
        int solve() {
            s1 = replace(s1);
            VS l1 = convert(s1);
            int n1 = l1.size();
            s2 = replace(s2);
            VS l2 = convert(s2);
            int n2 = l2.size();
            if ( has_only_spaces(s1) || has_only_spaces(s2) )
                return NONE;
            int res = 0;
            for ( int i1 = 0; i1 < n1; ++ i1 ) {
                for ( int j1 = i1; j1 < n1; ++ j1 ) {
                    for ( int i2 = 0; i2 < n2; ++ i2 ) {
                        int len = j1 - i1 + 1;
                        if ( i2 + len - 1 >= n2 )
                            continue;
                        bool ok = true;
                        for ( int i = 0; i < len; ++ i ) {
                            if ( l1[i1+i] != l2[i2+i] ) {
                                ok = false;
                            }
                        }
                        if ( ok )
                            res = max( res, len );
                    }
                }
            }
            return res;
        }

        void output( int test_no, int result ) {
            if ( result == NONE ) {
                cout << test_no << ". " << "Blank!" << endl;
            } else {
                cout << test_no << ". " << "Length of longest match: " << result << endl;
            }
        }
        
        int run() {
            int test_no = 1;
            while ( init(), input() ) {
                output(test_no ++, solve());
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

