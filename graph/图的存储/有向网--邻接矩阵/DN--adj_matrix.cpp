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

//��ͼG�д��ڶ���v���򷵻�v��ͼ�е�λ����Ϣ�����򷵻�������Ϣ
int locateVex(MGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i] == v)
			return i;
	}
	return -1;//ͼ��û�иö���
}

//�����ڽӾ����ʾ������������G
void createDN(MGraph &G){
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
	}
}

//��ӡ�ڽӾ���
void printDN(MGraph G){
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



/*���ԣ�
6,10
v1 v2 v3 v4 v5 v6

v1,v2,5
v1,v4,7

v2,v3,4

v3,v1,8
v3,v6,9

v4,v3,5
v4,v6,6

v5,v4,5

v6,v1,3
v6,v5,1
*/
void main(){
	MGraph G;
	createDN(G);	
	printDN(G);
}