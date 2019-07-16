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
Status GetElem_L(LinkList L, int i, ElemType *e);
Status ListInsert_L(LinkList L, int i, ElemType e);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType a, ElemType b));
int equal(ElemType a, ElemType b);
void Union(LinkList *La, LinkList Lb);
void PrintList(LinkList L);

int main()
{
	LinkList La;
	LinkList Lb;
	int num;
	printf("请输入集合La中元素的个数:");
	scanf("%d", &num);
	printf("请输入集合La中的元素:");
	CreatList_L(&La,num);
	printf("请输入集合Lb中元素的个数:");
	scanf("%d", &num);
	printf("请输入集合Lb中的元素:");
	CreatList_L(&Lb,num);
	printf("合并前的集合LA:\n");
	PrintList(La);
	printf("\n合并前的集合LB:\n");
	PrintList(Lb);
	Union(&La,Lb);
	printf("\n合并后的集合LA:\n");
	PrintList(La);

	return 0;
}


void CreatList_L(LinkList *L, int n)
{
	//逆位序输入n个元素的值，建立带表头节点的单链线性表L
	int i;
	LinkList p;
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
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
	while(p)
	{
		printf("%3d", (*p).data);
		p = p->next;
	}
}

Status ListEmpty(LinkList L)
{
	if(L->next)
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
	while(p)
	{
		length++;
		p = p->next;
	}
	return length;
}


Status GetElem_L(LinkList L, int i, ElemType *e)
{
	//L为带头结点的单链表的头指针
	//当第i个元素存在时，其值附给e，并返回OK，否则返回ERROR
	LinkList p;
	p = L->next;	//初始化，指向第一个节点，j为计数器
	int j = 1;
	while(p && j<i)		//顺指针向后查找，直到p指向第i个元素或者p为空
	{
		p = p->next;
		++j;
	}
	if(!p || j>i)
	{
		return ERROR;
	}
	*e = p->data;
	return OK;
}

int equal(ElemType a, ElemType b)
{
	if(a == b)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType a, ElemType b))
{
	//在顺序线性表L中查找第一个值与e满足compare()的元素的位序
	//若找到，则返回其在L中的位序，否则返回0
	int length;
	int i = 1;		//i的初值为第一个元素的位序
	LinkList p;		
	p = L->next;	//p的初值为第一个元素的存储位置
	length = ListLength(L);
	while(i<=length && !(*compare)(p->data,e))
	{
		p = p->next;	//don not foreget it
		++i;
	}
	if(i<=length)
	{
		return i;
	}
	else
	{
		return 0;
	}
}

Status ListInsert_L(LinkList L, int i, ElemType e)
{
	//在带头结点的单链线性表L中第i个位置之前插入元素e
	LinkList p, s;
	//LNode *p, *s;
	p = L;
	int j;
	j = 0;
	while(p && j<i-1)	//寻找第i-1个结点
	{
		p = p->next;
		++j;
	}
	if(!p || j>i-1)		//i<1或者大于表长加1
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));		//生成新结点
	s->data = e;								//插入L中
	s->next = p->next;
	p->next = s;
	return OK;
}

void Union(LinkList *La, LinkList Lb)
{
	//将所有在线性表Lb中，但不在La中的数据元素插入到La中
	int La_len, Lb_len;
	int i;
	ElemType e;
	La_len = ListLength(*La);
	Lb_len = ListLength(Lb);
	for(i=1; i<=Lb_len; i++)
	{
		GetElem_L(Lb,i,&e);
		if(!LocateElem(*La,e,equal))
		{
			ListInsert_L(*La,++La_len,e);
		}
	}
}