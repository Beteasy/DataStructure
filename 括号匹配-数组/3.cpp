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


Status InitList_Sq(SqList *L);

void Match();


int main()
{
	Match();
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

void Match()
{
	SqList La;
	InitList_Sq(&La);
	char ch;
	int i=0;
	printf("��������ʽ:");
	ch = getchar();		//	���ն˶�ȡһ���ַ�
	while(ch != '\n')
	{
		switch(ch)
		{
		case '(':
		case '[':
		case '{':La.elem[i++] = ch;
				La.length++;
				break;		//����������ţ�����������Ա��ĩβ
		case ')':
				if(La.length>0)		//������Ա�Ϊ��	
				{
					if(La.elem[La.length-1] == '(')		//�����������ƥ��
					{
						La.length--;		//�����Ƴ�
					}
					else
					{
						La.elem[i++]=ch;	//�����ƥ�䣬����Ԫ�ط������Ա��ĩβ
						La.length++;
					}
				}
				else	//ԭ��Ϊ�ձ���Ԫ�ط������Ա��ĩβ
				{
					La.elem[i++]=ch;	
					La.length++;
				}
				break;

		case ']':
				if(La.length>0)		
				{
					if(La.elem[La.length-1] == '[')		
					{
						La.length--;	
					}
					else
					{
						La.elem[i++]=ch;	
						La.length++;
					}
				}
				else	
				{
					La.elem[i++]=ch;	
					La.length++;
				}
				break;

		case '}':
				if(La.length>0)		
				{
					if(La.elem[La.length-1] == '{')
					{
						La.length--;
					}
					else
					{
						La.elem[i++]=ch;	
						La.length++;
					}
				}
				else	
				{
					La.elem[i++]=ch;	
					La.length++;
				}
					break;
		}
		ch = getchar();		//���ն˶�ȡ��һ���ַ�
	}
	if(La.length==0)
	{
		printf("���ʽ�е�����ƥ��\n");
	}
	else
	{
		printf("���ʽ�е����Ų�ƥ��\n");
		printf("��ǰ���Ա��е�����Ϊ:");
		for(int i=0;i<La.length; i++)
		{
			printf("%c", La.elem[i]);
		}
	}
}