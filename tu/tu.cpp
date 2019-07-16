#include <stdio.h>
#include <stdlib.h>

/******图的邻接表存储表示********/
#define MAX_VERTEX_NUM 20
typedef int VertexType;

//这是表节点结构体的声明
typedef struct ArcNode {
	int adjvex;		//该弧所指向的顶点在表头中的位置（即一维数组中的位置）
	struct ArcNode *nextarc;	//指向下一条弧的指针（同类型的结构体)
}ArcNode;

//这是表头节点结构体的声明
typedef struct VNode {
	VertexType data;	//顶点信息（在表头中的节点）
	ArcNode *firstarc;	//链域，指向第一条依附该顶点的弧的指针
}VNode;

//图的声明
typedef struct {
	VNode vertices[MAX_VERTEX_NUM];	//声明一个表头节点的一维数组(数组中的每一个结点都包含VNode中的顶点信息域和链域）
	int vexnum, arcnum;	//图的当前顶点数和弧数
}ALGraph;


/************函数声明*********/
void createGraph(ALGraph *G);
/*void printGraph(ALGraph G);
int LOC_VERTEX(ALGraph G, int v);
void printLink(ALGraph G);*/


int main()
{
	ALGraph G;
	createGraph(&G);
	/*printf("图中的顶点为:");
	printGraph(G);
	printf("图中链表关系为:");
	printLink(G);*/
    return 0;
}


//创建无向图
void createGraph(ALGraph *G)
{
	int dingdian, hnum, dnum/*, v1, v2*/, i/*, pos_v1, pos_v2*/;
	//ArcNode *node;
	printf("请输入顶点的个数:");
	scanf("%d", &dnum);
	printf("请输入弧的条数:");
	scanf("%d", &hnum);
	(*G).vexnum = dnum;
	(*G).arcnum = hnum;
	printf("请输入顶点");
	for (i = 0; i < (*G).vexnum; i++)
	{	//读取顶点，并将firstarc置为空
		printf("请输入第%d个结点", i+1);
		scanf("%d", &dingdian);
		(*G).vertices[i].data = dingdian;
		(*G).vertices[i].firstarc = NULL;
		//printf("第%d个顶点所在表中位置为%d", i, LOC_VERTEX((*G), dingdian));
	}
	/*printf("请输入弧，用两个顶点表示,如v1,v2表示从v1到v2，v2,v1表示从v2到v1:\n");
	for (i = 0; i < (*G).arcnum; i++)
	{	//根据弧构建链表关系
		scanf_s("%d,%d", &v1, &v2);
		pos_v1 = LOC_VERTEX((*G), v1);
		printf("%d所在表中位置为%d", v1,pos_v1);
		pos_v2 = LOC_VERTEX((*G), v2);
		printf("%d所在表中位置为%d", v2,pos_v2);
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