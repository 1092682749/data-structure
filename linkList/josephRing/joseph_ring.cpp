#include<stdio.h>
#include<stdlib.h>
#define NULL 0
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	ElemType sequence;
	LNode *next;
}LNode,*LinkList;

//����һ������ͷ�ڵ��ѭ����������
void createCircularList(LinkList &L, int n){
	printf("������������Ԫ�أ�\n");

	//�����һ��Ԫ�أ���ͷ�ڵ�
	LinkList head = (LinkList)malloc(sizeof(LNode));
	head->sequence = 1;
	head->next = NULL;
	scanf("%d", &head->data);
	L = head;

	LinkList p = head;
	int i = 2;
	while(i <= n){
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->sequence = i;
		s->next = NULL;
		scanf("%d", &s->data);

		p->next = s;
		p = s;
		i++;
	}
	p->next = L;
}

//��ӡ�������ѭ������
void printCircularList(LinkList L){
	printf("��ӡ����ѭ������");
	LinkList head = L;
	LinkList p = L->next;
	printf("%d ",head->data);
	while(p!=head){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//Լɪ�򻷵�ʵ��
void josephRing(LinkList L, int m, int n){
	int *outNum = new int[n], num=0;//���˳�˳���¼���
	
	int count = 1;//����
	LinkList p = L, q = L;	
	while(p->next!=p){
		if(count%m == 0){
			q->next = p->next;
			outNum[num] = p->sequence;
			num++;

			free(p);
			p = q->next;
			count = 1;
		}else{
			q = p;
			p = p->next;
			count++;
		}
	}
	outNum[num] = p->sequence;

	printf("�˳��ı��˳���ǣ�");
	for(int i = 0; i < n; i++){
		printf("%d ", outNum[i]);
	}
	printf("\n");
}

//ʵ������m=20��n=7��7���˵�����������3��1��7��2��4��8��4��
//����ϯ���˵ı������Ϊ6��1��7��5��3��2��4��
void main(){
	LinkList L;
	createCircularList(L, 7);
	printCircularList(L);

	josephRing(L, 20, 7);
}