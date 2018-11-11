// Template de vecteur avec bornes inférieure et supérieure (héritage publique)
// Yves ROGGEMAN - 2015/10 - <VectX.cpp>
// Programme d'appel - Utilise VectX.hpp

#include "VectX.hpp"


#include <cstddef>     // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>     // abs, div, rand...
#include <utility>     // swap, move, forward...
#include <iostream>    // cin, std::cout...
#include <exception>

template <typename Elem>
VectX<Elem> inc (VectX<Elem> v) {    // constructeur de copie
  for (std::ptrdiff_t i = v.inf(); i <= v.sup(); ++i) ++v[i];
  return std::move(v);               // "élision forcée"
}

int main() {
  std::cout << std::endl;
  try {
    VectX<int> v(-3, 2, 5);          // constructeur initialisant
    v[0] = 3;
    v[-2] = v[1] + 2;
    std::cout << v;
    const VectX<int> w(v);           // constructeur de copie
//    const VectX<int> w = v;        // idem avec élision
    ++v[-2];
    std::cout << v;
    std::cout << w;                  // w conservé
    VectX<int> *p = &v;
    (*p)[1] = 8;
    std::cout << v;
    std::cout<< *p;
    v = VectX<int>(1, 5, 7);         // opérateur de transfert
    std::cout << v;
    std::cout<< *p;
    VectX<int> z(-1, 1);             // non initialisé !
    std::cout << z;
    z = v;                           // opérateur d'assignation
    ++v[2];
    std::cout << v;
    std::cout << z;                  // z est copie de v
    p = new VectX<int>(0, 4, -2);    // initialise à -2
    std::cout << *p;
    delete p;                        // appel au destructeur
    VectX<int> t(inc(v));            // constructeur de transfert, après copie
//    VectX<int> t = inc(v);         // idem avec élision
    std::cout << t;
    std::cout << v;
    VectX<int> u;                    // taille = 0 !
    std::cout << u;
    u = std::move(v);                // opérateur de transfert (forcé)
    std::cout << u;
    std::cout << v;
    VectX<int> m[3];                 // matrice => constructeur trivial
    m[0] = VectX<int>(7, 7);         // opérateur de transfert après construction
    m[0][7] = 6;
    m[2] = u;                        // opérateur de copie
    for (std::size_t i = 0; i < 3; ++i) std::cout << m[i];
    Vect<int> v1 = u;                // OK si héritage public
    std::cout << v1;
    v1 = m[0];                       // idem    std::cout << v1;
    Vect<int> *q = new VectX<int>(-2, 0, -1);
    std::cout << *q;
    std::cout << *dynamic_cast<VectX<int>*>(q);
    std::cout << static_cast<Vect<int>>(*q);
    delete q;                        // OK si destructeur virtuel
    std::cout << v[-5] << std::endl; // provoque "out of range"
  }
  catch (const std::exception& E) {
    std::cerr << std::endl << "*** " << E.what() << " ***" << std::endl;
    return 1;
  }
  std::cout << std::endl;
  return 0;
}
