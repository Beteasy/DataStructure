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
	printf("�����뼯��La��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��La�е�Ԫ��:");
	CreatList_L(Pa,num);
	//CreatList_L(La,num);
	LinkList p = Pa->next;
	while(p)
	{
		printf("%d",  p->data);
		p = p->next;
	}
	/*printf("�����뼯��Lb��Ԫ�صĸ���:");
	scanf("%d", &num);
	printf("�����뼯��Lb�е�Ԫ��:");*/
	/*CreatList_L(Lb,num);
	printf("�ϲ�ǰ�ļ���LA:\n");
	PrintList(La);
	printf("�ϲ�ǰ�ļ���LB:\n");
	PrintList(Lb);*/
	return 0;
}


/*LinkList CreatList_L(int n)
{
	//��λ������n��Ԫ�ص�ֵ����������ͷ�ڵ�ĵ������Ա�L
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
	//��λ������n��Ԫ�ص�ֵ����������ͷ�ڵ�ĵ������Ա�L
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