#include <stdio.h>
#include <stdlib.h>


/*************二叉树链式存储表示********************/
typedef int TElemtype;
typedef struct BiTreeNode
{
	TElemtype data;
	struct BiTreeNode *lchild, *rchild;		//因为左右孩子指针指向的是结点,所以要用结构体指针
}BiTreeNode, *BiTree;


/***********函数声明*************/
void InitBiTree(BiTree *T);


int main()
{
	BiTree THead;
	InitBiTree(&THead);
	return 0;
}

void InitBiTree(BiTree *T)
{
	(*T) = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
}

/*void CreateBiTree(BiTree *T)
{
	
}*/