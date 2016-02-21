#include<stdio.h>
#define mazeRowNum 10//�Թ�����
#define mazeColNum 10//�Թ�����
#define MAXSIZE 100//ջ��С

//�Թ��е�����λ��
typedef struct{
	int x;//�к�
	int y;//�к�
}PosType;

//ջ��Ԫ������
typedef struct{
	//int ord;//ͨ������·���ϵġ���š�
	PosType seat;//ͨ�������Թ��еġ�����λ�á�
	int direction;//�Ӵ�ͨ����������һͨ����ķ���,di=1,2,3,4�ֱ��ʾ�����ϣ�������
}SElemType;

///////////////////////////////////////////////////////////////////////////
typedef struct SqStack{
	SElemType data[MAXSIZE];
	int top;//ָ��ջ��Ԫ��
}SqStack;

//��ʼ����ջ
void initStack(SqStack &s){
	s.top = 0;
}

//��ջ��
bool isEmpty(SqStack s){
	if(s.top == 0){
		printf("�ǿ�ջ\n");//
		return true;
	}else{
		return false;
	}
}

//��ջ��
bool isFull(SqStack s){
	if(s.top == MAXSIZE){
		return true;
	}
	else{
		return false;
	}
}

//��ջ
void push(SqStack &s, SElemType e){
	if(!isFull(s)){
		s.data[s.top] = e;
		s.top++;
	}else
		printf("��ջ��������ջ����ʧ��\n");
}

//��ջ
void pop(SqStack &s, SElemType &e){
	if(!isEmpty(s)){
		e = s.data[s.top-1];
		s.top--;
	}
	else
		printf("��ջΪ��ջ����ջ����ʧ��\n");
}

///////////////////////////////////////////////////////////////////////////

//�����Թ���' '��ʾͨ���飬'#'��ʾǽ�ڣ��ں����ִ�й����У��Թ���Ԫ�ؿ��ܱ��'*'��ʾ·����'@'��ʾ�����߹������޷��������
static char maze[mazeRowNum][mazeRowNum] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
	{'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

PosType start = {1, 1};//�����Թ����
PosType end = {8, 8};//�����Թ��յ�



//�������߹���ͨ�������ºۼ����Է�ֹ����·�����Ǽ�·��
void footPrint(PosType curpos){
	maze[curpos.x][curpos.y] = '*';//��ʾ�����˸�ͨ����
}
//���߹���ͨ���鵫���޷�������ڣ��ǡ���ͨ�ġ�·������������롰����ͬ��
void markPrint(PosType curpos){
	maze[curpos.x][curpos.y] = '@';//��ʾ��ͨ������Ȼ����ǽ�ڣ���������Ȼ��ͨ
}

PosType nextPos(PosType curpos, int direction){
	switch(direction){
		case 1: curpos.y++;break;//���ߣ��кŲ��䣬�кż�1
		case 2: curpos.x++;break;//�����ߣ��кż�1���кŲ���
		case 3: curpos.y--;break;//�����ߣ��кŲ��䣬�кż�1
		case 4: curpos.x--;break;//���ߣ��кż�1���кŲ���
	}
	return curpos;
}
//�жϵ�ǰλ���Ƿ��ͨ,��Ϊ' ',������'#'��'*'�����߹�����'@'�����߹�����ͨ��
bool pass(PosType curpos){
	if(maze[curpos.x][curpos.y] == ' ')
		return true;
	else
		return false;
}
//bool mazePath(char maze[][mazeColNum], PosType start, PosType end){
//���Թ��д��ڴ����start������end��ͨ���������һ��·�������ջ�У���ջ�׵�ջ������������TRUE,���򷵻�FALSE
bool mazePath(PosType start, PosType end){
	SqStack s;
	initStack(s);
	PosType curpos = start;//�趨��ǰλ��Ϊ����ڡ�λ��
	//int curstep = 0;  //̽���ĵ�һ�������ڱ�ʾ·�����
	do{
		if(pass(curpos)){//��ǰ·����ͨ����δ���������ͨ���飩
			footPrint(curpos);//����"����һ��"�ı�ǣ�Ϊ����õ�·���Ǽ�·��
			//SElemType e = {curpos, 1};
			SElemType e;
			e.seat = curpos;
			e.direction = 1;
			push(s, e);  //����·��
			if(curpos.x == end.x && curpos.y == end.y)  //�������
				return true;
			curpos = nextPos(curpos, 1);//��һλ���ǵ�ǰλ�õĶ���
			//curstep++;   //̽����һ��
		}else{//��ǰλ�ò���ͨ������ջ��Ԫ�س�ջ����Ϊջ��λ���ǵ�ǰλ�õġ�����ͨ���飬����ǰλ�õ�ǰһ��λ��
			SElemType e;
			pop(s, e);
			//���������ջ��λ�õ����ܾ�����ͨ�������������·��ͨ�������
			while(e.direction == 4 && !isEmpty(s)){
				markPrint(e.seat);//��Ǵ�ͨ�����Ѿ��߹��Ҳ���ͨ�������Ϊ�˱�����������ͬ
				pop(s, e);
			}
			//������ջ��λ��������������ķ���δ̽�������л�����һ������ķ���Ϊ��ǰλ��
			if(e.direction < 4){
				e.direction++;
				push(s, e);
				curpos = nextPos(e.seat, e.direction);
			}
		}//end else
	}while(!isEmpty(s));//ջ��Ϊ����ѭ������
	return false;
}

//��ӡ�Թ�
void printMaze(){
	for(int i = 0; i < mazeRowNum; i++){
		for(int j = 0; j < mazeColNum; j++){
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//����ӡ�Թ��е�·��
void printPath(){
	for(int i = 0; i < mazeRowNum; i++){
		for(int j = 0; j < mazeColNum; j++){
			if(i == 0 || j == 0 || i == mazeRowNum-1 || j == mazeColNum-1 || maze[i][j] == '*'){
				printf("%c ", maze[i][j]);
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");		
}
void main(){
	printf("�Թ��ĳ�ʼ״̬��\n");
	printMaze();
	if(mazePath(start, end)){
		printf("����ͨ·��\n");
		printf("�Թ�����̬��\n");
		printMaze();
		printf("�Թ����·����\n");
		printPath();
	}else
		printf("������ͨ·��\n");		
}