// Template de vecteur - Version dynamique complète
// Yves ROGGEMAN - 2015/10 - <Vect9.cpp>
// Programme d'appel - Utilise <Vect9.hpp>

#include "Vect9.hpp"

#include <cstddef>     // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>     // abs, div, rand...
#include <utility>     // swap, move, forward...
#include <iostream>    // cin, std::cout...
#include <exception>

template <typename T>
T sumVect (const Vect<T>& v) {
  T sum = 0;
  for (std::size_t i = 0; i < v.siz(); ++i) sum += v[i];
  return sum;
}

template <typename T>
Vect<T> inc (Vect<T> v) {        // constructeur de copie
  for (std::size_t i = 0; i < v.siz(); ++i) ++v[i];
  return std::move(v);           // "élision forcée"
}

int main() {
  std::cout << std::endl;
  try {
    Vect<int> v(3, 5);            // constructeur initialisant
    v[0] = 1;
    v[2] = v[0] + 2;
    std::cout << v[0] << ' ' << v[1] << ' ' << v[2] << std::endl;
    std::cout << v.siz() << std::endl;
    std::cout << v;
    int s = sumVect(v);
    std::cout << s << std::endl;
    const Vect<int> w(v);         // constructeur de copie
//    const Vect<int> w = v;      // idem avec élision
    ++v[2];
    std::cout << v;
    std::cout << w;               // w conservé
    Vect<int> *p = &v;
    (*p)[1] = 8;
    std::cout << v;
    std::cout<< *p;
    v = Vect<int>(5, 7);          // opérateur de transfert
    std::cout << v;
    std::cout<< *p;
    Vect<int> z(10);
    std::cout << z;
    z = v;                        // opérateur d'assignation
    ++v[2];
    std::cout << v;
    std::cout << z;               // z est copie de v
//    z = 3;                      // ERREUR car constructeur explicit
    p = new Vect<int>(3, -2);     // initialise à -2
    std::cout << *p;
    delete p;                     // appel destructeur
    Vect<int> t(inc(v));          // constructeur de transfert, après copie
//    Vect<int> t = inc(v);       // idem avec élision
    std::cout << t;
    std::cout << v;
    Vect<int> u;                  // taille = 0 !
    std::cout << u;
    u = std::move(v);             // opérateur de transfert (forcé)
    std::cout << u;
    std::cout << v;
    Vect<int> m[3];               // matrice => constructeur trivial
    m[0] = Vect<int>(2);          // opérateur de transfert après construction
    m[0][1] = 6;
    m[2] = u;                     // opérateur de copie
    for (size_t i = 0; i < 3; ++i) std::cout << m[i];
    std::cout << std::endl;
    std::cout << m[1][0] << std::endl;     // provoque "out of range"
  }
  catch (const std::exception& E) {
    std::cerr << std::endl << "*** " << E.what() << " ***" << std::endl;
    return 1;
  }
  std::cout << std::endl;
  return 0;
}
