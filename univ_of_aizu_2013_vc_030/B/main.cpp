
// @snippet<sh19910711/contest-base:headers.cpp>
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

// @snippet<sh19910711/contest-base:solution/define_classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
  class SolverInterface {
  public:
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    SolverInterface* solver;
    Storages* storages;
  protected:
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base-multi-tests.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}; 
    virtual int run() {
      int tests = get_tests();
      this->before_all_actions();
      for ( int i = 0; i < tests; ++ i ) {
        this->before_action(i);
        this->action();
        this->after_action(i);
      }
      this->after_all_actions();
      return 0;
    }

  private:
    int get_tests() {
      std::string line;
      std::getline(std::cin, line);
      std::string dummy;
      std::getline(std::cin, dummy);
      std::istringstream iss(line);
      int res;
      iss >> res;
      return res;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SHUFFLES = 100 + 11;
  const int CARDS = 52;

}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::vector<int> Vector;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int shuffles;
    Int shuffle[SHUFFLES][CARDS];
    Vector A;
  };
  struct OutputStorage {
    Int cards[CARDS];
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Solver: public SolverInterface {
  public:
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      do_shuffles(in->shuffle, in->A, out->cards);
      return out;
    }

  protected:
    static void do_shuffles( const Int shuffle[SHUFFLES][CARDS], const Vector& queries, Int cards[CARDS] ) {
      Int result[2][CARDS];
      init_cards(result[0]);
      int n = queries.size();
      int cur = 0;
      for ( Vector::const_iterator it_i = queries.begin(); it_i != queries.end(); ++ it_i ) {
        const Int& shuffle_id = *it_i;
        do_shuffle(shuffle[shuffle_id], result[cur], result[cur ^ 1]);
        cur = cur ^ 1;
      }
      std::copy(result[cur], result[cur] + CARDS, cards);
    }

    static void do_shuffle( const Int shuffle[CARDS], Int cur[CARDS], Int next[CARDS] ) {
      for ( int i = 0; i < CARDS; ++ i ) {
        next[i] = cur[shuffle[i]];
      }
    }

    static void init_cards( Int cards[CARDS] ) {
      for ( int i = 0; i < CARDS; ++ i ) {
        cards[i] = i;
      }
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    void before_action( const int& test_id ) {
      if ( test_id > 0 ) {
        std::cout << endl;
      }
      all_numbers.clear();
      string line;
      while ( std::getline(std::cin, line) && line != "" ) {
        std::istringstream iss(line);
        Int tmp;
        while ( iss >> tmp ) {
          all_numbers.push_back(tmp);
        }
      }
      std::reverse(all_numbers.begin(), all_numbers.end());
    }

    bool input( InputStorage* in ) {
      input_shuffles(in->shuffles);
      for ( int i = 0; i < in->shuffles; ++ i ) {
        input_shuffle(in->shuffle[i]);
      }
      input_queries(in->A);
      return true;
    }

    void output( const OutputStorage* out ) {
      for ( int i = 0; i < CARDS; ++ i ) {
        output_card(out->cards[i]);
      }
    }

  private:
    void output_card( const Int& card_id ) {
      const string values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
      const string types[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
      string value = values[card_id % 13];
      string type = types[card_id / 13];
      std::cout << value << " of " << type << endl;
    }

    bool input_queries( Vector& queries ) {
      queries = all_numbers;
      for ( Vector::iterator it_i = queries.begin(); it_i != queries.end(); ++ it_i ) {
        int& query = *it_i;
        query -= 1;
      }
      std::reverse(queries.begin(), queries.end());
      return true;
    }

    bool input_shuffle( Int shuffle[CARDS] ) {
      for ( int i = 0; i < CARDS; ++ i ) {
        shuffle[i] = all_numbers.back() - 1;
        all_numbers.pop_back();
      }
      return true;
    }

    bool input_shuffles( Int& shuffles ) {
      shuffles = all_numbers.back();
      all_numbers.pop_back();
      return true;
    }

    Vector all_numbers;
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  static solution::InputStorage in;
  static solution::OutputStorage out;
  static solution::Storages storages;
  static solution::Solution solution;
  static solution::Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif


