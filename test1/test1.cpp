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

//--------���Ա�Ķ�̬����˳��洢�ṹ------------
#define LIST_INIT_SIZE 100	//���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCREMENT 10	//���Ա�洢�ռ�ķ�������
//typedef struct
typedef struct
{
	ElemType *elem;	//�洢�ռ��ַ
	int length;	//��ǰ����
	int listsize;	//��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ)
}SqList;

//��������
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
	printf("�ϲ�ǰ�ļ���LA:\n");
	printList(&La);
	printf("\n");
	printf("�ϲ�ǰ�ļ���LB:\n");
	printList(&Lb);
	printf("\n");
	Union(&La,Lb);
	printf("�ϲ���ļ���LA:\n");
	printList(&La);
	printf("\n");
	return 0;
}


Status InitList_Sq(SqList *L)
{
	//����һ���յ����Ա�L
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!(*L).elem)
	{
		exit(OVERFLOW);	//���䴢��ʧ��
	}
	(*L).length = 0;	//�ձ���Ϊ0
	(*L).listsize = LIST_INIT_SIZE;	//��ʼ�洢����
	return OK;
}

void creatList(SqList *L)
{
	ElemType x;
	int num;
	int i = 0;
	printf("�����뼯����Ԫ�صĸ���:");
	scanf("%d", &num);
	
	printf("�����뼯���е�Ԫ��:");
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
	//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
	//i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)+1
	if( i<1 || i>(*L).length+1 )
	{
		return ERROR;	//iֵ���Ϸ�
	}
	if( (*L).length >= (*L).listsize )	//��ǰ�洢�ռ����������ӷ���
	{
		ElemType *newbase;	
		newbase = (ElemType *) realloc ( (*L).elem, ( (*L).listsize + LISTINCREMENT ) * sizeof (ElemType));
		if(!newbase)	//����洢ʧ��
		{
			exit(OVERFLOW);
		}
		(*L).elem  = newbase;	//�»�ַ
		(*L).listsize += LISTINCREMENT;	//���Ӵ洢����
	}
	ElemType *p, *q;
	q = &((*L).elem[i-1]);	//qΪ����λ��
	for(p = &((*L).elem[((*L).length-1)]); p >= q; --p)	//����λ�ü�֮���Ԫ������
	{
		*(p+1) = *p;
	}
	*q = e;	//����e
	++(*L).length;	//����1
	return OK;
}

int LocateElem_Sq(SqList L, ElemType e,  Status (*compare)(ElemType, ElemType))
{
	//��˳�����Ա�L�в��ҵ�һ��ֵ��e����compare()��Ԫ�ص�λ��
	//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
	int i;
	ElemType *p;
	i = 1;	//i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	p = L.elem;	//P�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	while(i<=L.length&&!(*compare)(*p++,e))	//�Ⱥ�*p�Ƚϣ�Ȼ��p��1����
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
	//�����������Ա�Lb�У�������La�е�����Ԫ�ز��뵽La��
	int La_len, Lb_len;
	int i;
	ElemType e;
	La_len = ListLength(*La);	//�����Ա�ĳ���
	Lb_len = ListLength(Lb);
	for(i=1; i<=Lb_len; i++)
	{
		GetElem(Lb,i,&e);
		if(!LocateElem_Sq(*La,e,equal))	//La�в�������e��ͬ��Ԫ�������֮
		{
			ListInsert_Sq(La,++La_len,e);
		}
	}
}