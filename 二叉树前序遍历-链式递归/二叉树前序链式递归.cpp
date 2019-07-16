#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status;

/*************��������ʽ�洢��ʾ********************/
typedef int TElemType;
typedef struct BiTreeNode
{
	TElemType data;
	struct BiTreeNode *lchild, *rchild;		//��Ϊ���Һ���ָ��ָ����ǽ��,����Ҫ�ýṹ��ָ��
}BiTreeNode, *BiTree;


/***********��������*************/
void InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);


int main()
{
	BiTree THead;
	InitBiTree(&THead);
	printf("������������(0����û������Һ��ӣ��������ڽ����):");
	CreateBiTree(&THead);
	printf("ǰ������Ľ��Ϊ:\n");
	PreOrderTraverse(THead);
	printf("\n��������Ľ��Ϊ:\n");
	InOrderTraverse(THead);
	printf("\n���������Ľ��Ϊ:\n");
	PostOrderTraverse(THead);
	return 0;
}

void InitBiTree(BiTree *T)
{
	//��ʼ��һ�ÿյĶ�����
	/*(*T) = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;*/
	(*T)=NULL;
}


Status CreateBiTree(BiTree *T)
{
	//ǰ��ݹ鴴��һ��������
	TElemType child;
	scanf("%d", &child);
	if(child == 0)
	{
		//0��������������������ڽ����
		/*(*T)->lchild = NULL;
		(*T)->rchild = NULL;*/
		(*T)=NULL;
	}
	else
	{
		/*(*T)->lchild = (BiTreeNode *)malloc(sizeof(BitreeNode));
		((*T)->lchild)->data = child;
		CreateBiTree((*T)->lchild);
		CreateBiTree((*T)->rchild);*/
		(*T)= (BiTreeNode *)malloc(sizeof(BiTreeNode));
		(*T)->data = child;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
	return OK;
}

void PreOrderTraverse(BiTree T)
{
	//ǰ�����������
	if(T)
	{
		printf("%3d", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	//�������������
	if(T)
	{
		InOrderTraverse(T->lchild);
		printf("%3d", T->data);
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTree T)
{
	//��������������
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%3d", T->data);
	}
}