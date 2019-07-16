#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>


//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef int ElemType;

//--------------���Ա�ĵ�����洢�ṹ-----------------
typedef struct LNode
{
	ElemType data;
	struct LNode *next;

}LNode, *LinkList;



//��������
void CreatList_L(LinkList *L, int n);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status ListInsert_L(LinkList L, int i, ElemType e);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType a, ElemType b));
int equal(ElemType a, ElemType b);
void PrintList(LinkList L);
//void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc);
void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc);
void InitList_L(LinkList *L);

int main()
{
	LinkList La;
	LinkList Lb;
	LinkList Lc;
	int num;
	printf("�����뼯��La��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��La�е�Ԫ��:");
	CreatList_L(&La,num);
	printf("�����뼯��Lb��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��Lb�е�Ԫ��:");
	CreatList_L(&Lb,num);
	InitList_L(&Lc);
	printf("\n�ϲ�ǰ�ļ���LA:\n");
	PrintList(La);
	printf("\n�ϲ�ǰ�ļ���LB:\n");
	PrintList(Lb);
	printf("\n�ϲ���ļ���Lc:\n");
	//MergeList_L(&La, &Lb, &Lc);
	MergeList_L(&La,&Lb,&Lc);
	PrintList(Lc);

	return 0;
}


void CreatList_L(LinkList *L, int n)
{
	LinkList p;
	int i;
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	for(i=n;i>0;--i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

void InitList_L(LinkList *L)
{
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
}

void PrintList(LinkList L)
{
	LinkList p;
	p = L->next;
	while(p)
	{
		printf("%3d", p->data);
		p = p->next;
	}
}

int ListLength(LinkList L)
{
	LinkList p = L;
	int length = 0;
	p = p->next;
	while(p)
	{
		++length;
		p = p->next;
	}
	return length;
}

Status ListEmpty(LinkList L)
{
	if(L->next == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p;
	p = L->next;
	int j = 1;
	while(p && j<i)
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

Status ListInsert_L(LinkList L, int i, ElemType e)
{
	LinkList p, s;
	p = L;
	int j = 0;
	while(p && j<i-1)
	{
		p = p->next;
		++j;
	}
	if(!p || j>i-1)
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

/*void MergeList_L(LinkList La, LinkList Lb, LinkList Lc)
{
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;	//��La��ͷ������ΪLc��ͷ���
	while(pa && pb)
	{
		if(pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;	//����ʣ���
	free(Lb);	//�ͷ�Lb��ͷ���
}*/


void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc)
{
	LinkList pa, pb, pc;
	pa = (*La)->next;
	pb = (*Lb)->next;
	(*Lc) = pc = (*La);	//��La��ͷ������ΪLc��ͷ���
	while(pa && pb)
	{
		if(pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;	//����ʣ���
	free((*Lb));	//�ͷ�Lb��ͷ���
}


/*void MergeList_L(LinkList La, LinkList Lb, LinkList *Lc)
{
	InitList_L(Lc);
	int i, j, k;
	i = j = 1;
	k = 0;
	ElemType ai, bj;
	int La_len = ListLength(La);
	int Lb_len = ListLength(Lb);
	while(i<=La_len && j<=Lb_len)
	{
		GetElem(La,i,&ai);
		GetElem(Lb,j,&bj);
		if(ai<=bj)
		{
			ListInsert_L(*Lc,++k,ai);
			++i;
		}
		else
		{
			ListInsert_L(*Lc,++k,bj);
			++j;
		}
	}
	while(i<=La_len)
	{
		GetElem(La,i++,&ai);
		ListInsert_L(*Lc,++k,ai);
	}
	while(j<=Lb_len)
	{
		GetElem(Lb,j++,&bj);
		ListInsert_L(*Lc,++k,bj);
	}
}*/