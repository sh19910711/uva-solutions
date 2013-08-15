
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
    virtual void output() const {};
    
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

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class Vector {
  public:
    typedef ValueType Type;
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
  private:
    Type data[SIZE];
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  template <typename Type, int SIZE_X = 0, int SIZE_Y = 0, int SIZE_Z = 0> struct VectorTypes {
    typedef storage::Vector<Type   , SIZE_X> Type1D;
    typedef storage::Vector<Type1D , SIZE_Y> Type2D;
    typedef storage::Vector<Type2D , SIZE_Z> Type3D;
  };
  template <int SIZE_X = 0, int SIZE_Y = 0, int SIZE_Z = 0> struct BasicVectors {
    typedef VectorTypes<int    , SIZE_X , SIZE_Y , SIZE_Z> IntVectors;
    typedef VectorTypes<double , SIZE_X , SIZE_Y , SIZE_Z> DoubleVectors;
    typedef VectorTypes<std::string , SIZE_X , SIZE_Y , SIZE_Z> StringVectors;
  };
}

// @snippet<sh19910711/contest:table/trie.cpp>
namespace table {
  // @desc トライ木の実装
  template <class ValueType> class Trie {
  public:
    typedef std::string::const_iterator Iterator;
    static const int SIZE = 256;
    ValueType value;
    Trie *next[SIZE];
    Trie() { clear(); }
    void clear() { std::fill( next, next+SIZE, (Trie*)NULL ); }
    Trie& find( const std::string& s ) {
      Trie* res = this;
      for ( Iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
        const int& c = *it_i;
        if ( ! res->next[c] ) res->next[c] = new Trie;
        res = res->next[c];
      }
      return *res;
    }
    int count( const std::string& s ) {
      Trie* res = this;
      for ( Iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
        const int& c = *it_i;
        if ( ! res->next[c] ) return 0;
        res = res->next[c];
      }
      return 1;
    }
    ValueType& operator []( const std::string& s ) { return find(s).value; }
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;

  typedef table::Trie<bool> Trie;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  const int SIZE = 1000000 + 11;
  const int QUERIES = 10000 + 11;
  const int VOLUMES = 100 + 11;
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef storage::BasicVectors<SIZE>::StringVectors::Type1D Words;
  typedef storage::BasicVectors<QUERIES>::IntVectors::Type1D Volumes;
  typedef storage::BasicVectors<QUERIES>::IntVectors::Type1D Scores;
  typedef storage::VectorTypes<char, QUERIES>::Type1D Chars;
  typedef storage::VectorTypes<Chars, VOLUMES>::Type1D QueryChars;
  typedef storage::VectorTypes<Scores, VOLUMES>::Type1D QueryScores;
  typedef storage::BasicVectors<QUERIES>::IntVectors::Type1D QueryResults;
  
  Int   N;
  Words dict;
  
  Int           queries;
  Volumes       volumes;
  QueryChars    chars;
  QueryScores   scores;
  Trie          trie;
  
  QueryResults query_results;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      trie = generate_trie_tree(get_sorted_words(dict, N), N);
      sort_query_info();
      for ( int i = 0; i < queries; ++ i )
        query_results[i] = query(trie, volumes[i], chars[i], scores[i]);
    }

    void sort_query_info() {
      for ( int i = 0; i < queries; ++ i ) {
        for ( int j = 0; j < volumes[i]; ++ j ) {
          for ( int k = j + 1; k < volumes[i]; ++ k ) {
            if ( chars[i][j] > chars[i][k] ) {
              std::swap(chars[i][j], chars[i][k]);
              std::swap(scores[i][j], scores[i][k]);
            } else if ( chars[i][j] == chars[i][k] ) {
              if ( scores[i][j] < scores[i][k] ) {
                std::swap(chars[i][j], chars[i][k]);
                std::swap(scores[i][j], scores[i][k]);
              }
            }
          }
        }
      }
    }

    const Words get_sorted_words( const Words& dict, const int& N ) {
      Words res = dict;
      for ( int i = 0; i < N; ++ i ) {
        res[i] = get_sorted_word(dict[i]);
      }
      return res;
    }

    const String get_sorted_word( const String& s ) {
      String res = s;
      std::sort(res.begin(), res.end());
      return res;
    }

    Trie generate_trie_tree( const Words& dict, const Int& n ) const {
      Trie res;
      for ( int i = 0; i < n; ++ i )
        res[dict[i]] = true;
      return res;
    }
    
    const Int query( const Trie& trie, const Int& volume, const Chars& chars, const Scores& scores ) const {
      Trie t = trie;
      Int res = 0;
      int bit_volume = 1 << volume;
      for ( int state = 0; state < bit_volume; ++ state ) {
        String tmp;
        for ( int i = 0; i < volume; ++ i ) {
          int bi = 1 << i;
          if ( state & bi )
            tmp += chars[i];
        }
        if ( t.count(tmp) ) {
          Int sum = 0;
          for ( int i = 0; i < volume; ++ i ) {
            int bi = 1 << i;
            if ( state & bi )
              sum += scores[i];
          }
          res = std::max(res, sum);
        }
      }
      return res;
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
    
    bool input() {
      if ( ! ( std::cin >> N ) )
        return false;
      for ( int i = 0; i < N; ++ i ) {
        std::cin >> dict[i];
      }
      std::cin >> queries;
      for ( int i = 0; i < queries; ++ i ) {
        std::cin >> volumes[i];
        for ( int j = 0; j < volumes[i]; ++ j ) {
          std::cin >> chars[i][j] >> scores[i][j];
        }
      }
      return true;
    }
    
    void output() const {
      for ( int i = 0; i < queries; ++ i ) {
        std::cout << query_results[i] << std::endl;
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



