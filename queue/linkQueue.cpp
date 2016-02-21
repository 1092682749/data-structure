#include<stdio.h>
#include<stdlib.h>
//����Ҫ�ڶ�ͷִ��ɾ�������ӣ����������βִ�в��루��ӣ�����������Ҫ֪����ͷλ�úͶ�βλ�ü���Ψһȷ��һ������
//�����Ա����ƣ�Ҳ��2�ִ洢��ʾ��˳����к�������
//��ʵ��ʵ��������
//�ж϶����Ƿ�Ϊ�գ�Q.f == Q.r
#define NULL 0
typedef char QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode;

typedef struct{
	QNode *f;//��ͷָ��
	QNode *r;//��βָ��
}LinkQueue;

//��ʼ��һ������ͷ�ڵ�Ŀն���
void initQueue(LinkQueue &Q){
	Q.f = Q.r = (QNode *)malloc(sizeof(QNode));
	Q.f->next = NULL;
}
//���ٶ���
void destroyQueue(LinkQueue &Q){
	while(Q.f){
		QNode *p = Q.f->next;
		free(Q.f);
		Q.f = p;
	}
}

//��Ӳ���,�ڶ�β����
void enQueue(LinkQueue &Q, QElemType e){
	QNode *p = (QNode *)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
	Q.r->next = p;
	Q.r = p;
}

//���Ӳ������ڶ�ͷɾ��,����e����ɾ����Ԫ��
void deQueue(LinkQueue &Q, QElemType &e){
	if(Q.f == Q.r){
		printf("����Ϊ�գ�ɾ������ʧ�ܣ�\n");
		return;
	}
	QNode *p = Q.f->next;
	e = p->data;
	Q.f->next = p->next;
	//���Ҫɾ������βָ��(�������д�ʱֻ��һ��Ԫ��)������Ҫ�޸�βָ��
	if(p == Q.r)
		Q.r = Q.f;
	free(p);
	printf("Ԫ��%c����\n", e);
}

//������Ӳ�������һ������,��ӵ��n��Ԫ��
void createQueue(LinkQueue &Q, int n){
	int i = 0;
	printf("������%d���ַ�Ԫ�أ�\n", n);
	while(i < n){
		char dataTmp;
		scanf("%c", &dataTmp);
		enQueue(Q, dataTmp);
		i++;
		getchar();//�Ե����з�
	}
}

void printQueue(LinkQueue Q){
	QNode *p = Q.f->next;
	while(p){
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n\n");
}
void main(){
	LinkQueue Q;//����һ������
	initQueue(Q);
	createQueue(Q, 5);
	printQueue(Q);
	printf("ִ����Ӳ�����");
	printf("������Ҫ������ַ������ݣ�");
	QElemType e;
	scanf("%c", &e);
	enQueue(Q, e);
	printQueue(Q);

	printf("ִ�г��Ӳ�����");
	deQueue(Q, e);	
	printQueue(Q);
}