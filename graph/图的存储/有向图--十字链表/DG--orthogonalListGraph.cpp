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
	int tailvex, headvex;//�û��Ļ�β����㣩�ͻ�ͷ���յ㣩��ָ��Ķ������ͼ��λ��
	struct ArcNode *tailNextarc, *headNextArc;//�ֱ�Ϊָ��β����㣩��ͬ�Ļ�����һ������ָ�롢��ͷ���յ㣩��ͬ�Ļ�����һ������ָ��
}ArcNode;//�������Ϣ

typedef struct VNode{
	VertexType data;//������Ϣ
	ArcNode *firstIn;//ָ���һ���Ըö���Ϊ��β����㣩��ָ��
	ArcNode *firstOut;//ָ���һ���Ըö���Ļ�ͷ���յ㣩��ָ��
}VNode, VexList[MAX_VERTEX_NUM];//��������Ϣ

typedef struct{
	VexList vexs;//��������
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
	//GraphKind kind;//ͼ�������־
}OLGraph;//�ڽӱ��ʾ��ͼ

//��ͼG�д��ڶ���v���򷵻�v��ͼ�е�λ����Ϣ�����򷵻�������Ϣ
int locateVex(OLGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i].data == v)
			return i;
	}
	return -1;//ͼ��û�иö���
}


//����ʮ�������ʾ����������ͼG
void createDN(OLGraph &G){
	printf("���붥�����ͻ�����:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//���춥������,����ʼ��
	printf("����%d�����㣨�Կո�����磺v1 v2 v3��:", G.vexnum);
	getchar();//�Ե����з�
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m].data);
		G.vexs[m].firstIn = NULL;//��ʼ��Ϊ��ָ��////////////////��Ҫ������
		G.vexs[m].firstOut = NULL;
		getchar();//�Ե��ո��
	}

	//����ʮ������
	VertexType v1, v2;//�ֱ���һ�����Ļ�β�ͻ�ͷ�������յ㣩
	printf("\nÿ������һ���������Ķ��㣨�Ȼ�β��ͷ�����磺v1v2��:\n");
	fflush(stdin);//�������󣬺����ٶ���ʱ�������
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%dv%d",&v1, &v2);
		fflush(stdin);//�������󣬺����ٶ���ʱ�������
		i = locateVex(G, v1);//�����
		j = locateVex(G, v2);//���յ�
		
		//���á�ͷ�巨���ڸ�������Ļ���ͷ�����뻡���
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));//����һ������㣬��Ϊ��vivj�Ļ�ͷ���յ㣩
		p->tailvex = i;
		p->tailNextarc = G.vexs[i].firstOut;
		G.vexs[i].firstOut = p;
		p->headvex = j;
		p->headNextArc = G.vexs[j].firstIn;
		G.vexs[j].firstIn = p;
	}
}

//��ӡʮ������
void printOrthogonalList(OLGraph G){
	printf("\n");
	for(int i = 0; i < G.vexnum; i++){
		printf("�Զ���v%dΪ��β�Ļ���Ϊ��", G.vexs[i].data);
		ArcNode *p = G.vexs[i].firstOut;
		while(p){
			printf("v%dv%d ", G.vexs[i].data, G.vexs[p->headvex].data);
			p = p->tailNextarc;
		}
		printf("\n");
	}
	printf("\n");
}


/*���ԣ�
4,7
v1 v2 v3 v4

v1v2
v1v3

v3v1
v3v4

v4v1
v4v2
v4v3
*/
void main(){
	OLGraph G;
	createDN(G);
	printOrthogonalList(G);
}

