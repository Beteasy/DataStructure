#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define TRUE    1
#define FALSE   0
#define  OK     1
#define  ERROR  0
#define  INFEASIBLE  -1
#define  OVERFLOW    -2
#define LIST_INIT_SIZE  100//线性表存储空间的初始分量
#define LISTINCREAMENT  10//线性表存储空间的分配增量
typedef  int Status;
typedef int ElemType;


//=====================================================
//动态分配顺序存储结构
//=====================================================


typedef struct{
ElemType *elem;//存储空间基址
int     length;//当前长度
int  listsize;//当前分配的存储容量
}SqList;






//=========================================================
//等于函数
//=========================================================
Status equal(ElemType a,ElemType b)
{if(a==b)
return TRUE;
else 
return FALSE;
}


//=====================================================
//线性表长度的计算
//=====================================================
Status ListLength(SqList La)
{
return La.length;
}


//=========================================================
//打印函数
//=========================================================
void print(ElemType *c)
 {
   printf("%d ",*c);
 }


//=====================================================
//构造一个空的线性表L
//=====================================================
Status InitList_Sq(SqList *l)
{
(*l).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if(!(*l).elem)
exit(OVERFLOW);
(*l).length=0;//线性表中元素的个数为length=0
(*l).listsize=LIST_INIT_SIZE;//线性表的大小为100个字节
return OK;
}


//=====================================================
//在顺序线性表L中第i个位置之前插入新的元素e
//=====================================================
Status ListInsert_Sq(SqList *l,int i,ElemType e)
{
ElemType *newbase,*q,*p;
if(i<1||i>(*l).length+1)
return ERROR;
if((*l).length>=(*l).listsize){
newbase=(ElemType*)realloc((*l).elem,((*l).listsize+LISTINCREAMENT)*sizeof(ElemType));
     if(!newbase)  exit(OVERFLOW);
(*l).elem=newbase;
(*l).listsize+=LISTINCREAMENT;//线性表增加listincrement长度
}
 q=&((*l).elem[i-1]);//指针ｑ指向线性表的第ｉ个元素
 for(p=&((*l).elem[(*l).length-1]);p>=q;--p)
*(p+1)=*p;
 *q=e;
 ++(*l).length;
 return OK;
}


//=====================================================
//查找第一个与e满足compare（）的元素位序
//=====================================================
int LocateElem_Sq(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
//若找到则返回其在L中的为序，否则返回0
ElemType *p;
    int i=1;
p=L.elem;
while(i<=L.length&&!(*compare)(*p++,e))
i++;
if(i<=L.length)
return i;
else
return 0;
}




//=========================================================
//用e返回L中第i个数据元素的值
//=========================================================
Status getelem(SqList l,int i,ElemType *e)
{ if(i<1||i>l.length)
  exit(ERROR);
*e=*(l.elem+i-1);
return OK;
}


//=========================================================
//依次对L的每一个数据元素调用函数vi（），一旦vi（）失败，则操作失败
//=========================================================
Status ListTraverse(SqList l,void(*vi)(ElemType *))
 {
   ElemType *p;
   int i;
   p=l.elem;
   for(i=1;i<=l.length;i++)
     vi(p++);
   printf("\n");
   return OK;
 }


//=====================================================
//将所有在Lb中而不再La中的数据元素插入到La中
//=====================================================
void Union(SqList *la,SqList lb)
{
int la_len,lb_len;
    int i;
ElemType e;
la_len=ListLength(*la);
lb_len=ListLength(lb);
for(i=1;i<=lb_len;i++)
{
getelem(lb,i,&e);
if(!LocateElem_Sq(*la,e,equal))
ListInsert_Sq(la,++la_len,e);


}
}

//=====================================================
//主函数
//=====================================================
void main()
{
SqList la,lb;
    int j,i;
i=InitList_Sq(&la);//构造一个空的线性表，如果构造成功，则返回ok
if(i==1)
for(j=1;j<=6;j++)
          i=ListInsert_Sq(&la,j,j);
printf("la= ");
      ListTraverse(la,print);
       InitList_Sq(&lb);
for(j=1;j<=6;j++)
        i=ListInsert_Sq(&lb,j,2*j);
printf("lb= ");
      ListTraverse(lb,print);
 Union(&la,lb);
   printf("la= ");
       ListTraverse(la,print);
}

