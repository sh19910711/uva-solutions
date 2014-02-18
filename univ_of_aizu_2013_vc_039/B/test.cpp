#include <iostream>
#include <array>
using namespace std;

const int MOD = 2;

typedef std::array<int, 3> Array;
typedef std::array<Array, 3> Matrix;

Matrix A;

void print( const Matrix& mat ) {
  for ( auto i = 0; i < 3; ++ i ) {
    for ( auto j = 0; j < 3; ++ j ) {
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Matrix f( const Matrix& mat ) {
  Matrix res;
  for ( auto i = 0; i < 3; ++ i ) {
    for ( auto j = 0; j < 3; ++ j ) {
      res[i][j] = 0;
    }
  }
  for ( auto i = 0; i < 3; ++ i ) {
    for ( auto j = 0; j < 3; ++ j ) {
      const int dr[4] = {1, -1, 0, 0};
      const int dc[4] = {0, 0, 1, -1};

      for ( int k = 0; k < 4; ++ k ) {
        int nr = i + dr[k];
        int nc = j + dc[k];
        if ( nr < 0 || nr >= 3 || nc < 0 || nc >= 3 )
          continue;
        res[i][j] += mat[nr][nc];
        res[i][j] %= MOD;
      }
    }
  }
  return res;
}

int main() {
  A = Matrix {
    Array {1, 0, 1},
    Array {0, 0, 0},
    Array {1, 0, 1},
  };
  for ( int i = 0; i < 100; ++ i ) {
    print(A);
    A = f(A);
  }
  return 0;
}
