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
#define LIST_INIT_SIZE  100//���Ա�洢�ռ�ĳ�ʼ����
#define LISTINCREAMENT  10//���Ա�洢�ռ�ķ�������
typedef  int Status;
typedef int ElemType;


//=====================================================
//��̬����˳��洢�ṹ
//=====================================================


typedef struct{
ElemType *elem;//�洢�ռ��ַ
int     length;//��ǰ����
int  listsize;//��ǰ����Ĵ洢����
}SqList;






//=========================================================
//���ں���
//=========================================================
Status equal(ElemType a,ElemType b)
{if(a==b)
return TRUE;
else 
return FALSE;
}


//=====================================================
//���Ա��ȵļ���
//=====================================================
Status ListLength(SqList La)
{
return La.length;
}


//=========================================================
//��ӡ����
//=========================================================
void print(ElemType *c)
 {
   printf("%d ",*c);
 }


//=====================================================
//����һ���յ����Ա�L
//=====================================================
Status InitList_Sq(SqList *l)
{
(*l).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if(!(*l).elem)
exit(OVERFLOW);
(*l).length=0;//���Ա���Ԫ�صĸ���Ϊlength=0
(*l).listsize=LIST_INIT_SIZE;//���Ա�Ĵ�СΪ100���ֽ�
return OK;
}


//=====================================================
//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
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
(*l).listsize+=LISTINCREAMENT;//���Ա�����listincrement����
}
 q=&((*l).elem[i-1]);//ָ���ָ�����Ա�ĵڣ��Ԫ��
 for(p=&((*l).elem[(*l).length-1]);p>=q;--p)
*(p+1)=*p;
 *q=e;
 ++(*l).length;
 return OK;
}


//=====================================================
//���ҵ�һ����e����compare������Ԫ��λ��
//=====================================================
int LocateElem_Sq(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
//���ҵ��򷵻�����L�е�Ϊ�򣬷��򷵻�0
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
//��e����L�е�i������Ԫ�ص�ֵ
//=========================================================
Status getelem(SqList l,int i,ElemType *e)
{ if(i<1||i>l.length)
  exit(ERROR);
*e=*(l.elem+i-1);
return OK;
}


//=========================================================
//���ζ�L��ÿһ������Ԫ�ص��ú���vi������һ��vi����ʧ�ܣ������ʧ��
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
//��������Lb�ж�����La�е�����Ԫ�ز��뵽La��
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
//������
//=====================================================
void main()
{
SqList la,lb;
    int j,i;
i=InitList_Sq(&la);//����һ���յ����Ա��������ɹ����򷵻�ok
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

