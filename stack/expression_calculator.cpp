//���ʽ��ֵ
/*
������������ջopջ    ������ջnumջ
opջ�ﲻ���ܳ���')'��ֻ������'+'��'-'��'*'��'/'��'('��'#'����chΪ��ǰ�ַ����������붼�Ϸ�
1.opջ��Ϊ'('��'#'����chΪ�������Ļ���opջ��Ϊ������numջ;��������ջ����
2.opջ��Ϊ'*'��'/'����chΪ'*'��'/'��')'��'*'��'/'��'#'����ջ��Ԫ�س�ջ���м��㣬������chΪ����������opջ��Ϊ��������numջ�������ch��'('����������ջ�����������������
3.opջ��Ϊ'+'��'-'����chΪ'+'��'-'��')'��'#'����ջ��Ԫ�س�ջ���м��㣬������chΪ����������opջ��Ϊ��������numջ
4.opջ��Ϊ'#'�����������ȡ��numջջ��Ԫ��Ϊ������
����ch��Ϊ')'������м���ֱ��ջ������'('������
����ch��Ϊ'#',����м���ֱ��ջ������'#'���������������numջջ��Ԫ��Ϊ������

 
1.chΪ'+'��'-'����opջ��Ϊ'('ʱ��ջ�������������ֱ��opջ��Ϊ'('
2.chΪ'*'��'/'����opջ��Ϊ'('��'+'��'-'��ջ������opΪ'*'��'/'��������
3.chΪ���֣���ջ
4.chΪ'('������ջ
5.chΪ')'����ѭ������ֱ������'(',������'('
5.chΪ'#'�������������������ʱӦ����ѭ��������opջΪ�գ���ô����numջջ��Ԫ�ؼ�Ϊ������
*/


//ʵ����(5*(12-3)+4)/2;4+2*3-10/5;
void dealExpression(){
	SqStack op, num;
	initStack(op);
	initStack(num);
	printf("������򵥱��ʽ(��#�Ž���)��");
	char currentChar;
	scanf("%c", currentChar);
	while(currentChar!='#'){
		switch(currentChar){
			case '+':
			case '-':
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					while(e != '('){//opջ��Ϊ����ջ��Ԫ�ز�Ϊ'('����Ϊ'+'��'-'��'*'��'/'����Ӧ�ý�������
						calculate();						
					}
					//��ʱeΪ'('����Ӧ��ջ
					push(op, currentChar);
					scanf("%c", currentChar);
				}				
				break;
			case '*':
			case '/':
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					if(e == '*'||e == '/'){//��Ӧ���м���
						calculate();
					}
					push(op, currentChar);
					scanf("%c", currentChar);
				}
				break;
			case '(':
				push(op, currentChar);
				scanf("%c", currentChar);
				break;
			case ')':
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
				}
				break;
			default://currentCharΪ���֣�����numջ
				int opNum = 0;
				do{
					opNum = opNum*10 + currentChar-'0';
					scanf("%c", currentChar);
				}while(currentChar>='0'&&currentChar<='9');
				push(num, opNum);
				break;
		}//end switch
	}
	//while������˵�����ʽ�Ѿ������������ֻҪopջ��Ϊ�գ���Ӧ���м���
	//��opջΪ��ʱ���򵯳�numջջ��Ԫ�ؼ�Ϊ������
	//SElemType e;
	//getTopElem(op, e);
	while(isEmpty()){
		calculate();
	}
	SElemType result;
	getTopElem(op, result);
	printf("��������%d\n", result);
}

void calculate(SqStack op, SqStack num){
	SElemType op1, op2;
	SElemType opf;
	pop(num, op2);
	pop(num, op1);
	pop(op, opf);

	SElemType tmpResult;
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
	push(num, tmpResult);
}