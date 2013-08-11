
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
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:hash/rolling_hash/interface.cpp>
namespace hash {
  namespace rolling_hash {
    // ローリングハッシュのインターフェース
    template <class T> class IRollingHash {
    public:
    };
  }
}

// @snippet<sh19910711/contest:math/extgcd.cpp>
namespace math {
  // 拡張ユークリッド互除法: a*x+b*y=gcd(x,y)
  template <class T> T extgcd( T a, T b, T& x, T& y ) {
    for ( T u = y = 1, v = x = 0; a; ) {
      T q = b / a;
      std::swap( x -= q * u, u );
      std::swap( y -= q * v, v );
      std::swap( b -= q * a, a );
    }
    return b;
  }
}

// @snippet<sh19910711/contest:math/mod_inverse.cpp>
namespace math {
  // @desc mod mでaの逆元を求める
  template <class T> T mod_inverse( T a, T m ) {
    T x, y;
    extgcd( a, m, x, y );
    x %= m;
    while ( x < 0 )
      x += m;
    return x;
  }
}

// @snippet<sh19910711/contest:math/mod_pow.cpp>
namespace math {
  template<class T> T mod_pow( T x, T n, T mod ) {
    if ( n == 0 ) return 1;
    T res = mod_pow( x * x % mod, n / 2, mod );
    if ( n & 1 ) res = res * x % mod;
    return res;
  }
}

// @snippet<sh19910711/contest:hash/rolling_hash/rolling_hash.cpp>
namespace hash {
  namespace rolling_hash {
    // ローリングハッシュの実装
    class RollingHash: public IRollingHash<long long> {
    public:
      typedef long long LL;
      LL B, MOD, hash, bases, mod, b_inv;
      std::deque<LL> H;
      std::deque<int> Q;
      RollingHash( LL B, LL MOD ): B(B), MOD(MOD) { init(); }
      void init() {
        hash = 0, bases = 1, b_inv = math::mod_inverse( B, MOD ) % MOD;
        Q.clear();
        H.clear();
      }
      void pushBack( int c ) {
        hash = ( hash * B + c ) % MOD, bases = ( bases * B ) % MOD;
        Q.push_back(c);
        H.push_back(hash);
      }
      void popBack() {
        char c = Q.back();
        hash = ( ( hash - c + MOD ) % MOD * b_inv ) % MOD;
        bases = ( bases * b_inv ) % MOD;
        Q.pop_back();
        H.pop_back();
      }
      void pushFront( int c ) {
        hash = ( hash + ( c * bases ) % MOD ) % MOD;
        bases = ( bases * B ) % MOD;
        Q.push_front(c);
        H.push_front(hash);
      }
      void popFront() {
        char c = Q.front();
        hash = ( hash - ( bases * b_inv * c ) % MOD + MOD ) % MOD;
        bases = ( bases * b_inv ) % MOD;
        Q.pop_front();
        H.pop_front();
      }
      void init( std::string s ) { int n = s.size(); for ( int i = 0; i < n; ++ i ) pushBack(s[i]); }
      long long getHash() { return hash; }
    };
  }
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class Vector {
  public:
    typedef ValueType Type;
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
    void fill( const Type& value ) { std::fill(data, data + SIZE, value); }
  private:
    Type data[SIZE];
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
  template <typename Type, int SIZE_X, int SIZE_Y, int SIZE_Z> struct VectorTypes {
    typedef storage::Vector<Type   , SIZE_X> Type1D;
    typedef storage::Vector<Type1D , SIZE_Y> Type2D;
    typedef storage::Vector<Type2D , SIZE_Z> Type3D;
  };
  template <int SIZE_X, int SIZE_Y, int SIZE_Z> struct BasicVectors {
    typedef VectorTypes<Int    , SIZE_X , SIZE_Y , SIZE_Z> IntVectors;
    typedef VectorTypes<Double , SIZE_X , SIZE_Y , SIZE_Z> DoubleVectors;
    typedef VectorTypes<String , SIZE_X , SIZE_Y , SIZE_Z> StringVectors;
  };
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  typedef hash::rolling_hash::RollingHash RollingHash;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE               = 50 + 11;
  const String TEXT_ALINDROME  = "alindrome";
  const String TEXT_PALINDROME = "palindrome";
  const String TEXT_SIMPLE     = "simple";
  const Int RESULT_ALINDROME   = 0;
  const Int RESULT_PALINDROME  = 1;
  const Int RESULT_SIPLE       = 2;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef BasicVectors<SIZE, SIZE, SIZE>::StringVectors::Type1D Strings;
  typedef BasicVectors<SIZE, SIZE, SIZE>::IntVectors::Type1D Results;
  
  Int N;
  Strings S;
  
  // RollingHash HF(983LL, HASH_MOD);
  // RollingHash HB(983LL, HASH_MOD);
  
  Results R;
}


// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      R = check_strings(S, N);
    }
    
    Results check_strings( const Strings& list, const Int& n ) {
      Results res;
      for ( int i = 0; i < n; ++ i ) {
        res[i] = check_string(list[i]);
      }
      return res;
    }
    
    Int check_string( const String& s ) {
      String s_rev = s;
      std::reverse(s_rev.begin(), s_rev.end());
      
      const Int HASH_BASE = 983;
      const Int HASH_MOD  = std::numeric_limits<Int>::max() / HASH_BASE / 2;
      RollingHash hash_front(HASH_BASE, HASH_MOD);
      RollingHash hash_back(HASH_BASE, HASH_MOD);
      
      hash_front.init(s);
      hash_back.init(s_rev);
      
      int len = s.size();
      
      cout << "s = " << s << endl;
      cout << "hash_front: " << endl;
      for ( Int i = 1; i + 1 < len; ++ i ) {
        string s_left = s.substr(0, i);
        Int front = hash_front.H[i - 1];
        Int back = ( ( hash_back.H[len - 1] - hash_back.H[i] + HASH_MOD ) % HASH_MOD ) * math::mod_inverse(math::mod_pow(HASH_BASE, i + 1, HASH_MOD), HASH_MOD); 
        cout << s_left << ": " << front << " / " << back << endl;
      }
      
      for ( int i = 1; i + 1 < len; ++ i ) {
        int s_left_len = i;
        int s_right_len = len - i;
      }
      
      if ( is_palindrome(len, hash_front, hash_back) ) {
        return RESULT_PALINDROME;
      }
      
      return RESULT_SIPLE;
    }
    
    bool is_palindrome( const int& len, const RollingHash& hash_front, const RollingHash& hash_back ) {
      return hash_front.hash == hash_back.hash;
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }
    
    void init() {
      R.fill(RESULT_SIPLE);
    }
    
    bool input() {
      if ( ! ( cin >> N ) )
        return false;
      for ( int i = 0; i < N; ++ i )
        cin >> S[i];
      return true;
    }
    
    void output() {
      for ( int i = 0; i < N; ++ i ) {
        if ( R[i] == RESULT_ALINDROME ) {
          std::cout << TEXT_ALINDROME << std::endl;
        } else if ( R[i] == RESULT_PALINDROME ) {
          std::cout << TEXT_PALINDROME << std::endl;
        } else if ( R[i] == RESULT_SIPLE ) {
          std::cout << TEXT_SIMPLE << std::endl;
        }
      }
    }
    
    Solver solver;
    
  private:
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif



