
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
    
    const int A_SIZE = 70;
    const int W_SIZE = 50011;
    const int S_SIZE = 500011;
    const int HASH_BASE_1 = 131;
    const int HASH_BASE_2 = 149;

    string A, W, S;
    CharMapArray<int> T;
    int NA, NW, NS;
    VI LW, LS;
    VI DW, DS;
    ULL base_1[S_SIZE];
    ULL hash_w_1[W_SIZE];
    ULL hash_s_1[S_SIZE];
    ULL base_2[S_SIZE];
    ULL hash_w_2[W_SIZE];
    ULL hash_s_2[S_SIZE];
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

    void calc_diff_w( int offset ) {
        DW.resize(NW-1);
        for ( int i = 0; i + 1 < NW; ++ i ) {
            DW[i] = enc(LW[i+1], offset) - enc(LW[i], offset) + A_SIZE;
            // cout << "W i+1: " << W[i+1] << ", LW: " << LW[i+1] << " => enc: " << enc(LW[i+1], offset) << endl;
            // cout << "W i  : " << W[i] << ", LW: " << LW[i] << " => enc: " << enc(LW[i],offset) << endl;
            // cout << "DW[i]: " << DW[i] << endl;
        }
    }

    void calc_diff_s() {
        DS.resize(NS-1);
        for ( int i = 0; i + 1 < NS; ++ i ) {
            DS[i] = LS[i+1] - LS[i] + A_SIZE;
            // cout << "S i+1: " << S[i+1] << ", LS: " << LS[i+1] << endl;
            // cout << "S i  : " << S[i] << ", LS: " << LS[i] << endl;
            // cout << "DS[i]: " << DS[i] << endl;
        }
    }

    void calc_base() {
        // cout << "@calc_base" << endl;
        base_1[0] = 1;
        for ( int i = 0; i + 1 < S_SIZE; ++ i ) {
            base_1[i+1] = base_1[i] * HASH_BASE_1;
        }
        base_2[0] = 1;
        for ( int i = 0; i + 1 < S_SIZE; ++ i ) {
            base_2[i+1] = base_2[i] * HASH_BASE_2;
        }
    }

    void calc_hash_w() {
        hash_w_1[0] = 0;
        for ( int i = 0; i < NW - 1; ++ i ) {
            hash_w_1[i+1] = hash_w_1[i] + ( ( DW[i] + 1 ) * base_1[i] );
        }
        hash_w_2[0] = 0;
        for ( int i = 0; i < NW - 1; ++ i ) {
            hash_w_2[i+1] = hash_w_2[i] + ( ( DW[i] + 1 ) * base_2[i] );
        }

    }

    void calc_hash_s() {
        hash_s_1[0] = 0;
        for ( int i = 0; i < NS - 1; ++ i ) {
            hash_s_1[i+1] = hash_s_1[i] + ( ( DS[i] + 1 ) * base_1[i] );
        }
        hash_s_2[0] = 0;
        for ( int i = 0; i < NS - 1; ++ i ) {
            hash_s_2[i+1] = hash_s_2[i] + ( ( DS[i] + 1 ) * base_2[i] );
        }
    }

    int search( char first_char ) {
        int cnt = 0;
        for ( int i = 0; i + NW - 2 < NS - 1; ++ i ) {
            // cout << hash_s[i+NW-1] << " - " << hash_s[i] << " == " << hash_w[NW-1];
            // cout << " * " << base[i] << "( = " << hash_w[NW-1] * base[i] << endl;
            if ( S[i] == first_char ) {
                if ( hash_s_1[i+NW-1] - hash_s_1[i] == hash_w_1[NW-1] * base_1[i] ) {
                    if ( hash_s_2[i+NW-1] - hash_s_2[i] == hash_w_2[NW-1] * base_2[i] ) {
                        // cout << S[i] << " : " << W[0] << endl;
                        cnt ++;
                    }
                }
            }
        }
        // cout << "cnt = " << cnt << endl;
        return cnt;
    }

    char get_first_char( char c, int offset ) {
        int id = T[c];
        return A[(id+offset)%NA];
    }
    
    class Solution: public ISolution {
    public:
        void init() {
            R.clear();
        }
        bool input() { 
            return cin >> A >> W >> S;
        }
        void solve_one() {
            CharMapArray<int> CNT;
            for ( int i = 0; i < NA; ++ i )
                CNT[A[i]] = 0;
            for ( int i = 0; i < NS; ++ i ) {
                CNT[S[i]] ++;
            }
            for ( int i = 0; i < NA; ++ i ) {
                char c = get_first_char(W[0], i);
                // cout << "offset " << i << ": " << c << ", ai = " << T[c] << endl;
                if ( CNT[c] == 1 ) {
                    // cout << "ok: " << c << endl; 
                    R.push_back(i);
                }
            }
        }
        void solve() {
            // cout << A << ", " << W << ", " << S << endl;
            if ( W.size() == 1 ) {
                solve_one();
                sort( R.begin(), R.end() );
                return;
            }

            parse_a();
            parse_w();
            parse_s();
            // cout << "LW: " << LW << endl;
            // cout << "LS: " << LS << endl;
            
            calc_diff_s();
            // cout << "DS: " << DS << endl;
            
            calc_hash_s();
            // cout << "hash s_1: " << vector<ULL>( hash_s_1+1, hash_s_1+NS ) << endl;

            for ( int i = 0; i < NA; ++ i ) {
                calc_diff_w(i);
                // cout << "DW: " << DW << endl;
            
                calc_hash_w();
                // cout << "hash w_1: " << vector<ULL>( hash_w_1+1, hash_w_1+NW ) << endl;
            
                if ( search(get_first_char(W[0], i)) == 1 )
                    R.push_back(i);
            }
            sort( R.begin(), R.end() );
        }
        void output() {
            if ( R.empty() ) {
                cout << "no solution";
            } else if ( R.size() == 1 ) {
                cout << "unique: " << R;
            } else {
                cout << "ambiguous: " << R;
            }
            cout << endl;
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





