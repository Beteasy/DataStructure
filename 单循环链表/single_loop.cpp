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
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
void PrintList(LinkList L);
Status ListDelete(LinkList *L, ElemType e);

int main()
{
	LinkList La;
	int num;
	ElemType e;
	printf("�����뼯��La��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��La�е�Ԫ��:");
	CreatList_L(&La,num);
	printf("������ָ��ɾ����Ԫ��:");
	scanf("%d", &e);
	printf("ɾ��ǰ�ļ���LA:\n");
	PrintList(La);
	ListDelete(&La, e);
	printf("\nɾ����ļ���LA:\n");
	PrintList(La);
	return 0;
}

void CreatList_L(LinkList *L, int n)
{
	//��λ������n��Ԫ�ص�ֵ����������ͷ�ڵ�ĵ������Ա�L
	int i;
	LinkList p;
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = *L;			//�����ձ�
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
	if(p==*L)	//LΪ�ձ�
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