/* [INFO-F202] Langages de Programmation 2: Projet C++
 * Auteur: Alexandre Heneffe, 000440761
 * Date: 22 décembre 2017
 */

#ifndef _CircDoubleLinkedList_H
#define _CircDoubleLinkedList_H

#include "min_max.hpp"
#include "Item.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

template <typename T>
class List final: public Min_Max<T>{
	public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
		List();
	    List(std::size_t max_size); //constructeur avec paramètre
		~List();
		List(const List& other);     //Constructeur de copie
		List (List&&);               //Constructeur de transfert
		List& operator= (const List& other) //opérateur d'assignation
		{
			if (this != &other){
				this->clear();
				_size = 0;
				if (not other.empty()) {this->insert_back(other);}
			}
			return *this;
		}
		List& operator= (List&& other){    //operateur de transfert
			if (this != &other){
				clear();  //nettoie le destinataire
				_size = 0;
				if (not other.empty()) {
					this->insert_back(&other);
					other.clear(); //nettoie la source
				}
			}
		}

		bool empty() const;
        std::size_t size() const;
        std::size_t max_size() const;
		T front() const override;
		T back() const override;
		void pop_front() override;
		void pop_back() override;
		void clear() override;
		typename List<T>::const_iterator insert(T t);
		void insert_back(const List& other);
		void swap(List<T>&);
		void show1() const;

        inline friend bool operator== (List<T>& L1, List<T> L2){
            if (L1._size != L2._size) {return false;}
            iterator other = L2.begin();
            for (iterator i = L1.begin(); i != L1.end(); ++i){
                if (*other != *i) { return false;}
                ++other;
            }
            return true;
        }
        inline friend bool operator!= (List<T>& L1, List<T> L2){
            if (L1._size != L2._size) {return true;}
            iterator other = L2.begin();
            for (iterator i = L1.begin(); i != L1.end(); ++i){
                if (*other != *i) { return true;}
                ++other;
            }
            return false;
        }

        template <typename X> friend inline void swap (List<X>&, List<X>&);
		template <typename U> friend std::ostream& operator<<(std::ostream& os, const List<T>& l);
	    template <typename V> friend std::istream& operator>>(std::istream& is, List<T>& l);
		void show(std::ostream &os) const;
        T convert_to (const std::string &str);

		class const_iterator final: public Min_Max<T>::const_iterator {
			public:
				const_iterator(Item<T>* ptr): Min_Max<T>::const_iterator(), _current(ptr){}
				~const_iterator() = default; //destructeur
				//constructeur copie
				const_iterator(const const_iterator& other): Min_Max<T>::const_iterator(), \
				                                            _current(other._current) {}
				const_iterator& operator= (const const_iterator& other){
                    //operateur d'assignation
					if (this != &other){
						_current = other._current;
					}
					return *this;
				}

				inline void swap (const_iterator& it2) {
					swap(this->_current, it2._current);
				}
				const_iterator& operator++() override{  //++i
					_current = _current->get_next();
					return *this;
				}

				const_iterator operator++(int) {
					const_iterator res = *this;
					++(*this);
					return res;
				}
				const T& operator*() override {return _current->get_refelem();}

				bool operator==(const const_iterator it2) {return (_current == it2._current);}
				bool operator!=(const const_iterator it2) {return (_current != it2._current);}

			private:
                template <typename X> static void swap(X& a, X& b) {
                    const X tmp = a; a = b; b = tmp;
                }
				Item<T>* _current;
		};

		using iterator = const_iterator;

		inline typename List<T>::iterator begin(){return iterator(_head->get_next());}
		inline typename List<T>::iterator end(){return iterator(_head);}
		inline typename List<T>::const_iterator cbegin(){return const_iterator(_head->get_next());}
		inline typename List<T>::const_iterator cend(){return const_iterator(_head);}

	private:
		template <typename X> static void swap (X& a, X& b) {
			const X tmp = a; a = b; b = tmp;
		}
        std::size_t const _max_size;
		Item<T> *_head;  //pointeur vers le premier élément de la liste
		using Min_Max<T>::_size;
};      //FIN DECLARATION LIST

////////////////////////////////////////////////////////////////////////////////////////
//DEFINITIONS LIST

template <typename T>
List<T>::List(): Min_Max<T>::Min_Max(), _max_size(std::numeric_limits<std::size_t>::infinity()), \
                            _head(new Item<T>(T())){    //constructeur
	_head->set_previous(_head);
	_head->set_next(_head);
}

template <typename T>
List<T>::List(std::size_t max_size): Min_Max<T>::Min_Max(), _max_size(max_size),\
                                     _head(new Item<T>(T())) {
    _head->set_previous(_head);
    _head->set_next(_head);
}

template <typename T>
List<T>::List(const List& other): Min_Max<T>::Min_Max(), _max_size(other._max_size), \
                                _head(new Item<T>(T())){
	this->_size = 0;
	_head->set_next(_head);
	_head->set_previous(_head);
	if (not other.empty()) {
		this->insert_back(other);
	}
}  //constructeur de copie

template <typename T>
List<T>::List(List&& other): Min_Max<T>::Min_Max(), _max_size(other._max_size), \
                            _head(new Item<T>(T())) {
	_size = 0;
	if (not other.empty()) {
		this->insert_back(other);
		other.clear();
	}
} //constructeur de transfert

template <typename T>
void List<T>::insert_back(const List& other) {
	Item<T>* current = other._head;
	for (unsigned int i = 0; i < (other._size); ++i) {
		Item<T>* newItem = new Item<T>((current->get_next())->get_elem());
		Item<T>* last = _head->get_previous();
		newItem->set_next(_head);
		newItem->set_previous(last);
		last->set_next(newItem);
		_head->set_previous(newItem);
		this->_size += 1;
		current = current->get_next();
	}
}

template <typename T>
List<T>::~List() { //destructeur
    this->clear();
    delete _head;
}

template <typename T>
bool List<T>::empty() const{return _size == 0;}

template <typename T>
std::size_t List<T>::size() const {return _size;}

template <typename T>
std::size_t List<T>::max_size() const {return _max_size;}

template <typename T>
T List<T>::front() const{ //Renvoie valeur Max

    if (this->empty()){ throw std::out_of_range("Erreur: La liste est vide !");}
    else {return (_head->get_next())->get_elem();}
}

template <typename T>
T List<T>::back() const{ //Renvoie valeur Min

	if (this->empty()){ throw std::out_of_range("Erreur: La liste est vide !");}
	else {return (_head->get_previous())->get_elem();}
}

template <typename T>
void List<T>::pop_front(){         //delete le Max

    if (this->empty()) {throw std::out_of_range("Erreur: Aucun élément à pop");}
    else{
        Item<T>* current = _head->get_next();
        if (current->get_next() == _head) {Item<T>* newNext = nullptr; _head->set_next(newNext);}
        else{
            Item<T>* newNext = current->get_next();
            newNext->set_previous(_head);
            _head->set_next(newNext);
        }
        delete current;
        _size -= 1;
    }
}

template <typename T>
void List<T>::pop_back() {         //delete le Min

    if (this->empty()) {throw std::out_of_range("Erreur: Aucun élément à pop");}
    else{
        Item<T>* current = _head->get_previous();
        if (_head->get_next() == current) {_head->set_next(_head);}
        else {(current->get_previous())->set_next(_head);}
        delete current;
        _size -= 1;
    }
}

template <typename T>
void List<T>::clear(){          //Vide la liste;
	while (not this->empty()) { //Tant que liste pas vide
		this->pop_front();
	}
	_head->set_next(_head);
	_head->set_previous(_head);
	_size = 0;
}

template <typename T>
typename List<T>::const_iterator List<T>::insert(T t)
{ //Insère un nouvel élément dans la liste => newItem
	Item<T>* newItem = new Item<T>(t); //nouvel objet item
	if (_head->get_next() == nullptr){ //Premier inséré
		_head->set_next(newItem);
		_head->set_previous(newItem);  //précédent = lui-même
		newItem->set_next(_head);      //suivant = lui-même
		newItem->set_previous(_head);
		_size += 1;
	}

	else{
		Item<T>* current = _head->get_next();
		bool placed = false;
		do{
			if (newItem->get_elem() >= current->get_elem()){
				newItem->set_next(current);      //newItem -> current
				Item<T>* temp = current->get_previous();
				newItem->set_previous(temp);  //prev_current <- newItem
				(current->get_previous())->set_next(newItem);
				current->set_previous(newItem);
				placed = true; _size += 1;
			}
			else if (current->get_next() == _head){
				newItem->set_previous(current);
				newItem->set_next(_head);
				current->set_next(newItem);
				_head->set_previous(newItem);
				placed = true; _size += 1;
			}
			current = current->get_next();
		}while (not placed && current != _head);
	}
	return const_iterator(newItem);
}

template <typename T>
void List<T>::swap(List<T>& L2) {
	List<T>::swap(this._head, L2._head);
	List<T>::swap(this._size, L2._size);
}

template <typename T>
inline void swap(List<T>& L1, List<T>& L2) {
	List<T>::swap(L1._head, L2._head);
	List<T>::swap(L1._size, L2._size);
}

template <typename T>
void List<T>::show(std::ostream &os) const{
	if (this->empty()) {os << "[]";}
	else{
		os << "[";
		Item<T>* current = _head->get_next();
		do {
			if (current->get_next() == _head) {os << current->get_elem();}
			else {os << current->get_elem() << ", ";}
			current = current->get_next();
		} while(current != _head);
		os << "]" << " taille: " << _size;
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l)
{
    l.show(os);
    return os;
}

template <typename T> T convert_to (const std::string &str)
{
    std::istringstream ss(str);
    T num;
    ss >> num;
    return num;
}

template <typename T>
std::istream& operator>>(std::istream& file, List<T>& l)
{
    std::string line;
    while ( getline (file,line) )
    {
        T temp = convert_to<T>(line);
        l.insert(temp);
    }
    return file;
}

#endif //_CircDoubleLinkedList_H
