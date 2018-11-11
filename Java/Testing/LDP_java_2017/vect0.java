/* [INFO-F202] Langages de Programmations 2 - JAVA
 * Auteur: Alexandre Heneffe
 * Matricule: 000440761
 */

public class vect0<T extends Number> {

	private T[] array;
	private int size;
	private static final int NB_THREADS = 3;
	private T res;
	
	public vect0(T[] elements) { //constructeur
		array = elements;
		size = elements.length;
	}
	
	//GETTER
	public int size() { return this.size; }
	public T get_elem(int i) { return array[i]; }
	public T get_res() { return res; }
	//SETTER
	public void set_elem(int i, T e) { array[i] = e; }
	public void set_res(T r) { res = r;	}

	public T add(T a, T b) {
		if (a instanceof Integer && b instanceof Integer) {
			return (T) (Integer) (a.intValue() + b.intValue());
		}
		else if (a instanceof Double && b instanceof Double) {
			return (T) (Double) (a.doubleValue() + b.doubleValue());
		}
		else if (a instanceof Float && b instanceof Float) {
			return (T) (Float) (a.floatValue() + b.floatValue());
		}
		else if (a instanceof Long && b instanceof Long) {
			return (T) (Long) (a.longValue() + b.longValue());
		}
		else if (a instanceof Short && b instanceof Short) {
			return (T) ((Short) ((short) (a.shortValue() + b.shortValue())));
		}
		else if (a instanceof Byte && b instanceof Byte) {
			return (T) ((Byte) ((byte) (a.byteValue() + b.byteValue())));
		}
		else 
			{throw new RuntimeException("Erreur: addition de 2 types différents");}
	}

	public T multiply(T a, T b) {
		if (a instanceof Integer && b instanceof Integer) {
			return (T) (Integer) (a.intValue() * b.intValue());
		}
		else if (a instanceof Double && b instanceof Double) {
			return (T) (Double) (a.doubleValue() * b.doubleValue());
		}
		else if (a instanceof Float && b instanceof Float) {
			return (T) (Float) (a.floatValue() * b.floatValue());
		}
		else if (a instanceof Long && b instanceof Long) {
			return (T) (Long) (a.longValue() * b.longValue());
		}
		else if (a instanceof Short && b instanceof Short) {
			return (T) ((Short) ((short) (a.shortValue() * b.shortValue())));
		}
		else if (a instanceof Byte && b instanceof Byte) {
			return (T) ((Byte) ((byte) (a.byteValue() * b.byteValue())));
		}
		else 
			{throw new RuntimeException("Erreur: Produit de 2 types différents");}
	}

	public void add(vect0<T> v2) {
		
		if (size() != v2.size()) 
			{throw new RuntimeException("Erreur: 2 vecteurs de tailles différentes");}
		int task = size / (NB_THREADS+1);
		Thread[] thread_tab = new Thread[NB_THREADS];
		int b = 0; int j = 0; int test = 5;
		while (b < size && j < NB_THREADS) {
			thread_tab[j] = new Thread(new Sum<T>(this, v2, b, b+task));
			b+=task; j+=1;
		}
		
		for (int k=0; k < NB_THREADS; ++k) {
			thread_tab[k].start();
		}
		for (int i=b; i < size; ++i) {
			array[i] = add(array[i], v2.array[i]);
		}
		for (int i=0; i < NB_THREADS; ++i) {
			try {
				thread_tab[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public T prod_scal(vect0<T> v2){
		
		if (size() != v2.size()) 
			{throw new RuntimeException("Erreur: 2 vecteurs de tailles différentes");}
		res = null; //Résultat du produit vectoriel
		T r = null; //resultat du thread principal 
		int task = size / (NB_THREADS+1);
		Thread[] thread_tab = new Thread[NB_THREADS]; //tableau de thread
		int b = 0; int j = 0;
		while (b < size && j < NB_THREADS) { //attribution des tâches
			thread_tab[j] = new Thread(new Prod<T>(this, v2, b, b+task));
			b+=task; j+=1;
		}
		
		for (int k=0; k < NB_THREADS; ++k) {
			thread_tab[k].start(); //Lancement des threads
		}
		for (int i=b; i < size; ++i) {
			if (r == null) {r = multiply(array[i], v2.array[i]);}
			else {
				T tmp = multiply(array[i], v2.array[i]);
				r = add(r, tmp);
			}
		}
		for (int i=0; i < NB_THREADS; ++i) {
			try {
				thread_tab[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		r = add(r, res);
		return r;
	}
	
	public void print_vect() { //Affichage du vecteur
		if (size == 0) {
			System.out.println("Array: []");
		}
		else {
			System.out.print("Array: [");
			for (int i=0; i<size; ++i) {
				System.out.print(array[i]);
				if (i<size-1) {
					System.out.print(", ");
				}
			}
			System.out.println("]");
		}
	}
}
