
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

    const string YES = "LOOP";
    const string NO = "NO LOOP";

    VS P;
    int fs, ms;

    int get_number() {
        string s;
        getline(cin, s);
        ISS iss(s);
        int res;
        iss >> res;
        return res;
    }

    void count_up( const string& s ) {
        if ( s[0] == 'F' )
            fs ++;
        else
            ms ++;
        if ( s[1] == 'F' )
            fs ++;
        else
            ms ++;
    }

    bool solve() {
        for_each(P.begin(), P.end(), count_up);
        return fs == ms && P.size() >= 2;
    }

    class Solution: public ISolution {
    public:

        void init() {
            P.clear();
            fs = ms = 0;
        }

        bool input() {
            string s;
            if ( ! getline(cin, s) )
                return false;
            ISS iss(s);
            string word;
            while ( iss >> word )
                P.push_back(word);
            return true;
        }

        void output( bool result ) {
            cout << ( result ? YES : NO ) << endl;
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


