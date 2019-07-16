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

/**************����ʽ�ṹ��*********************/
#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
typedef struct
{
	SElemType *elem;
	int length;
	int listsize;
}Expression;


/******************��������*************************/
Status InitStack(SqStack *S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
void ReadInList(Expression *exp);
//void ReadInArray(char arr[]);
void InitList(Expression *L);
void Match(Expression exp);
Status StackEmpty(SqStack S);
void PrintStack(SqStack S);

int main()
{
	//char arr[20]={'\0'};
	Expression exp;
	InitList(&exp);
	ReadInList(&exp);
	//ReadInArray(arr);
	Match(exp);
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
	if(S.base == S.top)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void ReadInList(Expression *exp)
{
	printf("��������ʽ���Իس�����:");
	char ch;
	ch = getchar();
	int i=0;
	(*exp).length=0;
	while(ch != '\n')
	{
		if((*exp).length>=(*exp).listsize)		//����ռ��������ӷ���
		{
			(*exp).elem = (SElemType *)realloc((*exp).elem,(LIST_INIT_SIZE+LISTINCREMENT)*sizeof(SElemType));
			if(!(*exp).elem)		//�ռ����ʧ��
			{
				exit(OVERFLOW);
			}
			(*exp).listsize += LISTINCREMENT;
		}
		(*exp).elem[i] = ch;
		//arr[i] = ch;
		i++;
		(*exp).length++;
		//num++;
		ch = getchar();
	}
	printf("����ı��ʽΪ:");
	for(i=0; i<(*exp).length; i++)
	{
		printf("%c",(*exp).elem[i]);
	}
	printf("\n");
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

void InitList(Expression *L)
{
	(*L).elem = (SElemType *)malloc(LIST_INIT_SIZE*sizeof(SElemType));
	if(!(*L).elem)
	{
		exit(OVERFLOW);
	}
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;
}

/*void Match(Expression exp)
{
	int i;
	char top;
	char e;
	SqStack S;
	
	InitStack(&S);
	for(i=0; i<exp.length; i++)
	{
		if(exp.elem[i]=='(' || exp.elem[i]=='[' || exp.elem[i]=='{')		//����������ţ���ֱ�ӽ���ѹջ����
		{
			Push(&S,exp.elem[i]);
		}
		else if(exp.elem[i]==')')		//����������ţ������ж��Ƿ�ƥ�䣬���ƥ�䣬��ջ����Ԫ�س�ջ������ƥ�䣬�����ѹջ����
		{
			if(GetTop(S,&top))			//һ����һ��������û��ƥ�䣬����ʽ�е����Ų�ƥ�䡪��˼������ɲ�����������������ܷ�����Ż�(ֱ������)
			{
				if(top == '(')			//�����ԣ������Ż���������
				{
					Pop(&S,&e);
				}
				else
				{
					Push(&S,exp.elem[i]);
					//break;
				}
			}
			else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
			{
				Push(&S,exp.elem[i]);
				//break;
			}
		}
		else if(exp.elem[i]==']')
		{
			if(GetTop(S,&top))			
			{
				if(top == '[')
				{
					Pop(&S,&top);
				}
				else
				{
					Push(&S,exp.elem[i]);
					//break;
				}
			}
			else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
			{
				Push(&S,exp.elem[i]);
				//break;
			}
		}
		else if(exp.elem[i]=='}')
		{
			if(GetTop(S,&top))		
			{
				if(top == '{')
				{
					Pop(&S,&top);
				}
				else
				{
					Push(&S,exp.elem[i]);
					//break;
				}
			}
			else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
			{
				Push(&S,exp.elem[i]);
				//break;
			}
		}
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
}*/


void Match(Expression exp)
{
	int i=0;
	char top;
	char e;
	SqStack S;
	
	InitStack(&S);
	for(i=0; i<exp.length; i++)
	//while(i<exp.length)
	{
		switch(exp.elem[i])
		{
		case '(':
		case '[':
		case '{':Push(&S,exp.elem[i]);
				break;		//����������ţ���ֱ�ӽ���ѹջ����

		case ')':
				if(GetTop(S,&top))			//һ����һ��������û��ƥ�䣬����ʽ�е����Ų�ƥ�䡪��˼������ɲ�����������������ܷ�����Ż�(ֱ������)
				{
					if(top == '(')			//�����ԣ������Ż���������
					{
						Pop(&S,&e);
					}
					else
					{
						Push(&S,exp.elem[i]);
					}
				}
				else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
				{
					Push(&S,exp.elem[i]);
				}
				break;

		case ']':
				if(GetTop(S,&top))			
				{
					if(top == '[')
					{
						Pop(&S,&top);
					}
					else
					{
						Push(&S,exp.elem[i]);
					}
				}
				else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
				{
					Push(&S,exp.elem[i]);
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
						Push(&S,exp.elem[i]);
					}
				}
				else	//ԭ��Ϊ��ջ��ֱ�Ӱ�������ѹ��ȥ
				{
					Push(&S,exp.elem[i]);
				}
				break;
		}
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