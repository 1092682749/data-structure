//������ͼ���ڽӱ���Ϊ�洢�ṹ��ʵ��ͼ������ȱ����㷨
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
	int adjvex;//�û���ָ��Ķ������ͼ��λ��
	//VRType w;//������ӦȨֵ
	struct ArcNode *nextarc;//ָ����һ���ߵ�ָ��
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
void createUDN(ALGraph &G){
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
	printf("\nÿ������һ���������Ķ��㣨�Ȼ�β��ͷ�����磺v1v2��:\n");
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
		ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));//����һ������㣬��Ϊ��vivj�Ļ�β����㣩
		p2->adjvex = i;
		//p2->w = w;
		p2->nextarc = G.vexs[j].firstarc;
		G.vexs[j].firstarc = p2;
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


int visited[MAX_VERTEX_NUM];//���ʱ�ʶ����

void DFS(ALGraph G, int ivex){
	//�ӵ�i����������ݹ��������ȱ���ͼG
	visited[ivex] = 1;
	printf("v%d ", G.vexs[ivex].data);//��ӡ�����ʣ��ö���
	for(ArcNode *p = G.vexs[ivex].firstarc; p; p = p->nextarc){//���ڵ�ivex�������ÿ��δ�����ʵ��ڽӵ�ݹ����DFS
		if(!visited[p->adjvex]){
			DFS(G, p->adjvex);
		}
	}
}

//������ȱ�������ͼG���൱������������������ݹ��㷨��
void DFSTraverseGraph(ALGraph G){
	//��ʼ�����ʱ�־����
	for(int i = 0; i < G.vexnum; i++){
		visited[i] = 0;//0��ʾδ�����ʣ�1��ʾ�ѱ�����
	}
	printf("�������������ʼ���㣨�磺v1):");
	VertexType startVex;
	scanf("v%d", &startVex);
	int startVexPos = locateVex(G, startVex);
	printf("һ��������ȱ�������Ϊ��");
	if(!visited[startVexPos])
		DFS(G, startVexPos);
	printf("\n");
	/*
	for(i = 0; i < G.vexnum; i++){//ͼ��ÿ�������������һ��DFS����
		if(!visited[i]){//�Ի�δ���ʹ��Ķ������DFS
			DFS(G, i);
		}
	}
	*/
}


//������ȱ�������ͼG���൱������������������ǵݹ��㷨��
void DFSTraverseGraph2(ALGraph G){
	int stack[MAX_VERTEX_NUM];//ά��һ��ջ���洢����ͼ�Ķ���ģ�λ�ã���Ϣ
	int top = 0;//��ʼ��ջ��ָ�룬Ϊ��ջ

	//��ʼ�����ʱ�־����
	for(int i = 0; i < G.vexnum; i++){
		visited[i] = 0;//0��ʾδ�����ʣ�1��ʾ�ѱ�����
	}
	printf("�������������ʼ���㣨�磺v1):");
	VertexType startVex;
	scanf("v%d", &startVex);
	int startVexPos = locateVex(G, startVex);
	printf("һ��������ȱ�������Ϊ��");

	ArcNode *p;// = G.vexs[startVexPos].firstarc;
	int ivex = startVexPos;
	while(!visited[ivex] || top!=-1){//ջ��Ϊ��
		if(!visited[ivex]){//��vex���û�б����ʹ�
			visited[ivex] = 1;
			printf("v%d ", G.vexs[ivex].data);
			stack[top++] = ivex;
		}
			
		p = G.vexs[ivex].firstarc;
		while(p && visited[p->adjvex])//p��Ϊ����p�Ѿ������ʹ���������
			p = p->nextarc;
		//��ʱpָ���Ե�ǰ����Ϊͷ����δ�����ʵ�һ��β����
		if(p){//���p��Ϊ��
			ivex = p->adjvex;
		}else{//���pΪ�գ�˵����ǰ��������к�����·����ͨ�Ķ�����ѷ��ʣ���ջ��Ԫ�س�ջ��������һ����δ�����ʵĶ���
			ivex = stack[--top];//ջ��Ԫ�س�ջ
		}
	}
	printf("\n");
}


//������ȱ�������ͼG���൱�����İ���α��������ǵݹ��㷨��
void BFSTraverseGraph(ALGraph G){
	int queue[MAX_VERTEX_NUM];//ά��һ���������洢����ͼ�Ķ���ģ�λ�ã���Ϣ
	int front = 0, rail = 0;//��ʼ����ͷ����βָ�룬Ϊ�ն���

	//��ʼ�����ʱ�־����
	for(int i = 0; i < G.vexnum; i++){
		visited[i] = 0;//0��ʾδ�����ʣ�1��ʾ�ѱ�����
	}

	printf("�������������ʼ���㣨�磺v1):");
	VertexType startVex;
	scanf("v%d", &startVex);
	int startVexPos = locateVex(G, startVex);
	printf("һ��������ȱ�������Ϊ��");

	queue[rail++] = startVexPos;//��������
	int ivex;// = startVexPos;
	ArcNode *p;
	while(front != rail){//���ǿն���
		ivex = queue[front++];//��ͷԪ�س���
		if(!visited[ivex]){
			visited[ivex] = 1;
			printf("v%d ", G.vexs[ivex].data);
		}
		p = G.vexs[ivex].firstarc;
		while(p){//pָ����ivex���ڽӵģ�ͬһ����εģ���δ������
			if(!visited[p->adjvex])
				queue[rail++] = p->adjvex;//���
			p = p->nextarc;
		}
	}	
	printf("\n");	
}

/*���ԣ�8,9
v1 v2 v3 v4 v5 v6 v7 v8 v9

v1v2
v1v3

v2v4
v2v5

v3v6
v3v7

v4v8
v5v8
v6v7
*/
void main(){
	ALGraph G;
	createUDN(G);
	//printAdjList(G);

	printf("\n������ȱ������ݹ��㷨����\n");
	DFSTraverseGraph(G);
	fflush(stdin);//�������󣬺����ٶ���ʱ�������

	printf("\n������ȱ������ǵݹ��㷨����\n");
	DFSTraverseGraph2(G);
	fflush(stdin);//�������󣬺����ٶ���ʱ�������

	printf("\n������ȱ������ǵݹ��㷨����\n");
	BFSTraverseGraph(G);
}