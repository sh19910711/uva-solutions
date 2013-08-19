
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
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() const {};
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      this->pre_calc();
      while ( this->action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef ValueType Type;
    VectorClass() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
  private:
    std::vector<Type> data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_X> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_Z> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
}

// @snippet<sh19910711/contest:table/trie.cpp>
namespace table {
  // @desc トライ木の実装
  template <class ValueType> class Trie {
  public:
    typedef std::string::const_iterator Iterator;
    static const int SIZE = 256;

    std::vector<Trie *> next;
    int cnt;

    Trie() { clear(); }

    void clear() {
      next.resize(SIZE);
      std::fill( next.begin(), next.end(), (Trie*)NULL );
      cnt = 0;
    }

    Trie* set( const std::string& s ) {
      Trie* res = this;
      int len = s.size();
      for ( int i = 0; i < len; ++ i ) {
        const int& c = s[i];
        if ( ! res->next[c] ) {
          res->next[c] = new Trie;
          res->cnt ++;
        }
        res = res->next[c];
      }
      return res;
    }

    const Trie* find( const char* s, const int& n ) const {
      const Trie* res = this;
      for ( int i = 0; i < n; ++ i ) {
        const int& c = s[i];
        if ( res->next[c] == NULL )
          return NULL;
        res = res->next[c];
      }
      return res;
    }

    const Trie* find( const std::string& s ) const {
      return find(s.c_str(), s.size());
    }

  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  typedef table::Trie<bool> Trie;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int MAX_CHARS = 30 + 11;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef storage::Vector<String, SIZE>::Type Words;
  
  Int N;
  Words D;

  Trie T;

  char SA[MAX_CHARS];
  char SB[MAX_CHARS];
  char SC[MAX_CHARS];
  char SD[MAX_CHARS];
  int NSA, NSB, NSC, NSD;

  char SB_prefix[MAX_CHARS];
  int NSB_prefix;
  
  Int result;
}


// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {

  class Solver {
  public:
    void solve() {
      T = generate_trie(D, N);
      result = 0;
      count_matches(D, N, T);
    }

    static const Trie generate_trie( const Words& D, const Int& N ) {
      Trie res;
      for ( int i = 0; i < N; ++ i )
        res.set(D[i]);
      return res;
    }

    static const bool is_prefix_of_longer_string( const String& key, const Trie& T ) {
      const Trie* p = T.find(key);
      return p->cnt > 0;
    }
    
    static const Int count_matches( const Words& D, const Int& N, const Trie& T ) {
      for ( int i = 0; i < N; ++ i ) {
        if ( is_prefix_of_longer_string(D[i], T) ) {
          std::strcpy(SA, D[i].c_str());
          NSA = std::strlen(SA);
          const Trie* from_a_end = &T;
          for ( int i = 0; i < NSA; ++ i ) {
            from_a_end = from_a_end->next[SA[i]];
          }
          std::strcpy(SC, SA);
          NSC = std::strlen(SC);
          find_c(from_a_end, T);
        }
      }
      return -1;
    }

    static const void find_c( const Trie* p, const Trie& T ) {
      if ( p->cnt ) {
        for ( int i = 0; i < 256; ++ i ) {
          if ( p->next[i] != NULL ) {
            SC[NSC ++] = (char)i;
            find_c(p->next[i], T);
            NSC --;
          }
        }
      } else {
        NSB_prefix = 0;
        for ( int i = NSA; i < NSC; ++ i )
          SB_prefix[NSB_prefix ++] = SC[i];
        if ( count_b_prefix_matches(T) ) {
          std::strcpy(SB, SB_prefix);
          NSB = NSB_prefix;
          const Trie* from_b_prefix_end = &T;
          for ( int i = 0; i < NSB; ++ i ) {
            from_b_prefix_end = from_b_prefix_end->next[SB[i]];
          }
          find_b(from_b_prefix_end, T);
        }
      }
    }

    static const bool count_b_prefix_matches( const Trie& T ) {
      return T.find(SB_prefix)->cnt > 0;
    }

    static const void find_b( const Trie* p, const Trie& T ) {
      if ( p->cnt ) {
        for ( int i = 0; i < 256; ++ i ) {
          if ( p->next[i] != NULL ) {
            SB[NSB ++] = (char)i;
            find_b(p->next[i], T);
            NSB --;
          }
        }
      } else {
        NSD = 0;
        if ( NSC > NSA ) {
          int offset = NSC - NSA;
          for ( int i = offset; i < NSB; ++ i )
            SD[NSD ++] = SB[i];
          const Trie* pd = T.find(SD);
          if ( pd != NULL && pd->cnt == 0 )
            result ++;
        } 
      }
    }
    
  protected:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input() )
        return false;
      solver.solve();
      this->output();
      return true;
    }
    
    bool input() {
      if ( ! ( std::cin >> N ) )
        return false;
      if ( N == 0 )
        return false;
      for ( int i = 0; i < N; ++ i )
        std::cin >> D[i];
      return true;
    }
    
    void output() {
      std::cout << result << std::endl;
    }
    
    Solver solver;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution().run();
}
#endif



