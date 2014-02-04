#include <iostream>
#include <algorithm>
using namespace std;

typedef std::string String;

int box_id_list[24][6] = {
  {0, 1, 2, 3, 4, 5}, 
  {0, 2, 4, 1, 3, 5}, 
  {0, 3, 1, 4, 2, 5}, 
  {0, 4, 3, 2, 1, 5}, 
  {1, 0, 3, 2, 5, 4}, 
  {1, 2, 0, 5, 3, 4}, 
  {1, 3, 5, 0, 2, 4}, 
  {1, 5, 2, 3, 0, 4}, 
  {2, 0, 1, 4, 5, 3}, 
  {2, 1, 5, 0, 4, 3}, 
  {2, 4, 0, 5, 1, 3}, 
  {2, 5, 4, 1, 0, 3}, 
  {3, 0, 4, 1, 5, 2}, 
  {3, 1, 0, 5, 4, 2}, 
  {3, 4, 5, 0, 1, 2}, 
  {3, 5, 1, 4, 0, 2}, 
  {4, 0, 2, 3, 5, 1}, 
  {4, 2, 5, 0, 3, 1}, 
  {4, 3, 0, 5, 2, 1}, 
  {4, 5, 3, 2, 0, 1}, 
  {5, 1, 3, 2, 4, 0}, 
  {5, 2, 1, 4, 3, 0}, 
  {5, 3, 4, 1, 2, 0}, 
  {5, 4, 2, 3, 1, 0}
};

template <class FaceType> struct Box {
  int cur;
  FaceType faces[6];

  Box(): cur(0) {}

  void set_face( const int& x, const FaceType& type ) {
    this->faces[x] = type;
  }

  FaceType* get_faces() {
    FaceType next[6];
    for ( int i = 0; i < 6; ++ i )
      next[i] = faces[box_id_list[cur][i]];
    for ( int i = 0; i < 6; ++ i )
      this->faces[i] = next[i];
    return this->faces;
  }

  bool next() {
    if ( this->cur + 1 >= 0 && this->cur + 1 < 24 ) {
      this->cur += 1;
      this->get_faces();
      return true;
    }
    return false;
  }

  FaceType& operator[]( const int& x ) {
    return faces[x];
  }

  friend std::ostream& operator <<( std::ostream& os, Box<FaceType>& box ) {
    for ( int i = 0; i < 6; ++ i )
      os << box.faces[i] << ", ";
    return os;
  }
};


int main() {
  Box<char> box;
  for ( int i = 0; i < 6; ++ i ) {
    box[i] = 'A' + i;
  }
  return 0;
}













