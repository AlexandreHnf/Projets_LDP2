// Modèle de vecteur de taille variable - Classe polymorphe (héritable)
// Yves ROGGEMAN - 2015/10 - <VectB.hpp>
// Tableau privé - Taille dynamique - Opérateurs [] avec exception

#ifndef  _VECTB_H_
#define  _VECTB_H_

#include <cstddef>     // nullptr_t, ptrdiff_t, size_t
#include <iostream>    // cin, cout...
#include <exception>
#include <stdexcept>   // standard errors

template <typename Elem>
class Vect {
  template <typename T>
    friend std::ostream& operator<< (std::ostream&, const Vect<T>&);
  std::size_t _dim;
  Elem* _val;
protected:
  virtual std::ostream& _dsp (std::ostream&) const;
public:
  std::size_t siz () const {return _dim;}
  virtual const Elem& operator[] (std::ptrdiff_t) const;
  virtual Elem& operator[] (std::ptrdiff_t);
  explicit Vect (std::size_t dim = 0): _dim(dim), _val(new Elem[dim]) {}
  Vect (std::size_t, const Elem&);            // constructeur initialisant
  Vect (const Vect&);                         // constructeur de copie
  Vect (Vect&&);                              // constructeur de transfert
  Vect& operator= (const Vect&);              // opérateur d'assignation
  Vect& operator= (Vect&&);                   // opérateur de transfert
  virtual ~Vect () {delete[] _val;}           // destructeur => polymorphe
};

//----------------------------------------------------------------------------

template <typename Elem>
const Elem& Vect<Elem>::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= _dim)
    throw std::out_of_range("Vect : Index out of range");
  return _val[i];
}

template <typename Elem>
Elem& Vect<Elem>::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= _dim)
    throw std::out_of_range("Vect : Index out of range");
  return _val[i];
}

//----------------------------------------------------------------------------

template <typename Elem>
Vect<Elem>::Vect (std::size_t dim, const Elem& elem):
    _dim(dim), _val(new Elem[dim]) {
  for (std::size_t i = 0; i < dim; ++i) _val[i] = elem;
}

template <typename Elem>
Vect<Elem>::Vect (const Vect& v): _dim(v._dim), _val(new Elem[v._dim]) {
  for (std::size_t i = 0; i < v._dim; ++i) _val[i] = v._val[i];
}

template <typename Elem>
Vect<Elem>::Vect (Vect&& v): _dim(v._dim), _val(v._val) {
  v._dim = 0; v._val = nullptr;
}

template <typename Elem>
Vect<Elem>& Vect<Elem>::operator= (const Vect& v) {
  if (this != &v) {
    delete[] _val; _dim = v._dim; _val = new Elem[v._dim];
    for (std::size_t i = 0; i < v._dim; ++i) _val[i] = v._val[i];
  }
  return *this;
}

template <typename Elem>
Vect<Elem>& Vect<Elem>::operator= (Vect&& v) {
  if (this != &v) {
    delete[] _val; _dim = v._dim; _val = v._val;
    v._dim = 0; v._val = nullptr;
  }
  return *this;
}

//----------------------------------------------------------------------------

template <typename Elem>
std::ostream& Vect<Elem>::_dsp (std::ostream& out) const {
  out << _dim << ": [";
  for (std::size_t i = 0; i < _dim; ++i) out << ' ' << _val[i];
  out << " ] "<< std::endl;
  return out;
}

template <typename Elem>
std::ostream& operator<< (std::ostream& out, const Vect<Elem>& v) {
  return v._dsp(out);
}

#endif   /* _VECTB_H_ */
