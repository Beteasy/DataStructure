// k.cpp: 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>

#define MAX_EDGE 20
#define MAX_VERTEXES 20
#define INFINITY 99999
#define R 20

typedef  int VertexType;

//定义边的结构体
typedef struct
{
	VertexType begin;
	VertexType end;
	int weight;
}Edge;

//定义图的结构体
typedef struct
{
	VertexType Matrix[MAX_VERTEXES][MAX_VERTEXES];
	int vertexes_num, edges_num;	//图的当前顶点数和边数                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
}MGraph;


typedef  struct
{
	int x;
	int y;
	int value;

}circleType;


//函数声明
void initMGraph(MGraph *G);
void createMGraph(MGraph *G);
void sortEdges(Edge Edges[], int num);
int createEdges(MGraph G, Edge edges[MAX_EDGE]);
int findMark(int parent[],int pos);
void createMST(MGraph G);
void judgeLoop(Edge edges[],  int len);

int main()
{
	
	MGraph G;
	initMGraph(&G);
	initgraph(800,600);
	createMGraph(&G);
	createMST(G);
	system("pause");
    return 0;
}

//初始化图
void initMGraph(MGraph *G)
{
	int i, j;
	printf("请输入图顶点的数目：");
	scanf("%d", &G->vertexes_num);
	printf("请输入图边的数目：");
	scanf("%d", &G->edges_num);
	for (i = 0; i < G->vertexes_num; i++)
	{
		for (j = 0; j < G->vertexes_num; j++)
		{
			if (i == j)
			{
				G->Matrix[i][j] = 0;		//初始化对角线上的权值为0（自己到自己）
			}
			else
			{
				G->Matrix[i][j] = INFINITY;	//初始化除了对角线上的权值为无穷大
			}
		}
	}
}

//创建图
void createMGraph(MGraph *G)
{
	int i=0, j, begin, end, weight;
	char ch;
	MOUSEMSG m;
	//printf("请输入边的各个顶点以及权值(a,b,weight)\n");
	/*for (i = 0; i < G->edges_num; i++) 
	{
		scanf("%d%d%d", &begin, &end, &weight);
		G->Matrix[begin][end] = weight;
	}*/
	//for (i = 0; i < G->vertexes_num; i++)
	//draw circle
	while(1)
	{
		if(MouseHit())
		{
			m = GetMouseMsg();
			switch(m.uMsg)
			{
				case WM_LBUTTONDOWN:
				circle(m.x,m.y,20);
				cir[i].x = m.x;
				cir[i].y = m.y;
				cir[i].value = i;
				sprintf(&ch,"%d",i);
				outtextxy(m.x,m.y-5,ch);
				i++;
				break;
			}
			if(i==(*G).vertexes_num)
			{
				break;
			}
		}
	}
	//draw line
	while(1)
	{
		if(MouseHit())
		{
			m = GetMouseMsg();
			switch(m.uMsg)
			{
				case WM_RBUTTONDOWN:
				
				sprintf(&ch,"%d",i);
				outtextxy(m.x,m.y-5,ch);
				i++;
				break;
			}
			if(i==(*G).edges_num)
			{
				break;
			}
		}
	}

	for (i = 0; i < G->vertexes_num; i++)
	{
		for (j = i; j < G->vertexes_num; j++)
		{
			G->Matrix[j][i] = G->Matrix[i][j];
		}
	}
}

//构建边集数组
int createEdges(MGraph G, Edge edges[MAX_EDGE])
{
	int i, j, k = 0;
	for (i = 0; i < G.vertexes_num; i++)
	{
		for (j = i+1; j < G.vertexes_num; j++)
		{
			if (G.Matrix[i][j] < INFINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.Matrix[i][j];
				k++;
			}
		}
	}
	return k;	//返回边集数组的长度
}

//对边按从小到大的顺序排序
void sortEdges(Edge Edges[], int num)
{
	int i, j;                 
	Edge t;
	bool change = true;
	for (i = num - 1, change = true; i >= 1 && change; i--)
	{
		change = false;
		for (j = 0; j < i; j++)
		{
			if (Edges[j].weight>Edges[j + 1].weight)
			{
				t = Edges[j];
				Edges[j] = Edges[j + 1];
				Edges[j + 1] = t; 
				change = true;
			}
		}
	}
}

int findMark(int parent[],int pos)
{
	while (parent[pos] > 0)
	{
		pos = parent[pos];
	}
	return pos;
}

//构造最小生成树
void createMST(MGraph G)
{
	/*int i, len, m, n, k = 0;*/
	int len;
	//int parent[MAX_VERTEXES] = {0};
	Edge edges[MAX_EDGE];

	len = createEdges(G,edges);

	sortEdges(edges, len);

	judgeLoop(edges,len);
	
	/*for (i = 0; i < G.edges_num; i++)
	{
		n = judge_Loop(parent, edges[i].begin);
		m = judge_Loop(parent, edges[i].end);
		if (n != m)
		{
			parent[n] = m;
			printf("(%d,%d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}*/

}

void judgeLoop(Edge edges[],  int len)
{
	int i, m, n;
	int parent[MAX_VERTEXES] = {0};
	for(i=0;i<len;i++)
	{
		n = findMark(parent, edges[i].begin);
		m = findMark(parent, edges[i].end);
		if (n != m)
		{
			parent[n] = m;
			printf("(%d,%d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}