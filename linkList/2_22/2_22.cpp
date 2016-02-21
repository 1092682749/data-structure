#include<stdio.h>
#include<stdlib.h>
/*һԪ����ʽ�ı�ʾ�����
����ʽPn(x)�����ݿ�д��Pn(x) = P0+P1*x+p2*x^2+...+Pn*x^n,����n+1��ϵ��Ψһȷ�������
����һ�����Ա�p=(p0,p1,p2,...,pn),ÿһ���ָ��i������ϵ��pi�������
��Qm(x)��һԪm�ζ���ʽ����������Ա�Q=(q0,q1,q2,...,qm)����ʾ
��ʧһ���ԣ���m<n������������ʽ��ҵĽ������ʽRn(x)=Pn(x)+Qm(x)�������Ա�
(p0+q0, p1+q1, ..., pm+qm, p(m+1), ..., pn)

������
	��P��Q��R����˳��洢�ṹ������ʽ��ӵ��㷨���彫ʮ�ּ򵥣���ͨ��Ӧ���д������ܸܺߣ�ʹ��˳��洢�ṹ����󳤶Ⱥ���ȷ����
����ܶ����ϵ��Ҳ����Ϊ0������S(x)=1+3x^10000+2x^20000,���������������3����0Ԫ�أ���˳��洢�ṹ�����Ա�Ĵ洢�ռ佫�ǳ��˷�
�ʲ��õ�����ṹ��������ʱ��Ҫ�洢ָ���ˡ�
	һԪn�ζ���ʽPn(x)=p1*x^e1 + p2*x^e2 +...+pm*x^em,����pi��ָ��Ϊei����ķ���ϵ����������
0<=e1<e2<...<em=n,����һ������Ϊm��ÿ��Ԫ�������������ϵ����+ָ��������Ա�(p1,e1),(p2,e2),...,(pm,em)�����Ψһ
ȷ������ʽPn(x).
	�����£�n+1(=m)��ϵ������Ϊ0�����ֱ�ʾ������ʡ�ռ䡣

ʵ�֣�
	"�Ͷ���ʽ"�����еĽڵ����������ɣ���Ӧ�ô���������ʽ��������ժȡ������������£�����ָ��qa��qb�ֱ�ָ�����ʽA��B�е�ǰ���бȽϵ�ĳ���ڵ㣬
��Ƚ������ڵ��е�ָ���������3�������
	1.qa��ָ�ڵ��ָ��ֵ<qb��ָ�ڵ��ָ��ֵ����Ӧժȡqa��ָ�ڵ���뵽���Ͷ���ʽ���У�
	2.qa��ָ�ڵ��ָ��ֵ>qb��ָ�ڵ��ָ��ֵ����Ӧժȡqb��ָ�ڵ���뵽���Ͷ���ʽ���У�
	3.qa��ָ�ڵ��ָ��ֵ=qb��ָ�ڵ��ָ��ֵ�������ڵ��ϵ�����
		3.1��ϵ����Ӻ�����Ϊ0�����޸�qa��ָ�ڵ��ϵ��ֵ��ͬʱ�ͷ�qb��ָ�ڵ�
		3.2��ϵ����Ӻ���Ϊ0���Ӷ���ʽA�ĵ�������ɾ����Ӧ�ڵ㣬���ͷ�qa��qb��ָ�ڵ�
ע�⣺
	��ʾһԪ����ʽ��Ӧ������������

*/
#include<stdio.h>
#include<stdlib.h>
#define NULL 0
typedef struct term{
	float coef;
	int expn;
	struct term *next;
}term, *LinkList;//termΪһ�������ͣ���һ���ṹ�壩��LinkListΪָ�������Ľṹ���ָ��

typedef LinkList polynomial;

int cmp(LinkList qa, LinkList qb){//�Ƚ����ָ����С
	if(qa->expn > qb->expn)
		return 1;
	else if(qa->expn == qb->expn)
		return 0;
	else
		return -1;
}

//����������L�д�������t��ָ����ȵ�Ԫ�أ���ָ��qָ��L�е�һ��ָ��Ϊt->expn�Ľڵ��λ�ã�
//����qָ���һ��ָ��������t->expn���>0�Ľڵ��ǰ��λ��
bool locateElem(LinkList L, LinkList t, LinkList &q){
	LinkList p1 = L->next;
	LinkList p2 = L;//p2��ָ��p1��ǰ��
	while(p1){
		if(t->expn > p1->expn){
			p1 = p1->next;
			p2 = p2->next;
		}else if(t->expn == p1->expn){
			q = p1; 
			return true;
		}else{//p1->expn > t->expn,��ΪL�������������������ߵ�����һ����˵��û�ҵ�����t��ָ����ȵĽڵ�Ԫ��
			//�򷵻�q��ǰ�����
			q = p2;
			return false;
		}
	}
	if(!p1){//t->expn�ȵ�ǰ�б�����Ԫ�ص�ָ�������������whileѭ������Ϊp2������β�ڵ㣬p1=NULL������
		q = p2;
		return false;
	}
}
//����m���ϵ����ָ����������ʾһԪ����ʽ�Ĵ���ͷ�ڵ����������P
//����β�巨
void createPolyn(polynomial &P, int m){
	//�Ƚ���һ������ͷ�ڵ�Ŀ���������ʼ��
	P = (polynomial)malloc(sizeof(term));
	P->next = NULL;
	LinkList r = P;//rָ������ָ��ǰ���Ա�����һ��Ԫ�أ���βԪ��

	printf("����ϵ��,ָ��,����2x^5������(2,5):\n");//���ذ���������
	for(int i = 0; i < m; i++){//��������m��������
		LinkList t = (LinkList)malloc(sizeof(term));
		t->next = NULL;
		LinkList q;
		scanf("%f,%d",&t->coef,&t->expn);
		if(!locateElem(P, t, q)){//��ǰ�����в����ڸ�ָ�������룬��ʱqΪ�����е�һ��ָ��>t->expn�Ľڵ��ǰ�����
			t->next = q->next;
			q->next = t;
		}else{//��ǰ�б����Ѿ������нڵ�Ԫ�ص�ָ���뱾����������ָ����ͬ�����Ա���������Ч��Ӧ��������
			i--;
		}
	}
}
//��ӡ����ʽ����
void printPolynomial(polynomial P){
	LinkList q = P->next;
	printf("��ӡ����ʽ�����Ա�[");
	while(q){
		printf("(%.2f,%d)  ",q->coef, q->expn);
		q = q->next;
	}
	printf("]\n\n");
}


//����ʽ�ӷ���Pa=Pa+Pb,����2������ʽ�Ľڵ㹹�ɡ��Ͷ���ʽ��
void addPolyn(polynomial &Pa, polynomial &Pb){
	LinkList qa = Pa->next;
	LinkList qb = Pb->next;
	LinkList qc = Pa;//pc����ָ��"�Ͷ���ʽ����"�����һ���ڵ�

	float sumOfCoef;
	while(qa&&qb){
		switch(cmp(qa, qb)){
			case 1:
				qc->next = qb;
				qc = qb;
				qb = qb->next;
				break;
			case 0://��ǰ�Ƚϵ������ָ����ͬ
				sumOfCoef = qa->coef + qb->coef;
				if(sumOfCoef != 0.0){//ϵ��֮�Ͳ�Ϊ0,���޸�qa��ָ�ڵ��ϵ����ͬʱ�ͷ�gb��ָ�ڵ�
					LinkList s = qb;//s������free��
					qa->coef = sumOfCoef;
					
					qc->next = qa;
					qc = qa;
					qa = qa->next;
					qb = qb->next;

					free(s);
				}else{//ϵ��֮�Ͳ�Ϊ0����Ӷ���ʽ����A��ɾ��qa��ָ�ڵ㣬��free��qa��qb��ָ�ڵ�
					LinkList s1 = qa;
					LinkList s2 = qb;

					qc->next = qa ->next;
					//qc��λ�ò���,qa��qb����ƶ�
					qa = qa->next;
					qb = qb->next;

					free(s1);
					free(s2);
					
				}
				break;
			case -1:
				qc->next = qa;
				qc = qa;
				qa = qa->next;
				break;
		}//end switch
	}//end while
	qc->next = qa?qa:qb;//����ʣ���
	free(Pb);//�ͷ�Pb��ͷ�ڵ�
}

//ʵ����Pa(x)=7+3x+9x^8+5x^17, ����((7,0),(3,1),(9,8),(5,17))
//Pb(x)=8x+22x^7-9x^8,����((8,1),(22,7),(-9,8))
//�Ͷ���ʽΪPa(x) = 7+11x+22x^7+5x^17,�����Ӧ�������(7,0),(11,1),(22,7),(5,17)��
void main(){

	polynomial Pa;
	createPolyn(Pa, 4);//��ʼ������������ʽ����Pa
	printPolynomial(Pa);

	polynomial Pb;
	createPolyn(Pb, 3);//��ʼ������������ʽ����Pa
	printPolynomial(Pb);

	printf("ִ�ж���ʽ����Ժ�\n");
	addPolyn(Pa, Pb);
	printPolynomial(Pa);
}