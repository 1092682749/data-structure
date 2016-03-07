#include<stdio.h>
//#include<stdlib.h>
/*
ͼ�ı�ʾ����
DG������ͼ������DN�������������ڽӾ����ڽӱ����ڽӱ�--Ϊ����ȣ���ʮ������
UDG������ͼ������UDN�������������ڽӾ����ڽӱ��ڽӶ��ر�
*/

//1.�����ʾ�����ڽӾ��󣩣�����������Ϊ��
#define INFINITY 32767//���ֵ���ٶ�Ϊ�����
#define MAX_VERTEX_NUM 10//��󶥵���Ŀ
//typedef enum GraphKind {DG, DN, UDG, UDN};  //����ͼ��0����������1������ͼ��2����������3

typedef int VRType;//�����ϵ���ͣ�������Ȩͼ��������0��1��ʾ���ڷ񣻶��ڴ�Ȩͼ��������Ϊ��ӦȨֵ
typedef int VertexType;//��������
typedef VRType AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
	//GraphKind kind;//ͼ�������־
}MGraph;//�ڽӾ����ʾ��ͼ


typedef struct{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];//��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ�������
closedge close;






//��ͼG�д��ڶ���v���򷵻�v��ͼ�е�λ����Ϣ�����򷵻�������Ϣ
int locateVex(MGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i] == v)
			return i;
	}
	return -1;//ͼ��û�иö���
}

//�����ڽӾ����ʾ������������G
void createUDN(MGraph &G){
	printf("���붥�����ͻ�����:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//���춥������
	printf("����%d�����㣨�Կո�����磺v1 v2 v3��:", G.vexnum);
	getchar();//�Ե����з�
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m]);
		getchar();//�Ե��ո��
	}

	
	//��ʼ���ڽӾ���
	int i=0, j=0;
	for(i = 0; i < G.vexnum; i++){
		for(j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = INFINITY;
	}

	//�����ڽӾ���
	VertexType v1, v2;//�ֱ���һ�����Ļ�β�ͻ�ͷ�������յ㣩
	VRType w;//������Ȩͼ��������0��1��ʾ���ڷ񣻶��ڴ�Ȩͼ��������Ϊ��ӦȨֵ	
	printf("\nÿ������һ���������Ķ��㣨�Ȼ�β��ͷ����Ȩֵ���磺v1 v2 3��:\n");
	fflush(stdin);//�������󣬺����ٶ���ʱ�������
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%d v%d %d",&v1, &v2, &w);
		fflush(stdin);//�������󣬺����ٶ���ʱ�������
		i = locateVex(G, v1);
		j = locateVex(G, v2);
		G.arcs[i][j] = w;

		//����Ϊ���������������ڽӾ�������ڶԽ��߶Գƣ����Ի��ö�������������ֵ����������������������Ҫ
		G.arcs[j][i] = w;//��Ҫ������
	}
}

//��ӡ�ڽӾ���
void printUDN(MGraph G){
	printf("\n��ӡ������G���ڽӾ���\n");
	for(int i = 0; i < G.vexnum; i++){
		for(int j = 0; j < G.vexnum; j++)
		{
			if(G.arcs[i][j] != INFINITY)
				printf("%9d ", G.arcs[i][j]);
			else
				printf("INFINITY  ");
		}
		printf("\n");
	}
	printf("\n");
}

int minimun(MGraph G, closedge close){
	int min = INFINITY;
	int min_i = -1;
	for(int i = 0; i < G.vexnum; i++){
		if(close[i].lowcost>0 && close[i].lowcost < min){
			min = close[i].lowcost;
			min_i = i;
		}
	}
	return min_i;//���ؾ�����С���۵ıߣ�u->vi����vi���±꣬������vi����ͼ�е�λ��
}


//��prim�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߣ�O��n^2��
void miniSpanTreePRIM(MGraph G, VertexType u){
	int k = locateVex(G, u);//�ҵ�����u��ͼ�е�λ��
	//��ʼ����������
	for(int i = 0; i < G.vexnum; i++){
		if(i != k){
			close[i].adjvex = k;
			close[i].lowcost = G.arcs[k][i];
		}
	}
	close[k].lowcost = 0;//��ʼʱ��U={u}

	for(i = 1; i < G.vexnum; i++){//ѡ�������G.vexnum-1�����㣬ÿ��ѡ��һ��������ҪѡG.vexnum-1��
		k = minimun(G, close);//���T����һ����㣺��k����
		printf("v%dv%d\n",G.vexs[close[k].adjvex], G.vexs[k]);//����������ı�(����ʼ��,���յ�)
		close[k].lowcost = 0;//����k���㲢��U��
		for(int j = 0; j < G.vexnum; j++){//����U�����¶���vk�Ĳ��룬����V-U��ĸ��������lowcost�ı仯��Ҫ����
			if(G.arcs[k][j] < close[j].lowcost){
				close[j].adjvex = k;
				close[j].lowcost = G.arcs[k][j];//����ѡ����С���۱�
			}
		}
	}
	printf("\n");
}


/*���ԣ�
6,10
v1 v2 v3 v4 v5 v6

v1,v2,6
v1,v3,1
v1,v4,5

v2,v3,5
v2,v5,3

v3,v4,5
v3,v5,6
v3,v6,4

v4,v6,2

v5,v6,6
*/
void main(){
	MGraph G;
	createUDN(G);	
	//printUDN(G);


	VertexType u;
	printf("�����빹����С�������ĳ����㣺");
	scanf("v%d", &u);
	fflush(stdin);//�������󣬺����ٶ���ʱ�������
	miniSpanTreePRIM(G, u);

}