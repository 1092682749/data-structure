#include<stdio.h>
#include<stdlib.h>
#define NULL 0
typedef char TElemType;
//��̬��������
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ջ�����ʵ��
#define MAXSIZE 100
typedef BiTNode* SElemType;
typedef struct SqStack{
	SElemType data[MAXSIZE];
	int top;//ָ��ջ��Ԫ��
}SqStack;

//��ʼ����ջ
void initStack(SqStack &s){
	s.top = 0;
}

//��ջ��
bool isEmpty(SqStack s){
	if(s.top == 0){
		//printf("�ǿ�ջ\n");//
		return true;
	}else{
		return false;
	}
}

//��ջ��
bool isFull(SqStack s){
	if(s.top == MAXSIZE){
		return true;
	}
	else{
		return false;
	}
}

//ȡջ��Ԫ��
void getTopElem(SqStack s, SElemType &e){
	if(!isEmpty(s))
		e = s.data[s.top-1];
	else
		printf("��ջΪ��ջ��ȡջ��Ԫ��ʧ��\n");
}

//��ջ
void push(SqStack &s, SElemType e){
	if(!isFull(s)){
		s.data[s.top] = e;
		s.top++;
	}else
		printf("��ջ��������ջ����ʧ��\n");
}

//��ջ
void pop(SqStack &s, SElemType &e){
	if(!isEmpty(s)){
		e = s.data[s.top-1];
		s.top--;
	}
	else
		printf("��ջΪ��ջ����ջ����ʧ��\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//�����������н���һ�Ŷ��������������ж��룺'a', 'b', 'c', '.', '.', 'd', 'e', '.', 'g', '.', '.', 'f', '.', '.', '.' 
//,'.'�������
//����������abc..de.g..f...#
void createBiTreeByPreOrder(BiTree &T){
	//�������������������нڵ��ֵ��һ���ַ���������ַ���ʾ������������������ʾ�Ķ�����
	//ע�⣺��������ַ���������#�ţ�Ϊn��������Ӧ�Ŀ�������ž�Ӧ����n+1��
	char ch;
	scanf("%c", &ch);
	//printf("test:%c\n", ch);
	if(ch != '#'){
		if(ch == '.'){
			T = NULL;
		}else{
			T = (BiTNode *)malloc(sizeof(BiTNode));
			T->data = ch;
			createBiTreeByPreOrder(T->lchild);
			createBiTreeByPreOrder(T->rchild);
		}
	}
}

//���������ӡ�������ĵݹ��㷨(��������)
void preOrderPrint(BiTree T){
	if(T){
		printf("%c ", T->data);
		preOrderPrint(T->lchild);
		preOrderPrint(T->rchild);
	}
}

//���������ӡ�������ķǵݹ��㷨(��������)
void preOrderPrint2(BiTree T){
	SqStack s;
	initStack(s);
	BiTNode *p = T;	
	while(p || !isEmpty(s)){		
		if(p){
			printf("%c ", p->data);
			push(s, p);
			p = p->lchild;
		}else{
			//printStack(s);
			pop(s, p);//ջ��ָ�루��ǰ��ĸ��ڵ�ָ�룩����
			p = p->rchild;
		}
	}
}

//���������ӡ�������ĵݹ��㷨���󡢸����ң�
void inOrderPrint(BiTree T){
	if(T){
		inOrderPrint(T->lchild);
		printf("%c ", T->data);		
		inOrderPrint(T->rchild);
	}
}
//���������ӡ�������ķǵݹ��㷨���󡢸����ң�
void inOrderPrint2(BiTree T){
	SqStack s;
	initStack(s);
	BiTNode *p = T;	
	while(p || !isEmpty(s)){
		if(p){
			push(s, p);
			p = p->lchild;
		}else{
			pop(s, p);//ջ��ָ�루��ǰ��ĸ��ڵ�ָ�룩����
			printf("%c ", p->data);			
			p = p->rchild;
		}
	}
}

//���������ӡ�������ĵݹ��㷨�����ҡ�����
void postOrderPrint(BiTree T){
	if(T){
		postOrderPrint(T->lchild);
		postOrderPrint(T->rchild);
		printf("%c ", T->data);
	}
}

//���������ӡ�������ķǵݹ��㷨�����ҡ�����
void postOrderPrint2(BiTree T){
	SqStack s;
	initStack(s);
	BiTNode *p = T;
	while(p || !isEmpty(s)){
		if(p){
			push(s, p);
			p = p->lchild;
		}else{ 
			BiTNode *top;
			getTopElem(s, top);//ȡ��ջ��Ԫ��
			if(top->data > 0){//ջ��Ԫ�ص���������û�б����ʹ�
				p = top->rchild;
				top->data = -top->data;//���������ѱ�����־
				
			}else{//ջ��Ԫ�ص��������Ѿ����ʹ���
				printf("%c ", -top->data);
				pop(s, top);
				//p = NULL;				
			}
		}		
	}
}

typedef BiTNode* QElemType;
typedef struct{
	QElemType data[20];
	int f;//ָ���ͷԪ��
	int r;//ָ���βԪ�ص���һ��λ��
}SqQueue;
//��ʼ��һ���ն���
void initQueue(SqQueue &Q){
	Q.f = Q.r = 0;
}

//����α��������ϵ��£������ң���
void hierarchicalTraversePrint(BiTree T){
	//QElemType queue[20];//ά��һ��˳����У���������δ��ÿ��ʵ�ڵ㣬ʵ������һ�������������
	//int f = 0, r = 0;//��ͷ��β
	SqQueue Q;//ά��һ��˳����У���������δ��ÿ��ʵ�ڵ㣬ʵ������һ�������������
	initQueue(Q);
	//ע�⣬����д��int f, r = 0;����fû�б���ֵ
	if(T){
		//queue[0] = T;//���ڵ����
		Q.data[Q.r] = T;//���ڵ����
		Q.r++;
	}
	while(Q.f != Q.r){
		//�Ƚ���ͷԪ�ص������������
		if(Q.data[Q.f]->lchild){
			Q.data[Q.r] = Q.data[Q.f]->lchild;
			Q.r++;
		}
		//����ͷԪ�ص��Һ����������
		if(Q.data[Q.f]->rchild){
			Q.data[Q.r] = Q.data[Q.f]->rchild;
			Q.r++;
		}
		//Ȼ���ӡ�����ʣ���ͷԪ��,������ͷԪ�س���		
		printf("%c ", Q.data[Q.f]->data);
		Q.f++;//��ͷԪ�س���
	}
	/*
	while(f!=r){
		//�Ƚ���ͷԪ�ص������������
		if(queue[f]->lchild){
			queue[r] = queue[f]->lchild;
			r++;
		}
		//����ͷԪ�ص��Һ����������
		if(queue[f]->rchild){
			queue[r] = queue[f]->rchild;
			r++;
		}
		//Ȼ���ӡ�����ʣ���ͷԪ��,������ͷԪ�س���		
		printf("%c ", queue[f]->data);
		f++;//��ͷԪ�س���	
	}
	*/
	printf("\n");
}

//������������
int getBiTreeDepth(BiTree T){
	if(!T){
		return 0;
	}
	int leftTreeDepth = getBiTreeDepth(T->lchild);
	int rightTreeDepth = getBiTreeDepth(T->rchild);
	return leftTreeDepth > rightTreeDepth ? (leftTreeDepth+1) : (rightTreeDepth+1);
}

//��������Ľڵ���
int getBiTreeSize(BiTree T){
	if(!T)
		return 0;
	int leftTreeSize = getBiTreeSize(T->lchild);
	int rightTreeSize = getBiTreeSize(T->rchild);
	return leftTreeSize + rightTreeSize + 1;
}

//���������Ҷ�ӽڵ���
void getBiTreeLeafNodesNum(BiTree T, int &count){
	if(T){
		if(!T->lchild && !T->rchild)
			count++;
		//else{
			getBiTreeLeafNodesNum(T->lchild, count);
			getBiTreeLeafNodesNum(T->rchild, count);
		//}
	}
}

//���������Ҷ�ӽڵ���
int getBiTreeLeafNodesNum2(BiTree T){
	if(T){
		if(!T->lchild && !T->rchild)
			return 1;
		else{
			int leftTreeLeafNodesNum = getBiTreeLeafNodesNum2(T->lchild);
			int rightTreeLeafNodesNum = getBiTreeLeafNodesNum2(T->rchild);
			return leftTreeLeafNodesNum + rightTreeLeafNodesNum;
		}
	}else{
		return 0;
	}
}
void main(){
	BiTree T;
	printf("�밴�������������������ڵ��ֵ���Կո��ʾ��������#�Ž���:\n");
	createBiTreeByPreOrder(T);

	
	printf("���������ӡ������:\n");
	preOrderPrint(T);
	printf("\n");
		
	printf("���������ӡ���������ǵݹ��㷨��:\n");
	preOrderPrint2(T);
	printf("\n");

	printf("���������ӡ������:\n");
	inOrderPrint(T);
	printf("\n");	
	
	printf("���������ӡ���������ǵݹ��㷨��:\n");
	inOrderPrint2(T);
	printf("\n");
	
	printf("���������ӡ������:\n");
	postOrderPrint(T);
	printf("\n");

	printf("���������ӡ���������ǵݹ��㷨��:\n");
	postOrderPrint2(T);
	printf("\n");
	
	printf("����α�����ӡ���������ǵݹ��㷨��:\n");
	hierarchicalTraversePrint(T);

	int depth = getBiTreeDepth(T);
	printf("�ö������������Ϊ%d\n", depth);
	

	int size = getBiTreeSize(T);
	printf("�ö��������Ľ����Ϊ%d\n", size);
	
	int leafNodesNum = 0;
	getBiTreeLeafNodesNum(T, leafNodesNum);
	printf("�ö���������Ҷ�ӵ���Ϊ%d\n", leafNodesNum);
	
	int leafNodesNum2 = 0;
	leafNodesNum2 = getBiTreeLeafNodesNum2(T);
	printf("�ö���������Ҷ�ӵ���Ϊ%d\n", leafNodesNum2);
	
	
}