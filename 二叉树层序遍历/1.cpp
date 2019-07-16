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

//ȫ�ֱ�������
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

