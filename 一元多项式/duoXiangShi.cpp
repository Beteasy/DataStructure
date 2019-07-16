#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2


//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;


typedef struct		//��ı�ʾ������ʽ������ΪLinkList������Ԫ��
{
	float coef;		//ϵ��
	int expn;		//ָ��
}term,ElemType;		//������������term���ڱ�ADT��ElemTypeΪLinkList�����ݶ�����



//���Ա�ĵ�����洢�ṹ
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList, *Position;


typedef LinkList polynomial;


//��������
void InitList(polynomial *P);
void CreatPolyn(polynomial *P, int m);
//Position GetHead(polynomial *P);
Position GetHead(polynomial P);
void SetCurElem(polynomial *p, ElemType e);
int ListLength(polynomial P);
Status ListEmpty(polynomial P);
int equal(term a, term b);
Status LocateElem(LinkList L, ElemType e, polynomial *q, int (*cmp)(ElemType, ElemType));
Status MakeNode(polynomial *p, ElemType e);
Status InsFirst(polynomial q, polynomial s);
void PrinyPolyn(polynomial P);
Position NextPos(polynomial P, Position h);
ElemType GetCurElem(polynomial p);
Status DelFirst(polynomial h, polynomial q);
Status FreeNode(polynomial q);
Status Append(polynomial *P, polynomial q);
void AddPolyn(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b));



int main()
{
	polynomial Pa;
	polynomial Pb;
	InitList(&Pa);
	InitList(&Pb);
	int m;
	printf("���������ʽPA����ĸ���:");
	scanf("%d", &m);
	CreatPolyn(&Pa,m);
	printf("���������ʽPB����ĸ���:");
	scanf("%d", &m);
	CreatPolyn(&Pb,m);
	printf("���ǰPA�е���:");
	PrinyPolyn(Pa);
	printf("���ǰPB�е���:");
	PrinyPolyn(Pb);
	AddPolyn(&Pa, &Pb, equal);
	printf("��������ʽ��ӵĽ��Ϊ:");
	PrinyPolyn(Pa);
	return 0;
}


void InitList(polynomial *P)
{
	(*P) = (polynomial)malloc(sizeof(LNode));
	(*P)->data.coef = 0.0;
	(*P)->data.expn = -1;
	(*P)->next = NULL;
}



Position GetHead(polynomial P)
{
	return P;
}

void SetCurElem(polynomial *P, ElemType e)
{
	(*P)->data.coef = e.coef;
	(*P)->data.expn = e.expn;
}



int ListLength(polynomial P)
{
	int length = 0;
	polynomial h;
	h = P->next;
	while(h)
	{
		length++;
		h = h->next;

	}
	return length;
}

Status ListEmpty(polynomial P)
{
	if(!P->next)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int equal(term a, term b)
{
	if(a.expn < b.expn)
	{
		return -1;
	}
	if(a.expn == b.expn)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

Status LocateElem(polynomial P, ElemType e, Position *q, int (*cmp)(ElemType, ElemType))
{
	//����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ���qָʾL�е�һ��ֵΪe�Ľ���λ�ò�����TRUE
	//����qָʾ��һ����e�����ж�����compare()ȡֵ>0��Ԫ�ص�ǰ����λ�ã�������FALSE
	int i=1;			//i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	int length;
	polynomial cur, pre;
	cur = P->next;		//cur�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	length = ListLength(P);
	//printf("length = %d\n",length);		//���Խڵ�����Ƿ�����   ��������
	while(i<=length && (*cmp)(cur->data,e)!=0)
	{
		i++;
		cur = cur->next;
	}
	if(i<=length)
	{
		*q = cur;
		return TRUE;
	}
	else
	{
		i=1;
		pre = P;
		cur = P->next;
		while(i<=length && (*cmp)(cur->data,e)<0)
		{
			i++;
			pre = cur;
			cur = cur->next;
		}
		/*if(i<=length)
		{
			*q = pre;
		}*/
		*q = pre;			//�����Ƿ������e�����ж�����compare()ȡֵ>0��Ԫ�أ�q��Ҫָ��һ���ڵ㣬�����ظýڵ㡣�����ڵ�Ȼ����ǰ������������ڣ�����Ҫ�������һ���ڵ�
		return FALSE;
	}
}

Status MakeNode(polynomial *p, ElemType e)
{
	(*p) = (polynomial)malloc(sizeof(LNode));
	if(!(*p))
	{
		return ERROR;
	}
	else
	{
		(*p)->data.coef = e.coef;
		(*p)->data.expn = e.expn;
		return OK;
	}
}

Status InsFirst(polynomial q, polynomial s)
{
	s->next = q->next;
	q->next = s;
	return OK;
}

//����m���ϵ����ָ����������ʾһԪ����ʽ����������P
void CreatPolyn(polynomial *P, int m)
{
	//InitList(P);
	//printf("%f,%d", (*P)->data.coef, (*P)->data.expn);		//P��������
	ElemType e;
	int i;
	polynomial q, s;
	Position h;
	//h = GetHead(P);
	h = GetHead(*P);
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(&h,e);		//����ͷ��������Ԫ��
	//printf("%f,%d", h->data.coef, h->data.expn);				//h��������
	printf("���������ʽ��ÿ���ϵ����ָ�����м��ö��Ÿ�����ÿ��֮���ÿո����:\n");
	for(i=1; i<=m; i++)		//һ������m��������
	{
		scanf("%f,%d", &e.coef, &e.expn);
		//printf("%f,%d", e.coef, e.expn);						//e�������ݲ�������
		//printf("%d\n", LocateElem(*P,e,&q,equal));			//locate��������
		//printf("%f, %d", q->data.coef, q->data.expn);			//q�����쳣		�޸ĺ�����
		//getch();
		if(!LocateElem(*P,e,&q,equal))		//��ǰ�����в����ڸ�ָ����
		{
			if(MakeNode(&s,e))
			{
				InsFirst(q,s);				//���ɽ�㲢��������		//InsFirst������󣬲�Ӧ�ô�q�ĵ�ַ��Ӧ��ֱ�Ӵ�q���޸ĺ�����
				//printf("%f, %d", s->data.coef, s->data.expn);			//����S�����Ƿ�����    ��������
			}
		}
	}
}

void PrinyPolyn(polynomial P)
{
	polynomial cur = P->next;
	while(cur)
	{
		printf("%.2f*x^%d\n", cur->data.coef, cur->data.expn);
		cur = cur->next;
	}
}

//��֪hָ����������P�е�һ���ڵ㣬����h��ָ��ڵ��ֱ�Ӻ�̵�λ�ã����޺�̣��򷵻�NULL
Position NextPos(polynomial P, Position h)
{
	polynomial cur;
	cur = P;
	while(cur != h)
	{
		cur = cur->next;
	}
	if(cur->next)
	{
		return cur->next;
	}
	else
	{
		return NULL;
	}
}

//��֪pָ�����������е�һ���ڵ㣬����p��ָ��ڵ�������Ԫ�ص�ֵ
ElemType GetCurElem(polynomial p)
{
	return p->data;
}

//��֪hָ�����������ͷ��㣬ɾ�������еĵ�һ���ڵ㣬����q����
Status DelFirst(polynomial h, polynomial q)
{
	h->next = q->next;
	return OK;
}

Status FreeNode(polynomial q)
{
	free(q);
	return OK;
}


Status Append(polynomial *P, polynomial q)
{
	polynomial cur, pre;
	cur = (*P);
	while(cur->next)
	{
		cur = cur->next;
	}
	while(q)
	{
		pre = q;
		q = q->next;
		InsFirst(cur,pre);
		cur = pre;
		//cur->next = q;
		//q = q->next;
	}
	/*polynomial *cur;
	polynomial pre;
	cur = P;
	while((*cur)->next)
	{
		(*cur) = (*cur)->next;
	}
	while(q)
	{
		pre = q;
		q = q->next;
		InsFirst(*cur,pre);
		*cur = pre;
		//q = q->next;
		//(*cur)->next = q;
	}*/
	/*polynomial pre;
		while(qb)
		{
			//DelFirst(hb,qb);
			pre = qb;
			qb = qb->next;
			InsFirst(ha,pre);
			ha = pre;
			//FreeNode(qb);
			//qb = NextPos(*Pb,hb);
		}*/
	return OK;
}
//����ʽ�ӷ���PA = PA + PB��������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ��
void AddPolyn(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b))
{
	Position ha, hb, qa, qb;
	ElemType a, b,sum;
	ha = GetHead(*Pa);			//ha��hb�ֱ�ָ��PA��PB��ͷ���
	hb = GetHead(*Pb);
	qa = NextPos(*Pa,ha);		//qa��qb�ֱ�ָ��PA��PB�е�ǰ���
	qb = NextPos(*Pb,hb);
	while(qa && qb)				//qa��qb��Ϊ�ǿ�
	{
		a = GetCurElem(qa);		//a��bΪ�����е�ǰ�Ƚ�Ԫ��
		b = GetCurElem(qb);
		//printf("%f,%d", a.coef, a.expn);		//����ͷ����뵱ǰ����ָ���Ƿ���ȷ  ��������
		//printf("%f,%d", b.coef, b.expn);
		switch((*cmp)(a,b))
		{
		case -1:	//����ʽPA�е�ǰ����ָ��ֵС
			ha = qa;
			qa = NextPos(*Pa,qa);
			/*if(qa)
			{
				printf("����ָ���ƶ��Ƿ�ɹ�%f,%d\n", qa->data.coef, qa->data.expn);
			}*/
			
			break;

		case 0:		//���ߵ�ָ��ֵ���
			sum.coef = a.coef + b.coef;
			sum.expn = a.expn;
			if(sum.coef != 0)		//�޸Ķ���ʽPA�е�ǰ����ϵ��ֵ
			{
				SetCurElem(&qa,sum);
				ha = qa;
				//printf("���Ը��½��:%f,%d\n", ha->data.coef, ha->data.expn);
			}
			else
			{
				//ɾ������ʽPA�е�ǰ���
				DelFirst(ha,qa);
				FreeNode(qa);
			}
			DelFirst(hb,qb);
			FreeNode(qb);
			qb = NextPos(*Pb,hb);
			qa = NextPos(*Pa,ha);
			/*if(qa)
			{
				printf("����ָ���ƶ��Ƿ�ɹ�%f,%d\n", qa->data.coef, qa->data.expn);
			}
			if(qb)
			{
				printf("����ָ���ƶ��Ƿ�ɹ�%f,%d\n", qb->data.coef, qb->data.expn);
			}*/
			break;
		case 1:		//����ʽPB�е�ǰ����ָ��ֵС
			DelFirst(hb,qb);
			InsFirst(ha,qb);
			qb = NextPos(*Pb,hb);
			qa = NextPos(*Pa,ha);
			/*if(qa)
			{
				printf("����ָ���ƶ��Ƿ�ɹ�%f,%d\n", qa->data.coef, qa->data.expn);
			}
			if(qb)
			{
				printf("����ָ���ƶ��Ƿ�ɹ�%f,%d\n", qb->data.coef, qb->data.expn);
			}*/
			
			break;
		}//switch
	}//while
	//printf("\n%d", ListEmpty(*Pb));
	if(!ListEmpty(*Pb))
	{
		//printf("\n%d", ListEmpty(*Pb));
		Append(Pa,qb);		//����PB��ʣ����
		/*polynomial pre;
		while(qb)
		{
			//DelFirst(hb,qb);
			pre = qb;
			qb = qb->next;
			InsFirst(ha,pre);
			ha = pre;
			//FreeNode(qb);
			//qb = NextPos(*Pb,hb);
		}*/
	}
	FreeNode(hb);			//�ͷ�PB��ͷ���
}