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

typedef int ElemType;

//--------线性表的动态分配顺序存储结构------------
#define LIST_INIT_SIZE 100	//线性表存储空间的初始分配量
#define LISTINCREMENT 10	//线性表存储空间的分配增量
//typedef struct
typedef struct
{
	ElemType *elem;	//存储空间基址
	int length;	//当前长度
	int listsize;	//当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;


Status InitList_Sq(SqList *L);

void Match();


int main()
{
	Match();
	return 0;
}
Status InitList_Sq(SqList *L)
{
	//构造一个空的线性表L
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!(*L).elem)
	{
		exit(OVERFLOW);	//分配储存失败
	}
	(*L).length = 0;	//空表长度为0
	(*L).listsize = LIST_INIT_SIZE;	//初始存储容量
	return OK;
}

void Match()
{
	SqList La;
	InitList_Sq(&La);
	char ch;
	int i=0;
	printf("请输入表达式:");
	ch = getchar();		//	从终端读取一个字符
	while(ch != '\n')
	{
		switch(ch)
		{
		case '(':
		case '[':
		case '{':La.elem[i++] = ch;
				La.length++;
				break;		//如果是左括号，将其放入线性表的末尾
		case ')':
				if(La.length>0)		//如果线性表不为空	
				{
					if(La.elem[La.length-1] == '(')		//如果两个括号匹配
					{
						La.length--;		//将其移除
					}
					else
					{
						La.elem[i++]=ch;	//如果不匹配，将新元素放入线性表的末尾
						La.length++;
					}
				}
				else	//原来为空表将新元素放入线性表的末尾
				{
					La.elem[i++]=ch;	
					La.length++;
				}
				break;

		case ']':
				if(La.length>0)		
				{
					if(La.elem[La.length-1] == '[')		
					{
						La.length--;	
					}
					else
					{
						La.elem[i++]=ch;	
						La.length++;
					}
				}
				else	
				{
					La.elem[i++]=ch;	
					La.length++;
				}
				break;

		case '}':
				if(La.length>0)		
				{
					if(La.elem[La.length-1] == '{')
					{
						La.length--;
					}
					else
					{
						La.elem[i++]=ch;	
						La.length++;
					}
				}
				else	
				{
					La.elem[i++]=ch;	
					La.length++;
				}
					break;
		}
		ch = getchar();		//从终端读取下一个字符
	}
	if(La.length==0)
	{
		printf("表达式中的括号匹配\n");
	}
	else
	{
		printf("表达式中的括号不匹配\n");
		printf("当前线性表中的内容为:");
		for(int i=0;i<La.length; i++)
		{
			printf("%c", La.elem[i]);
		}
	}
}