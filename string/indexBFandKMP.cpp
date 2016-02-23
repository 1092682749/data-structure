#include<stdio.h>
//���Ķ���˳��洢��ʾ
#define MAXSTRLEN 50  // // �û�����50���ڶ�����󴮳�
typedef unsigned char SString[MAXSTRLEN + 1];//0�ŵ�Ԫ��Ŵ��ĳ���

//�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ�����ֵΪ0�����У�T�ǿգ�1<=pos<=StrLength(S)��
int indexBF(SString S, SString T, int pos){
	int i = pos, j = 1;
	while(i <= S[0] && j <= T[0]){
		if(S[i] == T[j]){
			i++;
			j++;
		}else{
			i = i - j + 2;//i�ص�ԭλ����i - j + 1 ,����i�˵�Զλ�õ���һ��λ����i - j + 1 + 1
			j = 1;
		}
	}
	if(j > T[0]){//���j > len(T)��˵��ģʽ��T��S��ĳ�Ӵ���ȫƥ��
		return i - T[0];//��Ϊi���Ѿ�������һ���ˣ�������i-len(T)������i-len(T)+1
	}else
		return 0;
}

//�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ�����ֵΪ0�����У�T�ǿգ�1<=pos<=StrLength(S)��
int indexKMP(SString S, SString T, int pos, int next[]){
	int i = pos, j = 1;
	while(i <= S[0] && j <= T[0]){
		if(j == 0 || S[i] == T[j]){
			i++;  //�����ȽϺ����ַ�
			j++;
		}else{
			j = next[j];//ģʽ�����һ���
		}
	}
	if(j > T[0]){//���j > len(T)��˵��ģʽ��T��S��ĳ�Ӵ���ȫƥ��
		return i - T[0];//��Ϊi���Ѿ�������һ���ˣ�������i-len(T)������i-len(T)+1
	}else
		return 0;
}

//��ģʽ��T��next����������������ֵ������next����
void getNextVal(SString T, int next[]){
	next[1] = 0;
	int i = 1, j = 0;
	while(i < T[0]){
		if(j == 0 || T[i] == T[j]){
			i++;  //�����ȽϺ����ַ�
			j++;
			if(T[i] == T[j])//����ȥif(T[i] == T[j])��next[i] = next[j];��2�䣬��õ��ľ�������֮ǰ��next����㷨
				next[i] = next[j];
			else
				next[i] = j;
		}else{
			j = next[j];//ģʽ�����һ���
		}
	}	
}

void init(SString &S, char str[]){
	int i = 0;
	while(str[i]!='\0'){
		S[i+1] = str[i];
		i++;
	}
	S[i+1] = '\0';
	S[0] = i;
}

void printStr(SString Str){
	for(int i = 1; i <= Str[0]; i++){
		printf("%c", Str[i]);
	}
	printf("\n");
}
void main(){
	SString S ;
	init(S, "ababcabcacbab");
	printStr(S);

	SString T;
	init(T, "abcac");
	printStr(T);

	int index = indexBF(S, T, 1);
	printf("index is %d\n", index);

	int next[6] = {0};
	getNextVal(T, next);
	//��ӡnextֵ
	printf("\n\nnext[]��");
	for(int k = 1; k <= T[0]; k++)
		printf("%d ", next[k]);
	printf("\n");

	index = indexKMP(S, T, 1, next);
	printf("index is %d\n", index);
}