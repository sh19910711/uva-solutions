
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

    typedef pair <int, int> Result;

    const int SIZE = 10000 + 11;
    const int NONE = -1;
    const int INF = std::numeric_limits<int>::max() / 2;
    const string IMPOSSIBLE = "impossible";

    int n, m;
    VI G[SIZE];
    int D[SIZE];
    bool V[SIZE];

    int query( int k ) {
        return D[k];
    }

    void output_query( int result ) {
        if ( result == NONE ) {
            cout << IMPOSSIBLE << endl;
        } else {
            cout << result << endl;
        }
    }

    Result visit( int prev, int from ) {
        V[from] = true;
        Result res(0, from);
        for ( VI::iterator it_i = G[from].begin(); it_i != G[from].end(); ++ it_i ) {
            int to = *it_i;
            if ( to != prev ) {
                Result t = visit(from, to);
                t.first ++;
                res = min(res, t);
            }
        }
        return res;
    }

    int find_diameter( int from ) {
        Result r = visit(-1, 0);
        Result t = visit(-1, r.second);
        return t.first;
    }

    int find( int from ) {
        int len = find_diameter(from);
        return NONE;
    }

    class Solution: public ISolution {
    public:

        void init() {
            fill(G, G + SIZE, VI());
        }

        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            for ( int i = 0; i < m; ++ i ) {
                int a, b;
                cin >> a >> b;
                a --;
                b --;
                G[a].push_back(b);
                G[b].push_back(a);
            }
            return true;
        }

        void solve() {
            for ( int i = 0; i < n; ++ i ) {
                D[i] = INF;
                V[i] = false;
            }
            for ( int i = 0; i < n; ++ i )
                if ( ! V[i] )
                    D[i] = find(i);

            int queries;
            cin >> queries;
            for ( int i = 0; i < queries; ++ i ) {
                int k;
                cin >> k;
                output_query(query(k));
            }
        }

        int run() {
            int tests;
            std::cin >> tests;
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
                cout << "Case " << i + 1 << ":" << endl;
                solve();
            }
            return 0;
        }
        
    };
    
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


