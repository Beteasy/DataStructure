#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2


//Status是函数的类型，其值是函数结果状态代码
typedef int Status;


typedef struct		//项的表示，多项式的项作为LinkList的数据元素
{
	float coef;		//系数
	int expn;		//指数
}term,ElemType;		//两个类型名：term用于本ADT，ElemType为LinkList的数据对象名



//线性表的单链表存储结构
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList, *Position;


typedef LinkList polynomial;


//函数声明
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
	printf("请输入多项式PA中项的个数:");
	scanf("%d", &m);
	CreatPolyn(&Pa,m);
	printf("请输入多项式PB中项的个数:");
	scanf("%d", &m);
	CreatPolyn(&Pb,m);
	printf("相加前PA中的项:");
	PrinyPolyn(Pa);
	printf("相加前PB中的项:");
	PrinyPolyn(Pb);
	AddPolyn(&Pa, &Pb, equal);
	printf("两个多项式相加的结果为:");
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
	//若有序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中第一个值为e的结点的位置并返回TRUE
	//否则q指示第一个与e满足判定函数compare()取值>0的元素的前驱的位置，并返回FALSE
	int i=1;			//i的初值为第一个元素的位序
	int length;
	polynomial cur, pre;
	cur = P->next;		//cur的初值为第一个元素的位置
	length = ListLength(P);
	//printf("length = %d\n",length);		//测试节点插入是否正常   测试正常
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
		*q = pre;			//不管是否存在与e满足判定函数compare()取值>0的元素，q都要指向一个节点，并返回该节点。若存在当然返回前驱，如果不存在，则需要返回最后一个节点
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

//输入m项的系数和指数，建立表示一元多项式的有序链表P
void CreatPolyn(polynomial *P, int m)
{
	//InitList(P);
	//printf("%f,%d", (*P)->data.coef, (*P)->data.expn);		//P调试正常
	ElemType e;
	int i;
	polynomial q, s;
	Position h;
	//h = GetHead(P);
	h = GetHead(*P);
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(&h,e);		//设置头结点的数据元素
	//printf("%f,%d", h->data.coef, h->data.expn);				//h调试正常
	printf("请输入多项式中每项的系数与指数，中间用逗号隔开，每组之间用空格隔开:\n");
	for(i=1; i<=m; i++)		//一次输入m个非零项
	{
		scanf("%f,%d", &e.coef, &e.expn);
		//printf("%f,%d", e.coef, e.expn);						//e读入数据测试正常
		//printf("%d\n", LocateElem(*P,e,&q,equal));			//locate测试正常
		//printf("%f, %d", q->data.coef, q->data.expn);			//q返回异常		修改后正常
		//getch();
		if(!LocateElem(*P,e,&q,equal))		//当前链表中不存在该指数项
		{
			if(MakeNode(&s,e))
			{
				InsFirst(q,s);				//生成结点并插入链表		//InsFirst定义错误，不应该传q的地址，应该直接传q，修改后正常
				//printf("%f, %d", s->data.coef, s->data.expn);			//测试S构成是否正常    测试正常
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

//已知h指向线性链表P中的一个节点，返回h所指向节点的直接后继的位置，若无后继，则返回NULL
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

//已知p指向线性链表中的一个节点，返回p所指向节点中数据元素的值
ElemType GetCurElem(polynomial p)
{
	return p->data;
}

//已知h指向线性链表的头结点，删除链表中的第一个节点，并以q返回
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
//多项式加法：PA = PA + PB，利用两个多项式的结点构成“和多项式”
void AddPolyn(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b))
{
	Position ha, hb, qa, qb;
	ElemType a, b,sum;
	ha = GetHead(*Pa);			//ha和hb分别指向PA和PB的头结点
	hb = GetHead(*Pb);
	qa = NextPos(*Pa,ha);		//qa和qb分别指向PA和PB中当前结点
	qb = NextPos(*Pb,hb);
	while(qa && qb)				//qa和qb均为非空
	{
		a = GetCurElem(qa);		//a和b为两表中当前比较元素
		b = GetCurElem(qb);
		//printf("%f,%d", a.coef, a.expn);		//测试头结点与当前结点的指向是否正确  测试正常
		//printf("%f,%d", b.coef, b.expn);
		switch((*cmp)(a,b))
		{
		case -1:	//多项式PA中当前结点的指数值小
			ha = qa;
			qa = NextPos(*Pa,qa);
			/*if(qa)
			{
				printf("测试指针移动是否成功%f,%d\n", qa->data.coef, qa->data.expn);
			}*/
			
			break;

		case 0:		//两者的指数值相等
			sum.coef = a.coef + b.coef;
			sum.expn = a.expn;
			if(sum.coef != 0)		//修改多项式PA中当前结点的系数值
			{
				SetCurElem(&qa,sum);
				ha = qa;
				//printf("测试更新结点:%f,%d\n", ha->data.coef, ha->data.expn);
			}
			else
			{
				//删除多项式PA中当前结点
				DelFirst(ha,qa);
				FreeNode(qa);
			}
			DelFirst(hb,qb);
			FreeNode(qb);
			qb = NextPos(*Pb,hb);
			qa = NextPos(*Pa,ha);
			/*if(qa)
			{
				printf("测试指针移动是否成功%f,%d\n", qa->data.coef, qa->data.expn);
			}
			if(qb)
			{
				printf("测试指针移动是否成功%f,%d\n", qb->data.coef, qb->data.expn);
			}*/
			break;
		case 1:		//多项式PB中当前结点的指数值小
			DelFirst(hb,qb);
			InsFirst(ha,qb);
			qb = NextPos(*Pb,hb);
			qa = NextPos(*Pa,ha);
			/*if(qa)
			{
				printf("测试指针移动是否成功%f,%d\n", qa->data.coef, qa->data.expn);
			}
			if(qb)
			{
				printf("测试指针移动是否成功%f,%d\n", qb->data.coef, qb->data.expn);
			}*/
			
			break;
		}//switch
	}//while
	//printf("\n%d", ListEmpty(*Pb));
	if(!ListEmpty(*Pb))
	{
		//printf("\n%d", ListEmpty(*Pb));
		Append(Pa,qb);		//链接PB中剩余结点
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
	FreeNode(hb);			//释放PB额头结点
}