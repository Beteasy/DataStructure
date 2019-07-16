#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef char SElemType;

/**********ջ��˳��洢��ʾ******************/
#define STACK_INIT_SIZE 10		//�洢�ռ��ʼ������
#define STACKINCREMENT 5		//�洢�ռ��������

typedef struct
{
	SElemType *base;	//��ջ����֮ǰ������֮����base��ֵΪNULL
	SElemType *top;		//ջ��ָ��
	int stacksize;
}SqStack;


/******************��������*************************/
Status InitStack(SqStack *S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
void Match();
Status StackEmpty(SqStack S);
void PrintStack(SqStack S);

int main()
{
	Match();
	return 0;
}

Status InitStack(SqStack *S)
{
	//����һ����ջS
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
	{
		exit(OVERFLOW);
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType *e)
{
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if(S.top == S.base)		//k��ջ
	{
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}

Status Push(SqStack *S, SElemType e)
{
	if((*S).top-(*S).base>=(*S).stacksize)	//ջ��,׷�ӿռ�
	{
		(*S).base = (SElemType*)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)		//�洢����ʧ��
		{
			exit(OVERFLOW);
		}
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
	
}

Status Pop(SqStack *S, SElemType *e)
{
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ָ��������OK�����򷵻�ERROR
	if((*S).top==(*S).base)		//ջ��
	{
		return ERROR;
	}
	*e = *(--(*S).top);
	return OK;
}

Status StackEmpty(SqStack S)
{
	//�ж�ջ�Ƿ�Ϊ��,��Ϊ�գ�����TRUE�����򷵻�FALSE
	if(S.base == S.top)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void PrintStack(SqStack S)
{
	SElemType *cur=S.base;
	while(cur<S.top)
		{
			printf("%c", *cur);
			*cur++;
		}
		printf("\n");
}

void Match()
{
	char top;
	char e;
	SqStack S;
	InitStack(&S);		//��ʼ��ջ
	char ch;
	printf("��������ʽ:");
	ch = getchar();		//	���ն˶�ȡһ���ַ�
	while(ch != '\n')
	{
		switch(ch)
		{
		case '(':
		case '[':
		case '{':Push(&S,ch);
				break;		//����������ţ���ֱ�ӽ���ѹջ����

		case ')':
				if(GetTop(S,&top))		//��ȡջ��Ԫ��	
				{
					if(top == '(')		//�����������ƥ��
					{
						Pop(&S,&e);		//��ջ��Ԫ�س�ջ
					}
					else
					{
						Push(&S,ch);	//�����ƥ�䣬����Ԫ��ѹջ
					}
				}
				else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
				{
					Push(&S,ch);
				}
				break;

		case ']':
				if(GetTop(S,&top))		//��ȡջ��Ԫ��		
				{
					if(top == '[')		//�����������ƥ��
					{
						Pop(&S,&top);	//��ջ��Ԫ�س�ջ
					}
					else
					{
						Push(&S,ch);	//�����ƥ�䣬����Ԫ��ѹջ
					}
				}
				else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
				{
					Push(&S,ch);
				}
				break;

		case '}':
				if(GetTop(S,&top))		
				{
					if(top == '{')
					{
						Pop(&S,&top);
					}
					else
					{
						Push(&S,ch);
					}
				}
				else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
				{
					Push(&S,ch);
				}
				break;
		}
		ch = getchar();		//���ն˶�ȡ��һ���ַ�
	}
	if(StackEmpty(S))
	{
		printf("���ʽ�е�����ƥ��\n");
	}
	else
	{
		printf("���ʽ�е����Ų�ƥ��\n");
		printf("��ǰջ�е�����Ϊ:");
		PrintStack(S);
	}
}