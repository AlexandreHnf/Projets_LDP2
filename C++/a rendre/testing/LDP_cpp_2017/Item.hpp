/* [INFO-F202] Langages de Programmation 2: Projet C++
 * Auteur: Alexandre Heneffe, 000440761
 * Date: 22 décembre 2017
 */

#ifndef _ITEM_H
#define _ITEM_H

template <typename T>
class Item{
public:
    //constructeur + destructeur
    Item(T newElem);
    ~Item() = default;    //destructeur
    Item(const Item& other);    //Constructeur de copie
    inline Item& operator= (const Item& other) //opérateur d'assignation
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
    T& get_refelem();
    Item* get_previous() const;
    Item* get_next() const;

    //SETTER
    void set_previous(Item*& newPrevious);
    void set_next(Item*& newNext);

private:
    Item *_previous; //pointeur vers précédent de type Item dans la liste
    T _elem;
    Item *_next; //pointeur vers un élément suivant de type Item
};  //FIN DECLARATION ITEM

//DEFINITIONS Item

//constructeur
template <typename T>
Item<T>::Item(T newElem): _previous(nullptr), _elem(newElem), _next(nullptr){}
//~Item() = default;    //destructeur

template <typename T>
//Constructeur de copie
Item<T>::Item(const Item& other): _previous(nullptr), _elem(other._elem), _next(nullptr){}

//getter elem
template <typename T>
T Item<T>::get_elem() const { return _elem; }

//getter elem renvoie une référence;
template <typename T>
T& Item<T>::get_refelem() { return _elem; }

//getter previous
template <typename T>
typename Item<T>::Item* Item<T>::get_previous() const{ return _previous; }

//getter next
template <typename T>
typename Item<T>::Item* Item<T>::get_next() const { return _next; }

//setter previous
template <typename T>
void Item<T>::set_previous(Item*& newPrevious){ _previous = newPrevious; }

//setter next
template <typename T>
void Item<T>::set_next(Item*& newNext) { _next = newNext; }

#endif //_ITEM_H
