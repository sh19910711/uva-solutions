
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

    string s;

    int compress( int n ) {
        return ceil(log2(n));
    }

    VI to_vi( string s ) {
        VI res;
        int n = s.size();
        int tmp = 0;
        for ( int i = 0; i < n; ++ i ) {
            if ( s[i] == ' ' ) {
                tmp ++;
            } else {
                if ( tmp )
                    res.push_back(tmp);
                tmp = 0;
            }
        }
        if ( tmp )
            res.push_back(tmp);
        return res;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return getline(cin, s);
        }
        
        int solve() {
            VI A = to_vi(s);
            transform(A.begin(), A.end(), A.begin(), compress);
            return *max_element(A.begin(), A.end());
        }

        void output( int result ) {
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

