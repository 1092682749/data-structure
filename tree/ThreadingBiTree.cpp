#include<stdio.h>
#include<stdlib.h>

//#define Link 0//ָ���־
//#define Thread 1//������־
typedef char TElemType; 
//��������������
typedef enum PointerTag {Link, Thread};//����child�����ͣ�link��ʾ��ָ�룬ָ���ӽ�㣬thread��ʾ��������ָʾǰ�����̽��
//ö������һ�����ϣ������е�Ԫ��(ö�ٳ�Ա)��һЩ���������ͳ�����Ԫ��֮���ö��Ÿ���
//��һ��ö�ٳ�Ա��Ĭ��ֵΪ���͵�0������ö�ٳ�Ա��ֵ��ǰһ����Ա�ϼ�1��
//������Ϊ�趨ö�ٳ�Ա��ֵ���Ӷ��Զ���ĳ����Χ�ڵ�������

typedef struct ThrBiNode{
	TElemType data;
	ThrBiNode *lchild, *rchild;//���Һ���ָ��
	PointerTag lTag, rTag;//���ұ�־
}ThrBiNode, *ThrBiTree;


/*Ϊ����������������Ա�Ĵ洢�ṹ���ڶ�����������������Ҳ���һ��ͷ��㣬����
��lchild���ָ��ָ��������ĸ���㣬��rchild���ָ��ָ���������ʱ���ʵ����һ����㣻��֮����
�����������������еĵ�һ������lchild��ָ������һ���ڵ��rchild���ָ���ָ��ͷ��㡣��ñ�Ϊ������������һ��˫�����������ȿ��Դӵ�һ�������
˳��̽��б�����Ҳ���Դ����һ�������˳ǰ�����б�����
*/


//���������������������(�󡢸�����)
void inThreading(ThrBiTree T, ThrBiTree &pre){////////////////////////////////////////////////TǰҪ��ȡ��ַ����test
	if(T){
		inThreading(T->lchild, pre);//������������

		if(!T->lchild){//��ǰ��������Ϊ��
			T->lTag = Thread;
			T->lchild = pre;
		}else{
			T->lTag = Link;
		}

		if(!pre->rchild){//ǰ�������Һ���Ϊ��
			pre->rTag = Thread;
			pre->rchild = T;
		}else{
			pre->rTag = Link;
		}
		pre = T;		
		inThreading(T->rchild, pre);//������������
	}
}

//�������������T�������� ������������Thrtָ��ͷ���
void inOrderThreading(ThrBiTree T, ThrBiTree &Thrt){
	//��ʼ����������Ϊ�佨��һ��ͷ���
	Thrt = (ThrBiTree)malloc(sizeof(ThrBiNode));
	Thrt->lTag = Link;
	Thrt->rTag = Thread;
	//Thrt->rchild = Thrt;//��ָ���ָ����Ϊ��TΪ�����Ļ���ֻ��ָ�������if��䣬��ôThrt->rchild
	if(!T){//���������Ϊ��������Thrt->lchildָ���ָ
		Thrt->lchild = Thrt;
		Thrt->rchild = Thrt;//��ָ���ָ
	}else{
		Thrt->lchild = T;
		ThrBiNode *pre = Thrt;//preָ����ָ��ǰ����ǰ�����
		inThreading(T, pre);
		//����Ϊ���һ������������
		//��ʱpreӦָ�����һ�����
		pre->rTag = Thread;
		pre->rchild = Thrt;//���һ������rchild��ָ���ָ
		Thrt->rchild = pre;//ͷ����rchild��ָ��ָ�����һ�����
	}
}

//Tָ��ͷ��㣬ͷ����lchild����ָ��ָ��������ĸ����
//���������ӡ����������T���ǵݹ��㷨��
void inOrderTraversePrint(ThrBiTree T){
	ThrBiNode *p = T->lchild;//pָ������
	
	while(p != T){//�������������ʱ��p == T
		while(p->lTag == Link){
			p = p->lchild;
		}
		//��ʱpָ������������еĵ�һ����㣨�����µĽ�㣩

		printf("%c ", p->data);//��ӡ�����ʣ���������Ϊ�յĽ��

		while(p->rTag == Thread && p->rchild != T){
			p = p->rchild;
			printf("%c ", p->data);//���ʺ�̽��
		}
		//��p��ָ����rchildָ����Ǻ��ӽ�����������ʱ��p�ĺ��Ӧ�������������������µĽ�㣬��������������ʱ���ʵĵ�һ���ڵ�
		p = p->rchild;
	}
	printf("\n");
}


//�����������н���һ�Ŷ�����,'.'�������
//��������1��abc..de.g..f...#
//��������2:-+a..*b..-c..d../e..f..#
void createBiTreeByPreOrder(ThrBiTree &T){
	//�������������������нڵ��ֵ��һ���ַ���������ַ���ʾ������������������ʾ�Ķ�����
	//ע�⣺��������ַ���������#�ţ�Ϊn��������Ӧ�Ŀ�������ž�Ӧ����n+1��
	char ch;
	scanf("%c", &ch);
	if(ch != '#'){
		if(ch == '.'){
			T = NULL;
		}else{
			T = (ThrBiNode *)malloc(sizeof(ThrBiNode));
			T->data = ch;
			createBiTreeByPreOrder(T->lchild);
			createBiTreeByPreOrder(T->rchild);
		}
	}
}
void main(){
	ThrBiTree T;
	printf("�밴�������������������ڵ��ֵ���Կո��ʾ��������#�Ž���:\n");
	createBiTreeByPreOrder(T);//����������
	
	ThrBiTree Thrt;
	inOrderThreading(T, Thrt);//��������T����������

	inOrderTraversePrint(Thrt);//�������������������ͨ��������������������Ա�һ����
	//��Ȼ֮ǰ�Ĳ���������ֱ�Ӹ��ݶ������Ľṹ���б�����Ȼ���ԣ���Ρ����򡢺�������
}