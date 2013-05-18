
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

    string a, b;
    int cur;

    class Node {
    public:
        char value;
        Node* left;
        Node* right;

        Node(): left(NULL), right(NULL) {}
        Node( char value, Node* left, Node* right ): value(value), left(left), right(right) {}
    };

    Node* get_tree( string s ) {
        int p = s.find(a[cur]);
        if ( p == (int)string::npos )
            return NULL;
        cur ++;
        return new Node(a[cur - 1], get_tree(s.substr(0, p)), get_tree(s.substr(p + 1)));
    }

    string rec( Node* v ) {
        if ( v == NULL )
            return "";
        return rec(v->left) + rec(v->right) + v->value;
    }

    string solve() {
        cur = 0;
        Node* root = get_tree(b);
        return rec(root);
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> a >> b;
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

