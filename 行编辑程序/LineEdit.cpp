#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//Status是函数的类型，其值是函数结果状态代码
typedef int Status;

typedef char SElemType;

/**********栈的顺序存储表示******************/
#define STACK_INIT_SIZE 10		//存储空间初始分配量
#define STACKINCREMENT 5		//存储空间分配增量

typedef struct
{
	SElemType *base;	//在栈构造之前和销毁之后，以base的值为NULL
	SElemType *top;		//栈顶指针
	int stacksize;
}SqStack;

/*****************函数声明************************/
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
	//构造一个空栈S
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
	//若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
	if(S.base == S.top)		//空栈
	{
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}


Status Push(SqStack *S, SElemType e)
{
	if((*S).top-(*S).base>=(*S).stacksize)		//栈满,追加空间
	{
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)		//存储分配失败
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
		//若栈不空，则删除S的栈顶元素，用e返回其指，并返回OK，否则返回ERROR
	if((*S).base == (*S).top)	//栈空
	{
		return ERROR;
	}
	*e = *(--(*S).top);
	return OK;
}

Status StackEmpty(SqStack S)
{
	//判断栈是否为空，若为空，返回TRUE,否则返回FALSE
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
	//把S置为空栈
	char e;
	while((*S).top-(*S).base>0)		//不能取等于
	{
		Pop(S,&e);
	}
	return OK;
}


Status DestroyStack(SqStack *S)
{
	//销毁栈S，S不在存在
	free((*S).base);		//注意free的用法，free之后还要置为空
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
	//利用字符栈S，从终端接收一行并传送至调用过程的数据区
	SqStack S;
	InitStack(&S);	//构造空栈S
	char ch, c;
	printf("请输入编辑内容:");
	ch =  getchar();
	while(ch != EOF)	//EOF为全文结束符
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
			case '#':Pop(&S,&c);break;		//退栈
			case '@':ClearStack(&S);break;	//重置S为空栈
			default:Push(&S,ch);				//有效字符进栈，
			}
			ch = getchar();			//从终端接收下一个字符
		}
		//将从栈底到栈顶的栈内字符传送至调用过程的数据区
		if(StackEmpty(S))
		{
			printf("缓冲区的内容为空!\n");
		}
		else
		{
			printf("缓冲区的内容为:");
			PrintStack(S);
			printf("\n");
		}
		ClearStack(&S);			//重置S为空栈,为读入下一行内容做准备
		if(ch != EOF)
		{
			printf("请输入编辑内容:");
			ch = getchar();
		}
	} 
	DestroyStack(&S);	//销毁栈
}