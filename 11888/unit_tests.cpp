
// @snippet<sh19910711/contest:unit-tests.cpp>
#define __MY_UNIT_TEST__
#include "./main.cpp"
#include <gtest/gtest.h>

/*
 *  # Example
 *
 *  int add( int x, int y ) {
 *    return x + y;
 *  }
 *
 *  TEST(AddTest, Test1) {
 *    ASSERT_EQ(2, add(1, 1));
 *  }
 */

namespace test {
  using namespace solution;

  int call_is_palindrome( const string& s ) {
    Solver solver;
    int len = s.size();
    string s_rev = s;
    std::reverse(s_rev.begin(), s_rev.end());
    const Int HASH_BASE = 983;
    const Int HASH_MOD  = std::numeric_limits<Int>::max() / 3;
    RollingHash hash_front(HASH_BASE, HASH_MOD);
    RollingHash hash_back(HASH_BASE, HASH_MOD);
    hash_front.init(s);
    hash_back.init(s_rev);
    return solver.is_palindrome(len, hash_front, hash_back) ? 1 : 0;
  }

  TEST(Hoge, Hoge) {
    ASSERT_EQ(0, call_is_palindrome("abcde"));
    ASSERT_EQ(1, call_is_palindrome("abcba"));
    ASSERT_EQ(1, call_is_palindrome("aabaa"));
  }
}
