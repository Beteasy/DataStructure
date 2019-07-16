#include <stdio.h>
#include <stdlib.h>

/******ͼ���ڽӱ�洢��ʾ********/
#define MAX_VERTEX_NUM 20
typedef int VertexType;

//���Ǳ�ڵ�ṹ�������
typedef struct ArcNode {
	int adjvex;		//�û���ָ��Ķ����ڱ�ͷ�е�λ�ã���һά�����е�λ�ã�
	struct ArcNode *nextarc;	//ָ����һ������ָ�루ͬ���͵Ľṹ��)
}ArcNode;

//���Ǳ�ͷ�ڵ�ṹ�������
typedef struct VNode {
	VertexType data;	//������Ϣ���ڱ�ͷ�еĽڵ㣩
	ArcNode *firstarc;	//����ָ���һ�������ö���Ļ���ָ��
}VNode;

//ͼ������
typedef struct {
	VNode vertices[MAX_VERTEX_NUM];	//����һ����ͷ�ڵ��һά����(�����е�ÿһ����㶼����VNode�еĶ�����Ϣ�������
	int vexnum, arcnum;	//ͼ�ĵ�ǰ�������ͻ���
}ALGraph;


/************��������*********/
void createGraph(ALGraph *G);
/*void printGraph(ALGraph G);
int LOC_VERTEX(ALGraph G, int v);
void printLink(ALGraph G);*/


int main()
{
	ALGraph G;
	createGraph(&G);
	/*printf("ͼ�еĶ���Ϊ:");
	printGraph(G);
	printf("ͼ�������ϵΪ:");
	printLink(G);*/
    return 0;
}


//��������ͼ
void createGraph(ALGraph *G)
{
	int dingdian, hnum, dnum/*, v1, v2*/, i/*, pos_v1, pos_v2*/;
	//ArcNode *node;
	printf("�����붥��ĸ���:");
	scanf("%d", &dnum);
	printf("�����뻡������:");
	scanf("%d", &hnum);
	(*G).vexnum = dnum;
	(*G).arcnum = hnum;
	printf("�����붥��");
	for (i = 0; i < (*G).vexnum; i++)
	{	//��ȡ���㣬����firstarc��Ϊ��
		printf("�������%d�����", i+1);
		scanf("%d", &dingdian);
		(*G).vertices[i].data = dingdian;
		(*G).vertices[i].firstarc = NULL;
		//printf("��%d���������ڱ���λ��Ϊ%d", i, LOC_VERTEX((*G), dingdian));
	}
	/*printf("�����뻡�������������ʾ,��v1,v2��ʾ��v1��v2��v2,v1��ʾ��v2��v1:\n");
	for (i = 0; i < (*G).arcnum; i++)
	{	//���ݻ����������ϵ
		scanf_s("%d,%d", &v1, &v2);
		pos_v1 = LOC_VERTEX((*G), v1);
		printf("%d���ڱ���λ��Ϊ%d", v1,pos_v1);
		pos_v2 = LOC_VERTEX((*G), v2);
		printf("%d���ڱ���λ��Ϊ%d", v2,pos_v2);
		node = (ArcNode *)malloc(sizeof(ArcNode));
		node->adjvex = pos_v2;
		node->nextarc = NULL;
		if ((*G).vertices[pos_v1].firstarc == NULL)
		{
			(*G).vertices[pos_v1].firstarc = node;
		}
		else
		{
			node->nextarc = (*G).vertices[pos_v1].firstarc;
			(*G).vertices->firstarc = node;
		}
	}*/
	
}