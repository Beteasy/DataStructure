#include <stdio.h>
#include <stdlib.h>


/*************��������ʽ�洢��ʾ********************/
typedef int TElemtype;
typedef struct BiTreeNode
{
	TElemtype data;
	struct BiTreeNode *lchild, *rchild;		//��Ϊ���Һ���ָ��ָ����ǽ��,����Ҫ�ýṹ��ָ��
}BiTreeNode, *BiTree;


/***********��������*************/
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