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

int main(){

	/////////////////////////////////////// LISTE ///////////////////////////////////////////
	std::cout << "/////////////////////////////////LISTE/////////////////////////" << '\n';
	List<int> *L = new List<int>;
	std::cout << *L << std::endl;

    //List<double> input_l;
    //std::cout << input_l << std::endl;
    //std::cin >> input_l;
    //std::cout << input_l << std::endl;

    std::ifstream file_int ("string_values.txt");
    if (file_int.is_open()) {
        List<std::string> linput = List<std::string>(9);
        file_int >> linput;
        std::cout << linput << std::endl;
        file_int.close();
    }
    else {std::cout << "impossible d'ouvrir le fichier" << std::endl;}


	std::cout << "pop_back" << '\n';
	L->pop_back();
	std::cout << "back" << '\n';
	L->back();
	int n = 12;
	//int* test = new int[n];
	int test[n] = {2, 4, 3, 2, 1, 7, 8, 5, 9, 0, 10, 0};
	std::cout << "Insertions: " << '\n';
	for (int i = 0; i < n; ++i) {L->insert(test[i]);}
	std::cout << *L << std::endl;

	std::cout << "max: " << L->front() << std::endl;
	std::cout << "min: " << L->back() << std::endl; //O(1)
	//std::cout << "element 2, 0, 11, 4: " << (*L)[2] << " " << (*L)[0] << " " << (*L)[11] << " " << (*L)[4] << std::endl;
	//List<int>::Iterator it;
    std::cout << "Test de l'itérateur LIST: " << std::endl;
	std::cout << "premier element: " << *(L->begin()) << '\n';
	std::cout << "1er elem = bidon ?: " <<( L->begin() == L->end()) << '\n';
	std::cout << "Liste: " << '\n';
	//int p = 1;
	for (List<int>::const_iterator i = L->cbegin(); i != L->cend(); ++i){
		//*i = p;
		std::cout << *i << ",";
	}
	std::cout << '\n';
	std::cout << *L << '\n';
	List<int>::const_iterator j = L->cbegin();
	std::cout << "j: " << *j << '\n';
	//std::cout << "j: " << *j++ << '\n';
	std::cout << "j: " << *j << '\n';
	List<int>::iterator h = L->begin();
	std::cout << "h: " << *h << '\n';

//    std::cout << "Test du SWAP: " << std::endl;
//	  List<int>::iterator q1 = L->begin();
//    List<int>::iterator q2 = L->begin();
//    ++q2;
//    std::cout << "q1: " << *q1 << " q2: " << *q2 << std::endl;
//    q1.swap(q2);
//    std::cout << "q1: " << *q1 << " q2: " << *q2 << std::endl;

	//int t = (*L)[12];
	//std::cout << "t: " << t << '\n';
	std::cout << "pop back: " << '\n';
	L->pop_back();
	std::cout << *L << std::endl;
	//L[0] = 4;
	std::cout << "Test constructeur de copie LIST" << '\n';
	List<int> L2 = *L; //appel constructeur copie
	std::cout << "L: " << *L <<'\n';
	std::cout << "L2: " << L2 << '\n';
	L2.pop_front();
	std::cout << "L: " << *L << '\n';
	std::cout << "L2: " << L2 << '\n';

	// std::cout << "Test constructeur de transfert LIST" << '\n';
	// List<int> Lt
	// Lt.insert(5); Lt.insert(6);
	// std::cout << Lt << '\n';
	// List<int> Lt2 = Lt; //appel constructeur transfert ??

	std::cout << "Test opérateur assignation LIST" << '\n';
	List<int> Lc1; List<int> Lc2;
	Lc1.insert(1); Lc2.insert(3); Lc2.insert(4);
	std::cout << "Lc1: " << Lc1 << " Lc2: " << Lc2 << '\n';
	Lc1 = Lc2;
	std::cout << "Lc1: " << Lc1 << " Lc2: " << Lc2 << '\n';
	Lc1.pop_back();
	std::cout << "Lc1: " << Lc1 << " Lc2: " << Lc2 << '\n';

	std::cout << "Test opérateur de transfert LIST" << '\n';
	//balbla

//	std::cout << "Test constructeur de copie ITEM" << '\n';
//	List<int>::Item f(5);
//	List<int>::Item g = f;
//	std::cout << "f et g" << f.get_elem() << " " << g.get_elem() << '\n';
//	g.set_elem(6);
//	std::cout << "f et g" << f.get_elem() << " " << g.get_elem() << '\n';
	std::cout << "Clear de la Liste: " << std::endl;
	L->clear();
	//std::cout << "L[1]: " << (*L)[1] << std::endl;
	int k = 10;
	int *m = &k;
	//int &g = m;
	//g = 6;
	std::cout << "m: " << *m << '\n';
	//std::cout << "Test du SWAP" << '\n';
	// List<int> L1;
	// L1.insert(1);
	// List<int> L2;
	// L2.insert(5);
	// std::cout << "L1: " << L1 << "\n" << L2 << '\n';
	// swap(L1, L2);
	// std::cout << "L1: " << L1 << "\n" << L2 << '\n';
	delete L;

	std::cout << "Insertion avec TABLEAU" << '\n';
	// List<int> *mm = new List<int>({1,2,3});
	// std::cout << *mm << '\n';
	// delete mm;

    std::cout << "Test du SWAP LIST" << std::endl;
    List<int> L5, L6;
    L5.insert(4); L6.insert(5);
    std::cout << "L5: " << L5 << " L6: " << L6 << '\n';
    swap(L5, L6);
    std::cout << "L5: " << L5 << " L6: " << L6 << '\n';

    std::cout << "Test du == LIST: " << std::endl;
    List<int> e1, e2;
    e1.insert(1); e1.insert(2); e1.insert(3);
    e2.insert(1); e2.insert(2); e2.insert(4);
    std::cout << "e1: " << e1 << " e2: " << e2 << std::endl;
    std::cout << "e1 != e2 ?: " << (e1 != e2) << std::endl;
    std::cout << "e1 == e2 ?: " << (e1 == e2) << std::endl;
    std::cout << "e1: " << e1 << " e2: " << e2 << std::endl;


	/////////////////////////////////////////////////////////////////////////////
	////////////////////////////// PARTIE TABLEAU ////////////////////////////////

	std::cout << "/////////////////////////TABLEAU/////////////////////" << '\n';
	Tableau<int> *Ta = new Tableau<int>;
	//Tableau<int> *Ta2 = new Tableau<int>;
	std::cout << *Ta << '\n';
	std::cout << "Insertion: " << '\n';
	int tab[9] = {2,4,3,0,5,6,9,2,1};
	for (int i = 0; i < 9; ++i) {
		std::cout << "elem: " <<  tab[i] << " ";
		Ta->insert(tab[i]);
		std::cout << *Ta << '\n';
	}

	std::cout << "front: " << Ta->front() << '\n';
	std::cout << "back: " << Ta->back() << '\n';
	std::cout << "pop front: " << '\n';
	Ta->pop_front();
	std::cout << *Ta << '\n';

	std::cout << "pop back: " << '\n';
	Ta->pop_back();
	std::cout << *Ta << '\n';

    std::cout << "Test de l'itérateur TABLEAU: " << std::endl;
    std::cout << *Ta << std::endl;
    std::cout << "premier element: " << *(Ta->begin()) << '\n';
    std::cout << "Dernier element: " << *(Ta->end()) << std::endl;
    std::cout << "1er elem = bidon ?: " <<( Ta->begin() == Ta->end()) << '\n';
    std::cout << "Tableau: ";
    //int p = 4;
    for (Tableau<int>::const_iterator i = Ta->cbegin(); i != Ta->cend(); ++i){
        //*i = p;
        std::cout << *i << ",";
    }
    std::cout << '\n';

	std::cout << "Clear: " << '\n';
	Ta->clear();

	std::cout << "test du constructeur de copie: " << "\n";
	//Tableau<int> *ta = new Tableau<int>;
	Tableau<int> ta1;
	ta1.insert(8); ta1.insert(9);
	std::cout << ta1 << "\n";
	Tableau<int> ta2 = ta1; //appel au constructeur de copie
	std::cout << "ta1: " << ta1 << " ta2: " << ta2 << "\n";
	std::cout << "pop front ta2: " << '\n';
	ta2.pop_front();
	std::cout << ta1 << " " << ta2 << "\n";

	std::cout << "Test de l'opérateur de copie: " << std::endl;
	Tableau<int> t1; Tableau<int> t2;
	t1.insert(6); t1.insert(7); t2.insert(8); t2.insert(9);
	std::cout << "a" << t1 << " " << t2 << "\n";
	t1 = t2;
	std::cout << "b" << t1 << " " << t2 << "\n";
    std::cout << "pop back t1: " << std::endl;
	t1.pop_back();
	std::cout << "c" << t1 << " " << t2 << "\n";

//    std::cout << "Test du SWAP TABLEAU" << std::endl;
//    Tableau<int> T5, T6;
//    T5.insert(4); T6.insert(5);
//    std::cout << "T5: " << T5 << " T6: " << T6 << '\n';
//    swap(T5, T6);
//    std::cout << "T5: " << T5 << " T6: " << T6 << '\n';

    std::cout << "Test du == TABLEAU: " << std::endl;
    Tableau<int> te1, te2;
    te1.insert(1); te1.insert(2); te1.insert(3);
    te2.insert(1); te2.insert(2); te2.insert(4);
    std::cout << "te1: " << te1 << " te2: " << te2 << std::endl;
    std::cout << "te1 != te2 ?: " << (te1 != te2) << std::endl;
    std::cout << "te1 == te2 ?: " << (te1 == te2) << std::endl;
    std::cout << "te1: " << te1 << " te2: " << te2 << std::endl;

	Tableau<int> maxi(6);
    std::cout << maxi << std::endl;

	delete Ta;

	return 0;
}
