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

//全局变量声明
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
	scanf("%d", &child);
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

