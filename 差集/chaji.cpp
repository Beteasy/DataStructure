#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define Maxsize 100
typedef int Status;

typedef int ElemType;

typedef struct
{
	ElemType data[Maxsize];
	int length;
}SqList;

void CreatList(SqList *L);
Status GetElem(SqList L, int i, ElemType *e);
Status PrintList(SqList L);
Status LocateElem(SqList L, ElemType e, Status (*compare)(ElemType a, ElemType b));
Status equal(ElemType a, ElemType b);
Status ListDelete(SqList *L, int i, ElemType *e);
void Difference(SqList *La, SqList Lb);
Status ListEmpty(SqList L);

int main()
{
	SqList La, Lb;
	CreatList(&La);
	CreatList(&Lb);
	PrintList(La);
	PrintList(Lb);
	Difference(&La, Lb);
	PrintList(La);
	return 0;
}


void CreatList(SqList *L)
{
	int  num, i, n;
	printf("enter n:");
	scanf("%d", &n);
	printf("enter nums:");
	for(i=0; i<n; i++)
	{
		scanf("%d", &num);
		(*L).data[i]  = num;
	}
	(*L).length  = n;
}

Status ListEmpty(SqList L)
{
	if(L.length==0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status PrintList(SqList L)
{
	int i=0;
	if(ListEmpty(L))
	{
		printf("an empty list\n");
		return FALSE;
	}
	while(i<L.length)
	{
		printf("%3d", L.data[i++]);
	}
	printf("\n");
	return OK;
}

int ListLength(SqList L)
{
	return L.length;
}
 
/*Status GetElem(SqList L, int i, ElemType *e)
{
	if(i<1 || i>L.length)
	{
		return ERROR;
	}
	*e = L.data[i-1];
	return OK;
}*/

/*Status equal(ElemType a, ElemType b)
{
	if(a==b)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	*/

/*Status LocateElem(SqList L, ElemType e, Status (*compare)(ElemType a, ElemType b))
{
	int i=0;
	while(i<L.length && !(*compare)(L.data[i],e))
	{
		i++;
	}
	if(i+1<=L.length)
	{
		return i+1;
	}
	else
	{
		return 0;
	}
}*/

/*Status ListDelete(SqList *L, int i, ElemType *e)
{
	ElemType *p, *q;
	if(i<1 || i>(*L).length)
	{
		return ERROR;
	}
	p = &(*L).data[i-1];
	*e = *p;
	q = &(*L).data[(*L).length-1];
	for(++p;p<=q;++p)
	{
		*(p-1) = *p;
	}
	--(*L).length;
	return OK;
}*/

/*void Difference(SqList *La, SqList Lb)
{
	int i=1, pos;
	ElemType e;
	int Lb_len = ListLength(Lb);
	for(i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);
		if(pos=LocateElem(*La,e,equal))	//if La has the same elem, delete it in La
		{
			ListDelete(La,pos,&e);
		}

	}
}	*/

void Difference(SqList *La, SqList Lb)
{
	//ElemType e;
	int i, j, k;
	for(i=0; i<Lb.length; i++)
	{
		for(j=0; j<(*La).length; j++)
		{
			if((*La).data[j] == Lb.data[i])		//如果Lb中的元素与La中的元素相同
			{
				for(k=j+1; k<(*La).length; k++)
				{
					(*La).data[k-1] = (*La).data[k];		//被删除元素之后的元素左移
				}
				(*La).length--;					//La的表长减一

			}
		}
	}
}