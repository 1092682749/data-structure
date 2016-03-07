/*
DAG �����޻�ͼ��Ӧ��--���������ܷ�˳����ɹ��̣�������Ƿ���ڻ���
AOV���������ʾ�����

�������������黷���⣬��������DFS
������ͼ���޻�ʱ����ͼ��ĳ�����������ȱ���ʱ�������˳�DFS�����Ķ��㼴����Ϊ0�Ķ��㣬�����������е����һ�����㣬�ɴˣ����˳�DFS�������Ⱥ��¼�����Ķ������У���Ϊ�����������������
*/

//����ʾ�������ڽӱ���Ϊ����ͼ�Ĵ洢�ṹ


#include<stdio.h>
#include<stdlib.h>
/*
ͼ�ı�ʾ����
DG������ͼ������DN�������������ڽӾ����ڽӱ����ڽӱ�--Ϊ����ȣ���ʮ������
UDG������ͼ������UDN�������������ڽӾ����ڽӱ��ڽӶ��ر�
*/
#define MAX_VERTEX_NUM 10//��󶥵���Ŀ
#define NULL 0
typedef int VRType;//���ڴ�Ȩͼ��������Ϊ��ӦȨֵ
typedef int VertexType;//��������
//typedef enum GraphKind {DG, DN, UDG, UDN};  //����ͼ��0����������1������ͼ��2������

typedef struct ArcNode{	
	int adjvex;//�û���ָ��Ķ������ͼ��λ��
	//VRType w;//������ӦȨֵ
	struct ArcNode *nextarc;//ָ����һ������ָ��
}ArcNode;//�������Ϣ

typedef struct VNode{
	VertexType data;//������Ϣ

	ArcNode *firstarc;//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjVexList[MAX_VERTEX_NUM];//��������Ϣ

typedef struct{
	AdjVexList vexs;//��������
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
	//GraphKind kind;//ͼ�������־
}ALGraph;//�ڽӱ��ʾ��ͼ


//��ͼG�д��ڶ���v���򷵻�v��ͼ�е�λ����Ϣ�����򷵻�������Ϣ
int locateVex(ALGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i].data == v)
			return i;
	}
	return -1;//ͼ��û�иö���
}


//�����ڽӱ��ʾ����������ͼG
void createDG(ALGraph &G){
	printf("���붥�����ͻ�����:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//���춥������,����ʼ��
	printf("����%d�����㣨�Կո�����磺v1 v2 v3��:", G.vexnum);
	getchar();//�Ե����з�
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m].data);
		G.vexs[m].firstarc = NULL;//��ʼ��Ϊ��ָ��////////////////��Ҫ������
		getchar();//�Ե��ո��
	}

	//�����ڽӱ�
	VertexType v1, v2;//�ֱ���һ�����Ļ�β�ͻ�ͷ�������յ㣩
	//VRType w;//������Ȩͼ��������0��1��ʾ���ڷ񣻶��ڴ�Ȩͼ��������Ϊ��ӦȨֵ	
	printf("\nÿ������һ���������Ķ��㣨�Ȼ�β��ͷ���磺v1v2:\n");
	fflush(stdin);//�������󣬺����ٶ���ʱ�������
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%dv%d",&v1, &v2);
		fflush(stdin);//�������󣬺����ٶ���ʱ�������
		i = locateVex(G, v1);//�����
		j = locateVex(G, v2);//���յ�
		
		//���á�ͷ�巨���ڸ�������Ļ���ͷ�����뻡���
		ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));//����һ������㣬��Ϊ��vivj�Ļ�ͷ���յ㣩
		p1->adjvex = j;
		//p1->w = w;
		p1->nextarc = G.vexs[i].firstarc;
		G.vexs[i].firstarc = p1;
		/*��Ϊ������ͼ�����Բ��ش���2�������
		ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));//����һ������㣬��Ϊ��vivj�Ļ�β����㣩
		p2->adjvex = i;
		//p2->w = w;
		p2->nextarc = G.vexs[j].firstarc;
		G.vexs[j].firstarc = p2;
		*/
	}
}

//��ӡ�ڽӱ�
void printAdjList(ALGraph G){
	printf("\n");
	for(int i = 0; i < G.vexnum; i++){
		printf("��������v%d�Ļ�Ϊ��", G.vexs[i].data);
		ArcNode *p = G.vexs[i].firstarc;
		while(p){
			printf("v%dv%d ", G.vexs[i].data, G.vexs[p->adjvex].data);
			p = p->nextarc;
		}
		printf("\n");
	}
	printf("\n");
}


#define OK 1
#define ERROR 0
typedef int status;

static int indegree[MAX_VERTEX_NUM] = {0};//��Ÿ����������ȵ�����



void findInDegree(ALGraph G, int indegree[]){	
	ArcNode *p;
	for(int i = 0; i < G.vexnum; i++){
		for(p = G.vexs[i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]++;
		}
	}		
}

//������ͼ�޻�·�������G�Ķ����һ���������в�����OK�����򷵻�ERROR
status toplogicalSort(ALGraph G){
	//�ȳ�ʼ��������������
	findInDegree(G, indegree);
	

	int stack[MAX_VERTEX_NUM];//ά��һ��ջ��������Ϊ0�Ķ��㣬��ջΪ��ʱ����˵��ͼ�в�������ǰ���Ķ����ˣ���û�����Ϊ0�Ķ����ˣ���˵��ͼ���޻�
	//���������ʱ��Ȼ���ڶ��㣬������Щ������ǰ������˵���л�
	int top = 0;//ջ��ָ��

	//�����Ϊ0�Ķ�����ջ
	for(int i = 0; i < G.vexnum; i++){
		if(!indegree[i]){
			stack[top++] = i;
		}
	}

	int count = 0;//������Ķ������
	ArcNode *p;
	while(top != 0){//ջ��Ϊ��
		int topElemVex_i = stack[--top];//ջ��Ԫ�س�ջ������һ����ǰ���Ķ���
		printf("v%d ", G.vexs[topElemVex_i].data);//�����ǰ���
		count++;

		//ȥ���Ըý��Ϊǰ���ĵ������Ļ����Խ���ض������ȼ�1�Ĳ�����ʵ��
		for(p = G.vexs[topElemVex_i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]--;
			if(!indegree[p->adjvex]){
				stack[top++] = p->adjvex;//���Ϊ0����ջ
			}
		}
	}
	printf("\n");

	if(count < G.vexnum)//������ͼ�л�·
		return ERROR;
	else
		return OK;
}

/*���ԣ�
6,8
v1 v2 v3 v4 v5 v6

v1v2
v1v3
v1v4

v3v2

v4v3
v4v5

v6v4
v6v5
*/
void main(){
	ALGraph G;
	createDG(G);
	//printAdjList(G);
	printf("��ͼ��������������Ϊ��");
	toplogicalSort(G);		
}

