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

//Tableau à taille fixe

template <typename T>
class Tableau final: public Min_Max<T>{
public:
    typedef unsigned int size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    Tableau();   //consructeur
    Tableau(std::size_t max_size);
    Tableau(const Tableau& other); //constructeur de copie
    Tableau(Tableau&&); //constructeur de transfert
    Tableau& operator= (const Tableau& other) //opérateur assignation
    {
        std::cout << "assignation ... " << std::endl;
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
    void right_shift(std::size_t index);
    void insert_back(const Tableau& other);
    void swap(Tableau<T>&);
    void show1() const;

    inline friend bool operator== (Tableau<T>& T1, Tableau<T>& T2){
        /*
        if (T1._size != T2._size or T1._max_size != T2._max_size) {return false;}
        iterator other = T2.begin();
        for (iterator i = T1.begin(); i != T1.end(); ++i){
            if (*other != *i) { return false;}
            ++other;
        }
        return true;
        */
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
        /*
        if (T1._size != T2._size or T1._max_size != T2._max_size) {return true;}
        iterator other = T2.begin();
        for (iterator i = T1.begin(); i != T1.end(); ++i){
            if (*other != *i) { return true;}
            ++other;
        }
        return false;
        */
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
        //const_iterator(T* ptr): _current(ptr){}
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
            //std::cout << "max_size: " << Tableau<T>::max_size() << std::endl;
            //_current = _current + 1;
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
        //const T& operator*(){ std::cout << _first_free << std::endl; return *_current;}
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
    /*
    inline typename Tableau<T>::iterator begin(){return iterator(_vect);}
    inline typename Tableau<T>::iterator end(){return iterator(_vect+_size);}
    inline typename Tableau<T>::const_iterator cbegin(){return const_iterator(_vect);}
    inline typename Tableau<T>::const_iterator cend(){return const_iterator(_vect+_size);}
    */
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

    // for (int i = 1; i < _max_size; ++i){
    // 	_vect[i] = 0; //valeurs par défaut; il faut ?
    // }
    _vect = new T[_max_size];
    //std::cout << "ok" << "\n";
    //_vect[_max_size-1] = T(); //élément bidon a la fin
}

template <typename T>
Tableau<T>::Tableau(std::size_t max_size): Min_Max<T>::Min_Max(), _max_size(max_size),\
					    _vect(nullptr), _first_busy(_max_size), _first_free(0){
    _vect = new T[_max_size];
    //std::cout << "min_max donné" << "\n";
    //_vect[_max_size-1] = T(); //élément bidon a la fin
}

template <typename T>
Tableau<T>::Tableau(const Tableau& other): Min_Max<T>::Min_Max(), _max_size(other._max_size),\
					_vect(new T[_max_size]), _first_busy(_max_size-1), _first_free(0)
{
    std::cout << "copie..." << "\n";
    //_vect = new T[_max_size];
    _vect[_max_size-1] = T(); //elem bidon a la fin
    _size = 0;
    //std::cout << *this << std::endl;
    if (not other.empty()){
        this->insert_back(other);
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
    }
} //constructeur de transfert

template <typename T>
void Tableau<T>::insert_back(const Tableau& other) { //pour operateur assignation et
//constructeur de copie et constructeur de transfert + opérateur de transfert
    /*
	for (std::size_t i = 0; i < other._size; ++i){
		//std::cout << "other i " << other._vect[i] << '\n';
		_vect[i] = other._vect[i];
	}
	_size = other._size;
    */
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
        //else {return _vect[0];}
    else {return _vect[_first_busy];}
}

template <typename T>
T Tableau<T>::back() const { //Renvoie valeur Min
    if (this->empty()) { throw std::out_of_range("Erreur: Le Tableau est vide !"); }
        //else { return _vect[_first_free - 1]; }
        ///*
    else {
        if (_first_free == 0) {return _vect[_max_size-1];}
        else {return _vect[_first_free-1];}
    }
    //*/
}

template <typename T>
void Tableau<T>::pop_front(){         //delete le Max
    if (this->empty()) {throw std::out_of_range("Erreur: Aucun élément à pop");}
        /*
        else{
            for (std::size_t i = _first_busy; i < _size; ++i){
                _vect[i] = _vect[i+1]; //glissement vers la gauche
            }
            _first_free = _size;
            _size -= 1;
        }
        */

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
        //_first_free -= 1;
    }
}

template <typename T>
void Tableau<T>::clear(){
    while (not this->empty()) { //Tant que tableau pas vide
        this->pop_back(); //évite de faire des glissements internes
        //this->show1();
        //std::cout << *this << '\n';
    }
    _size = 0;
    _first_free = 0;
}

template <typename T>
void Tableau<T>::right_shift(std::size_t index) {
    for (std::size_t i = _first_free; i > index; --i){
        //std::cout << "oui" << '\n';
        _vect[i] = _vect[i-1];
    }
}

template <typename T>
typename Tableau<T>::const_iterator Tableau<T>::insert(T t){
    /*
    if (_size == _max_size-1){
        throw std::out_of_range("Erreur: Tableau deja rempli !!");}
    else { //si encore de la place dans le Tableau
        //recherche de l'endroit ou insérer
        std::cout << "first_busy: " << _first_busy << " first_free: " << _first_free << std::endl;
        std::size_t index; bool found = false;
        if (this->empty()) {index = _first_free; found = true; _first_busy = 0;}
        else{
            std::size_t i = _first_busy;
            while (i < _first_free && not found){
                if (t >= _vect[i]) {index = i; found = true;}
                i += 1;
            }
        }
        if (not found) {_vect[_first_free] = t;} //si à placer a la fin
        else {
            this->right_shift(index);
            _vect[index] = t; //l'élément à insérer
        }
        _size += 1;
        _first_free += 1;
        return const_iterator(_vect+_size);
    }
    */

    if (_size == _max_size-1){
        throw std::out_of_range("Erreur: Tableau deja rempli !!");}
    else {
        //std::cout << "t: " << t << std::endl;
        std::size_t place;
        if (_first_busy != _max_size) { //Si tableau pas vide
            //std::cout << "pas vide " << std::endl;
            _vect[_first_free] = t;
            //std::cout << *this << std::endl;
            //std::cout << _vect[0] << _vect[3] << std::endl;
            place = _first_free;
            if (_first_free == _max_size - 1) { _first_free = 0; }
            else { _first_free += 1; }
            bool placed = false;
            std::size_t prev;
            //std::cout << "first: " << _first_busy << " last: " << _first_free << std::endl;
            //std::cout << _vect[0] << _vect[1] << std::endl;
            while (place != _first_busy && not placed) {
                //std::cout << "insertion " << std::endl;
                if (place == 0) { prev = _max_size - 1; }
                else { prev = place - 1; }
                //std::cout << "prev: " << _vect[prev] << "place: " << _vect[place] << std::endl;
                if (_vect[place] > _vect[prev]) {
                    T tmp = _vect[prev];
                    _vect[prev] = _vect[place];
                    _vect[place] = tmp;
                    place = prev;
                    //placed = true;
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
void Tableau<T>::show1() const{
    if (this->empty()){std::cout << "Tableau: []" << "taille: " << _size << '\n';}
    else{
        std::cout << "Tableau: [" << '\n';
        for (std::size_t i = 0; i < this->_size; ++i){
            std::cout << _vect[i] << ", " << '\n';
        }
        std::cout << "]" << " taille: " << this->_size << '\n';
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
    /*
	if (this->empty()) {os << "[] => taille: " << _size;}
	else{
		os << "[";
		for (std::size_t i = 0; i < this->_size; ++i) {
			if (i == this->_size-1) {os << _vect[i];}
			else {os << _vect[i] << ", ";}
		}
		os << "]" << " > taille: " << this->_size;
	}
    */

    if (this->empty()) {os << "[] => taille: " << _size;}
    else{
        os << "[";
        std::size_t i = _first_busy;
        std::size_t j = 0;
        while (i != _first_free) {
            if (j == _size-1) {os << _vect[i];}
            else {os << _vect[i] << ", ";}
            //os << _vect[i] << ", ";
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
