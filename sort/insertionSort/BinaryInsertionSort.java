package sort.insertionSort;

public class BinaryInsertionSort {

	/**
	 * @param args
	 */
	//��˳���L���۰��������,�����۰���ҿ����ҵ�Ҫ�����λ��
	public static void binaryInsertSort(int[] L){
		for(int i = 2; i <= L.length-1; i++){		
			//�����۰�����ҵ�Ҫ�����λ��
			int low = 1, high = i-1;//��1->i-1�������������в����i��Ԫ�أ�ʹ֮��Ϊ1->i������������
			L[0] = L[i];//�ݴ�Ҫ�����Ԫ��
			while(low <= high){
				int mid = (low+high)/2;
				if(L[0] < L[mid])
					high = mid -1;
				else
					//L[0] >= L[mid]
					low = mid+1;//���ڵ��ɴ��ڴ�����������ֵ����ֵ�ͻ����ں��棬�Ӷ�����ȶ���
			}
			//��ʱhigh = low-1����high+1��low��λ�ü�ΪҪ�����λ��
			for(int j = i-1; j >= low; j--)
				L[j+1] = L[j];
			L[low] = L[0];
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 53, 27, 36, 15, 69, 42}; //0�ŵ�Ԫδʹ��
		binaryInsertSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
