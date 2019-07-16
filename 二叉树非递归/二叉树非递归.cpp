#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;


/**********二叉树链式存储表示*****************/
typedef int TElemType;
typedef struct BiTreeNode
{
	TElemType data;
	struct BiTreeNode *lchild, *rchild;
}BiTreeNode, *BiTree;

/*************栈的顺序存储表示****************/
#define STACK_INIT_SIZE 10	//存储空间初始分配量
#define STACKINCREMENT 5	//存储空间分配增量
typedef BiTree SElemType ;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

/****************函数声明***************/
void InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
Status InitStack(SqStack *S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
Status StackEmpty(SqStack S);
void PreOrderTraverse(BiTree T);
void PrintStack(SqStack S);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);


int main()
{
	BiTree THead;
	InitBiTree(&THead);
	printf("请输入数据元素(0表示没有左或右孩子,不记录在内):");
	CreateBiTree(&THead);
	printf("前序遍历的结果为:\n");
	PreOrderTraverse(THead);
	printf("\n中序遍历的结果为:\n");
	InOrderTraverse(THead);
	printf("\n后序遍历的结果为:\n");
	PostOrderTraverse(THead);
	return 0;
}

void InitBiTree(BiTree *T)
{
	(*T) = NULL;
}


Status CreateBiTree(BiTree *T)
{

	//前序递归创建二叉树
	TElemType child;
	scanf("%d", &child);
	if(child == 0)
	{
		(*T) = NULL;
	}
	else
	{
		(*T) = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		(*T)->data = child;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
	return OK;
}

Status InitStack(SqStack *S)
{
	//构造一个空的栈S
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
	{
		exit(OVERFLOW);		//空间分配失败
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType *e)
{
	//若栈不空，则用e返回S的栈顶元素,并返回OK，否则返回ERROR
	if(S.top == S.base)
	{
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}

Status Push(SqStack *S, SElemType e)
{
	if(((*S).top-(*S).base) >= (*S).stacksize)		//栈的空间满了
	{
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));		//分配新的空间
		if(!(*S).base)
		{
			exit(OVERFLOW);		//分配空间失败
		}
		(*S).top = (*S).base + (*S).stacksize;		//更新栈顶指针
		(*S).stacksize += STACKINCREMENT;		//更新栈的空间的大小
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
	return FALSE;
}

/*void PrintStack(SqStack S)
{
	SElemType *cur=S.base;
	while(cur<S.top)
		{
			printf("%d", (*cur)->data);
			*cur++;
		}
		printf("\n");
}*/

void PreOrderTraverse(BiTree T)
{
	//前序非递归遍历二叉树
	SqStack S;
	InitStack(&S);
	BiTree p, e;
	p = T;
	while(p || !StackEmpty(S))
	{
		 
		while(p)
		{
			printf("%6d",p->data);
			Push(&S,p);
			p = p->lchild;
			
		}
		if(!StackEmpty(S))
		{
			Pop(&S,&e);
			p = e->rchild;
		}
	}
}

void InOrderTraverse(BiTree T)
{
	//中序非递归遍历二叉树
	SqStack S;
	InitStack(&S);
	BiTree p, e;
	p = T;
	while(p || !StackEmpty(S))
	{
		while(p)
		{
			Push(&S,p);
			p = p->lchild;
		}
		if(!StackEmpty(S))
		{
			Pop(&S,&e);
			printf("%6d", e->data);
			p = e->rchild;
		}
	}
}

/*void PostOrderTraverse(BiTree T)
{
	SqStack S;
	InitStack(&S);
	BiTree p, e, top;
	p = T;
	while(p || !StackEmpty(S))
	{
		while(p)
		{
			Push(&S,p);
			p = p->lchild;
		}
		if(!StackEmpty(S))
		{
			GetTop(S,&top);
			//Pop(&S,&e);
			//printf("%3d", top->data);
			p = top->rchild;
		}
		if(!p && !StackEmpty(S))
		{
			Pop(&S,&e);
			printf("%3d", e->data);
			if(!StackEmpty(S))
			{
				GetTop(S,&top);
				p = top->rchild;
			}
		}
	}
}*/

void PostOrderTraverse(BiTree T)
{
	SqStack S;		//设置栈用于存储结点
	InitStack(&S);
	BiTree p, e, Etop;
	p = T;
	//int num;
	int flag[10];	//设置一个标记数组，用于记录结点的访问情况，0代表访问左子树，1代表访问右子树
	while(p || !StackEmpty(S))
	{
		while(p)
		{
			Push(&S,p);
			flag[((S.top)-(S.base))-1] = 0;	//此处访问左子树，将结点访问情况标记为0
			p = p->lchild;
		}
		while(!StackEmpty(S) && flag[((S.top)-(S.base))-1] == 1)	//如果栈不空，并且结点的右子树访问完，从右子树返回，则该结点访问完毕，将其出栈
		{
			Pop(&S,&e);
			printf("%6d", e->data);
		}
		if(!StackEmpty(S))	//结点的左子树访问完以后，开始访问其右子树，将结点的访问情况标记为1
		{
			GetTop(S,&Etop);
			flag[((S.top)-(S.base))-1] = 1;
			p = Etop->rchild;
		}
		
	}
}

// 二叉树层序非递归.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h> 

/******预定义*******/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef int TElemType;

typedef struct BiTreeNode
{
	TElemType data;
	struct BiTreeNode *lchild, *rchild;
}BiTreeNode, *BiTree;

/*****循环队列的顺序存储结构******/
#define MAXQSIZE 20
typedef BiTree  QElemType;

typedef struct {
	QElemType *base;	//初始化的动态分配存储空间	
	int front;		//头指针，若队列不空，指向队列头元素
	int rear;		//尾指针，若队列不为空，指向队列尾元素的下一个位置
}SqQueue;


/*******函数声明***********/
Status InitQueue(SqQueue *Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);
int QueueLength(SqQueue Q);
void InitBiTree(BiTree *T);
Status createBiTree(BiTree *T);
void LayTraverse(BiTree T);
void LayTraverse_digui(BiTree T);


SqQueue Q;



int main()
{
	InitQueue(&Q);
	BiTree THead;
	InitBiTree(&THead);
	printf("请输入结点数据(0代表没有左或右孩子，不计算在结点内):");
	createBiTree(&THead);
	printf("层序递归遍历的结果为:");
	LayTraverse_digui(THead);
	printf("\n");
	printf("层序非递归遍历的结果为:");
	LayTraverse(THead);
	system("pause");
	return 0;
}


/********循环队列的基本操作算法**********/

//构造一个空队列
Status InitQueue(SqQueue *Q)
{
	(*Q).base = (QElemType *)malloc(sizeof(QElemType)*MAXQSIZE);	//为队列分配存储空间
	if (!(*Q).base)
	{		//空间分配失败
		exit(OVERFLOW);
	}
	(*Q).front = 0;
	(*Q).rear = 0;
	return OK;
}

//入队操作
Status EnQueue(SqQueue *Q, QElemType e)
{
	if (((*Q).rear + 1) % MAXQSIZE == (*Q).front)	//队列空间满了
	{
		return ERROR;
	}
	(*Q).base[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % MAXQSIZE;	//将尾指针向后移动,此处是循环队列，所以不是直接+1
	return OK;
}

//出队操作
Status DeQueue(SqQueue *Q, QElemType *e)	//若队列不空，则将对头元素出队，用e返回，并返回OK
{
	if ((*Q).rear == (*Q).front)	//队列为空
	{
		return ERROR;
	}
	*e = ((*Q).base[(*Q).front]);
	(*Q).front = ((*Q).front + 1) % MAXQSIZE;
	return OK;
}

//求队列的长度
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


void InitBiTree(BiTree *T)
{
	(*T) = NULL;
}

Status createBiTree(BiTree *T)
{
	TElemType child;
	scanf_s("%d", &child);
	if (child == 0)
	{
		(*T) = NULL;
	}
	else
	{
		(*T) = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		(*T)->data = child;
		createBiTree(&(*T)->lchild);
		createBiTree(&(*T)->rchild);
	}
	return OK;
}

//二叉树层序遍历递归算法
void LayTraverse_digui(BiTree T)
{
	if (T)
	{
		printf("%3d", T->data);
		if (T->lchild)
		{
			EnQueue(&Q, T->lchild);
		}
		if (T->rchild)
		{
			EnQueue(&Q, T->rchild);
		}
		if (QueueLength(Q))
		{
			DeQueue(&Q, &T);
			LayTraverse_digui(T);
		}
		
	}
}



//二叉树层序遍历非递归算法
void LayTraverse(BiTree T)
{
	SqQueue Q;
	InitQueue(&Q);
	if (T)
	{
		EnQueue(&Q,T);
		while (QueueLength(Q))
		{
			DeQueue(&Q, &T);
			printf("%3d", T->data);
			if(T->lchild)
			{
				EnQueue(&Q, T->lchild);
			}
			if (T->rchild)
			{
				EnQueue(&Q, T->rchild);
			}
		}
	}
	
}

