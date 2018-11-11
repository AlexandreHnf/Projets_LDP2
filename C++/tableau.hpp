/* [INFO-F202] Langages de Programmation 2: Projet C++
 * Auteur: Alexandre Heneffe, 000440761
 * Date: 22 décembre 2017
 */

#ifndef _TABLEAU_H
#define _TABLEAU_H

#include "min_max.hpp"
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class Tableau final: public Min_Max<T>{
	public:
        typedef unsigned int size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
		Tableau();   //constructeur
	    Tableau(std::size_t max_size);
		Tableau(const Tableau& other); //constructeur de copie
		Tableau(Tableau&&); //constructeur de transfert
		Tableau& operator= (const Tableau& other) //opérateur assignation
        {
            if (this != &other){
                this->clear();
                _size = 0;
                if (not other.empty()) {
                    this->insert_back(other);
                    _first_busy = other._first_busy;
                    _first_free = other._first_free;
                    _max_size = other._max_size;
                }
            }
            return *this;
        }
		Tableau& operator= (Tableau&& other) { //operateur transfert
            if (this != &other){
                this->clear();  //nettoie le destinataire
                _size = 0;
                if (not other.empty()) {
                    this->insert_back(&other);
                    _first_busy = other._first_busy;
                    _first_free = other._first_free;
                    _max_size = other._max_size;
                    other.clear(); //nettoie la source
                }
            }
        }
		~Tableau();  //destructeur
		bool empty() const;
		std::size_t size() const;
        std::size_t max_size() const;
		T front() const override;
		T back() const override;
		void pop_front() override;
		void pop_back() override;
		void clear() override;
		typename Tableau<T>::const_iterator insert(T t);
		void insert_back(const Tableau& other);
		void swap(Tableau<T>&);

        inline friend bool operator== (Tableau<T>& T1, Tableau<T>& T2){

            if (T1._size != T2._size or T1._max_size != T2._max_size \
                or T1._first_busy != T2._first_busy or T1._first_free != T2._first_free) {
                return false;
            }
            std::size_t i = T1._first_busy;
            while (i != T1._first_free) {
                if (T1._vect[i] != T2._vect[i]) {return false;}
                if (i == T1.max_size()-1) {i = 0;}
                else {i += 1;}
            }
            return true;
        }
        inline friend bool operator!= (Tableau<T>& T1, Tableau<T>& T2){

            if (T1._size != T2._size or T1._max_size != T2._max_size \
                or T1._first_busy != T2._first_busy or T1._first_free != T2._first_free) {
                return true;
            }
            std::size_t i = T1._first_busy;
            while (i != T1._first_free) {
                if (T1._vect[i] != T2._vect[i]) {return true;}
                if (i == T1.max_size()-1) {i = 0;}
                else {i += 1;}
            }
            return false;
        }

        template <typename X> friend inline void swap (Tableau<X>&, Tableau<X>&);
		template <typename U> friend std::ostream& operator<<(std::ostream& os, const Tableau<T>& t);
        template <typename V> friend std::istream& operator>>(std::istream& is, Tableau<T>& t);
		void show(std::ostream &os) const;
	    T convert (const std::string &str);

		class const_iterator {
			public:
                const_iterator(T* ptr, std::size_t first_busy, std::size_t max_size): \
                    _current(ptr), _place(first_busy), _max_size(max_size) {}
		 		~const_iterator() = default;
		 		const_iterator(const const_iterator& other): _current(other._current),\
                    _place(other._place), _max_size(other._max_size) {} //constructeur copie
		 		const_iterator& operator= (const const_iterator& other){ //operateur d'assignation
		 			if (this != &other){
		 				_current = other._current;
                        _place = other._place;
                        _max_size = other._max_size;
					}
		 			return *this;
		 		}

				inline void swap (const_iterator& it2) {
					swap(this->_current, it2._current);
				}

		    	const_iterator& operator++(){
                    if (_place == _max_size-1) {_current -= _max_size-1;}
                    else {_current += 1;}
                    _place += 1;
		 			return *this;
		 		}

		 		const_iterator operator++(int) {
		 			const_iterator res = *this;
		 			++(*this);
		 			return res;
		 		}

                const T* operator->() {return _current;}
                const T& operator*(){ return *_current;}

		 		bool operator==(const const_iterator it2) {return (_current == it2._current);}
		 		bool operator!=(const const_iterator it2) {return (_current != it2._current);}

			private:
                template <typename X> static void swap (X& a, X& b) {
                    const X tmp = a; a = b; b = tmp;
                }
		 		T* _current;
                std::size_t _place;
                std::size_t _max_size;
		};

		using iterator = const_iterator;
        inline typename Tableau<T>::iterator begin(){
            return iterator(_vect+_first_busy, _first_busy, _max_size);}
        inline typename Tableau<T>::iterator end(){
            return iterator(_vect+_first_free, _first_busy, _max_size);}
        inline typename Tableau<T>::const_iterator cbegin(){
            return const_iterator(_vect+_first_busy, _first_busy, _max_size);}
        inline typename Tableau<T>::const_iterator cend(){
            return const_iterator(_vect+_first_free, _first_busy, _max_size);}

	private:
		template <typename X> static void swap(X& a, X& b) {
			const X tmp = a; a = b; b = tmp;
		}
		std::size_t _max_size; // taille maximale du tableau
		T* _vect; //Le tableau de taille fixe
		std::size_t _first_busy; //indice du premier occupé
        std::size_t _first_free;  //indice du premier libre (apres le dernier elem)
		using Min_Max<T>::_size;
};    //FIN DECLARATION TABLEAU

/////////////////////////////////////////////////////////////////////////////////////
//DEFINITIONS TABLEAU

template <typename T>
Tableau<T>::Tableau(): Min_Max<T>::Min_Max(), _max_size(10), _vect(nullptr),\
					   _first_busy(_max_size), _first_free(0){

	_vect = new T[_max_size];
} //constructeur

template <typename T>
Tableau<T>::Tableau(std::size_t max_size): Min_Max<T>::Min_Max(), _max_size(max_size),\
					    _vect(nullptr), _first_busy(_max_size), _first_free(0){
    _vect = new T[_max_size];
} //constructeur avec paramètre

template <typename T>
Tableau<T>::Tableau(const Tableau& other): Min_Max<T>::Min_Max(), _max_size(other._max_size),\
					_vect(new T[_max_size]), _first_busy(_max_size-1), _first_free(0)
{
	_size = 0;
	if (not other.empty()){
		this->insert_back(other);
        _first_busy = other._first_busy;
        _first_free = other._first_free;
	}
} //constructeur de copie

template <typename T>
Tableau<T>::Tableau(Tableau&& other): Min_Max<T>::Min_Max(), _max_size(other._max_size),\
                     _vect(new T[_max_size]), _first_busy(_max_size-1), _first_free(0)
{
    _size = 0;
    if (not other.empty()) {
        this->insert_back(other);
        other.clear();
        _first_busy = other._first_busy;
        _first_free = other._first_free;
    }
} //constructeur de transfert

template <typename T>
void Tableau<T>::insert_back(const Tableau& other) { //pour operateur assignation et
//constructeur de copie et constructeur de transfert + opérateur de transfert
    std::size_t i = other._first_busy;
    while (i != other._first_free) {
        _vect[i] = other._vect[i];
        if (i == _max_size-1) {i = 0;}
        else {i += 1;}
    }
    _size = other._size;
}

template <typename T>
Tableau<T>::~Tableau(){delete[] _vect;} //destructeur

template <typename T>
bool Tableau<T>::empty() const {return _size == 0;}

template <typename T>
std::size_t Tableau<T>::size() const {return _size;}

template <typename T>
std::size_t Tableau<T>::max_size() const {return _max_size;}

template <typename T>
T Tableau<T>::front() const{
    if (this->empty()){ throw std::out_of_range("Erreur: Le Tableau est vide !");}
    else {return _vect[_first_busy];}
}

template <typename T>
T Tableau<T>::back() const { //Renvoie valeur Min
    if (this->empty()) { throw std::out_of_range("Erreur: Le Tableau est vide !"); }
    else {
    if (_first_free == 0) {return _vect[_max_size-1];}
       else {return _vect[_first_free-1];}
    }
}

template <typename T>
void Tableau<T>::pop_front(){         //delete le Max
    if (this->empty()) {throw std::out_of_range("Erreur: Aucun élément à pop");}
    else{
        _size -= 1;
        if (_first_busy == _max_size-1) {_first_busy = 0;}
        else {_first_busy += 1;}
    }
}

template <typename T>
void Tableau<T>::pop_back() {
    if (this->empty()) {throw std::out_of_range("Erreur: Aucun élément à pop");}
    else{
        _size -= 1;
        if (_first_free == 0) {_first_free = _max_size-1;}
        else {_first_free -= 1;}
    }
}

template <typename T>
void Tableau<T>::clear(){
	while (not this->empty()) { //Tant que tableau pas vide
		this->pop_back();
	}
	_size = 0;
	_first_free = 0;
}

template <typename T>
typename Tableau<T>::const_iterator Tableau<T>::insert(T t){

    if (_size == _max_size-1){
        throw std::out_of_range("Erreur: Tableau deja rempli !!");}
    else {
        std::size_t place;
        if (_first_busy != _max_size) { //Si tableau pas vide
            _vect[_first_free] = t;
            place = _first_free;
            if (_first_free == _max_size - 1) { _first_free = 0; }
            else { _first_free += 1; }
            bool placed = false;
            std::size_t prev;
            while (place != _first_busy && not placed) {
                if (place == 0) { prev = _max_size - 1; }
                else { prev = place - 1; }
                if (_vect[place] > _vect[prev]) {
                    T tmp = _vect[prev];
                    _vect[prev] = _vect[place];
                    _vect[place] = tmp;
                    place = prev;
                }
                else{placed = true;}
            }
        }
        else { _vect[0] = t; place = 0; _first_busy = 0; _first_free = 1;}
        _size += 1;
        return const_iterator(_vect+place, place, _max_size);
    }
}

template <typename T>
inline void swap (Tableau<T>& T1, Tableau<T>& T2) {
    Tableau<T>::swap(T1._vect, T2._vect);
    Tableau<T>::swap(T1._first_busy, T2._first_busy);
    Tableau<T>::swap(T1._first_free, T2._first_free);
    Tableau<T>::swap(T1._size, T2._size);
    Tableau<T>::swap(T1._max_size, T2._max_size);
}

template <typename T>
void Tableau<T>::swap (Tableau<T>& T2) {
	Tableau<T>::swap(this._vect, T2._vect);
	Tableau<T>::swap(this._first_busy, T2._first_busy);
	Tableau<T>::swap(this._first_free, T2._first_free);
	Tableau<T>::swap(this._size, T2._size);
	Tableau<T>::swap(this._max_size, T2._max_size);
}

template <typename T>
void Tableau<T>::show(std::ostream &os) const{

    if (this->empty()) {os << "[] => taille: " << _size;}
    else{
        os << "[";
        std::size_t i = _first_busy;
        std::size_t j = 0;
        while (i != _first_free) {
            if (j == _size-1) {os << _vect[i];}
            else {os << _vect[i] << ", ";}
            if (i == _max_size-1) {i = 0; ++j;}
            else {++i; ++j;}
        }
        os << "]" << " > taille: " << this->_size;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Tableau<T>& t)
{
	t.show(os);
	return os;
}

template <typename T> T convert (const std::string &str)
{
	std::istringstream ss(str);
	T num;
	ss >> num;
	return num;
}

template <typename T>
std::istream& operator>>(std::istream& file, Tableau<T>& t)
{
	std::string line;
	while ( getline (file,line) )
	{
		T temp = convert<T>(line);
		t.insert(temp);
	}
	return file;
}

#endif //_TABLEAU_H
