/* [INFO-F202] Langages de Programmations 2 - JAVA
 * Auteur: Alexandre Heneffe
 * Matricule: 000440761
 */

public class Prod<T extends Number> implements Runnable {
	
	private vect0<T> v1, v2; //2 vecteurs à multiplier
	private int inf, sup; //Intervalle de valeur à multiplier
	
	public Prod(vect0<T> v1, vect0<T> v2, int inf, int sup) {
		this.v1 = v1;
		this.v2 = v2; 
		this.inf = inf;
		this.sup = sup;
	}
	
	//@SuppressWarnings("unchecked")
	public void run() {
		for (int i=inf; i < sup; ++i) {
			//System.out.println("Dans thread prod ");
			T tmp = v1.multiply(v1.get_elem(i), v2.get_elem(i));
			if (v1.get_res() == null) { v1.set_res(tmp); }
			else {
				T tmp2 = v1.add(v1.get_res(), tmp);
				v1.set_res(tmp2);
			}
		}
	}
}