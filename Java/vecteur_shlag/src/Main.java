/* [INFO-F202] Langages de Programmations 2 - JAVA
 * Auteur: Alexandre Heneffe
 * Matricule: 000440761
 */

public class Main {

	public static void main(String[] args) {
		System.out.println("Test avec Integer: ");
		
		Integer[] l1 = new Integer[] {1,1,1,1,1,1};
		Integer[] l2 = new Integer[] {2,2,2,2,2,2};
		//Integer[] l1 = new Integer[] {1,2,3,4,5,6};
		//Integer[] l2 = new Integer[] {7,8,9,10,11,12};
		vect0<Integer> V1 = new vect0<Integer>(l1);
		vect0<Integer> V2 = new vect0<Integer>(l2);
		V1.print_vect();
		V2.print_vect();
		
		V1.add(V2);
		System.out.print("Somme vectorielle de V1 et V2: ");
		V1.print_vect();
		System.out.print("Produit scalaire de V1 et V2: ");
		System.out.println(V1.prod_scal(V2));
		
		
		System.out.println("Test avec Double: ");
		Double[] l3 = new Double[] {4.3,4.3,4.3,4.3};
		Double[] l4 = new Double[] {2.3,2.3,2.3,2.3};
		vect0<Double> V3 = new vect0<Double>(l3);
		vect0<Double> V4 = new vect0<Double>(l4);
		V3.print_vect();
		V4.print_vect();
		
		V3.add(V4);
		V3.print_vect();
		System.out.print("Produit scalaire de V3 et V4: ");
		System.out.println(V3.prod_scal(V4));
		
	}
}
