#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>

// @snippet<sh19910711/contest:utils/debug.cpp>
namespace utils {
  //
  // print std::tuple
  //
  namespace print_tuple_helpers {
    template<std::size_t...> struct seq{};
    template<std::size_t N, std::size_t... Is> struct gen_seq : gen_seq<N-1, N-1, Is...>{};
    template<std::size_t... Is> struct gen_seq<0, Is...> : seq<Is...>{};
    template<class Ch, class Tr, class Tuple, std::size_t... Is>
    void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>){
      using swallow = int[];
      (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
    }
  }
  
  template<class Ch, class Tr, class... Args>
  auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) -> std::basic_ostream<Ch, Tr>& {
    os << "(";
    print_tuple_helpers::print_tuple(os, t, print_tuple_helpers::gen_seq<sizeof...(Args)>());
    return os << ")";
  }
  
  //
  // print std::vector
  //
  namespace print_vector_helpers {
    const std::string OUTPUT_VECTOR_DELIMITER = ", ";
  }
  template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
    typedef typename std::vector<T>::const_iterator Iterator;
    for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
      os << *it_i;
      if ( it_i + 1 != v.end() )
        os << print_vector_helpers::OUTPUT_VECTOR_DELIMITER;
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
  
  typedef std::tuple<Double, Double> Vector2DBase;
  struct Vector2D: Vector2DBase, VectorInterface<Vector2D> {
    using Vector2DBase::tuple;
    Double& get_x() { return std::get<0>(*this); }
    const Double& get_x() const { return std::get<0>(*this); }
    Double& get_y() { return std::get<1>(*this); }
    const Double& get_y() const { return std::get<1>(*this); }

    Vector2D operator +( const Vector2D& a ) {
      return Vector2D(this->get_x() + a.get_x(), this->get_y() + a.get_y());
    }

    Vector2D operator -( const Vector2D& a ) {
      return Vector2D(this->get_x() - a.get_x(), this->get_y() - a.get_y());
    }

    Vector2D operator *( const Double& k ) {
      return Vector2D(this->get_x() * k, this->get_y() * k);
    }
    
    Vector2D operator /( const Double& k ) {
      return Vector2D(this->get_x() / k, this->get_y() / k);
    }

    Double get_dot( const Vector2D& v ) {
      return this->get_x() * v.get_x() + this->get_y() * v.get_y();
    }

    Double get_cross( const Vector2D& v ) {
      return this->get_x() * v.get_y() - this->get_y() * v.get_x();
    }

    Double get_norm() {
      return sq(this->get_x()) + sq(this->get_y());
    }
  };
  
  typedef std::tuple<Double, Double, Double> Vector3DBase;
  struct Vector3D: Vector3DBase, VectorInterface<Vector3D> {
    using Vector3DBase::tuple;
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
  
  template <class Point> Point get_middle( Point a, Point b ) {
    return ( a + b ) / 2.0;
  }

  template <class Vector, class Point> Point get_project( Point a, Point b, Point p ) {
    Vector base = b - a;
    Double k = (p - a).get_dot(base) / base.get_norm();
    return a + base * k;
  }
}

int main() {
  using namespace std;
  using namespace geometry;
  using namespace utils;

  cout << std::asin(std::sin(90.0 / 180.0 * M_PI)) * 180.0 / M_PI << endl;

  [&]() {
    Vector2D v1(50, 0);
    Vector2D v2(100, 100);

    cout << get_middle(v1, v2) << endl;
    cout << "cross: " << v1.get_cross(v2) << endl;
    cout << get_project<Vector2D>(Vector2D(0, 0), Vector2D(0, 100), Vector2D(50, 50)) << endl;
  }();

  [&]() {
    Vector3D v1(50, 0, 0);
    Vector3D v2(100, 100, 0);
    cout << get_middle(v1, v2) << endl;
    cout << "cross: " << v1.get_cross(v2) << endl;
    cout << get_project<Vector3D>(Vector3D(0, 0, 0), Vector3D(0, 100, 0), Vector3D(50, 50, 0)) << endl;
  }();
}


