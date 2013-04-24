
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

    const int SIZE = 101;
    const int NONE = -1;

    string s;
    int st;
    int A[SIZE];
    int AC;
    int B[SIZE];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> s;
        }

        string to_string( int n ) {
            OSS oss;
            oss << n;
            return oss.str();
        }

        int to_int( string s ) {
            ISS iss(s);
            int res;
            iss >> res;
            return res;
        }

        char to_char( int n ) {
            return '0' + n;
        }

        string convert( char c ) {
            int id = c - 'A';
            return to_string(st + id);
        }

        void convert() {
            int n = s.size();
            AC = 0;
            for ( int i = 0; i < n; ++ i ) {
                string t = convert(s[i]);
                for ( string::iterator it_i = t.begin(); it_i != t.end(); ++ it_i ) {
                    char c = *it_i;
                    A[AC++] = c - '0';
                }
            }
        }

        int calc() {
            convert();
            while ( AC > 3 ) {
                for ( int i = 0; i + 1 < AC; ++ i )
                    B[i] = ( A[i] + A[i + 1] ) % 10;
                for ( int i = 0; i + 1 < AC; ++ i )
                    A[i] = B[i];
                AC -= 1;
            }
            if ( AC != 3 )
                return NONE;
            string t;
            t += to_char(A[0]);
            t += to_char(A[1]);
            t += to_char(A[2]);
            return to_int(t);
        }

        bool check() {
            return calc() == 100;
        }
        
        int solve() {
            for ( st = 0; st <= 10000; ++ st )
                if ( check() )
                    return st;
            return NONE;
        }

        void output( int result ) {
            if ( result == NONE ) {
                cout << ":(" << endl;
            } else {
                cout << result << endl;
            }
        }
        
        int run() {
            while ( init(), input() ) {
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

