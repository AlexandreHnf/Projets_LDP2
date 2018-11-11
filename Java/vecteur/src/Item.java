
public class Item<T extends Number>{

	//private T array[];
	T data;
	//private int size;
	
	public Item(T newNum) {
//		if (newArray instanceof Integer) {
//			System.out.println("Constructeur avec array");
//			//array = new int[newArray.intValue().length];
//			@SuppressWarnings("unchecked")
//			T[] array=(T[])new Object[newArray.length];
//			for (int i=0; i < newArray.length; ++i) {
//				array[i] = newArray[i];
//			}
//			size = newArray.length;
//		}
//		if (newNum instanceof Integer) {
//			System.out.println("Constructeur avec un T");
//			Integer nnum = newNum.intValue();
//			num = (T)nnum;
//		}
		this.data = newNum;
		
	}
	public void printv() {
		System.out.print("num: ");
		System.out.println(num);
	}
}
