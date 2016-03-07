package search;

public class StaticSearch {

	/**
	 * @param args
	 */
	//��˳���ST��˳�������ؼ��ֵ���key������Ԫ�أ����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã����򷵻�0
	public static int searchSeq(int[] st, int key){//st���0�ŵ�Ԫ��ʹ��
		//�Ӻ���ǰ�ң�����0�ŵ�Ԫ����"������"	
		int i = st.length - 1;
		st[0] = key;//���ü�����
		while(st[i] != key){
				i--;
		}
		return i;
	}
	
	//�������st���۰������ؼ��ֵ���key������Ԫ�أ����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã����򷵻�0
	public int searchBin(int[] st, int key){//st���0�ŵ�Ԫ��ʹ��
		int low = 1, high = st.length - 1, mid = (low + high)/2;
		while(low <= high){
			if(st[mid] == key)
				return mid;
			else if(st[mid] > key)
				high = mid - 1;
			else
				//st[mid] < key
				low = mid + 1;
		}
		return 0;//low > highʱ��������ʧ��
	}
	
	public static int searchIndex(int[][] index, int[] st, int key){//Ϊ���㣬index[],st[]��ʹ��0�ŵ�Ԫ
		//�۰����������
		int low = 0, high = index[0].length - 1;
		int block = index[0].length, elemsInBlock = st.length / block;
		int start, mid = 0;
		while(low < high){
			mid = (low + high)/2;		
			if(index[0][mid] == key){
				start = mid;
				break;
			}else if(index[0][mid] > key)
				high = mid;
			else
				//index[0][mid] < key
				low = mid + 1;
		}
		start = index[1][low];
		
		//��startλ�ÿ�ʼ˳�����
		int i = 0;
		while(i < elemsInBlock && st[start+i] != key){
			i++;
		}
		if(i == elemsInBlock)
			return -1;
		else
			return start+i;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		//˳����Ҳ���
		int st[] = {0, 10, 20, 40, 80, 30, 60, 25};//0�ŵ�Ԫ��ʹ��
		int key = 75;
		int result = searchSeq(st, key);
		if(result > 0)
			System.out.println("����" + key + "�ɹ�,�ڲ��ұ��е�λ����" + result);
		else
			System.out.println("����" + key + "ʧ��");
		
		key = 80;
		result = searchSeq(st, key);
		if(result > 0)
			System.out.println("����" + key + "�ɹ�,�ڲ��ұ��е�λ����" + result);
		else
			System.out.println("����" + key + "ʧ��");
		*/
		
		/*
		//�����Ķ��ֲ��Ҳ���
		int st[] = {0, 8, 17, 25, 44, 68, 77, 98, 100, 115, 125};//0�ŵ�Ԫ��ʹ��
		int key = 17;
		int result = searchSeq(st, key);
		if(result > 0)
			System.out.println("����" + key + "�ɹ�,�ڲ��ұ��е�λ����" + result);
		else
			System.out.println("����" + key + "ʧ��");
		
		key = 120;
		result = searchSeq(st, key);
		if(result > 0)
			System.out.println("����" + key + "�ɹ�,�ڲ��ұ��е�λ����" + result);
		else
			System.out.println("����" + key + "ʧ��");
		*/
		
		
		
		//����˳����ң��ֽзֿ���ң���˳����ҵ�һ�ָĽ�����������ʹ���۰���ң�����ֻ����˳�����
		int[][] index = {{20, 53, 89},
				         {0, 5, 10}
		};//������
		int[] st = {18, 12, 8, 5, 20, 51, 36, 22, 29, 53, 89, 60, 72, 66, 76};//���ұ�
		int key = 22;
		int result = searchIndex(index, st, key);
		if(result > -1)
			System.out.println("����" + key + "�ɹ�,�ڲ��ұ��е�λ����" + result);
		else
			System.out.println("����" + key + "ʧ��");
		key = 6;
		result = searchIndex(index, st, key);
		if(result > -1)
			System.out.println("����" + key + "�ɹ�,�ڲ��ұ��е�λ����" + result);
		else
			System.out.println("����" + key + "ʧ��");
	}

}
