//ʵ����(5*(12-3)+4)/2=24;4+2*3-10/5=8;
#include<stdio.h>
#define MAXSIZE 30
char op[MAXSIZE], num[MAXSIZE];//ȫ�ֱ���
int opTop, numTop;
//void calculate(SqStack op, SqStack num){
void calculate(){
	/*
	SElemType op1, op2;
	SElemType opf;
	pop(num, op2);
	pop(num, op1);
	pop(op, opf);

	SElemType tmpResult;
	*/
	char op1, op2;
	int opf;
	op2 = num[numTop-1];
	numTop--;
	op1 = num[numTop-1];
	numTop--;
	opf = op[opTop-1];
	opTop--;

	int tmpResult = 0;
	switch(opf){
		case '+':
			tmpResult = op1 + op2;			
			break;
		case '-':
			tmpResult = op1 - op2;
			break;
		case '*':
			tmpResult = op1 * op2;
			break;
		case '/':
			tmpResult = op1 / op2;
			break;
	}
	//push(num, tmpResult);
	num[numTop] = tmpResult;
	numTop++;
}



//����򵥱��ʽ
void dealExpression(){
	//SqStack op, num;
	//initStack(op);
	//initStack(num);
	//��ʼ��opջ��numջ:ջΪ�գ�top=0;ջ����top=MAXSIZE
	opTop = 0, numTop = 0;

	printf("������򵥱��ʽ(��#�Ž���)��");
	char currentChar;
	scanf("%c", &currentChar);
	//printf("currentChar=%c", currentChar);
	while(currentChar!='#'){
		//printf("test1");
		//printf("currentChar=%c", currentChar);
		switch(currentChar){
			case '+':
			case '-':
				/*
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					while(e != '('){//opջ��Ϊ����ջ��Ԫ�ز�Ϊ'('����Ϊ'+'��'-'��'*'��'/'����Ӧ�ý�������
						calculate();						
					}
					//��ʱeΪ'('����Ӧ��ջ
					push(op, currentChar);
					scanf("%c", currentChar);
				}*/
				//printf("test4");
				while(opTop&&op[opTop-1]!='('){
					calculate();
				}								
				
				op[opTop] = currentChar;
				opTop++;
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			case '*':
			case '/':
				/*
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					if(e == '*'||e == '/'){//��Ӧ���м���
						calculate();
					}
					push(op, currentChar);
					scanf("%c", currentChar);
				}*/
				if(opTop&&(op[opTop-1]=='*'||op[opTop-1]=='/')){
					calculate();
				}
				op[opTop] = currentChar;
				opTop++;
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			case '(':
				op[opTop] = currentChar;
				opTop++;
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			case ')':
				/*
				if(!isEmpty(op)){//ջ��Ϊ��
					SElemType e;
					getTopElem(op, e);
					while(e!='('){
						calculate();
					}
					//��ʱopջ��Ԫ��eΪ'('��Ӧ�õ���������
					SElemType popElem;
					pop(op, popElem);
					scanf("%c", currentChar);
				}*/
				while(op[opTop-1]!='('){//��ǰ��'('����opջһ������'('ƥ�䵽,��opջһ����Ϊ��
					calculate();
				}
				opTop--;//��ջ������������
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			default://currentCharΪ���֣�����numջ
				//printf("testNum");
				int opNum = 0;
				do{
					opNum = opNum*10 + currentChar-'0';
					//printf("%d",opNum);
					scanf("%c", &currentChar);
					//printf("%c",currentChar);
				}while(currentChar>='0'&&currentChar<='9');
				//push(num, opNum);
				//printf("%d",opNum);
				num[numTop] = opNum;
				numTop++;
				//scanf("%c", currentChar);
				break;
		}//end switch
		//printf("test3");
	}
	//while������˵�����ʽ�Ѿ������������ֻҪopջ��Ϊ�գ���Ӧ���м���
	//��opջΪ��ʱ���򵯳�numջջ��Ԫ�ؼ�Ϊ������
	//SElemType e;
	//getTopElem(op, e);
	/*
	while(isEmpty()){
		calculate();
	}
	SElemType result;
	getTopElem(op, result);
	printf("��������%d\n", result);
	*/
	while(opTop){
		calculate();
	}
	int result = num[numTop-1];
	printf("��������%d\n", result);
}



void main(){
	dealExpression();
}