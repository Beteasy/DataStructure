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
void CreatList_L(LinkList L, int n);
//LinkList CreatList_L(int n);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status ListInsert_L(LinkList L, int i, ElemType e);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType a, ElemType b));
int equal(ElemType a, ElemType b);
void Union(LinkList La, LinkList Lb);
void PrintList(LinkList L);

int main()
{
	LinkList Pa;
	//LinkList Lb;
	int num;
	LNode La;
	//LNode Lb;
	Pa = &La;
	printf("请输入集合La中元素的个数:");
	scanf("%d", &num);
	printf("请输入集合La中的元素:");
	CreatList_L(Pa,num);
	//CreatList_L(La,num);
	LinkList p = Pa->next;
	while(p)
	{
		printf("%d",  p->data);
		p = p->next;
	}
	/*printf("请输入集合Lb中元素的个数:");
	scanf("%d", &num);
	printf("请输入集合Lb中的元素:");*/
	/*CreatList_L(Lb,num);
	printf("合并前的集合LA:\n");
	PrintList(La);
	printf("合并前的集合LB:\n");
	PrintList(Lb);*/
	return 0;
}


/*LinkList CreatList_L(int n)
{
	//逆位序输入n个元素的值，建立带表头节点的单链线性表L
	LinkList L;
	int i;
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	//p = (LinkList)malloc(sizeof(LNode));
	for(i = n; i>0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		//printf("%d", p->data);
		p->next = L->next;
		L->next = p;
	}
	return L;
}*/

void CreatList_L(LinkList L, int n)
{
	//逆位序输入n个元素的值，建立带表头节点的单链线性表L
	int i;
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for(i = n; i>0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
}

void PrintList(LinkList L)
{
	LinkList p;
	p = L->next;
	while(p!=NULL)
	{
		printf("%d", p->data);
		p = p->next;
	}
}