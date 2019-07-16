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

//--------线性表的动态分配顺序存储结构------------
#define LIST_INIT_SIZE 100	//线性表存储空间的初始分配量
#define LISTINCREMENT 10	//线性表存储空间的分配增量
//typedef struct
typedef struct
{
	ElemType *elem;	//存储空间基址
	int length;	//当前长度
	int listsize;	//当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;

//函数声明
Status InitList_Sq(SqList *L);
Status ListInsert_Sq(SqList *L, int i, ElemType e);
int LocateElem_Sq(SqList L, ElemType e,  Status (*compare)(ElemType, ElemType));
void creatList(SqList *L);
void printList(SqList *L);
int ListLength(SqList *L);
Status ListEmpty(SqList *L);
int equal(ElemType a, ElemType b);
Status GetElem(SqList L, int i, ElemType *e);
void Union(SqList *La, SqList Lb);


int main()
{
	SqList La;
	SqList Lb;
	InitList_Sq(&La);
	InitList_Sq(&Lb);
	creatList(&La);
	creatList(&Lb);
	printf("合并前的集合LA:\n");
	printList(&La);
	printf("\n");
	printf("合并前的集合LB:\n");
	printList(&Lb);
	printf("\n");
	Union(&La,Lb);
	printf("合并后的集合LA:\n");
	printList(&La);
	printf("\n");
	return 0;
}


Status InitList_Sq(SqList *L)
{
	//构造一个空的线性表L
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!(*L).elem)
	{
		exit(OVERFLOW);	//分配储存失败
	}
	(*L).length = 0;	//空表长度为0
	(*L).listsize = LIST_INIT_SIZE;	//初始存储容量
	return OK;
}

void creatList(SqList *L)
{
	ElemType x;
	int num;
	int i = 0;
	printf("请输入集合中元素的个数:");
	scanf("%d", &num);
	
	printf("请输入集合中的元素:");
	while(num--)
	{
		scanf("%d", &x);
		(*L).elem[i] = x;
		i++;
	}
	(*L).length = num;
}

void printList(SqList *L)
{
	int i = 0;
	while(i<(*L).length)
	{
		printf("%d\t", (*L).elem[i++]);
	}
}

int ListLength(SqList L)
{
	return L.length;
}

Status ListEmpty(SqList *L)
{
	if( (*L).length == 0 )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status ListInsert_Sq(SqList *L, int i, ElemType e)	
{
	//在顺序线性表L中第i个位置之前插入新的元素e
	//i的合法值为1<=i<=ListLength_Sq(L)+1
	if( i<1 || i>(*L).length+1 )
	{
		return ERROR;	//i值不合法
	}
	if( (*L).length >= (*L).listsize )	//当前存储空间已满，增加分配
	{
		ElemType *newbase;	
		newbase = (ElemType *) realloc ( (*L).elem, ( (*L).listsize + LISTINCREMENT ) * sizeof (ElemType));
		if(!newbase)	//分配存储失败
		{
			exit(OVERFLOW);
		}
		(*L).elem  = newbase;	//新基址
		(*L).listsize += LISTINCREMENT;	//增加存储容量
	}
	ElemType *p, *q;
	q = &((*L).elem[i-1]);	//q为插入位置
	for(p = &((*L).elem[((*L).length-1)]); p >= q; --p)	//插入位置及之后的元素右移
	{
		*(p+1) = *p;
	}
	*q = e;	//插入e
	++(*L).length;	//表长加1
	return OK;
}

int LocateElem_Sq(SqList L, ElemType e,  Status (*compare)(ElemType, ElemType))
{
	//在顺序线性表L中查找第一个值与e满足compare()的元素的位序
	//若找到，则返回其在L中的位序，否则返回0
	int i;
	ElemType *p;
	i = 1;	//i的初值为第一个元素的位序
	p = L.elem;	//P的初值为第一个元素的存储位置
	while(i<=L.length&&!(*compare)(*p++,e))	//先和*p比较，然后p加1后移
	{
		++i;
	}
	if(i<=L.length)
	{
		return i;
	}
	else
	{
		return 0;
	}
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

Status GetElem(SqList L, int i, ElemType *e)
{
	if( i<1 || i>L.length)
	{
		exit(OVERFLOW);
	}
	*e = L.elem[i-1];
	return OK;
}

void Union(SqList *La, SqList Lb)
{
	//将所有在线性表Lb中，但不在La中的数据元素插入到La中
	int La_len, Lb_len;
	int i;
	ElemType e;
	La_len = ListLength(*La);	//求线性表的长度
	Lb_len = ListLength(Lb);
	for(i=1; i<=Lb_len; i++)
	{
		GetElem(Lb,i,&e);
		if(!LocateElem_Sq(*La,e,equal))	//La中不存在与e相同的元素则插入之
		{
			ListInsert_Sq(La,++La_len,e);
		}
	}
}