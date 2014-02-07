
// @snippet<sh19910711/contest-base:headers.cpp>
#define __THIS_IS_CPP11__
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

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest:utils/collection_prototype.cpp>
namespace utils {
  // collection
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value );
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t );
  template <class T> void copy( const T& s, const int& n, T& t );
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v );
  template <class T> void sort( T& v, const int& n );
#endif
}

// @snippet<sh19910711/contest:utils/misc_prototype.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b );
  template <class T> void min( T& a, const T& b );
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v );
  template <class T> T to_type( const std::string& s );
  
}

// @snippet<sh19910711/contest:utils_prototypes.cpp>

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct Input;
  struct Output;
  struct Storages {
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const Output* solve( const Input* in, Output* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    virtual int run()                             = 0;
    virtual bool action()                         = 0;
    virtual bool input( Input* s )         = 0;
    virtual void output( const Output* s ) = 0;
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    SolverInterface* solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    
    int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
    
    bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

namespace geometry {
  typedef long double Double;
  Double sq( const Double& x ) { return x * x; }
  template <class VectorDim> struct VectorInterface {
    virtual ~VectorInterface() {}
    virtual VectorDim operator +( const VectorDim& ) = 0;
    virtual VectorDim operator -( const VectorDim& ) = 0;
    virtual VectorDim operator *( const Double& ) = 0;
    virtual VectorDim operator /( const Double& ) = 0;
    virtual Double get_dot( const VectorDim& ) = 0;
    virtual Double get_norm() = 0;
  };
}

namespace geometry {
  typedef std::tuple<Double, Double, Double> Vector3DBase;
  struct Vector3D: Vector3DBase, VectorInterface<Vector3D> {
    // using Vector3DBase::tuple;
    Vector3D() {}
    Vector3D( const Double& a, const Double& b, const Double& c ) {
      this->get_x() = a;
      this->get_y() = b;
      this->get_z() = c;
    }
    Vector3D( const Vector3DBase& v ) {
      *this = v;
    }
    Double& get_x() { return std::get<0>(*this); }
    const Double& get_x() const { return std::get<0>(*this); }
    Double& get_y() { return std::get<1>(*this); }
    const Double& get_y() const { return std::get<1>(*this); }
    Double& get_z() { return std::get<2>(*this); }
    const Double& get_z() const { return std::get<2>(*this); }
    
    Vector3D operator +( const Vector3D& v ) {
      return Vector3D(this->get_x() + v.get_x(), this->get_y() + v.get_y(), this->get_z() + v.get_z());
    }
    
    Vector3D operator -( const Vector3D& v ) {
      return Vector3D(this->get_x() - v.get_x(), this->get_y() - v.get_y(), this->get_z() - v.get_z());
    }
    
    Vector3D operator *( const Double& k ) {
      return Vector3D(this->get_x() * k, this->get_y() * k, this->get_z() * k);
    }
    
    Vector3D operator /( const Double& k ) {
      return Vector3D(this->get_x() / k, this->get_y() / k, this->get_z() / k);
    }
    
    Double get_dot( const Vector3D& v ) {
      return this->get_x() * v.get_x() + this->get_y() * v.get_y() + this->get_z() * v.get_z();
    }
    
    Vector3D get_cross( const Vector3D& v ) {
      return Vector3D(
        this->get_y() * v.get_z() - this->get_z() * v.get_y(),
        this->get_z() * v.get_x() - this->get_x() * v.get_z(),
        this->get_x() * v.get_y() - this->get_y() * v.get_x()
      );
    }
    
    Double get_norm() {
      return sq(this->get_x()) + sq(this->get_y()) + sq(this->get_z());
    }
  };
}

namespace geometry {
  namespace vector_helpers {
    template <class Point> Point get_middle( Point a, Point b ) {
      return ( a + b ) / 2.0;
    }
    
    template <class Vector, class Point> Point get_project( Point a, Point b, Point p ) {
      Vector base = b - a;
      Double k = (p - a).get_dot(base) / base.get_norm();
      return a + base * k;
    }
  }
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int MAX_D = 3;
  const Int MAX_V = 3;
  const String YES = "HIT";
  const String NO = "MISS";
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  using namespace geometry;
  typedef std::array<Double, MAX_D> DoubleArray;
  typedef std::array<DoubleArray, MAX_V> DoubleTable;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    DoubleArray S;
    DoubleArray T;
    DoubleTable P;
  };
  
  struct Output {
    bool result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      out->result = ! is_intersect(in->S, in->T, in->P);
      return out;
    }

    // 三角形abcと点pの距離
    template <class Vector> static Double get_distance( Vector va, Vector vb, Vector vc, Vector vp ) {
      Vector v_ab = vb - va;
      Vector v_bc = vc - vb;
      Vector v_n = v_ab.get_cross(v_bc);
      v_n = v_n / std::sqrt(v_n.get_norm());
      return std::abs(v_n.get_dot(va - vp)) / std::sqrt(v_n.get_norm());
    }

    // a <= b
    static bool less_than_equal( const Double& a, const Double& b ) {
      if ( std::abs( a - b ) < 1e-9 )
        return true;
      return a < b;
    }

    template <class Vector> static bool is_intersect( Vector va, Vector vb, Vector vc, Vector vp ) {
      Vector vab = vb - va;
      Vector vbp = vp - vb;
      Vector vbc = vc - vb;
      Vector vcp = vp - vc;
      Vector vca = va - vc;
      Vector vap = vp - va;
      Vector vn = vab.get_cross(vbc);
      vn = vn / std::sqrt(vn.get_norm());
      Double cross_1 = vn.get_cross(vab).get_dot(vap);
      Double cross_2 = vn.get_cross(vbc).get_dot(vbp);
      Double cross_3 = vn.get_cross(vca).get_dot(vcp);
      if ( less_than_equal(0, cross_1) && less_than_equal(0, cross_2) && less_than_equal(0, cross_3) )
        return true;
      if ( less_than_equal(cross_1, 0) && less_than_equal(cross_2, 0) && less_than_equal(cross_3, 0) )
        return true;
      return false;
    }
    
    static bool is_intersect( const DoubleArray& S, const DoubleArray& T, const DoubleTable& P ) {
      Vector3D vs(S[0], S[1], S[2]);
      Vector3D vt(T[0], T[1], T[2]);
      Vector3D vp[3];
      for ( auto i = 0; i < MAX_V; ++ i ) {
        vp[i] = Vector3D(P[i][0], P[i][1], P[i][2]);
      }
      Vector3D vn = ( vp[1] - vp[0] ).get_cross( vp[2] - vp[1] );
      vn = vn / std::sqrt(vn.get_norm());
      Double ds = get_distance(vp[0], vp[1], vp[2], vs);
      Double dt = get_distance(vp[0], vp[1], vp[2], vt);
      if ( std::abs(dt) < 1e-9 )
        return true;
      if ( less_than_equal(0.0, vn.get_dot(vs - vp[0]) * vn.get_dot(vt - vp[0])) )
        return false;
      Double k = ds / ( ds + dt );
      Vector3D vx(vs + ( vt - vs ) * k);
      return is_intersect(vp[0], vp[1], vp[2], vx);
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->S[0] >> in->S[1] >> in->S[2] ) )
        return false;
      if ( ! ( std::cin >> in->T[0] >> in->T[1] >> in->T[2] ) )
        return false;
      for ( auto i = 0; i < MAX_V; ++ i ) {
        for ( auto j = 0; j < MAX_D; ++ j ) {
          std::cin >> in->P[i][j];
        }
      }
      return true;
    }
    void output( const Output* out ) {
      std::cout << ( out->result ? YES : NO ) << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main_func.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // desc: http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html#id18
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  // 
  using namespace solution;
  static Input in;
  static Output out;
  static Storages storages;
  static Solution solution;
  static Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

// @snippet<sh19910711/contest:utils/collection.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value ) { std::fill(std::begin(v), std::begin(v) + n, value); }
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t ) { std::copy(std::begin(s), std::end(s), std::begin(t)); }
  template <class T> void copy( const T& s, const int& n, T& t ) { std::copy(std::begin(s), std::begin(s) + n, std::begin(t)); }
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v ) { std::sort(std::begin(v), std::end(v)); }
  template <class T> void sort( T& v, const int& n ) { std::sort(std::begin(v), std::begin(v) + n); }
#endif
}

// @snippet<sh19910711/contest:utils/misc.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b ) { a = std::max(a, b); }
  template <class T> void min( T& a, const T& b ) { a = std::min(a, b); }
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v ) { std::ostringstream oss; oss << v; return oss.str(); }
  template <class T> T to_type( const std::string& s ) { std::istringstream iss(s); T res; iss >> res; return res; }
  
}

// @snippet<sh19910711/contest:utils.cpp>

// @snippet<sh19910711/contest-base:main.cpp>


