// Template de vecteur avec bornes inférieure et supérieure
// Yves ROGGEMAN - 2015/10 - <VectX.hpp>
// Héritage publique de la classe Vect

#ifndef  _VECTX_H_
#define  _VECTX_H_

#include "VectB.hpp"

template <typename Elem>
class VectX: public Vect<Elem> {
  std::ptrdiff_t _inf;
protected:
  std::ostream& _dsp (std::ostream&) const override;
public:
  std::ptrdiff_t inf () const {return _inf;}
  std::ptrdiff_t sup () const {return _inf+Vect<Elem>::siz()-1;}
  const Elem& operator[] (std::ptrdiff_t i) const override
    {return Vect<Elem>::operator[](i-_inf);}
  Elem& operator[] (ptrdiff_t i) override
    {return Vect<Elem>::operator[](i-_inf);}
  VectX (): _inf(0) {}         // Soit 0 paramètre, soit inf et sup au minimum
  VectX (std::ptrdiff_t inf, std::ptrdiff_t sup):
    Vect<Elem>(sup-inf+1 < 0 ? 0 : sup-inf+1), _inf(inf) {}
  VectX (std::ptrdiff_t inf, std::ptrdiff_t sup, const Elem& elem):
    Vect<Elem>(sup-inf+1 < 0 ? 0 : sup-inf+1, elem), _inf(inf) {}
};

template <typename Elem>
std::ostream& VectX<Elem>::_dsp (std::ostream& out) const {
  out << '(' << _inf << ", " << sup() << ") ";
  return Vect<Elem>::_dsp(out);
}

#endif   /* _VECTX_H_ */
