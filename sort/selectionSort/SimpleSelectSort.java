package sort.selectionSort;

public class SimpleSelectSort {

	/**
	 * @param args
	 */
	public static int selectMin(int[] L, int i){
		int min = L[i], min_k = i;
		for(int k = i+1; k <= L.length-1; k++)
			if(L[k] < min){
				min = L[k];
				min_k = k;
			}
		return min_k;
	}
	
	//��˳���L����ѡ������
	public static void selectSort(int[] L){
		//��i�������������(����i->n��)ѡ��һ��min���뵽i��λ����
		for(int i = 1; i < L.length-1; i++){//i��ȡֵ��1...n-1
			int j = selectMin(L, i);//��L[i...n]��ѡ��һ��min�����������±�
			if(j!=i){//����L[i]��L[j]
				L[0] = L[i];
				L[i] = L[j];
				L[j] = L[0];
			}
				
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 8, 3, 9, 1, 6}; //0�ŵ�Ԫδʹ��
		selectSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}

}
