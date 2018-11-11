// Vecteur - Classe "vecteur de taille fixe"
// Code des méthodes externe ; définition d'un opérateur d'output
// Yves ROGGEMAN - 2015/10

#ifndef  _VECT6_H_
#define  _VECT6_H_

#include <cstddef>      // nullptr_t, ptrdiff_t, size_t
#include <stdexcept>    // standard exceptions
#include <ostream>      // output stream

class Vect {
  friend std::ostream& operator<< (std::ostream&, const Vect&);
  static const std::size_t _DIM = 10;
  int _val[_DIM];
public:
  static std::size_t siz () {return _DIM;};     // "trivial" getter
  inline int operator[] (std::ptrdiff_t) const; // getter
  inline int& operator[] (std::ptrdiff_t);      // setter
  explicit Vect (int = 0);
};

//-----------------------------------------------------------------------------

int Vect::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= _DIM)
    throw std::out_of_range("*** Index out of range ***");
  return _val[i];
}

int& Vect::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= _DIM)
    throw std::out_of_range("*** Index out of range ***");
  return _val[i];
}

Vect::Vect (int v) {
  for (std::size_t i = 0; i < _DIM; ++i) _val[i] = v;
}

//-----------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& out, const Vect& v) {
  out << "[ ";
  for (std::size_t i = 0; i < v._DIM; ++i) out << v._val[i] << ' ';
  out << ']';
  return out;
}

#endif   /*_VECT6_H_*/
