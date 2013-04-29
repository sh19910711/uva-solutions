
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

namespace solution {
    const int SIZE = 25 * 10000 + 11;
}

namespace solution {

    class Node {
    public:
        bool flag;
        int left, right;
        LL sum;
        LL add1, add2;
        LL value;
        LL steps;

        Node() {
            flag = false;
            add1 = add2 = value = steps = 0;
        }

        int getMid() {
            return ( left + right ) / 2;
        }

        int getLength() {
            return right - left + 1;
        }

        void changeAB( LL a, LL b, LL k ) {
            add1 += a;
            add2 += b;
            steps += k;
            sum += ( a + b ) * getLength() / 2;
        }

        void changeC( LL a ) {
            flag = true;
            value = a;
            add1 = add2 = 0;
            steps = 0;
            sum = value * getLength();
        }

    };

    Node tree[SIZE * 4];
    class SegmentTree {
    public:

        void down( int k ) {
            Node& cur = tree[k];
            if ( cur.flag ) {
                tree[k * 2].changeC(cur.value);
                tree[k * 2 + 1].changeC(cur.value);
                cur.flag = false;
            }
            if ( cur.add1 || cur.add2 || cur.steps ) {
                LL mid = cur.add1 + cur.steps * ( tree[k * 2].getLength() - 1 );
                tree[k * 2].changeAB(cur.add1, mid, cur.steps);
                tree[k * 2 + 1].changeAB(mid + cur.steps, cur.add2, cur.steps);
                cur.add1 = cur.add2 = cur.steps = 0;
            }
        }

        void build( LL l, LL r, LL k ) {
            Node& cur = tree[k];
            cur.left = l;
            cur.right = r;
            cur.add1 = cur.add2 = cur.sum = cur.value = cur.steps = 0;
            if ( l != r ) {
                build(l, cur.getMid(), k * 2);
                build(cur.getMid() + 1, r, k * 2 + 1);
            }
        }

        void updateAB( LL l, LL r, LL k, LL steps ) {
            Node& cur = tree[k];
            if ( l <= cur.left && cur.right <= r ) {
                LL cl, cr;
                if ( steps >= 0 ) {
                    cl = cur.left - l + 1;
                    cr = cur.right - l + 1;
                } else {
                    cl = r - cur.left + 1;
                    cr = r - cur.right + 1;
                }
                cur.changeAB(cl, cr, steps);
            } else {
                down(k);
                if ( l <= cur.getMid() ) {
                    updateAB(l, r, k * 2, steps);
                }
                if ( r > cur.getMid() ) {
                    updateAB(l, r, k * 2 + 1, steps);
                }
                cur.sum = tree[k * 2].sum + tree[k * 2 + 1].sum;
            }
        }

        void updateC( LL l, LL r, LL k, LL value ) {
            Node& cur = tree[k];
            if ( l <= cur.left && cur.right <= r ) {
                cur.changeC(value);
            } else {
                down(k);
                if ( l <= cur.getMid() ) {
                    updateC(l, r, k * 2, value);
                }
                if ( r > cur.getMid() ) {
                    updateC(l, r, k * 2 + 1, value);
                }
                tree[k].sum = tree[k * 2].sum + tree[k * 2 + 1].sum;
            }
        }

        LL getSum( LL l, LL r, LL k ) {
            Node& cur = tree[k];
            if ( l <= cur.left && cur.right <= r )
                return cur.sum;
            
            down(k);
            LL sum1 = 0, sum2 = 0;
            if ( l <= cur.getMid() ) {
                sum1 = getSum(l, r, k * 2);
            }
            if ( r > cur.getMid() ) {
                sum2 = getSum(l, r, k * 2 + 1);
            }
            return sum1 + sum2;
        }

    };

}


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;

    string Q;
    string T;
    int A, B, C;
    SegmentTree S;

    LL query_s( int l, int r ) {
        return S.getSum(l, r, 1);
    }

    void query_a( int l, int r ) {
        S.updateAB(l, r, 1, 1);
    }

    void query_b( int l, int r ) {
        S.updateAB(l, r, 1, -1);
    }

    void query_c( int l, int r, int x ) {
        S.updateC(l, r, 1, x);
    }

    class Solution: public ISolution {
    public:

        void init() {
            S.build(1, SIZE, 1);
        }

        bool input() {
            cin >> T;
            if ( T == "C" ) {
                cin >> A >> B >> C;
            } else {
                cin >> A >> B;
            }
            return false;
        }

        void solve() {
            if ( T == "S" ) {
                cout << query_s(A, B) << endl;
            } else if ( T == "A" ) {
                query_a(A, B);
            } else if ( T == "B" ) {
                query_b(A, B);
            } else if ( T == "C" ) {
                query_c(A, B, C);
            }
        }
        
        int run() {
            int tests;
            std::cin >> tests;
            init();
            for ( int i = 0; i < tests; ++ i ) {
                input();
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


