// Type abstrait de vecteur
// Tableau de taille variable : <Vect7.hpp>
// Yves ROGGEMAN - 2015/02

#include "Vect7.hpp"

#include <cstddef>      // nullptr_t, ptrdiff_t, size_t
#include <iostream>     // cin, cout...

long sumVect (const Vect& v) {
  long sum = 0;
  for (std::size_t i = 0; i < v.siz(); ++i) sum += v[i];
  return sum;
}

Vect incVect (Vect v) {                         // v is a copy
  for (std::size_t i = 0; i < v.siz(); ++i) ++v[i];
  return v;                                     // copy elision (move?)
}

Vect v(10);

int main() {
  v[0] = 1;
  v[2] = v[0] + 2;
  std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << std::endl;
  std::cout << v.siz() << std::endl;
  std::cout << v << std::endl;
  long s = sumVect(v);
  std::cout << s << std::endl;
  Vect w = v;                                   // copy constructor
  std::cout << w << std::endl;
  ++v[2];
  std::cout << v[2] << ' ' << w[2] << std::endl;
  Vect *p = &v;
  (*p)[1] = 8;
  std::cout << v << std::endl;
  std::cout << *p << std::endl;
  Vect z;                                       // empty Vect
  std::cout << z.siz() << std::endl;
  std::cout << z << std::endl;
  z = v;                                        // copy assignment operator
  std::cout << z.siz() << std::endl;
  std::cout << z << std::endl;
  z[2] *= 5;
  std::cout << v << std::endl;
  std::cout << z << std::endl;
  z = incVect(v);
  std::cout << v << std::endl;
  std::cout << z << std::endl;
  p = new Vect(3, 5);                           // constructor
  std::cout << p->siz() << std::endl;
  std::cout << *p << std::endl;
  *p = Vect(5, 42);                             // move from temporary
  (*p)[1] = 6;
  std::cout << p->siz() << std::endl;
  std::cout << *p << std::endl;
  std::cout << sumVect(*p) << std::endl;
  delete p;
  std::cout << p->siz() << std::endl;           // logical error!
  std::cout << v[-2] << std::endl;              // exception!
  return 0;
}
