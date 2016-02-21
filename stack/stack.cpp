/*ջ�ǲ������޵����Ա���ͷΪջ������βΪջ��
�����Ա�һ����ջҲ�����ִ洢��ʾ������1.˳��ջ����̬���顢��̬���飩2.��ջ����������̬����
������
	1.˳��ջ(topΪջ��Ԫ�ص���һ��λ��)
	��̬���飺
	#define STACK_INIT_SIZE 100//��ʼ������
	#define STACKINCREAMENCE 10//��������
	typedef int SElemType;
	typedef struct SqStack{
		SElemType *base;
		SElemType *top;
		int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
	}SqStack;

		ջ�����ڣ�base = NULL
		��ջ��top = base
		��ջ��top-base >= stacksize

	��̬���飺
	#define MAXSIZE 100
	typedef struct SqStack{
		SElemType data[MAXSIZE];
		int top;//ָ��ջ��Ԫ��
	}SqStack;

		��ջ��top = 0
		��ջ��top = MAXSIZE

	2.��ջ(������ʽ��topָ��ջ��Ԫ��)
	typedef struct SqNode{
		SElemType data;
		struct SqNode *next;
	}SqNode, *LinkStack;
	LinkStack top;//ջ��ָ��

		��ջ��StackNode *top = NULL
*/

//��ʵ���Ծ�̬����ʵ��˳��ջ�����У�topΪջ��Ԫ�ص���һ��λ��
#include<stdio.h>
#define MAXSIZE 100
typedef char SElemType;
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
		printf("�ǿ�ջ\n");//
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

//������ջ��������һ����ʼջ
void createStatck(SqStack &s, int n){
	printf("��������ջ��Ԫ�أ�\n");
	for(int i = 0; i < n; i++){
		SElemType e;
		scanf("%c", &e);
		push(s, e);
		getchar();//����س���
	}
	printf("\n");
}

//��ӡ���ջ��Ԫ��
void printStack(SqStack s){
	int stackLen = s.top;//ջ��
	printf("��ӡջ��Ԫ�أ�");
	for(int i = 0; i < stackLen; i++){
		printf("%c ", s.data[i]);
	}
	printf("\n");
}

void main(){
	SqStack s;
	initStack(s);
	
	createStatck(s, 5);//����һ����ջ����ջ��Ϊ��a��c��e��g��i��ջ
	printStack(s);

	//��ջ��Ԫ�أ�j
	printf("����һ����Ԫ����ջ������ĸj��:");
	SElemType pushElem;
	scanf("%c", &pushElem);
	push(s, pushElem);
	printStack(s);

	//��ջ
	SElemType popElem;
	pop(s, popElem);
	printf("\n��ջԪ��Ϊ%c\n", popElem);
	printStack(s);
}