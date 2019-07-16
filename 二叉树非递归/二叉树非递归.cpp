#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;


/**********��������ʽ�洢��ʾ*****************/
typedef int TElemType;
typedef struct BiTreeNode
{
	TElemType data;
	struct BiTreeNode *lchild, *rchild;
}BiTreeNode, *BiTree;

/*************ջ��˳��洢��ʾ****************/
#define STACK_INIT_SIZE 10	//�洢�ռ��ʼ������
#define STACKINCREMENT 5	//�洢�ռ��������
typedef BiTree SElemType ;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

/****************��������***************/
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
	printf("����������Ԫ��(0��ʾû������Һ���,����¼����):");
	CreateBiTree(&THead);
	printf("ǰ������Ľ��Ϊ:\n");
	PreOrderTraverse(THead);
	printf("\n��������Ľ��Ϊ:\n");
	InOrderTraverse(THead);
	printf("\n��������Ľ��Ϊ:\n");
	PostOrderTraverse(THead);
	return 0;
}

void InitBiTree(BiTree *T)
{
	(*T) = NULL;
}


Status CreateBiTree(BiTree *T)
{

	//ǰ��ݹ鴴��������
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
	//����һ���յ�ջS
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
	{
		exit(OVERFLOW);		//�ռ����ʧ��
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType *e)
{
	//��ջ���գ�����e����S��ջ��Ԫ��,������OK�����򷵻�ERROR
	if(S.top == S.base)
	{
		return ERROR;
	}
	*e = *(S.top-1);
	return OK;
}

Status Push(SqStack *S, SElemType e)
{
	if(((*S).top-(*S).base) >= (*S).stacksize)		//ջ�Ŀռ�����
	{
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));		//�����µĿռ�
		if(!(*S).base)
		{
			exit(OVERFLOW);		//����ռ�ʧ��
		}
		(*S).top = (*S).base + (*S).stacksize;		//����ջ��ָ��
		(*S).stacksize += STACKINCREMENT;		//����ջ�Ŀռ�Ĵ�С
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
	//ǰ��ǵݹ����������
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
	//����ǵݹ����������
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
	SqStack S;		//����ջ���ڴ洢���
	InitStack(&S);
	BiTree p, e, Etop;
	p = T;
	//int num;
	int flag[10];	//����һ��������飬���ڼ�¼���ķ��������0���������������1�������������
	while(p || !StackEmpty(S))
	{
		while(p)
		{
			Push(&S,p);
			flag[((S.top)-(S.base))-1] = 0;	//�˴���������������������������Ϊ0
			p = p->lchild;
		}
		while(!StackEmpty(S) && flag[((S.top)-(S.base))-1] == 1)	//���ջ���գ����ҽ��������������꣬�����������أ���ý�������ϣ������ջ
		{
			Pop(&S,&e);
			printf("%6d", e->data);
		}
		if(!StackEmpty(S))	//�����������������Ժ󣬿�ʼ�������������������ķ���������Ϊ1
		{
			GetTop(S,&Etop);
			flag[((S.top)-(S.base))-1] = 1;
			p = Etop->rchild;
		}
		
	}
}

// ����������ǵݹ�.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h> 

/******Ԥ����*******/
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

/*****ѭ�����е�˳��洢�ṹ******/
#define MAXQSIZE 20
typedef BiTree  QElemType;

typedef struct {
	QElemType *base;	//��ʼ���Ķ�̬����洢�ռ�	
	int front;		//ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear;		//βָ�룬�����в�Ϊ�գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;


/*******��������***********/
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
	printf("������������(0����û������Һ��ӣ��������ڽ����):");
	createBiTree(&THead);
	printf("����ݹ�����Ľ��Ϊ:");
	LayTraverse_digui(THead);
	printf("\n");
	printf("����ǵݹ�����Ľ��Ϊ:");
	LayTraverse(THead);
	system("pause");
	return 0;
}


/********ѭ�����еĻ��������㷨**********/

//����һ���ն���
Status InitQueue(SqQueue *Q)
{
	(*Q).base = (QElemType *)malloc(sizeof(QElemType)*MAXQSIZE);	//Ϊ���з���洢�ռ�
	if (!(*Q).base)
	{		//�ռ����ʧ��
		exit(OVERFLOW);
	}
	(*Q).front = 0;
	(*Q).rear = 0;
	return OK;
}

//��Ӳ���
Status EnQueue(SqQueue *Q, QElemType e)
{
	if (((*Q).rear + 1) % MAXQSIZE == (*Q).front)	//���пռ�����
	{
		return ERROR;
	}
	(*Q).base[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % MAXQSIZE;	//��βָ������ƶ�,�˴���ѭ�����У����Բ���ֱ��+1
	return OK;
}

//���Ӳ���
Status DeQueue(SqQueue *Q, QElemType *e)	//�����в��գ��򽫶�ͷԪ�س��ӣ���e���أ�������OK
{
	if ((*Q).rear == (*Q).front)	//����Ϊ��
	{
		return ERROR;
	}
	*e = ((*Q).base[(*Q).front]);
	(*Q).front = ((*Q).front + 1) % MAXQSIZE;
	return OK;
}

//����еĳ���
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

//��������������ݹ��㷨
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



//��������������ǵݹ��㷨
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

