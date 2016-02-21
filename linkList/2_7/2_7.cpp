#include<stdio.h>
//˳���1.ʹ�ö�̬�����һά����
//        2.ʹ�þ�̬�����һά����
//��ʵ��ʹ�þ�̬����
#define LIST_INIT_SIZE 100
typedef int ElemType;

typedef struct SqList{
	ElemType data[LIST_INIT_SIZE];
	int len;
}SqList;

//�ڵ�i��1<=i<=n����Ԫ��֮ǰ����һ��Ԫ�أ���Ҫ����ƶ�n-i+1��Ԫ�أ�
//������������Ҫ�ƶ��κ�Ԫ�أ��ɹ������λ����n+1����
//�Ӻ���ǰ�Ҳ����λ�ã�����i��ʾλ��,��i��Ԫ�ص��±�i-1,i�ķ�Χ��1~n+1
//ʱ�临�Ӷȣ�O(n)
void insertSqList(SqList &L,int i, ElemType e){
	if(i>L.len+1||i<1){
		printf("����λ�ò������Ϸ�");
	}else if(L.len >= LIST_INIT_SIZE){
		printf("���������޷������");
	}else{
		int j = L.len-1;
		for(j;j>=i-1;j--){
			L.data[j+1] = L.data[j];//�Ӻ���ǰ�ƶ�Ԫ��
		}
		L.data[i-1] = e;
		L.len++;
	}
}
//ɾ����i(1<=i<=L.len)��Ԫ��,����e������ֵ
//ʱ�临�Ӷȣ�O(n)
void delSqList(SqList &L, int i, ElemType &e){
	if(i>L.len||i<1){
		printf("ɾ��λ�ò������Ϸ�");
	}
	int j = i-1;//j��Ҫ��ɾ��Ԫ�ص��±�
	e = L.data[j];
	printf("ɾ���ĵ�%dλ�õ�������%d\n",i,e);
	for(j;j<L.len-1;j++){
		L.data[j] = L.data[j+1];
	}
	L.len--;
}


//��ӡ���˳�����Ա�
void printSqList(SqList L){
	printf("��ӡ���Ա�:");
	for(int i = 0; i < L.len; i++){
		printf("%d ",L.data[i]);
	}
	printf("\n");
}

//����һ������Ϊn��˳�����Ա�
void createSqList(SqList &L, int n){
	printf("������%d����:\n", n);
	for(int i = 0; i < n; i++){
		scanf("%d",&L.data[i]);
	}
	L.len = n;
	//printSqList(L);
}

//����һ�����Ա�ʵ����Ҳ�ǲ�����һ���ձ������Ԫ�صĹ���
//���Կ����ò����㷨ʵ�����Ա�Ĵ���
void createUseInsertSqList(SqList &L, int n){
	printf("������%d����:\n", n);
	int x;
	for(int i = 0; i < n; i++){
		scanf("%d", &x);
		insertSqList(L,i+1,x);
	}
	L.len = n;
}
//��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����У���Ҫ��La��Lb�鲢Ϊһ���µ����Ա�Lc����Lc�е�����Ԫ����Ȼ��ֵ�ǵݼ���������
//ʵ�֣�Ϊ����Lc�ķǵݼ�������a<=bʱ��c=a;��a>bʱ��c=b
//ʱ�临�Ӷȣ�O(La.len+Lb.len)
//ʵ����La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),Lc=(2,3,5,6,8,8,9,11,11,15,20),ע�Ⲣû��ȥ�أ�ֻ�����˺ϲ�
void mergeSqList(SqList La, SqList Lb, SqList &Lc){
	int i=0, j=0;
	Lc.len=La.len+Lb.len;//��ʼ��Lc
	int k =0;
	while(i<La.len&&j<Lb.len){
		if(La.data[i]<=Lb.data[j]){
			Lc.data[k]=La.data[i];
			i++;
			k++;
		}else{
			Lc.data[k]=Lb.data[j];
			j++;
			k++;
		}
	}
	while(i<La.len){
		Lc.data[k]=La.data[i];
		i++;
		k++;
	}
	while(j<Lb.len){
		Lc.data[k]=Lb.data[j];
		j++;
		k++;	
	}
}

//�����������Ա�La,Lb�ֱ��ʾ��������A��B(���Ա��е�����Ԫ�ؼ�Ϊ����Ԫ��)����Ҫ��һ���µļ���A=AUB
//ʵ�֣���չ���Ա�La,����Lb������ȡ��ÿ������Ԫ�أ�����ֵ��La�н��в�ã�����La�в����������֮��
//ʵ����La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),union�Ժ�La=(3,5,8,11,2,6,9,15,20),la.len=9,ע����ȥ�أ�����care�󲢼��Ժ��˳��
//ʱ�临�Ӷȣ�O(La.len * Lb.len)
int locateElem(SqList L, ElemType e){//�������Ա�L�е�һ��������Ԫ��e���(Ҳ�����������ȽϷ���)��Ԫ�ص�λ��(1~L.len)��
									//��û�ҵ��򷵻�0���ҵ��򷵻�λ��,ʱ�临�Ӷȣ�O(L.len)
									
	int i = 1;//i��ʾλ��
	while(i<=L.len&&L.data[i-1]!=e){
		i++;
	}
	if(i<=L.len)
		return i;
	else
		return 0;
}
void unionSqList(SqList &La, SqList Lb){
	for(int i = 0; i < Lb.len; i++){
		ElemType e = Lb.data[i];
		if(!locateElem(La, e)){//e��La�в�����//O(La.len)
			insertSqList(La,La.len+1, e);//�������ڱ�β���룬���Բ��������ʱ�临�Ӷ�����޹�
		}
	}
}

//��merge��һ��ѭ��������switch������if��䣬���ֳ�3���������a=bʱ��ֻ������֮һ���뵽Lc�У����ʱ�㷨��ɵĲ�����
//union��ȫ��ͬ����ʱ�临�Ӷ�ȴ��ͬ����ԭ���ж���
//1.La,Lb�е�Ԫ�ض�����ֵ������ͬһ������Ԫ�ز��ȣ������Lb��ÿ��Ԫ�أ�����Ҫ��La�дӱ�ͷ����β����ȫ������
//2.�������±�Lc��ʾ������������������ʵ���Ͻ��������ơ���ɣ�����������뵼���ƶ�һϵ��Ԫ��
//�ɴ˿ɼ����������Ա��ʾ���ϲ����м��ϵĸ������㣬Ӧ�ȶԱ��е�Ԫ�ؽ���������ɽ��ͼ��������ʱ�临�Ӷ�

void main(){
	
	//��ʼ��һ���յ����Ա�
	SqList L;
	L.len=0;
	
	createSqList(L, 5);//����һ�����Ա�
	printSqList(L);
	//printf("%d\n",locateElem(L, 6));
	

	/*
	createUseInsertSqList(L, 5);
	printSqList(L);
	*/

	/*
	//��ɲ��빦��
	printf("��Ҫ��������ݺ�λ��(1~%d)(�磺�ڵ�2��λ�ò���10�����룺10��2)��",L.len+1);
	int elem, pos;
	scanf("%d,%d",&elem,&pos);
	insertSqList(L,pos,elem);
	printSqList(L);
	*/

	/*
	//���ɾ������
	printf("��Ҫɾ�������ݵ�λ��(�磺Ҫɾ����2��λ�õ�����������(1~%d)��2)��",L.len);
	int pos;
	ElemType elem;
	scanf("%d",&pos);
	delSqList(L,pos,elem);
	printSqList(L);
	*/

	/*
	//���merge����
	SqList La, Lb, Lc;
	//��ʼ�����Ա�
	La.len = Lb.len =Lc.len = 0;
	printf("�������Ա�La:\n");
	createSqList(La, 4);//�������Ա�La
	printSqList(La);
	printf("�������Ա�Lb:\n");
	createSqList(Lb, 7);//�������Ա�Lc
	printSqList(Lb);
	mergeSqList(La, Lb, Lc);
	printSqList(Lc);
	*/

	/*
	//���union����
	SqList La, Lb;
	//��ʼ�����Ա�
	La.len = Lb.len = 0;
	printf("�������Ա�La:\n");
	createSqList(La, 4);//�������Ա�La
	printSqList(La);
	printf("�������Ա�Lb:\n");
	createSqList(Lb, 7);//�������Ա�Lc
	printSqList(Lb);
	unionSqList(La, Lb);
	printSqList(La);
	printf("La�ĳ���Ϊ%d\n",La.len);
	*/
}