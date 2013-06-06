
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

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    string s;

    int to_int( string s ) {
        ISS iss(s);
        int res;
        iss >> res;
        return res;
    }

    string convert( LL sum ) {
        sum = ( 10 * 100 * 100 * sum ) / ( 24 * 60 * 60 );
        OSS oss;
        oss << setw(7) << setfill('0') << sum;
        return oss.str();
    }

    string solve() {
        LL hh = to_int(s.substr(0, 2));
        LL mm = to_int(s.substr(2, 2));
        LL ss = to_int(s.substr(4, 2));
        LL cc = to_int(s.substr(6, 2));
        LL sum = hh * 60 * 60 * 100 + mm * 60 * 100 + ss * 100 + cc;
        return convert(sum);
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> s;
        }
        
        void output( string result ) {
            cout << result << endl;
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

