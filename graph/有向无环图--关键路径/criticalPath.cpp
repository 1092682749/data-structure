/*DAG �����޻�ͼ��Ӧ��--�ؼ�·�����ܷ�˳����ɹ��̣�������Ƿ���ڻ����������򣩣�����޻�����������������������������ʱ��
AOE�����߱�ʾ���������һ����Ȩ��DAG

  �ؼ�·����·���������·��
  ����ɹ��̵����ʱ���Ǵӿ�ʼ�㵽��ɵ���·���ĳ��ȣ�������˵��·��������ָ�������ʱ��֮�ͣ�����·���ϻ�����Ŀ��
  �ؼ�����ؼ�·���ϵ����л���ص㣺���翪ʼʱ��=��ٿ�ʼʱ��
*/

//��ʾ����Ȼ���ڽӱ���Ϊ����ͼ�Ĵ洢�ṹ
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
	VRType w;//������ӦȨֵ
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
	VRType w;//������Ȩͼ��������0��1��ʾ���ڷ񣻶��ڴ�Ȩͼ��������Ϊ��ӦȨֵ	
	printf("\nÿ������һ���������Ķ��㣨�Ȼ�β��ͷ����Ȩֵ���磺v1 v2 3��:\n");
	fflush(stdin);//�������󣬺����ٶ���ʱ�������
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%d v%d %d",&v1, &v2, &w);
		fflush(stdin);//�������󣬺����ٶ���ʱ�������
		i = locateVex(G, v1);//�����
		j = locateVex(G, v2);//���յ�
		
		//���á�ͷ�巨���ڸ�������Ļ���ͷ�����뻡���
		ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));//����һ������㣬��Ϊ��vivj�Ļ�ͷ���յ㣩
		p1->adjvex = j;
		p1->w = w;
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

int indegree[MAX_VERTEX_NUM] = {0};//��Ÿ����������ȵ�����
int ve[MAX_VERTEX_NUM];//�¼������緢��ʱ��
int vl[MAX_VERTEX_NUM];//�¼�����ٷ���ʱ��


typedef struct{
	int s[MAX_VERTEX_NUM];
	int top;
}stack;

void findInDegree(ALGraph G, int indegree[]){	
	ArcNode *p;
	for(int i = 0; i < G.vexnum; i++){
		for(p = G.vexs[i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]++;
		}
	}	
}

//������ͼ�޻�·�������G�Ķ����һ���������в��浽ջT�в�����OK�����򷵻�ERROR
//������G�����ڽӱ����洢�ṹ�������������¼������緢��ʱ��ve
status toplogicalOrder(ALGraph G, stack &T){
	//�ȳ�ʼ��������������
	findInDegree(G, indegree);

	stack S;//ά��һ��ջ��������Ϊ0�Ķ��㣬��ջΪ��ʱ����˵��ͼ�в�������ǰ���Ķ����ˣ���û�����Ϊ0�Ķ����ˣ���˵��ͼ���޻�
	S.top = 0;//���������ʱ��Ȼ���ڶ��㣬������Щ������ǰ������˵���л�

	//�����Ϊ0�Ķ�����ջ
	for(int i = 0; i < G.vexnum; i++){
		if(!indegree[i]){
			S.s[S.top++] = i;
		}
	}
	//��ʼ���¼������緢��ʱ������ve
	for(i = 0; i < G.vexnum; i++){
		ve[i] = 0;
	}

	int count = 0;//������Ķ������
	ArcNode *p;
	while(S.top != 0){//ջ��Ϊ��
		int topElemVex_i = S.s[--S.top];//ջ��Ԫ�س�ջ������һ����ǰ���Ķ���
		//printf("v%d ", G.vexs[topElemVex_i].data);//�����ǰ���
		T.s[T.top++] = topElemVex_i;//��Tջ����Ϊ���������е�һ����
		count++;

		//ȥ���Ըý��Ϊǰ���ĵ������Ļ����Խ���ض������ȼ�1�Ĳ�����ʵ��
		for(p = G.vexs[topElemVex_i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]--;
			if(!indegree[p->adjvex]){
				S.s[S.top++] = p->adjvex;//���Ϊ0����ջ
			}
			//��Sջ��ջ��Ԫ�����������е�ǰ���ʵĽ�㣬���������У���ô����������Ϊǰ���Ķ�������緢��ʱ����ܾͻ���Ҫ����
			//���¶���vi��v(p->adjvex)��v(p->adjvex)�����緢��ʱ��
			if(ve[topElemVex_i] + p->w > ve[p->adjvex]){
				ve[p->adjvex] = ve[topElemVex_i] + p->w ;
			}
		}
	}
	printf("\n");

	if(count < G.vexnum)//������ͼ�л�·
		return ERROR;
	else
		return OK;
}

//GΪ�����������G�ĸ���ؼ��
status criticalPath(ALGraph G, stack T){
	if(!toplogicalOrder(G, T))
		return ERROR;
	
	//��ʼ���¼�����ٿ�ʼʱ������vl
	for(int i = 0; i < G.vexnum; i++){
		vl[i] = ve[G.vexnum-1];//����ʼ���ɻ������緢��ʱ��
	}

	ArcNode *p;
	while(T.top != 0){//��Ϊ��ջ��ջT�������������У���ջ����ջ��Ϊ��������
		int topElemVex_i = T.s[--T.top];//ջ��Ԫ�س�ջ�������������ջ

		//���������������������ٿ�ʼʱ��
		for(p = G.vexs[topElemVex_i].firstarc; p ; p = p->nextarc){//pָ��Ķ�����topElemVex_i�����ֱ�Ӻ��
			if(vl[p->adjvex] - p->w < vl[topElemVex_i]){
				vl[topElemVex_i] = vl[p->adjvex] - p->w;
			}
		}
	}

	/*
	//test
	for(i = 0; i < G.vexnum; i++){
		printf("%d %d\n", ve[i], vl[i]);
	}
	*/




	printf("\n");
	//Ȼ��ʼ��������翪ʼʱ�����ٿ�ʼʱ��,�м�������м����ߣ�ע�����ǵĴ洢�ṹ���ڽӱ�
	//�������η����ڽӱ��е�ÿ������ָ�ŵĻ������Ϳ��Է��ʵ����еĻ����
	int ee;//������緢��ʱ��
	int el;//�����ٷ���ʱ��
	char tag;//��ʾ�Ƿ��ǹؼ����'*'��ʾ�ǹؼ��
	for(i = 0; i < G.vexnum; i++){
		for(p = G.vexs[i].firstarc; p ; p = p->nextarc){//Pָ��ÿ�����ڵ�
			//��ʱ�ǻ���vi---v(p->adjvex),pָ��vi�ĺ�̣���p��Ӧ�����翪ʼʱ������ٿ�ʼʱ��ֱ�Ϊee,el
			ee = ve[i];//eeΪ�ǰһʱ������翪ʼʱ��
			el = vl[p->adjvex] - p->w;//el= ����¼�����ٿ�ʼʱ��-�����ʱ��
			tag = (ee == el) ? '*' : ' ';
			printf("v%dv%d:%d, ����翪ʼʱ�䣺%d�������ʼʱ�䣺%d��%c\n", G.vexs[i].data, G.vexs[p->adjvex].data, p->w, ee, el, tag);//������ee��el����ʶ��*�ŵĴ���ؼ��
		}
	}
	printf("\n");
	return OK;
}

/*���ԣ�
6,8
v1 v2 v3 v4 v5 v6

v1 v2 3
v1 v3 2

v2 v4 2
v2 v5 3

v3 v4 4
v3 v6 3

v4 v6 2
v5 v6 1
*/
void main(){
	ALGraph G;
	createDG(G);
	//printAdjList(G);
	
	stack T;//ά��һ��ջ�������洢������������
	T.top = 0;

	//toplogicalOrder(G, T);
	/*
	printf("��ͼ��������������Ϊ��");
	for(int i = 0; i < T.top; i++)//��ջ�׵�ջ����һ��������
		printf("v%d ", G.vexs[T.s[i]]);
	printf("\n");
	*/

	criticalPath(G, T);
	
	
	
}

