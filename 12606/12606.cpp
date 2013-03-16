
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

    const string UNKNOWN = "unknown";
    const string TRUE = "true";
    const string FALSE = "false";

    const int SIZE = 101;
    int na, nb;
    string UN[SIZE];
    string UR[SIZE][2];
    string DN[SIZE];
    string DR[SIZE][2][2];
    string E;
    const int V_SIZE = 501;
    map <string, int> VID;
    string VN[V_SIZE];
    string VR[V_SIZE];
    int VC;

    string getline() {
        string line;
        getline( cin, line );
        return line;
    }

    bool is_lower( char c ) {
        return 'a' <= c && c <= 'z';
    }

    // exp[k...]を計算する
    string parse( const string& exp, int& k ) {
        cout << "@parse: exp = " << exp << ", k = " << k << endl;
        if ( exp[k] == '(' ) {
            k ++;
            string left = parse( exp, k );
            cout << "left: " << left << endl;
            k ++;
            k ++;
            string op = parse( exp, k );
        } else {
            char c = exp[k];
            if ( is_lower(c) ) {
                string name = string()+c;
                if ( ! VID.count(name) )
                    return UNKNOWN;
                return VR[VID[name]];
            }
        }
        return UNKNOWN;
    }

    class Solution: public ISolution {
    public:
        void init() {
            VID.clear();
        }
        bool input() {
            ISS iss1(getline());
            if ( ! ( iss1 >> na >> nb ) )
                return false;
            if ( na < 0 && nb < 0 )
                return false;
            for ( int i = 0; i < na; ++ i ) {
                ISS iss2(getline());
                iss2 >> UN[i];
                ISS iss3(getline());
                for ( int j = 0; j < 2; ++ j )
                    iss3 >> UR[i][j];
            }
            for ( int i = 0; i < nb; ++ i ) {
                ISS iss4(getline());
                iss4 >> DN[i];
                for ( int j = 0; j < 2; ++ j ) {
                    ISS iss5(getline());
                    for ( int k = 0; k < 2; ++ k )
                        iss5 >> DR[i][j][k];
                }
            }
            E = getline();
            string line;
            VC = 0;
            while ( ( line = getline() ) != "" ) {
                if ( line == "*" )
                    break;
                ISS iss(line);
                string a, b;
                iss >> a >> b;
                VN[VC] = a;
                VR[VC] = b;
                VID[a] = VC;
                VC ++;
            }
            return true;
        }
        void solve() {
            int k = 0;
            cout << parse(E,k) << endl;
        }
        int run() {
            while ( init(), input() ) {
                solve();
                output();
            }
            return 0;
        }
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}



