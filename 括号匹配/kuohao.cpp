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

/**************多项式结构体*********************/
#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
typedef struct
{
	SElemType *elem;
	int length;
	int listsize;
}Expression;


/******************函数声明*************************/
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
	printf("请输入表达式，以回车结束:");
	char ch;
	ch = getchar();
	int i=0;
	(*exp).length=0;
	while(ch != '\n')
	{
		if((*exp).length>=(*exp).listsize)		//如果空间满，增加分配
		{
			(*exp).elem = (SElemType *)realloc((*exp).elem,(LIST_INIT_SIZE+LISTINCREMENT)*sizeof(SElemType));
			if(!(*exp).elem)		//空间分配失败
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
	printf("输入的表达式为:");
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
		if(exp.elem[i]=='(' || exp.elem[i]=='[' || exp.elem[i]=='{')		//如果是左括号，则直接进行压栈操作
		{
			Push(&S,exp.elem[i]);
		}
		else if(exp.elem[i]==')')		//如果是右括号，则先判断是否匹配，如果匹配，则将栈顶的元素出栈，若不匹配，则进行压栈操作
		{
			if(GetTop(S,&top))			//一般有一个右括号没有匹配，则表达式中的括号不匹配——思考这个成不成立，如果成立，能否进行优化(直接跳出)
			{
				if(top == '(')			//经测试，上述优化方案成立
				{
					Pop(&S,&e);
				}
				else
				{
					Push(&S,exp.elem[i]);
					//break;
				}
			}
			else	//原来为空栈，直接把右括号压进去
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
			else	//原来为空栈，直接把右括号压进去
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
			else	//原来为空栈，直接把右括号压进去
			{
				Push(&S,exp.elem[i]);
				//break;
			}
		}
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
				break;		//如果是左括号，则直接进行压栈操作

		case ')':
				if(GetTop(S,&top))			//一般有一个右括号没有匹配，则表达式中的括号不匹配——思考这个成不成立，如果成立，能否进行优化(直接跳出)
				{
					if(top == '(')			//经测试，上述优化方案成立
					{
						Pop(&S,&e);
					}
					else
					{
						Push(&S,exp.elem[i]);
					}
				}
				else	//原来为空栈，直接把右括号压进去
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
				else	//原来为空栈，直接把右括号压进去
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
				else	//原来为空栈，直接把右括号压进去
				{
					Push(&S,exp.elem[i]);
				}
				break;
		}
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