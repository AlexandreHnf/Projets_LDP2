/* [INFO-F202] Langages de Programmation 2: Projet C++
 * Auteur: Alexandre Heneffe, 000440761
 * Date: 22 décembre 2017
 */

#include <iostream>
#include "min_max.hpp"
#include "CircBidirLinkedList.hpp"
#include "tableau.hpp"
#include <string>
#include <fstream>

int main()
{
    //1 = true, 0 = false;
    //////////////////////////////////////// LISTE ////////////////////////////////////
    std::cout << "==================================List===============================" << std::endl;
    std::cout << "-------------------Création des Listes avec fichiers " << std::endl;
    List<int> List_int;
    List<std::string> List_str;
    std::ifstream file_int ("int_values.txt");
    if (not file_int.is_open()) {
        throw std::invalid_argument("impossible d'ouvrir le fichier");
    }
    else{
        file_int >> List_int;
        file_int.close();
    }

    std::ifstream file_str ("string_values.txt");
    if (not file_str.is_open()) {
        throw std::invalid_argument("Impossible d'ouvrir le fichier");
    }
    else{
        file_str >> List_str;
        file_str.close();
    }

    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List string: " << List_str << std::endl;

    std::cout << "front List Int: " << List_int.front() << std::endl;
    std::cout << "front List String: " << List_str.front() << std::endl;
    std::cout << "back List Int: " << List_int.back() << std::endl;
    std::cout << "back List String: " << List_str.back() << std::endl;

    std::cout << "---------------pop front dans les 2: " << std::endl;
    List_int.pop_front();
    List_str.pop_front();

    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List string: " << List_str << std::endl;

    std::cout << "---------------pop back dans les 2: " << std::endl;
    List_int.pop_back();
    List_str.pop_back();

    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List string: " << List_str << std::endl;

    std::cout << "---------------Insertion de 8 et 'y' : " << std::endl;
    List_int.insert(8);
    List_str.insert("y");

    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List string: " << List_str << std::endl;

    std::cout << "---------------Constructeur de copie: " << std::endl;
    List<int> List_int2 = List_int;
    List<std::string> List_str2 = List_str;

    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List int copié : " << List_int2 << std::endl;
    std::cout << "List string: " << List_str << std::endl;
    std::cout << "List string copié : " << List_str2 << std::endl;
    std::cout << "List int == List int copié ?: " << (List_int == List_int2) << '\n';

    std::cout << "---------------pop front dans les 2 copiés: " << std::endl;
    List_int2.pop_front();
    List_str2.pop_front();

    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List int copié : " << List_int2 << std::endl;
    std::cout << "List string: " << List_str << std::endl;
    std::cout << "List string copié : " << List_str2 << std::endl;

    std::cout << "---------------clear des listes copiées: " << std::endl;
    List_int2.clear(); List_str2.clear();
    std::cout << "List int: " << List_int << std::endl;
    std::cout << "List int copié : " << List_int2 << std::endl;
    std::cout << "List string: " << List_str << std::endl;
    std::cout << "List string copié : " << List_str2 << std::endl;

    std::cout << "---------------Construction de 2 listes int : " << std::endl;
    List<int> c1; List<int> c2;
    c1.insert(1); c2.insert(3); c2.insert(4);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    c1 = c2;
    std::cout << "---------------Opérateur d'assignation: " << std::endl;
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    std::cout << "pop back de c1: " << std::endl;
    c1.pop_back();
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    std::cout << "---------------ajout de valeurs dans c1 et c2: " << std::endl;
    c1.insert(5);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    c1.insert(2);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    c2.insert(9);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;

    std::cout << "---------------Swap de c1 et c2; " << std::endl;
    swap(c1, c2);
    std::cout << "c1: " << c1 << ", c2: " << c2 << std::endl;
    std::cout << "c1 != c2 ?: " << (c1 != c2) << std::endl;
    std::cout << "c1 == c2 ?: " << (c1 == c2) << std::endl;

    std::cout << "---------------Test Iterateur: " << std::endl;
    std::cout << "premier élément de List string: " << *(List_str.begin()) << std::endl;
    std::cout << "Affichage avec itérateur: List int: ";
    for (List<int>::iterator i = List_int.begin(); i != List_int.end(); ++i){
        std::cout << *i << ",";
    }
    std::cout << std::endl;
    List<std::string>::const_iterator j = List_str.cbegin();
    std::cout << "List string: " << List_str << std::endl;
    std::cout << "j itérateur de List string" << std::endl;
    std::cout << "*j: " << *j << std::endl;
    std::cout << "*j++: " << *j++ << '\n';
    ++j;
    std::cout << "++j: " << *j << std::endl;

    std::cout << "Swap de itérateur de c1 et itérateur de c2: " << std::endl;
    List<int>::iterator q1 = c1.begin(); List<int>::iterator q2 = c2.begin();
    std::cout << "q1: " << *q1 << ", q2: " << *q2 << std::endl;
    q1.swap(q2);
    std::cout << "q1: " << *q1 << ", q2: " << *q2 << std::endl;

    //////////////////////////////////////// TABLEAU ////////////////////////////////////
    std::cout << "===============================TABLEAU===============================" << std::endl;

    std::cout << "-------------------Création des tableaux avec fichiers " << std::endl;

    Tableau<int> Tableau_int(13);
    Tableau<std::string> Tableau_str(13);
    std::ifstream file_int2 ("int_values.txt");
    if (not file_int2.is_open()) {
        throw std::invalid_argument("impossible d'ouvrir le fichier");
    }
    else{
        file_int2 >> Tableau_int;
        file_int2.close();
    }

    std::ifstream file_str3 ("string_values.txt");
    if (not file_str3.is_open()) {
        throw std::invalid_argument("impossible d'ouvrir le fichier");
    }
    else{
        file_str3 >> Tableau_str;
        file_str3.close();
    }

    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;


    std::cout << "front Tableau Int: " << Tableau_int.front() << std::endl;
    std::cout << "front Tableau String: " << Tableau_str.front() << std::endl;
    std::cout << "back Tableau Int: " << Tableau_int.back() << std::endl;
    std::cout << "back Tableau String: " << Tableau_str.back() << std::endl;

    std::cout << "---------------pop front dans les 2: " << std::endl;
    Tableau_int.pop_front();
    Tableau_str.pop_front();

    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;

    std::cout << "---------------pop back dans les 2: " << std::endl;
    Tableau_int.pop_back();
    Tableau_str.pop_back();

    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;

    std::cout << "---------------Insertion de 8 et 'y' : " << std::endl;
    Tableau_int.insert(8);
    Tableau_str.insert("y");

    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;

    //Tableau<int>::iterator i = Tableau_int.begin();
    //++i;

    std::cout << "---------------Constructeur de copie: " << std::endl;
    Tableau<int> Tableau_int2 = Tableau_int;
    Tableau<std::string> Tableau_str2 = Tableau_str;

    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau int copié : " << Tableau_int2 << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;
    std::cout << "Tableau string copié : " << Tableau_str2 << std::endl;
    std::cout << "Tableau int == Tableau int copié ?: " << (Tableau_int == Tableau_int2) << '\n';

    std::cout << "---------------pop front dans les 2 copiés: " << std::endl;
    Tableau_int2.pop_front();
    Tableau_str2.pop_front();

    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau int copié : " << Tableau_int2 << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;
    std::cout << "Tableau string copié : " << Tableau_str2 << std::endl;

    std::cout << "---------------clear des Tableaux copiées: " << std::endl;
    Tableau_int2.clear(); Tableau_str2.clear();
    std::cout << "Tableau int: " << Tableau_int << std::endl;
    std::cout << "Tableau int copié : " << Tableau_int2 << std::endl;
    std::cout << "Tableau string: " << Tableau_str << std::endl;
    std::cout << "Tableau string copié : " << Tableau_str2 << std::endl;


    std::cout << "---------------Construction de 2 Tableaux int : " << std::endl;
    Tableau<int> t1; Tableau<int> t2;
    t1.insert(1); t2.insert(3); t2.insert(4);
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
    t1 = t2;
    std::cout << "---------------Opérateur d'assignation: " << std::endl;
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
    std::cout << "pop back de t1: " << std::endl;
    t1.pop_back();
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
    std::cout << "---------------ajout de valeurs dans t1 et t2: " << std::endl;
    t1.insert(5);
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
    t1.insert(2);
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
    t2.insert(9);
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;

    std::cout << "---------------Swap de t1 et t2: " << std::endl;
    swap(t1, t2);
    std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
    std::cout << "t1 != t2 ?: " << (t1 != t2) << std::endl;
    std::cout << "t1 == t2 ?: " << (t1 == t2) << std::endl;

    std::cout << "---------------Test Iterateur: " << std::endl;
    std::cout << "premier élément de Tableau string: " << *(Tableau_str.begin()) << std::endl;
    std::cout << "Affichage avec itérateur: Tableau int: ";
    for (Tableau<int>::iterator i = Tableau_int.begin(); i != Tableau_int.end(); ++i){
        std::cout << *i << ",";
    }
    std::cout << std::endl;

    Tableau<std::string>::const_iterator k = Tableau_str.cbegin();
    std::cout << "Tableau string: " << Tableau_str << std::endl;
    std::cout << "k itérateur de Tableau string" << std::endl;
    std::cout << "*k: " << *k << std::endl;
    std::cout << "*k++: " << *k++ << '\n';
    ++k;
    std::cout << "++k: " << *k << std::endl;
    std::cout << "Swap de itérateur de t1 et itérateur de t2: " << std::endl;
    Tableau<int>::iterator p1 = t1.begin(); Tableau<int>::iterator p2 = t2.begin();
    std::cout << "p1: " << *p1 << ", p2: " << *p2 << std::endl;
    p1.swap(p2);
    std::cout << "p1: " << *p1 << ", p2: " << *p2 << std::endl;

    return 0;
}