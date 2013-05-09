
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

    const int VARIABLES = 26;

    string s;
    int n;
    int pre_values[VARIABLES];
    int values[VARIABLES];
    int A[VARIABLES];
    bool used[VARIABLES];

    string exp;
    int value;

    string get_cut( const string& s ) {
        ISS iss(s);
        string res;
        string t;
        while ( iss >> t )
            res += t;
        return res;
    }

    bool is_alphabet( const char& c ) {
        return 'a' <= c && c <= 'z';
    }

    void check_used() {
        for ( int i = 0; i < n; ++ i )
            if ( is_alphabet(s[i]) )
                used[s[i] - 'a'] = true;
    }

    void proc_inc_back() {
        for ( int i = 0; i + 2 < n; ++ i ) {
            char c = s[i];
            if ( is_alphabet(c) ) {
                if ( s[i + 1] == '+' && s[i + 1] == s[i + 2] ) {
                    values[c - 'a'] ++;
                    s[i + 1] = s[i + 2] = ' ';
                }
            }
        }
    }

    void proc_inc_front() {
        for ( int i = 2; i < n; ++ i ) {
            char c = s[i];
            if ( is_alphabet(c) ) {
                if ( s[i - 1] == '+' && s[i - 1] == s[i - 2] ) {
                    values[c - 'a'] ++;
                    s[i - 1] = s[i - 2] = ' ';
                }
            }
        }
    }

    void proc_dec_back() {
        for ( int i = 0; i + 2 < n; ++ i ) {
            char c = s[i];
            if ( is_alphabet(c) ) {
                if ( s[i + 1] == '-' && s[i + 1] == s[i + 2] ) {
                    values[c - 'a'] --;
                    s[i + 1] = s[i + 2] = ' ';
                }
            }
        }
    }

    void proc_dec_front() {
        for ( int i = 2; i < n; ++ i ) {
            char c = s[i];
            if ( is_alphabet(c) ) {
                if ( s[i - 1] == '-' && s[i - 1] == s[i - 2] ) {
                    values[c - 'a'] --;
                    s[i - 1] = s[i - 2] = ' ';
                }
            }
        }
    }

    void calc_value() {
        value = 0;
        for ( int i = 0; i < n; i += 2 ) {
            if ( s[i] == '+' ) {
                value += pre_values[s[i + 1] - 'a'];
            } else {
                value -= pre_values[s[i + 1] - 'a'];
            }
        }
    }

    void calc_expression() {
        check_used();
        proc_inc_front();
        proc_dec_front();
        for ( char c = 'a'; c <= 'z'; ++ c )
            pre_values[c - 'a'] = values[c - 'a'];
        proc_inc_back();
        proc_dec_back();
        s = get_cut(s);
        if ( s[0] != '-' )
            s = "+" + s;
        n = s.size();
        calc_value();
    }
    
    void solve() {
        s = get_cut(exp);
        n = s.size();
        calc_expression();
    }

    class Solution: public ISolution {
    public:

        void init() {
            for ( int i = 0; i < VARIABLES; ++ i ) {
                pre_values[i] = i + 1;
                values[i] = i + 1;
                used[i] = false;
            }
        }
        
        bool input() {
            return getline(cin, exp);
        }

        void output() {
            cout << "Expression: " << exp << endl;
            cout << "    value = " << value << endl;
            for ( char c = 'a'; c <= 'z'; ++ c ) {
                int i = c - 'a';
                if ( used[i] ) {
                    cout << "    " << c << " = " << values[i] << endl;
                }
            }
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

