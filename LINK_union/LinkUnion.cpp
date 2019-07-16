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
void Union(LinkList *La, LinkList Lb);
void PrintList(LinkList L);

int main()
{
	LinkList La;
	LinkList Lb;
	int num;
	printf("�����뼯��La��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��La�е�Ԫ��:");
	CreatList_L(&La,num);
	printf("�����뼯��Lb��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��Lb�е�Ԫ��:");
	CreatList_L(&Lb,num);
	printf("�ϲ�ǰ�ļ���LA:\n");
	PrintList(La);
	printf("\n�ϲ�ǰ�ļ���LB:\n");
	PrintList(Lb);
	Union(&La,Lb);
	printf("\n�ϲ���ļ���LA:\n");
	PrintList(La);

	return 0;
}


void CreatList_L(LinkList *L, int n)
{
	//��λ������n��Ԫ�ص�ֵ����������ͷ�ڵ�ĵ������Ա�L
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
	//��λ������n��Ԫ�ص�ֵ����������ͷ�ڵ�ĵ������Ա�L
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
	//LΪ��ͷ���ĵ������ͷָ��
	//����i��Ԫ�ش���ʱ����ֵ����e��������OK�����򷵻�ERROR
	LinkList p;
	p = L->next;	//��ʼ����ָ���һ���ڵ㣬jΪ������
	int j = 1;
	while(p && j<i)		//˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ���pΪ��
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
	//��˳�����Ա�L�в��ҵ�һ��ֵ��e����compare()��Ԫ�ص�λ��
	//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
	int length;
	int i = 1;		//i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	LinkList p;		
	p = L->next;	//p�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
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
	//�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
	LinkList p, s;
	//LNode *p, *s;
	p = L;
	int j;
	j = 0;
	while(p && j<i-1)	//Ѱ�ҵ�i-1�����
	{
		p = p->next;
		++j;
	}
	if(!p || j>i-1)		//i<1���ߴ��ڱ���1
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));		//�����½��
	s->data = e;								//����L��
	s->next = p->next;
	p->next = s;
	return OK;
}

void Union(LinkList *La, LinkList Lb)
{
	//�����������Ա�Lb�У�������La�е�����Ԫ�ز��뵽La��
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