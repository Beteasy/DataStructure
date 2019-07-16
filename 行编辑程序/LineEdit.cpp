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

/*****************��������************************/
Status InitStack(SqStack *S);
Status GetTop(SqStack S, SElemType e);
Status Push(SqStack *S, SElemType e);
Status ClearStack(SqStack *S);
void LineEdit();
Status DestroyStack(SqStack *S);
void PrintStack(SqStack S);

int main()
{
	LineEdit();
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
	if(S.base == S.top)		//��ջ
	{
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}


Status Push(SqStack *S, SElemType e)
{
	if((*S).top-(*S).base>=(*S).stacksize)		//ջ��,׷�ӿռ�
	{
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)		//�洢����ʧ��
		{
			exit(OVERFLOW);
		}
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
}

Status Pop(SqStack *S, SElemType *e)
{
		//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ָ��������OK�����򷵻�ERROR
	if((*S).base == (*S).top)	//ջ��
	{
		return ERROR;
	}
	*e = *(--(*S).top);
	return OK;
}

Status StackEmpty(SqStack S)
{
	//�ж�ջ�Ƿ�Ϊ�գ���Ϊ�գ�����TRUE,���򷵻�FALSE
	if(S.base == S.top)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status ClearStack(SqStack *S)
{
	//��S��Ϊ��ջ
	char e;
	while((*S).top-(*S).base>0)		//����ȡ����
	{
		Pop(S,&e);
	}
	return OK;
}


Status DestroyStack(SqStack *S)
{
	//����ջS��S���ڴ���
	free((*S).base);		//ע��free���÷���free֮��Ҫ��Ϊ��
	(*S).base = NULL;
	(*S).top = NULL;
	(*S).stacksize=0;
	return OK;
}

void PrintStack(SqStack S)
{
	SElemType *cur;
	cur = S.base;
	while(cur<S.top)
	{
		printf("%c", *(cur++));

	}
}

void LineEdit()
{
	//�����ַ�ջS�����ն˽���һ�в����������ù��̵�������
	SqStack S;
	InitStack(&S);	//�����ջS
	char ch, c;
	printf("������༭����:");
	ch =  getchar();
	while(ch != EOF)	//EOFΪȫ�Ľ�����
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
			case '#':Pop(&S,&c);break;		//��ջ
			case '@':ClearStack(&S);break;	//����SΪ��ջ
			default:Push(&S,ch);				//��Ч�ַ���ջ��
			}
			ch = getchar();			//���ն˽�����һ���ַ�
		}
		//����ջ�׵�ջ����ջ���ַ����������ù��̵�������
		if(StackEmpty(S))
		{
			printf("������������Ϊ��!\n");
		}
		else
		{
			printf("������������Ϊ:");
			PrintStack(S);
			printf("\n");
		}
		ClearStack(&S);			//����SΪ��ջ,Ϊ������һ��������׼��
		if(ch != EOF)
		{
			printf("������༭����:");
			ch = getchar();
		}
	} 
	DestroyStack(&S);	//����ջ
}