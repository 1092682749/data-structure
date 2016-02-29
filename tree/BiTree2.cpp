#include<stdio.h>
#define MAXSIZE 20
typedef char TElemType;
typedef struct{
	int llink;
	TElemType data;
	int rlink;
}BiNode;
typedef BiNode BiTree[MAXSIZE+1];//�±�Ϊ0�ĵ�Ԫ�ճ���

//�������������������н���ֵ��һ���ַ���������ַ���ʾ������������������ʾ�Ķ�����T
void createBiTree(BiTree &T, int &root, int &i){
	TElemType e;
	scanf("%c", &e);
	if(e!='#'){
		if(e!='.'){//����ĵ�ǰ�ڵ㲻�ǡ�����������ʵ���
			T[i].data = e;
			//T[i].llink = 0;
			//T[i].rlink = 0;
			root = i;
			createBiTree(T, T[root].llink, ++i);
			createBiTree(T, T[root].rlink, ++i);
		}else{
			root = 0;//����ĵ�ǰ�ڵ��ǡ��������������㣬���Ӧָ��������Ϊ0
			i--;//��̬�����±���ˣ���Ϊ����û�н���ֻ��ʵ�ڵ������
		}
	}
}
//����������������������ң����ݹ��㷨��
void preOrderPrint(BiTree T, int root){
	if(root){//���ڵ㲻Ϊ��
		printf("%c ", T[root].data);
		preOrderPrint(T, T[root].llink);
		preOrderPrint(T, T[root].rlink);
	}
}

//����������������������ң����ǵݹ��㷨��
void preOrderPrint2(BiTree T, int root){
	//BiNode s[MAXSIZE];//ά��һ��ջ��������¼�����Ľڵ�
	int s[MAXSIZE];//ά��һ��ջ��������¼�����Ľڵ�
	int top = 0;//ָ��ջ��Ԫ�ص���һ��λ�ã���ʼʱtop = 0
	int pointer = root;//pointerָ��ǰ��ĸ��ڵ�
	while(pointer || top){
		if(pointer){//���ڵ㲻Ϊ��
			printf("%c ", T[pointer].data);
			//s[top++] = T[pointer];//���ڵ���ջ
			s[top++] = pointer;//���ڵ���ջ
			pointer = T[pointer].llink;//�Ҹ��ڵ������
		}else{//���ڵ�Ϊ��
			//BiNode topElem = s[--top];//ջ��Ԫ�س�ջ������һ��ĸ��ڵ�		
			//pointer = topElem.rlink;
			int topElemPt = s[--top];//ջ��Ԫ�س�ջ������һ��ĸ��ڵ�
			pointer = T[topElemPt].rlink;
		}
	}
}

//����������������󡢸����ң����ݹ��㷨��
void inOrderPrint(BiTree T, int root){
	if(root){//���ڵ㲻Ϊ��		
		inOrderPrint(T, T[root].llink);
		printf("%c ", T[root].data);
		inOrderPrint(T, T[root].rlink);
	}
}

//����������������󡢸����ң����ǵݹ��㷨��
void inOrderPrint2(BiTree T, int root){
	//BiNode s[MAXSIZE];//ά��һ��ջ��������¼�����Ľڵ�
	int s[MAXSIZE];//ά��һ��ջ��������¼�����Ľڵ�
	int top = 0;//ָ��ջ��Ԫ�ص���һ��λ�ã���ʼʱtop = 0
	int pointer = root;//pointerָ��ǰ��ĸ��ڵ�
	while(pointer || top){
		if(pointer){//���ڵ㲻Ϊ��
			//s[top++] = T[pointer];//���ڵ���ջ
			s[top++] = pointer;//���ڵ���ջ
			pointer = T[pointer].llink;//�Ҹ��ڵ������
		}else{//���ڵ�Ϊ��
			//BiNode topElem = s[--top];//ջ��Ԫ�س�ջ������һ��ĸ��ڵ�
			//printf("%c ", topElem.data);
			//pointer = topElem.rlink;
			int topElemPt = s[--top];//ջ��Ԫ�س�ջ������һ��ĸ��ڵ�
			printf("%c ", T[topElemPt].data);
			pointer = T[topElemPt].rlink;
		}
	}
}
//������������������ҡ��������ݹ��㷨��
void postOrderPrint(BiTree T, int root){
	if(root){//���ڵ㲻Ϊ��
		postOrderPrint(T, T[root].llink);
		postOrderPrint(T, T[root].rlink);
		printf("%c ", T[root].data);
	}
}

//������������������ҡ��������ǵݹ��㷨��
void postOrderPrint2(BiTree T, int root){
	//BiNode s[MAXSIZE];//ά��һ��ջ��������¼�����Ľڵ�
	int s[MAXSIZE];//ά��һ��ջ��������¼�����Ľڵ�ָ��
	int top = 0;//ָ��ջ��Ԫ�ص���һ��λ�ã���ʼʱtop = 0
	int pointer = root;//pointerָ��ǰ��ĸ��ڵ�

	while(pointer || top){
		if(pointer){//���ڵ㲻Ϊ��
			//s[top++] = T[pointer];//���ڵ���ջ
			s[top++] = pointer;//���ڵ�ָ����ջ
			pointer = T[pointer].llink;//�Ҹ��ڵ������
		}else{//���ڵ�Ϊ��
			//BiNode topElem = s[top-1];//ȡ��ջ��Ԫ�أ�����һ��ĸ��ڵ�
			int topElemPt = s[top-1];//ȡ��ջ��Ԫ��ָ�룬����һ��ĸ��ڵ�ָ��
			if(topElemPt > 0){//��ǰ����ڵ����������û�б����ʹ�����������������������������ѱ�������־
				pointer = T[topElemPt].rlink;
				s[top-1] = -s[top-1];
			}else{
				//BiNode topElem = s[--top];//ջ��Ԫ�س�ջ������һ��ĸ��ڵ�
				topElemPt = -topElemPt;//��ԭ
				printf("%c ", T[topElemPt].data);
				top--;
			}
		}
	}
}


typedef BiNode QElemType;
typedef struct{
	//QElemType data[20];
	QElemType data[20];
	int f;//ָ���ͷԪ��
	int r;//ָ���βԪ�ص���һ��λ��
}SqQueue;

//��ʼ��һ���ն���
void initQueue(SqQueue &Q){
	Q.f = Q.r = 0;
}

//����α��������������ϵ��¡������ң�
void hierarchicalTraversePrint(BiTree T, int root){
	SqQueue Q;//ά��һ�����У�����δ��ϵ��¡������Ҵ�Ŷ������ĸ����ڵ㣨ʵ�����ǰ�������������㷨ʵ�ֲ�α�����
	initQueue(Q);
	//BiNode queue[20];
	
	//���ڵ����
	Q.data[Q.r] = T[root];
	Q.r++;
	while(Q.f != Q.r){
		//�Ƚ���ͷԪ�ص����ӣ�ʵ�ڵ㣩���
		if(Q.data[Q.f].llink){
			Q.data[Q.r] = T[Q.data[Q.f].llink];
			Q.r++;
		}
		//����ͷԪ�ص��Һ��ӣ�ʵ�ڵ㣩���
		if(Q.data[Q.f].rlink){
			Q.data[Q.r] = T[Q.data[Q.f].rlink];
			Q.r++;
		}
		//��ӡ�����ʣ���ͷԪ�أ����������
		printf("%c ", Q.data[Q.f].data);
		Q.f++;
	}
}
//������������
int getBiTreeDepth(BiTree T, int root){
	if(!root)//���ڵ�Ϊ����
		return 0;
	int leftTreeDepth = getBiTreeDepth(T, T[root].llink);
	int rightTreeDepth = getBiTreeDepth(T, T[root].rlink);
	return leftTreeDepth > rightTreeDepth ? (leftTreeDepth + 1) : (rightTreeDepth + 1);
}

//��������Ľ����
int getBiTreeSize(BiTree T, int root){
	if(!root)
		return 0;
	int leftTreeSize = getBiTreeSize(T, T[root].llink);
	int rightTreeSize = getBiTreeSize(T, T[root].rlink);
	return leftTreeSize + rightTreeSize + 1;
}

//��������ķ������������Ҷ�ӽڵ���
int getBiTreeLeafNodesNum(BiTree T, int root){
	if(!root)
		return 0;
	else{//���ڵ㲻Ϊ����
		if(!T[root].llink && !T[root].rlink){//�����ǰ���ڵ�����Һ��Ӿ���Ϊ��
			return 1;
		}
		int leftTreeLeafNodesNum = getBiTreeLeafNodesNum(T, T[root].llink);
		int rightTreeLeafNodesNum = getBiTreeLeafNodesNum(T, T[root].rlink);
		return leftTreeLeafNodesNum + rightTreeLeafNodesNum;
	}
}

void main(){
	BiTree tree;
	int root = 1;//���ڵ��λ��
	printf("�밴�������������������ڵ���#�Ž����������õ�Ŵ��棺\n");
	int pos = 1;//���Ƽ��뾲̬�����λ��
	createBiTree(tree, root, pos);	

	
	printf("���������ӡ������(�ݹ��㷨):\n");
	preOrderPrint(tree, root);
	printf("\n");
		

	printf("���������ӡ������(�ǵݹ��㷨):\n");
	preOrderPrint2(tree, root);
	printf("\n");
	

	printf("���������ӡ������(�ݹ��㷨):\n");
	inOrderPrint(tree, root);
	printf("\n");

	printf("���������ӡ������(�ǵݹ��㷨):\n");
	inOrderPrint2(tree, root);
	printf("\n");
	
	
	printf("���������ӡ������(�ݹ��㷨):\n");
	postOrderPrint(tree, root);
	printf("\n");

	printf("���������ӡ������(�ǵݹ��㷨):\n");
	postOrderPrint2(tree, root);
	printf("\n");
	
	
	printf("����α�����ӡ������(�ǵݹ��㷨):\n");
	hierarchicalTraversePrint(tree, root);
	printf("\n");
	

	
	int depth = getBiTreeDepth(tree, root);
	printf("�ö����������Ϊ:%d\n", depth);
	

	int size = getBiTreeSize(tree, root);
	printf("�ö������Ľ����Ϊ:%d\n", size);
	
	int leafNodesNum = getBiTreeLeafNodesNum(tree, root);
	printf("�ö�������Ҷ�ӽ����Ϊ:%d\n", leafNodesNum);
	
}
