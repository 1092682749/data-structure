#include<stdio.h>
#include<stdlib.h>
/*
ͼ�ı�ʾ����
DG������ͼ������DN�������������ڽӾ����ڽӱ����ڽӱ�--Ϊ����ȣ���ʮ������
UDG������ͼ������UDN�������������ڽӾ����ڽӱ��ڽӶ��ر�
*/
#define MAX_VERTEX_NUM 10//��󶥵���Ŀ
#define NULL 0
//typedef int VRType;//���ڴ�Ȩͼ��������Ϊ��ӦȨֵ
typedef int VertexType;//��������
//typedef enum GraphKind {DG, DN, UDG, UDN};  //����ͼ��0����������1������ͼ��2������

typedef struct ArcNode{	
	int ivex, jvex;//�ñ���������2���������ͼ��λ��
	struct ArcNode *ivexNextarc, *jvexNextarc;//�ֱ�ָ��ñ�������������������һ����
}ArcNode;//�������Ϣ

typedef struct VNode{
	VertexType data;//������Ϣ
	ArcNode *firstedge;//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjMuitiVexList[MAX_VERTEX_NUM];//��������Ϣ

typedef struct{
	AdjMuitiVexList vexs;//��������
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
	//GraphKind kind;//ͼ�������־
}AMLGraph;//�ڽӱ��ʾ��ͼ


//��ͼG�д��ڶ���v���򷵻�v��ͼ�е�λ����Ϣ�����򷵻�������Ϣ
int locateVex(AMLGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i].data == v)
			return i;
	}
	return -1;//ͼ��û�иö���
}

//�����ڽӶ��ر��ʾ����������ͼG
void createUDG(AMLGraph &G){
	printf("���붥�����ͻ�����:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//���춥������,����ʼ��
	printf("����%d�����㣨�Կո�����磺v1 v2 v3��:", G.vexnum);
	getchar();//�Ե����з�
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m].data);
		G.vexs[m].firstedge = NULL;//��ʼ��Ϊ��ָ��////////////////��Ҫ������
		getchar();//�Ե��ո��
	}

	//�����ڽӶ��ر�
	VertexType v1, v2;//�ֱ���һ������������
	printf("\nÿ������һ���������Ķ��㣨�磺v1v2��:\n");
	fflush(stdin);//�������󣬺����ٶ���ʱ�������
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%dv%d",&v1, &v2);
		fflush(stdin);//�������󣬺����ٶ���ʱ�������
		i = locateVex(G, v1);//�������������������ͼ�е�λ��
		j = locateVex(G, v2);
		
		//���á�ͷ�巨���ڸ�������ı���ͷ������߽��
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));//����һ���߽�㣬��������vivj��������
		p->ivex = i;
		p->ivexNextarc = G.vexs[i].firstedge;
		G.vexs[i].firstedge = p;
		p->jvex = j;
		p->jvexNextarc = G.vexs[j].firstedge;
		G.vexs[j].firstedge = p;
	}
}

//��ӡ�ڽӶ��ر�
void printAdjMultiList(AMLGraph G){
	printf("\n");
	for(int i = 0; i < G.vexnum; i++){
		printf("��������v%d�ı�Ϊ��", G.vexs[i].data);
		ArcNode *p = G.vexs[i].firstedge;

		while(p){
			if(p->ivex == i){
				printf("v%dv%d ", G.vexs[i].data, G.vexs[p->jvex].data);
				p = p->ivexNextarc;
			}else if(p->jvex == i){
				printf("v%dv%d ", G.vexs[i].data, G.vexs[p->ivex].data);
				p = p->jvexNextarc;
			}
		}
		printf("\n");
	}
	printf("\n");
}


/*
���ԣ�
4,3
v1 v2 v3 v4

  v1v2
  v1v3
  v2v4
*/
void main(){
	AMLGraph G;
	createUDG(G);
	printAdjMultiList(G);
}