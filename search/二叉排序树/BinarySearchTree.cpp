#include<stdio.h>
#include<stdlib.h>
#define NULL 0
#define TRUE 1
#define FALSE 0
typedef int status; 
typedef int TElemType;
typedef int KeyType;
//��̬��������
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

bool isFind = false;//��ʶ�Ƿ���ҵ�

//�ڸ�ָ��T��ָ�Ķ����������еݹ�Ĳ�����ؼ��ֵ���key������Ԫ�أ������ҳɹ�����ָ��pָ�������Ԫ�صĽ�㣬������True�������򷵻�False
//ָ��f��ָ��p��˫�ף����ʼֵΪNULL
status searchBST(BiTree T, KeyType key, BiTree &f, BiTree &p){
	if(!T){
		p = T;//ʹPָ��NULL
		isFind = false;//��ʶû�в��ҵ�
		return FALSE;
	}
	if(T->data == key){
		p = T;
		isFind = true;//��ʶ�Ѿ����ҵ�
		return TRUE;
	}else if(T->data > key){
		f = T; 
		return searchBST(T->lchild, key, f, p);
	}else{
		f = T; 
		return searchBST(T->rchild, key, f, p);
	}
}

status insertBST(BiTree &T, KeyType key){
	BiTNode *p;
	BiTNode *f = NULL;
	if(searchBST(T, key, f, p)){//�ҵ���
		return TRUE;
	}else{//û�ҵ����������ڣ���Ҫ�����ֵ
		//printf("����&dʧ�ܣ�����ԭ�����������в����ֵ\n");
		p = (BiTNode *)malloc(sizeof(BiTNode));
		p->data = key;
		p->lchild = p->rchild = NULL;
		if(!f){//fΪNULL��˵����������������һ�ÿ���
			T = p;
		}else if(key > f->data){
			f->rchild = p;
		}else{
			f->lchild = p;
		}
		return TRUE;
	}
}

status deleteBST(BiTree &T, KeyType key){
	BiTNode *p, *q;//q������p��˫��f�µ�λ��
	BiTNode *f = NULL;
	if(!searchBST(T, key, f, p)){//û�ҵ�
		return FALSE;
	}else{//�ҵ��ˣ���Ҫִ��ɾ������
		if(!f){//fΪNULL��˵��Ҫɾ�����Ƕ����������ĸ��ڵ�,ʾ����79
			if(p->lchild == NULL && p->rchild == NULL){//p��Ҷ�ӽ�㣬ʾ����5��68, 89��120
				T = NULL;
			}else if(p->lchild == NULL){//pֻ��������,ʾ��:100,88
				T = p->rchild;
			}else if(p->rchild == NULL){//pֻ��������,ʾ��:17
				T = p->lchild;				
			}else{//P��������������Ϊ��
				//��p���������ĸ��ڵ�Ϊ�µĸ��ڵ㣬�������ĸ��ڵ����ӵ��������������¶�
				T = p->lchild;
				q = T;
				while(q && q->rchild)
					q = q->rchild;
				//qָ��p���������������¶�
				if(q)
					q->rchild = p->rchild;
			}

		}else{
			if(p->lchild == NULL && p->rchild == NULL){//p��Ҷ�ӽ�㣬ʾ����5��68, 89��120
				q = NULL;
			}else if(p->lchild == NULL){//pֻ��������,ʾ��:100,88
				q = p->rchild;
			}else if(p->rchild == NULL){//pֻ��������,ʾ��:17
				q = p->lchild;				
			}else{//P��������������Ϊ��,ʾ��:62,90,
				//��p���������ĸ��ڵ����p��p����������p���������������¶�
				q = p->lchild;
				while(q->rchild){
					q = q->rchild;
				}
				q->rchild = p->rchild;//p���������Ƶ��������������¶�
			}
			//����ָ��p��˫�׵ĺ��ӣ���ɾ��p���
			if(f->lchild == p)
				f->lchild = q;
			else if(f->rchild == p)
				f->rchild = q;
			free(p);
		}//end else
	}//end else
	return TRUE;
}


//���������ӡ�������ĵݹ��㷨���󡢸����ң�
void inOrderPrint(BiTree T){
	if(T){
		inOrderPrint(T->lchild);
		printf("%d ", T->data);		
		inOrderPrint(T->rchild);
	}
	
}
void main(){
	BiTree T;
	T = NULL;//������ʼ������Ҫ������

	//���ԣ����ᶨ�ؼ�������79��62��68��90��88��89��17��5��100��120���ɶ���������
	KeyType keyArray[] = {79, 62, 68, 90, 88, 89, 17, 5, 100, 120};
	for(int i = 0; i < 10; i++){
		insertBST(T, keyArray[i]);
	}
	printf("��������ö�����Ϊ��");
	inOrderPrint(T);
	printf("\n");

	
	//����ʧ�������
	int test = 1;
	while(test <= 3){//��2�β���
		printf("\n������Ҫ���ҵĹؼ���key=");
		KeyType key;
		scanf("%d", &key);
		insertBST(T, key);
		if(isFind){
			printf("����%d�ɹ�\n", key);
		}else{
			printf("����%dʧ�ܣ�����ԭ�����������в����ֵ\n", key);		
			printf("����ؼ���%d����������ö�����Ϊ��", key);
			inOrderPrint(T);
			printf("\n");
		}
		test++;
	}
	

	
	//���ҳɹ���ɾ��
	test = 1;
	while(test <= 3){//��3�β���
	    printf("\n������Ҫ���ҵĹؼ���key=");
		KeyType key;
		scanf("%d", &key);
		deleteBST(T, key);
		if(isFind){
			printf("����%d�ɹ�,��ɾ���ùؼ���\n", key);
			printf("ɾ���ؼ���%d����������ö�����Ϊ��", key);
			inOrderPrint(T);
			printf("\n");
		}else{
			printf("����%dʧ��\n", key);		
		}
		test++;
	}
}


