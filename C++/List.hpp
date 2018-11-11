#ifndef List_H_
#define List_H_

#include "min_max.hpp"
#include <iostream>
#include <string>

//liste circulaire doublement liée

//template <typename T> class List;
template <typename T>
class List: public Min_Max<T>{
	public:
		List();
		~List();
		List(const List& other); //copier toute la liste
		//List& operator= (const List& other) = delete;
		List<T>& operator= (const List<T>& other) //opérateur d'assignation  david = goliath
		{
			if (this != &other){
				_head = other._head;
			}
			return *this;
		}
		bool isEmpty() const;
		T front() const override;
		T min() const override;
		T back() const override;
		T max() const override;
		int get_length() const;
		void pop_front() override;
		void pop_max() override;
		void pop_back() override;
		void pop_min() override;
		void clear() override;
		void insert(T t) override;
		void show() const;

		template <T> friend std::ostream& operator<<(std::ostream& os, const List<T>& l);
		T operator[](const int index) const;
		void afficher(std::ostream &os) const override;


		class Item;

		class iterator {
			public:
				iterator(Item* ptr): _ptr(ptr){}
				~iterator() = default;
				Item* get_ptr() { return _ptr;} //getter
				iterator& operator++(){
					_ptr = _ptr->get_next();
					return *this;
				}

				iterator operator++(int) {
					iterator res = *this;
					++(*this);
					return res;
				}

				T operator->(){return _ptr->get_elem();}   //Comment l'utiliser ??
				// T& operator*(){
				// 	Item tmp = *(_ptr);
				// 	T temp = tmp.get_elem();
				// 	//return _ptr->get_elem();
				// 	return temp;
				// }
				T operator*(){return _ptr->get_elem();}
				//(void)r++   => ??

				bool operator==(const iterator it2) {return (_ptr == it2._ptr);}
				bool operator!=(const iterator it2) {return (_ptr != it2._ptr);}

			private:
				Item* _ptr;
		};

		class const_iterator { //comment l'utiliser ?
			public:
				const_iterator(Item* ptr): _ptr(ptr){}
				~const_iterator() = default;
				//iterator operator=(const iterator& other) { _ptr = other._ptr; return *this; } //operateur assignation
				Item* get_ptr() { return _ptr;} //getter
				const_iterator& operator++(){
					_ptr = _ptr->get_next();
					return *this;
				}

				const_iterator operator++(int) {
					const_iterator res = *this;
					++(*this);
					return res;
				}

				T operator->() const{return _ptr->get_elem();}   //??
				T operator*() const{return _ptr->get_elem();}

				bool operator==(const const_iterator it2) {return (_ptr == it2._ptr);}
				bool operator!=(const const_iterator it2) {return (_ptr != it2._ptr);}

			private:
				Item* _ptr;
		};

		inline typename List<T>::iterator begin(){return iterator(_head->get_next());}
		inline typename List<T>::iterator end(){return iterator(_head);}
		inline typename List<T>::const_iterator cbegin(){return const_iterator(_head->get_next());}
		inline typename List<T>::const_iterator cend(){return const_iterator(_head);}

		class Item{
			public:
				//constructeur + destructeur
				Item(T newElem);
				~Item() = default;    //destructeur
				Item(const Item& other);    //Constructeur de copie
				//Item& operator= (const Item& other);    //Opérateur d'assignation
				List<T>::Item& operator= (const Item& other) //opérateur d'assignation  david = goliath
				{
					if (this != &other){
						_previous = other._previous;
						_elem = other._elem;
						_next = other._next;
					}
					return *this;
				}

				//GETTER
				T get_elem() const;
				Item* get_previous() const;
				Item* get_next() const;

				//SETTER
				void set_elem(T newElem);
				void set_previous(Item*& newPrevious);
 				void set_next(Item*& newNext);

			private:
				Item *_previous; //pointeur vers précédent de type Item dans la liste
				T _elem;
				Item *_next; //pointeur vers un élément suivant de type Item
		};  //FIN DECLARATION ITEM

		// class l_iterator : public Min_Max<T>::iterator{
		// 	public:
		// 		l_iterator(T* ptr): Min_Max<T>::iterator<T>::iterator(), _ptr(ptr){}
		// 		~l_iterator(){}
		// 		//l_iterator operator++() {l_iterator i = *this; _ptr++; return i;}
		// 		l_iterator operator++() override;
        //         //l_iterator operator++(int junk) { ptr_++; return *this; }
        //         T& operator*() { return *ptr_; }
        //         T* operator->() { return ptr_; }
		// 		bool operator==(const l_iterator& it2) { return _ptr == it2._ptr;}
		// 		bool operator!=(const l_iterator& it2) { return _ptr != it2._ptr;}
        //
		// 	private:
		// 		T* ptr;
        //
		// };
	private:
		Item *_head;  //pointeur vers le premier élément de la liste
					  //_head est également le max du coup
		int _length; //taille de la liste
};      //FIN DECLARATION LIST

//////////////////////////////////////////////////////////
//DEFINITIONS iterator
//template <typename T>
//List<T>::l_iterator::l_iterator(T* ptr): Min_Max<T>::iterator<T>::iterator(), _ptr(ptr){}

//template <typename T>
//bool List<T>::l_iterator::operator==(const l_iterator& it2) { return _ptr == it2._ptr;}

//template <typename T>
//bool List<T>::l_iterator::operator!=(const l_iterator& it2) { return _ptr != it2._ptr;}


////////////////////////////////////////////////////////////////////////////////////////
//DEFINITIONS LIST

template <typename T>
List<T>::List(): Min_Max<T>::Min_Max(), _head(new Item(T())), _length(0) {}    //consructeur

template <typename T>
List<T>::List(const List& other): Min_Max<T>::Min_Max(), _head(other._head), _length(0) {
	//_head = other._head;
	Item* newCurrent = _head;
	Item* current = other._head;
	while (current->get_next() != other._head){
		Item tmp = *(current->get_next());
		Item* newItem = &tmp;
		newItem->set_previous(newCurrent);
		newCurrent->set_next(newItem);
		current = current->get_next();
		if (current != other._head) {newCurrent = newCurrent->get_next();}
	}
	newCurrent->set_next(_head);
	_head->set_previous(newCurrent);
}  //constructeur de copie

template <typename T>
List<T>::~List(){}   //destructeur
//méthodes de classe parente + éventuelles autres méthodes

template <typename T>
bool List<T>::isEmpty() const{
	return (_head->get_next() == nullptr);
}

template <typename T>
T List<T>::front() const{ //Renvoie valeur Max
	try{
		if (this->isEmpty()){ throw std::string("Erreur: La liste est vide !");}
		else {return (_head->get_next())->get_elem();}
	}
	catch(std::string const& chaine) {
		std::cout << chaine << std::endl;
		return T();
	}
}

template <typename T>
T List<T>::min() const {return this->front();}

template <typename T>
T List<T>::back() const{ //Renvoie valeur Min
	try{
		if (this->isEmpty()){ throw std::string("Erreur: La liste est vide !");}
		else {return (_head->get_previous())->get_elem();}
	}
	catch(std::string const& chaine) {
		std::cout << chaine << std::endl;
		return T();
	}
}

template <typename T>
T List<T>::max() const {return this->back();}

template <typename T>
int List<T>::get_length() const{
	return _length;
}

template <typename T>
void List<T>::pop_front(){         //delete le Max
	try{
		if (this->isEmpty()) {throw std::string("Erreur: Aucun élément à pop");}
		else{
			Item* current = _head->get_next();
			if (current->get_next() == _head) {Item* newNext = nullptr; _head->set_next(newNext);}
			else{Item* newNext = current->get_next(); _head->set_next(newNext);}
			delete current;
			_length -= 1;
		}
	}
	catch(std::string const& chaine) {
		std::cout << chaine << std::endl;
	}
}

template <typename T>
void List<T>::pop_max() {this->pop_front();}

template <typename T>
void List<T>::pop_back() {         //delete le Min
	try{
		if (this->isEmpty()) {throw std::string("Erreur: Aucun élément à pop");}
		else{
			Item* current = _head->get_previous();
			Item* newNext = nullptr;
			if (current->get_next() == _head) {_head->set_next(newNext);}
			else {Item* newNext = _head; (current->get_previous())->set_next(newNext);}
			// current->set_previous(nullptr);
			// current->set_next(nullptr);
			delete current;
			_length -= 1;
		}
	}
	catch(std::string const& chaine) {
		std::cout << chaine << std::endl;
	}
}

template <typename T>
void List<T>::pop_min() {this->pop_back();}

template <typename T>
void List<T>::clear(){          //Vide la liste;
	while (not this->isEmpty()) { //Tant que liste pas vide
		this->pop_front();
		this->show();
	}
	_length = 0;
}

template <typename T>
void List<T>::insert(T t)    //Insère un nouvel élément dans la liste => newItem
{
	//TRIER LA LISTE
	Item* newItem = new Item(t); //nouvel objet item
	if (_head->get_next() == nullptr){
		//std::cout << "premier inséré" << std::endl;
		_head->set_next(newItem);
		_head->set_previous(newItem);  //précédent = lui-même
		newItem->set_next(_head);      //suivant = lui-même
		newItem->set_previous(_head);
		_length += 1;
	}

	else{
		//std::cout << "insérer autre part" << std::endl;
		Item* current = _head->get_next();
		bool placed = false;
		do{
			//std::cout << newItem->get_elem() << std::endl;
			if (newItem->get_elem() >= current->get_elem()){
				//std::cout << "Avant Current" << std::endl;
				//maj des pointeurs
				newItem->set_next(current);                         //newItem -> current
				Item* temp = current->get_previous();
				//std::cout << temp->get_elem() << std::endl;
				newItem->set_previous(temp);  //prev_current <- newItem
				(current->get_previous())->set_next(newItem);    //
				current->set_previous(newItem);
				placed = true; _length += 1;
			}
			else if (current->get_next() == _head){
				//std::cout << "A la fin" << std::endl;
				newItem->set_previous(current);
				newItem->set_next(_head);
				current->set_next(newItem);
				_head->set_previous(newItem);
				placed = true; _length += 1;
			}
			current = current->get_next();
			//std::cout << "current" << current->
		}while (not placed && current != _head);
	}
}

template <typename T>
void List<T>::show() const {
	if (this->isEmpty()){
		std::cout << "Liste: []" << std::endl;
	}
	else{
		std::cout << "Liste: [";
		Item* current = _head->get_next();
		do {
			std::cout << current->get_elem() << ", ";
			current = current->get_next();
			//std::cout << current->get_elem() << std::endl;
		} while(current != _head);
		std::cout << "]" << " taille: " << _length << std::endl;
	}
}

//template <T> std::ostream& operator<<(std::ostream& os, const List<T>& l);

template <typename T>
T List<T>::operator[](const int index) const{
	T res = T();
	try{
		if (this->isEmpty() or index >= _length) {throw std::string("Erreur: Indice invalide.");}
		else{
			int i = 0; bool found = false; //premier elem
			Item* current = _head->get_next();
			do{
				if (i == index) {
					res = current->get_elem(); found = true;
				}
				current = current->get_next(); i+= 1;
			} while(i <= index && not found);
		}
	}
	catch(std::string const& chaine){
		std::cout << chaine << std::endl;
	}
	return res;
}

// T& operator[](int index) {
// 	try{
// 		throw std::string("ERROR PEUT PAS MODIF VAL");
// 	}
// 	catch(std::string const& chaine){
// 		std::cout << chaine << std::endl;
// 	}
// }
//T& operator[](const int index) = delete;

// auto get_head() const
// {
// 	return _head;
// }

template <typename T>
void List<T>::afficher(std::ostream &os) const{
	if (this->isEmpty()) {os << "Liste: []";}
	else{
		os << "Liste: [";
		Item* current = _head->get_next();
		do {
			if (current->get_next() == _head) {os << current->get_elem();}
			else {os << current->get_elem() << ", ";}
			current = current->get_next();
			//std::cout << current->get_elem() << std::endl;
		} while(current != _head);
		os << "]" << " taille: " << _length;
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l)
{
    l.afficher(os);
    return os;
}

///////////////////////////////////////////////////////////////////////////////
//DEFINITIONS Item

//constructeur
template <typename T>
List<T>::Item::Item(T newElem): _previous(nullptr), _elem(newElem), _next(nullptr){}
//~Item() = default;    //destructeur

template <typename T>
//Constructeur de copie
List<T>::Item::Item(const Item& other): _previous(other._previous), _elem(other._elem), _next(other._next){}

//getter elem
template <typename T>
T List<T>::Item::get_elem() const { return _elem; }

 //getter previous
template <typename T>
typename List<T>::Item* List<T>::Item::get_previous() const{ return _previous; }

//getter next
template <typename T>
typename List<T>::Item* List<T>::Item::get_next() const { return _next; }

//pour mettre un élément dans l'Item
template <typename T>
void List<T>::Item::set_elem(T newElem){ _elem = newElem; }

//setter previous
template <typename T>
void List<T>::Item::set_previous(Item*& newPrevious){ _previous = newPrevious; }

//setter next
template <typename T>
void List<T>::Item::set_next(Item*& newNext) { _next = newNext; }

#endif //LIST_H_
