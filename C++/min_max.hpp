/* [INFO-F202] Langages de Programmation 2: Projet C++
 * Auteur: Alexandre Heneffe, 000440761
 * Date: 22 décembre 2017
 */

#ifndef MIN_MAX_H_
#define MIN_MAX_H_

#include <iostream>
#include <string>

template <typename T>
class Min_Max{   //classe abstraite de file min max
	public:
		Min_Max() : _size(0), _max_size(0) {} //constructeur avec val par défaut
		Min_Max(const Min_Max& other) = default; //constructeur copie
		Min_Max(Min_Max&&) = default; //constructeur transfert
		Min_Max& operator= (const Min_Max& other) = default; //opérateur d'assignation
		Min_Max& operator= (Min_Max&&) = default; //opérateur de transfert
		virtual ~Min_Max() = default;    //destructeur

		virtual T front() const = 0;
		inline virtual T max() const {return this->front();}
		virtual T back() const = 0;
		inline virtual T min() const {return this->back();}
		virtual void pop_front() = 0;
		virtual void pop_max() {this->pop_front();}
		virtual void pop_back() = 0;
		virtual void pop_min() {this->pop_back();}
		virtual void clear() = 0;

	protected:
		class const_iterator{   //classe abstraite itérateur
			public:
				const_iterator() = default; //par défaut
                const_iterator(const const_iterator& other) = default;
                const_iterator& operator= (const const_iterator& other) = default;

				virtual ~const_iterator() = default;

		 		virtual const_iterator& operator++() = 0;
				virtual const T& operator*() = 0;
		};

		std::size_t _size; //taille actuelle du conteneur
        std::size_t _max_size; //taille maximale du conteneur
};

#endif //MIN_MAX_H_
