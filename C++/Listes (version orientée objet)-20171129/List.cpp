/*
 * Yves Roggeman - November 2016 - List.cpp
 *
 */

#include "List.hpp"

#include <cstddef>   // NULL, ptrdiff_t, size_t
#include <cstdlib>   // EXIT_SUCCESS, abs, div, rand...
#include <exception> // exceptions management
#include <iostream>  // cin, cout...
//using namespace std;

template <typename T>
void list (const List<T>& L) {
  std::cout << "[ ";
  for(typename List<T>::const_Place p = L.begin(); p != L.end(); ++p)
    std::cout << *p << " ";
  std::cout << "]" << std::endl;
}

int main () {
  std::cout << ">>>" << std::endl;
  {
    std::cout << "***" << std::endl;
    List<int> L, M;
    List<int>::Place p;
    try {
      std::cout << "*p = " << *p << std::endl;
    } catch (const std::exception& err) {
      std::cerr << "*** Error: " << err.what() << " ***" << std::endl;
    }
    p = L.begin();
    try {
      std::cout << "*p = " << *p << std::endl;
    } catch (const std::exception& err) {
      std::cerr << "*** Error: " << err.what() << " ***" << std::endl;
    }
    p = L.insert(L.begin(), 3);
    std::cout << "L(" << L.size() << ") = "; list(L);
    std::cout << "M(" << M.size() << ") = "; list(M);
    std::cout << "*p = " << *p << std::endl;
    M = L;
    std::cout << "L(" << L.size() << ") = "; list(L);
    std::cout << "M(" << M.size() << ") = "; list(M);
    M.insert(M.begin(), 5);
    M.insert(M.end(), 7);
    std::cout << "M(" << M.size() << ") = "; list(M);
    try {
      p = M.end();
      ++p;
      std::cout << "*p = " << *p << std::endl;
    } catch (const std::exception& err) {
      std::cerr << "*** Error: " << err.what() << " ***" << std::endl;
    }
    swap(L, M);
    std::cout << "L(" << L.size() << ") = "; list(L);
    std::cout << "M(" << M.size() << ") = "; list(M);
    try {
      p = L.insert(M.begin(), 7);
    } catch (const std::exception& err) {
      std::cerr << "*** Error: " << err.what() << " ***" << std::endl;
    }
    p = M.insert(M.begin(), 7);
    std::cout << "L(" << L.size() << ") = "; list(L);
    std::cout << "M(" << M.size() << ") = "; list(M);
    std::cout << "*p = " << *p << std::endl;
    ++p;
    std::cout << "*p = " << *p << std::endl;
    p = M.insert(p, L.begin(), L.end());
    std::cout << "L(" << L.size() << ") = "; list(L);
    std::cout << "M(" << M.size() << ") = "; list(M);
    std::cout << "*p = " << *p << std::endl;
    try {
      L.erase(p);
    } catch (const std::exception& err) {
      std::cerr << "*** Error: " << err.what() << " ***" << std::endl;
    }
    M.erase(p);
    std::cout << "L(" << L.size() << ") = "; list(L);
    std::cout << "M(" << M.size() << ") = "; list(M);
    std::cout << "*p = " << *p << std::endl;
    M.clear();
    std::cout << "M(" << M.size() << ") = "; list(M);
    std::cout << "***" << std::endl;
  }
  std::cout << "<<<" << std::endl;
  return 0;
}
