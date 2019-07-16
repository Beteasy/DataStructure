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

//--------------线性表的单链表存储结构-----------------
typedef struct LNode
{
	ElemType data;
	struct LNode *next;

}LNode, *LinkList;


//函数声明
void CreatList_L(LinkList *L, int n);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
void PrintList(LinkList L);
Status ListDelete(LinkList *L, ElemType e);

int main()
{
	LinkList La;
	int num;
	ElemType e;
	printf("请输入集合La中元素的个数:");
	scanf("%d", &num);
	printf("请输入集合La中的元素:");
	CreatList_L(&La,num);
	printf("请输入指定删除的元素:");
	scanf("%d", &e);
	printf("删除前的集合LA:\n");
	PrintList(La);
	ListDelete(&La, e);
	printf("\n删除后的集合LA:\n");
	PrintList(La);
	return 0;
}

void CreatList_L(LinkList *L, int n)
{
	//逆位序输入n个元素的值，建立带表头节点的单链线性表L
	int i;
	LinkList p;
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = *L;			//创建空表
	for(i = n; i>0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

/*void CreatList_L(LinkList *L, int n)
{
	//正位序输入n个元素的值，建立带表头节点的单链线性表L
	int i;
	LinkList cur, tail;
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	tail = *L;
	for(i=n; i>0; --i)
	{
		cur = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &cur->data);
		tail->next = cur;
		tail = cur;
		tail->next = NULL;
	}
}*/


void PrintList(LinkList L)
{
	LinkList p;
	p = L->next;
	if(ListEmpty(L))
	{
		printf("an empty list\n");
	}
	while(p!=L)
	{
		printf("%3d", (*p).data);
		p = p->next;
	}
	printf("\n");
}


Status ListEmpty(LinkList L)
{
	if(L->next!=L)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int ListLength(LinkList L)
{
	LinkList p;
	int length = 0;
	p = L->next;
	while(p!=L)
	{
		length++;
		p = p->next;
	}
	return length;
}


Status ListDelete(LinkList *L, ElemType e)
{
	LinkList p, pre, q;
	p = (*L)->next;
	pre = *L;
	if(p==*L)	//L为空表
	{
		return ERROR;
	}
	while(p!=*L)
	{
		if(p->data == e)
		{
			pre->next = p->next;
			q = p;
			p = p->next;
			free(q);
		}
		else
		{
			pre = p;
			p = p->next;
		}
		
	}
	return OK;
}