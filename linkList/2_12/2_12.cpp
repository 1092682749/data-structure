#include<stdio.h>
#include<stdlib.h>
//�ο���
//http://www.2cto.com/kf/201410/347626.htmla

//���Ա�����ִ洢�ṹ��
//1.˳�����̬����ʵ�֡���̬����ʵ�֣�
//2.������������̬����
//��ʵ��ʵ�����Ա����ʽ�洢

#define NULL 0
typedef int ElemType;
//������洢�ṹ�ڵ㶨��
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
//Ĭ�ϵ���������ͷ�ڵ�


//�ڴ�ͷ�ڵ�ĵ�����ĵ�i(1<=i<=n+1)��λ��֮ǰ����Ԫ��e,��n+1��λ�ÿɹ�����
//���ҵ�ǰ������i-1���ڵ�
//ʱ�临�Ӷȣ�O(n)
void insertList(LinkList &L, int i, ElemType e){
	int j = 1;
	LinkList p = L;//p����ָ��ͷ�ڵ�
	while(j<i&&p){
		p = p->next;
		j++;
	}//˳���Ļ���jӦ��Ϊ�����λ��i,pΪ��ǰ����㼴i-1λ�õĽڵ�
	//���i���ڱ�+1�������Ϊp=NULL������ѭ�������i<1,�����Ϊj<i����������ѭ��
	if(j>i||!p){
		printf("����λ�ò������Ϸ�\n");
	}else{
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
	}	
}

//�ڴ�ͷ�ڵ�ĵ�������ɾ����i(1<=i<=n)��Ԫ�أ�����e����
//��Ҫ�ҵ���i��Ԫ�ص�ǰ�����
//ʱ�临�Ӷȣ�O(n)
void delList(LinkList &L, int i, ElemType &e){
	int j = 1;
	LinkList p = L;
	while(j<i&&p->next){
		p = p->next;
		j++;
	}//˳���Ļ�,jӦ��Ϊ�����λ��i,pΪ��ǰ����㼴i-1λ�õĽڵ�
//���i���ڱ��������Ϊp->next=NULL������ѭ�������i<1,�����Ϊj<i����������ѭ��
	if(j>i||!p->next){
		printf("ɾ��λ�ò������Ϸ�\n");
	}else{
		LinkList s = p->next;
		e = s->data;
		p->next = s->next;
		free(s);
		printf("��ɾ���ĵ�%d��λ�õ�������%d\n", i, e);
	}
}

//����һ������Ϊn�����Ե�����,ʹ��β�巨��˳��������
//����Ϊͷ�巨��Ϊ����������ô����Ԫ�ص�˳��Ӧ�������Ա�����߼�˳���෴��
void createList(LinkList &L, int n){
	//�Ƚ���һ����ͷ�ڵ�ĵ�����L,����ʼ��
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

	LinkList r = L;//rָ������ָ��ǰ���Ա�����һ��Ԫ�أ���βԪ��
	printf("������%d������:\n", n);
	for(int i = 0; i < n; i++){
		LinkList s = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &s->data);
		//getchar();
		s->next = NULL;
		r->next = s;
		r = s;
	}
}
//��ӡ������Ե�����
void printList(LinkList L){
	printf("��ӡ��������");
	LinkList p = L->next;
	while(p){//pΪ��ǰ��õ�Ԫ��
		printf("%d ", p->data);
		p=p->next;
	}
	printf("\n");
}

//��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����У���Ҫ��La��Lb�鲢Ϊһ���µ����Ա�Lc����Lc�е�����Ԫ����Ȼ��ֵ�ǵݼ���������  
//ʵ�֣�Ϊ����Lc�ķǵݼ�������a<=bʱ��c=a;��a>bʱ��c=b  
//ʱ�临�Ӷȣ�O(La.len+Lb.len)  
//ʵ����La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),Lc=(2,3,5,6,8,8,9,11,11,15,20),ע�Ⲣû��ȥ�أ�ֻ�����˺ϲ� 
//ע�⣺������˳����ʵ�ֵ�����֮����Lc������la��Lb�Ľڵ㣬����La,Lb�����ӵ�Lc��ȥ
void mergeList(LinkList &La, LinkList &Lb, LinkList &Lc){
	Lc = La;//��La��ͷ�ڵ���ΪLc��ͷ�ڵ�
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = Lc;//pc����ָ��Lc�����һ���ڵ�

	while(pa&&pb){
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;//����ʣ���
	free(Lb);//�ͷ�Lb��ͷ�ڵ�
}

//�����������Ա�La,Lb�ֱ��ʾ��������A��B(���Ա��е�����Ԫ�ؼ�Ϊ����Ԫ��)����Ҫ��һ���µļ���A=AUB  
//ʵ�֣���չ���Ա�La,ʵ��������merge������ֻ��Ҫȥ�أ�������2��ָ��ͬʱ���������Ա�������Ƚ�,������õĲ��������˺ϲ�ǰ��˳��
//ʵ����La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),union�Ժ��La=(2,3,5,6,8,9,11,15,20),La.len=9,ע����ȥ�أ� 
//ʱ�临�Ӷȣ�O(La.len + Lb.len) 
void unionList(LinkList &La, LinkList &Lb){
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = La;//pc����ָ�򲢼��б�����һ���ڵ�

	while(pa&&pb){
		if(pa->data < pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else if(pa->data > pb->data){
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}else{//a==b��ֻ��������֮һ
			LinkList s = pb;

			pc->next = pa;
			pc = pa;
			pa = pa->next;
			pb = pb->next;

			free(s);
		}
	}
	pc->next = pa?pa:pb;//����ʣ���
	free(Lb);//�ͷ�Lb��ͷ�ڵ�
}
void main(){  	
	LinkList L;
	createList(L, 5);//��ʼ��������һ�����Ե�����
	printList(L);	

	/*
	//��ɲ��빦��  
    printf("��Ҫ��������ݺ�λ��(1~6)(�磺�ڵ�2��λ�ò���10�����룺2,10)��");  
    int elem, pos;  
    scanf("%d,%d",&pos,&elem);  
    insertList(L,pos,elem);  
    printList(L);  
	*/
	
	
	/*
	//���ɾ������  
    printf("��Ҫɾ�������ݵ�λ��(1~5)(�磺�ڵ�2��λ��ɾ�������룺2)��");  
    int pos; 
	ElemType elem;
    scanf("%d",&pos);  
    delList(L,pos,elem); 
    printList(L); 
	*/

	/*
	//���merge����  
    LinkList La, Lb, Lc;   
    printf("�������Ա�La:\n");  
    createList(La, 4);//��ʼ�����������Ա�La  
    printList(La);  
    printf("�������Ա�Lb:\n");  
    createList(Lb, 7);//��ʼ�����������Ա�Lc  
    printList(Lb);  
    mergeList(La, Lb, Lc);  
    printf("merge�Ժ�õ���Lc:\n");  
    printList(Lc);  
	*/
	
	/*
	//���union����  
    LinkList La, Lb;   
    printf("�������Ա�La:\n");  
    createList(La, 4);//��ʼ�����������Ա�La  
    printList(La);  
    printf("�������Ա�Lb:\n");  
    createList(Lb, 7);//��ʼ�����������Ա�Lc  
    printList(Lb); 
    unionList(La, Lb);  
    printList(La); 
	*/
}