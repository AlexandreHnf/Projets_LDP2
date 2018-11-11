// Vecteur - Classe "vecteur de taille variable"
// Attribut pointeur => deepcopy via jeu complet de méthodes spéciales
// Yves ROGGEMAN - 2015/02

#ifndef  _VECT7_H_
#define  _VECT7_H_

#include <cstddef>      // nullptr_t, ptrdiff_t, size_t
#include <stdexcept>    // standard exceptions
#include <ostream>      // output stream

class Vect final {
  friend std::ostream& operator<< (std::ostream&, const Vect&);
  std::size_t _dim;
  int *_val;
public:
  std::size_t siz () const {return _dim;};
  inline int operator[] (std::ptrdiff_t) const;
  inline int& operator[] (std::ptrdiff_t);

  explicit Vect (std::size_t = 0, int = 0);   // constructor
  Vect (const Vect&);                         // copy constructor
  Vect (Vect&&);                              // move constructor
  Vect& operator= (const Vect&);              // copy assignment operator
  Vect& operator= (Vect&&);                   // move assignment operator
  ~Vect () {delete[] _val;};                  // destructor
};

//-----------------------------------------------------------------------------

int Vect::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= _dim)
    throw std::out_of_range("*** Index out of range ***");
  return _val[i];
}

int& Vect::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= _dim)
    throw std::out_of_range("*** Index out of range ***");
  return _val[i];
}

//-----------------------------------------------------------------------------

Vect::Vect (std::size_t dim, int v): _dim(dim), _val(new int[dim]) {
  for (std::size_t i = 0; i < dim; ++i) _val[i] = v;
}

Vect::Vect (const Vect& v): _dim(v._dim), _val(new int[v._dim]) {
  for (std::size_t i = 0; i < v._dim; ++i) _val[i] = v._val[i];
}

Vect::Vect (Vect&& v): _dim(v._dim), _val(v._val) {
  v._dim = 0; v._val = nullptr;
}

Vect& Vect::operator= (const Vect& v) {
  if (this != &v) {
    _dim = v._dim; delete[] _val; _val = new int[v._dim];
    for (std::size_t i = 0; i < v._dim; ++i) _val[i] = v._val[i];
  }
  return *this;
}

Vect& Vect::operator= (Vect&& v) {
  if (this != &v) {
    _dim = v._dim; v._dim = 0;
    delete[] _val; _val = v._val; v._val = nullptr;
  }
  return *this;
}

//-----------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& out, const Vect& v) {
  out << "[ ";
  for (std::size_t i = 0; i < v._dim; ++i) out << v._val[i] << ' ';
  out << ']';
  return out;
}

#endif   /*_VECT7_H_*/
