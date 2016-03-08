package sort.swampSort;

public class QuickSort {

	/**
	 * @param args
	 */
	//����˳���L���ֱ�L[low...high]�ļ�¼�������¼��Ϊ������������Ӧ�����ڵ�λ��
	//��ʱ������ǰ��ļ�¼��С�����ᣬ�������ļ�¼����������
	//��һ�˿���
	public static int partion(int[] L, int low, int high){
		L[0] = L[low];//L[0]�ݴ�����,�ֱ��еĵ�һ��Ԫ��һ��Ĭ��Ϊ������
		while(low < high){
			while(low < high && L[0] <= L[high])
				high--;
			//��ʱL[high]>L[0]
			L[low++] = L[high];
			while(low < high && L[0] >= L[low])
				low++;
			//��ʱL[low]>L[0]
			L[high--] = L[low];
		}
		//ѭ������ʱ��һ����low==high
		L[low] = L[0];
		return low;
	}
	
	//�ݹ����ƵĿ�������
	public static void quickSort(int[] L, int low, int high){
		//��˳���L��������L[low...high]����������
		if(low < high){
			int m = partion(L, low, high);
			quickSort(L, low, m-1);
			quickSort(L, m+1, high);
		}
		//low==highʱ��˵���������н���һ��Ԫ���ˣ���Ȼ�Ѿ�����Ӧ��Ϊÿһ��ݹ�Ľ���
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 46, 55, 13, 42, 94, 5, 17, 70}; //0�ŵ�Ԫδʹ��
		quickSort(test, 1, test.length-1);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
