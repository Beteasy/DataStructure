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


/******************函数声明*************************/
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
	if(S.top == S.base)		//k空栈
	{
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}

Status Push(SqStack *S, SElemType e)
{
	if((*S).top-(*S).base>=(*S).stacksize)	//栈满,追加空间
	{
		(*S).base = (SElemType*)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)		//存储分配失败
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
	//若栈不空，则删除S的栈顶元素，用e返回其指，并返回OK，否则返回ERROR
	if((*S).top==(*S).base)		//栈空
	{
		return ERROR;
	}
	*e = *(--(*S).top);
	return OK;
}

Status StackEmpty(SqStack S)
{
	//判断栈是否为空,若为空，返回TRUE，否则返回FALSE
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
	InitStack(&S);		//初始化栈
	char ch;
	printf("请输入表达式:");
	ch = getchar();		//	从终端读取一个字符
	while(ch != '\n')
	{
		switch(ch)
		{
		case '(':
		case '[':
		case '{':Push(&S,ch);
				break;		//如果是左括号，则直接进行压栈操作

		case ')':
				if(GetTop(S,&top))		//获取栈顶元素	
				{
					if(top == '(')		//如果两个括号匹配
					{
						Pop(&S,&e);		//将栈顶元素出栈
					}
					else
					{
						Push(&S,ch);	//如果不匹配，将新元素压栈
					}
				}
				else	//原来为空栈，直接把右括号压进去
				{
					Push(&S,ch);
				}
				break;

		case ']':
				if(GetTop(S,&top))		//获取栈顶元素		
				{
					if(top == '[')		//如果两个括号匹配
					{
						Pop(&S,&top);	//将栈顶元素出栈
					}
					else
					{
						Push(&S,ch);	//如果不匹配，将新元素压栈
					}
				}
				else	//原来为空栈，直接把右括号压进去
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
				else	//原来为空栈，直接把右括号压进去
				{
					Push(&S,ch);
				}
				break;
		}
		ch = getchar();		//从终端读取下一个字符
	}
	if(StackEmpty(S))
	{
		printf("表达式中的括号匹配\n");
	}
	else
	{
		printf("表达式中的括号不匹配\n");
		printf("当前栈中的内容为:");
		PrintStack(S);
	}
}