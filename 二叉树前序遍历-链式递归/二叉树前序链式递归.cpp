#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status;

/*************二叉树链式存储表示********************/
typedef int TElemType;
typedef struct BiTreeNode
{
	TElemType data;
	struct BiTreeNode *lchild, *rchild;		//因为左右孩子指针指向的是结点,所以要用结构体指针
}BiTreeNode, *BiTree;


/***********函数声明*************/
void InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);


int main()
{
	BiTree THead;
	InitBiTree(&THead);
	printf("请输入结点数据(0代表没有左或右孩子，不计算在结点内):");
	CreateBiTree(&THead);
	printf("前序遍历的结果为:\n");
	PreOrderTraverse(THead);
	printf("\n中序遍历的结果为:\n");
	InOrderTraverse(THead);
	printf("\n后续遍历的结果为:\n");
	PostOrderTraverse(THead);
	return 0;
}

void InitBiTree(BiTree *T)
{
	//初始化一棵空的二叉树
	/*(*T) = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;*/
	(*T)=NULL;
}


Status CreateBiTree(BiTree *T)
{
	//前序递归创建一个二叉树
	TElemType child;
	scanf("%d", &child);
	if(child == 0)
	{
		//0代表输入结束，不计算在结点内
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
	//前序遍历二叉树
	if(T)
	{
		printf("%3d", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	//中序遍历二叉树
	if(T)
	{
		InOrderTraverse(T->lchild);
		printf("%3d", T->data);
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTree T)
{
	//后续遍历二叉树
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%3d", T->data);
	}
}