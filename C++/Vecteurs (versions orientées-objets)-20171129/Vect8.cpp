// Type abstrait de vecteur (template)
// Tableau de taille fixe : <Vect8.hpp>
// Yves ROGGEMAN - 2015/10

#include "Vect8.hpp"

#include <cstddef>      // nullptr_t, ptrdiff_t, size_t
#include <iostream>     // cin, cout...

template <typename T, std::size_t N>
T sumVect (const Vect<T, N>& v) {
  T sum = 0;
  for (std::size_t i = 0; i < v.siz(); ++i) sum+=v[i];
  return sum;
}

template <typename T, std::size_t N>
Vect<T, N> incVect (Vect<T, N> v) {           // v is a copy
  for (std::size_t i = 0; i < v.siz(); ++i) ++v[i];
  return v;                                   // copy elision (move?)
}

Vect<int, 10> v;                              // default initialized (ctor)

int main() {
  std::cout << std::endl;
  try {
    v[0] = 1;
    v[2] = v[0] + 2;
    std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << std::endl;
    std::cout << v.siz() << std::endl;
    std::cout << v << std::endl;
    int s = sumVect(v);
    std::cout << s << std::endl;
    Vect<int, 10> w = v;                      // copy initialized
    std::cout << w << std::endl;
    ++v[2];
    std::cout << v[2] << ' ' << w[2] << std::endl;
    Vect<int, 10> *p = &v;
    (*p)[1] = 8;
    std::cout << v << std::endl;
    std::cout << *p << std::endl;
    Vect<int, 10> z;                          // default initialized (ctor)
    std::cout << z << std::endl;
    z = v;
    std::cout << z << std::endl;
    z[2] *= 5;
    std::cout << v << std::endl;
    std::cout << z << std::endl;
    z = incVect(v);
    std::cout << v << std::endl;
    std::cout << z << std::endl;
    p = new Vect<int, 10>(5);                 // constant initialization
    std::cout << *p << std::endl;
    // *p = 42;                               // 'explicit' => no conversion
    *p = Vect<int, 10>(42);                   // move from temporary
    (*p)[1] = 6;
    std::cout << p->siz() << std::endl;
    std::cout << *p << std::endl;
    std::cout << sumVect(*p) << std::endl;
    delete p;
    std::cout << *p << std::endl;             // logical error!
    std::cout << v[-2] << std::endl;          // exception!
  }
  catch (const std::exception& E) {
    std::cerr << std::endl << "*** " << E.what() << " ***" << std::endl;
    return 1;
  }
  std::cout << std::endl;
    return 0;
}
