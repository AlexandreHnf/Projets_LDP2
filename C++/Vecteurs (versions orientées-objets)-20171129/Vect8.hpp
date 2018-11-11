// Modèle de vecteur de taille fixe (statique)
// Code des méthodes externe ; définition d'un opérateur d'output
// Yves ROGGEMAN - 2015/10

#ifndef  _VECT8_H_
#define  _VECT8_H_

#include <cstddef>     // nullptr_t, ptrdiff_t, size_t
#include <iostream>    // cin, cout...
#include <exception>
#include <stdexcept>   // standard errors

template <typename Elem, std::size_t DIM = 0>
class Vect {
  template <typename T, std::size_t D>
    friend std::ostream& operator<< (std::ostream&, const Vect<T, D>&);
  Elem _val[DIM];
public:
  static std::size_t siz () {return DIM;};             // "trivial" getter
  inline const Elem& operator[] (std::ptrdiff_t) const; // getter
  inline Elem& operator[] (std::ptrdiff_t);             // setter
  Vect () = default;
  explicit Vect (const Elem&);
};

//-----------------------------------------------------------------------------

template <typename Elem, std::size_t DIM>
const Elem& Vect<Elem, DIM>::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= DIM)
    throw std::out_of_range("Vect : Index out of range");
  return _val[i];
}

template <typename Elem, std::size_t DIM>
Elem& Vect<Elem, DIM>::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= DIM)
    throw std::out_of_range("Vect : Index out of range");
  return _val[i];
}

template <typename Elem, std::size_t DIM>
Vect<Elem, DIM>::Vect (const Elem& v) {
  for (std::size_t i = 0; i < DIM; ++i) _val[i] = v;
}

//-----------------------------------------------------------------------------

template <typename Elem, std::size_t DIM = 0>
std::ostream& operator<< (std::ostream& out, const Vect<Elem, DIM>& v) {
  out << '[';
  for (std::size_t i = 0; i < DIM; ++i) out << ' ' << v._val[i];
  out << " ]";
  return out;
}

#endif   /*_VECT8_H_*/
