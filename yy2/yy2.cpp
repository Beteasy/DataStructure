#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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
void PrintPolyn(polynomial P);
Position NextPos(polynomial P, Position h);
ElemType GetCurElem(polynomial p);
Status DelFirst(polynomial h, polynomial q);
Status FreeNode(polynomial q);
Status Append(polynomial *P, polynomial q);
void AddPolyn(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b));
void SubtractPolyn(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b));
void menu(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b));
void gotoxy(int i,int j);


int main()
{
	polynomial Pa;
	polynomial Pb;
	InitList(&Pa);
	InitList(&Pb);
	menu(&Pa,&Pb,equal);
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
	//返回链表L中头结点的位置
	return P;
}

void SetCurElem(polynomial *P, ElemType e)
{
	//已知P指向线性表L中的一个结点，用e更新p所指向结点中数据元素的值
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
	//判断A,B的指数的大小关系
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
		*q = pre;			//不管是否存在与e满足判定函数compare()取值>0的元素，q都要指向一个节点，并返回该节点。若存在当然返回前驱，如果不存在，则需要返回最后一个节点
		return FALSE;
	}
}

Status MakeNode(polynomial *p, ElemType e)
{
	//分配由P指向的值为e的结点，并返回OK；若分配失败，则返回ERROR
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
	ElemType e;
	int i;
	polynomial q, s;
	Position h;
	h = GetHead(*P);
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(&h,e);		//设置头结点的数据元素
	printf("请输入多项式中每项的系数与指数，中间用逗号隔开，每组之间用空格隔开:\n");
	for(i=1; i<=m; i++)		//一次输入m个非零项
	{
		scanf("%f,%d", &e.coef, &e.expn);
		if(!LocateElem(*P,e,&q,equal))		//当前链表中不存在该指数项
		{ 
			if(MakeNode(&s,e))
			{
				InsFirst(q,s);				//生成结点并插入链
			}
		}
	}
}

void PrintPolyn(polynomial P)
{
	polynomial cur = P->next;
	while(cur)
	{
		printf("%.2f*x^%d   ", cur->data.coef, cur->data.expn);
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
	//释放P所指向结点
	free(q);
	return OK;
}


Status Append(polynomial *P, polynomial q)
{
	//将指针s所指（彼此以指针项相连）的一串结点链接在线性表L的最后一个结点
	//之后，并改变链表L的尾指针指向新的尾结点
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
	}
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
		switch((*cmp)(a,b))
		{
		case -1:	//多项式PA中当前结点的指数值小
			ha = qa;
			qa = NextPos(*Pa,qa);
			break;

		case 0:		//两者的指数值相等
			sum.coef = a.coef + b.coef;
			sum.expn = a.expn;
			if(sum.coef != 0)		//修改多项式PA中当前结点的系数值
			{
				SetCurElem(&qa,sum);
				ha = qa;
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
			break;
		case 1:		//多项式PB中当前结点的指数值小
			DelFirst(hb,qb);
			InsFirst(ha,qb);
			qb = NextPos(*Pb,hb);
			qa = NextPos(*Pa,ha);
			break;
		}//switch
	}//while
	if(!ListEmpty(*Pb))
	{
		Append(Pa,qb);		//链接PB中剩余结点
	}
	FreeNode(hb);			//释放PB额头结点
}


void SubtractPolyn(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b))
{
	//操作结果:完成多项式相减运算，即：PA=PA-PB，并销毁一元多项式PB
	polynomial q;
	q = (*Pb)->next;
	while(q)
	{
		q->data.coef = -q->data.coef;
		q = q->next;
	}
	AddPolyn(Pa,Pb,(*cmp));
}



void menu(polynomial *Pa, polynomial *Pb, Status (*cmp)(ElemType a, ElemType b))
{
	int m;
	char input;
	int flag = 0;
	int x;
	float sum=0;
	int ji=1;
	int i;
	polynomial cur;
	while(1)
	{
		system("cls");
		gotoxy(10,4);
		printf("**************功能选择***************");
		gotoxy(15,6);
		printf("进行加法运算请按1");
		gotoxy(15,8);
		printf("进行减法运算请按2");
		gotoxy(10,10);
		printf("*************************************");
		if(kbhit())
		{
			input = getch();
			system("cls");
			switch(input)
			{
			case '1':
				printf("请输入多项式PA中项的个数:");
				scanf("%d", &m);
				CreatPolyn(Pa,m);
				printf("请输入多项式PB中项的个数:");
				scanf("%d", &m);
				CreatPolyn(Pb,m);
				printf("相加前PA中的项:");
				PrintPolyn(*Pa);
				printf("\n相加前PB中的项:");
				PrintPolyn(*Pb);
				AddPolyn(Pa,Pb,*cmp);
				printf("\n两个多项式相加的结果为:");
				PrintPolyn(*Pa);
				printf("\n请输入x的值:");
				scanf("%d", &x);
				cur = (*Pa)->next;
				while(cur)
				{
					for(i=1; i<=cur->data.expn; i++)
					{
						ji *= x;
						
					}
					sum += cur->data.coef*ji;
					cur = cur->next;
				}
				printf("在给定值x=%d下，运算的结果为:%.3f",x ,sum);
				flag = 1;
				break;
			case '2':
				printf("请输入多项式PA中项的个数:");
				scanf("%d", &m);
				CreatPolyn(Pa,m);
				printf("请输入多项式PB中项的个数:");
				scanf("%d", &m);
				CreatPolyn(Pb,m);
				printf("相减前PA中的项:");
				PrintPolyn(*Pa);
				printf("\n相减前PB中的项:");
				PrintPolyn(*Pb);
				SubtractPolyn(Pa,Pb,*cmp);
				printf("\n两个多项式相减的结果为:");
				PrintPolyn(*Pa);
				printf("\n请输入x的值:");
				scanf("%d", &x);
				cur = (*Pa)->next;
				while(cur)
				{
					for(i=1; i<=cur->data.expn; i++)
					{
						ji *= x;
					}
					sum += cur->data.coef*ji;
					cur = cur->next;
				}
				printf("在给定值x=%d下，运算的结果为:%f",x ,sum);
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			printf("\n运算完成，按任意键退出程序");
			getch();
			break;
		}
	}

}

void gotoxy(int x, int y)      //将光标移动到X,Y坐标处  
{  
COORD pos = { x , y };  
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);  
SetConsoleCursorPosition(Out, pos);   
}