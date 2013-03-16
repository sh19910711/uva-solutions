
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

// @snippet<sh19910711/contest:io/config.cpp>
namespace io {
    const std::string OUTPUT_VECTOR_DELIMITER = " ";
}

// @snippet<sh19910711/contest:io/vector.cpp>
namespace io {
    template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
        typedef typename std::vector<T>::const_iterator Iterator;
        for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
            os << *it_i;
            if ( it_i + 1 != v.end() )
                os << OUTPUT_VECTOR_DELIMITER;
        }
        return os;
    }
    template <typename T> std::istream& operator >>( std::istream& is, std::vector<T>& v ) {
        int n = v.size();
        for ( int i = 0; i < n; ++ i ) {
            is >> v[i];
        }
        return is;
    }
}


// @snippet<sh19910711/contest:solution/multi_tests.cpp>
namespace solution {
    using namespace std;
    using namespace io;

    typedef unsigned long long ULL;

    template <class T> class CharMapArray {
    public:
        T data[256];
        T& operator []( const char& c ) {
            return data[(int)c];
        }
    };
    
    const int A_SIZE = 63;
    const int W_SIZE = 50011;
    const int S_SIZE = 500011;
    const int HASH_BASE = 131;

    string A, W, S;
    CharMapArray<int> T;
    int NA, NW, NS;
    VI LW, LS;
    VI DW, DS;
    ULL base[S_SIZE];
    ULL hash_w[W_SIZE];
    ULL hash_s[S_SIZE];
    VI R;
    
    void parse_a() {
        int n = A.size();
        NA = n;
        for ( int i = 0; i < n; ++ i ) {
            T[A[i]] = i;
        }
    }
    
    void parse_w() {
        int n = W.size();
        NW = n;
        LW.resize(n);
        for ( int i = 0; i < n; ++ i ) {
            LW[i] = T[W[i]];
        }
    }

    void parse_s() {
        int n = S.size();
        NS = n;
        LS.resize(n);
        for ( int i = 0; i < n; ++ i ) {
            LS[i] = T[S[i]];
        }
    }

    int enc( int c, int offset ) {
        return ( c + offset ) % NA;
    }

    void calc_diff( int offset ) {
        DW.resize(NW-1);
        DS.resize(NS-1);
        for ( int i = 0; i + 1 < NW; ++ i ) {
            DW[i] = enc(LW[i+1], offset) - enc(LW[i], offset) + A_SIZE;
        }
        for ( int i = 0; i + 1 < NS; ++ i ) {
            DS[i] = LS[i+1] - LS[i] + A_SIZE;
        }
    }

    void calc_base() {
        // cout << "@calc_base" << endl;
        base[0] = 1;
        for ( int i = 0; i + 1 < S_SIZE; ++ i ) {
            base[i+1] = base[i] * HASH_BASE;
        }
    }

    void calc_hash() {
        hash_w[0] = 0;
        for ( int i = 0; i < NW - 1; ++ i ) {
            hash_w[i+1] = hash_w[i] + ( ( DW[i] + 1 ) * base[i] );
        }
        hash_s[0] = 0;
        for ( int i = 0; i < NS - 1; ++ i ) {
            hash_s[i+1] = hash_s[i] + ( ( DS[i] + 1 ) * base[i] );
        }
    }

    int search() {
        int cnt = 0;
        for ( int i = 0; i + NW - 2 < NS - 1; ++ i ) {
            // cout << hash_s[i+NW-1] << " - " << hash_s[i] << " == " << hash_w[NW-1];
            // cout << " * " << base[i] << "( = " << hash_w[NW-1] * base[i] << endl;
            if ( hash_s[i+NW-1] - hash_s[i] == hash_w[NW-1] * base[i] ) {
                // cout << "i = " << i << endl;
                cnt ++;
            }
        }
        // cout << "cnt = " << cnt << endl;
        return cnt;
    }
    
    class Solution: public ISolution {
    public:
        bool input() { 
            return cin >> A >> W >> S;
        }
        void solve() {
            parse_a();
            parse_w();
            parse_s();
            // cout << "LW: " << LW << endl;
            // cout << "LS: " << LS << endl;

            R.clear();
            for ( int i = 0; i < NA; ++ i ) {
                calc_diff(i);
                // cout << "DW: " << DW << endl;
                // cout << "DS: " << DS << endl;
            
                calc_hash();
                // cout << "hash w: " << vector<ULL>( hash_w+1, hash_w+NW ) << endl;
                // cout << "hash s: " << vector<ULL>( hash_s+1, hash_s+NS ) << endl;
            
                if ( search() == 1 )
                    R.push_back(i);
            }

        }
        void output() {
            if ( R.empty() ) {
                cout << "no solution" << endl;
            } else if ( R.size() == 1 ) {
                cout << "unique: " << R << endl;
            } else {
                cout << "ambiguous: " << R << endl;
            }
        }
        int run() {
            calc_base();

            int tests;
            std::cin >> tests;
            for ( int i = 0; i < tests; ++ i ) {
                init();
                input();
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





