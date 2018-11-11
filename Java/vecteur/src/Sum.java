/* [INFO-F202] Langages de Programmations 2 - JAVA
 * Auteur: Alexandre Heneffe
 * Matricule: 000440761
 */

public class Sum<T extends Number> implements Runnable {
	
	private vect0<T> v1, v2; //2 vecteurs à additionner
	private int inf, sup; //Bornes dans vecteurs
	
	public Sum(vect0<T> v1, vect0<T> v2, int inf, int sup) {
		//constructeur
		this.v1 = v1;
		this.v2 = v2; 
		this.inf = inf;
		this.sup = sup;
	}
	
	public void run() {
		for (int i=inf; i < sup; ++i) {
			T tmp = v1.add(v1.get_elem(i), v2.get_elem(i));
			v1.set_elem(i, tmp);
		}
	}
}
