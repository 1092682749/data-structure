package sort.insertionSort;
public class StraightSort {
	/**
	 * @param args
	 */
	//��˳���L��ֱ�Ӳ�������
	public static void InsertSort(int[] L){
		//�Ƚ���һ��Ԫ�ؿ�����һ������������
		for(int i = 2; i <= L.length-1; i++){
			//���Ѿ������1->i-1���������в����i��Ԫ�أ��Ա�֤��Ȼ���򣬳�Ϊһ��1->i������������
			L[0] = L[i];//������
			int j = i-1;
			/*
			for(; j > 0; j--){//û�����ü����ڣ���Ȼ��j>0��Ϊ�����Ա��������±�Խ��
				if(L[0] < L[j])
					L[j+1] = L[j];
				else
					break;
			}
			*/
			for(; L[0] < L[j]; j--)
				L[j+1] = L[j];//���ü�����
			//��L[0] >= <[j]ʱ����ѭ��������j����һ���Լ���������L[j+1] = L[0]��
			//������Ϊ=������ѭ��ʱ��j����û���Լ�����L[0]����L[j]�ĺ����Ա�֤�ˡ��ȶ��� 
			L[j+1] = L[0];
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 53, 27, 36, 15, 69, 42}; //0�ŵ�Ԫδʹ��
		InsertSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}

}
