package sort.mergingSort;
public class MergeSort {
	/**
	 * @param args
	 */
	public static void merge(int[] L, int s, int m, int n){
		//�������L[s...m]��L[m+1...n]�鲢Ϊ�����L[s...n],������ʱ���֣�����ĸ��棩
		int i=s, j=m+1, k=0;
		int[] tmp = new int[L.length];
		for(k = s; i<=m && j<=n; k++){
			if(L[i] <= L[j])
				tmp[k] = L[i++];
			else
				tmp[k] = L[j++];
		}
		//����ʣ���Ԫ��
		while(i <= m)
			tmp[k++] = L[i++];
		while(j <= n)
			tmp[k++] = L[j++];
		
		//����ʱ��������Ѿ��ź����Ԫ�ط��ظ�L
		for(k=s; k <= n; k++ )
			L[k] = tmp[k];
	}
	//��L[]�鲢����
	public static void mergeSort(int[] L, int start, int end){
		if(start < end){
			int m = (start+end)/2;//���������л���һ��Ϊ2��Ȼ��2��Ϊ4��4��Ϊ8....����Ҫ������L�ĳ��ȣ�
			//ֱ��ÿ�������н�����һ��Ԫ�أ��Ϳ�ʼ�ϲ�
			mergeSort(L, start, m);//�ݹ�Ľ�L[start...m]�鲢Ϊ�����L[start...m]
			mergeSort(L, m+1, end);//�ݹ�Ľ�L[m+1...end]�鲢Ϊ�����L[m+1...end]
			merge(L, start, m, end);//�������L[start...m]��L[m+1...end]�鲢��L[start...end]
		}
		//��start == endʱ��˵����ʱ��������ֻ��һ��Ԫ�أ����ڴ˺�ÿ2����Ԫ�ؽ���ϲ��ɺ���2��Ԫ�ص�������
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 46, 55, 13, 42, 94, 5, 17, 70}; //0�ŵ�Ԫδʹ��
		mergeSort(test, 1, test.length-1);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
