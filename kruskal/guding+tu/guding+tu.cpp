// k.cpp: 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#define MAX_EDGE 20
#define MAX_VERTEXES 20
#define INFINITY 99999

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

typedef struct
{
	int x;
	int y;
}circleType[MAX_VERTEXES];

//函数声明
void initMGraph(MGraph *G);
void createMGraph(MGraph *G);
void sortEdges(Edge Edges[], int num);
int createEdges(MGraph G, Edge edges[MAX_EDGE]);
int judge_Loop(int parent[], int f);
void createMST(MGraph G);


circleType cir;


int main()
{
	initgraph(800, 600);
	MGraph G;
	initMGraph(&G);
	createMGraph(&G);
	printf("构造的最小生成树为:\n");
	createMST(G);
	system("pause");
	return 0;
}


//初始化图
void initMGraph(MGraph *G)
{
	int i, j;
	/*printf("请输入图顶点的数目：");
	scanf_s("%d", &G->vertexes_num);
	printf("请输入图边的数目：");
	scanf_s("%d", &G->edges_num);*/

	G->edges_num = 11;
	G->vertexes_num = 7;

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
	int i, j, begin, end, weight;
	/*printf("请输入边的各个顶点以及权值(a,b,weight)\n");
	for (i = 0; i < G->edges_num; i++)
	{
		scanf_s("%d%d%d", &begin, &end, &weight);
		G->Matrix[begin][end] = weight;
	}
	*/
	

	G->Matrix[0][1] = 7;
	G->Matrix[0][3] = 5;
	G->Matrix[1][2] = 8;
	G->Matrix[1][3] = 9;
	G->Matrix[1][4] = 7;
	G->Matrix[2][4] = 5;
	G->Matrix[3][4] = 15;
	G->Matrix[3][5] = 6;
	G->Matrix[4][5] = 8;
	G->Matrix[4][6] = 9;
	G->Matrix[5][6] = 11;

	for (i = 0; i < G->vertexes_num; i++)
	{
		for (j = i; j < G->vertexes_num; j++)
		{
			G->Matrix[j][i] = G->Matrix[i][j];
		}
	}

	cir[0].x = 200;
	cir[0].y = 20;
	cir[1].x = 50;
	cir[1].y = 150;
	cir[2].x = 50;
	cir[2].y = 300;
	cir[3].x = 200;
	cir[3].y = 450;
	cir[4].x = 350;
	cir[4].y = 300;
	cir[5].x = 350;
	cir[5].y = 150;
}

//构建边集数组
int createEdges(MGraph G, Edge edges[MAX_EDGE])
{
	int i, j, k = 0;
	int pos1, pos2;
	for (i = 0; i < G.vertexes_num; i++)
	{
		for (j = i + 1; j < G.vertexes_num; j++)
		{
			if (G.Matrix[i][j] < INFINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.Matrix[i][j];
				/*switch (k)
				{
				case 0:
					setlinecolor(WHITE);
					circle(200, 20,20);
					line(200, 20, 50, 150);
					//circle(cir[k].x, cir[k].y, 20);
					outtextxy(200, 15, '0');
					break;
				case 1:
					setlinecolor(WHITE);
					circle(50, 150, 20);
					line(50, 150, 50, 300);
					outtextxy(50, 145, '1');
					break;
				case 2:
					setlinecolor(WHITE);
					circle(50, 300, 20);
					line(50, 300, 200, 450);
					outtextxy(50, 395, '2');
					break;
				case 3:
					setlinecolor(WHITE);
					circle(200, 450, 20);
					line(200, 450, 350, 300);
					outtextxy(200, 445, '3');
					break;
				case 4:
					setlinecolor(WHITE);
					circle(350, 300, 20);
					line(350, 300, 350, 150);
					outtextxy(350, 395, '4');
					break;
				case 5:
					setlinecolor(WHITE);
					circle(350, 150, 20);
					line(350, 150, 200, 20);
					outtextxy(350, 145, '5');
					break;
				default:
					break;
				}*/
				char ch;
				//ch = (char)k;
				sprintf(&ch,"%d",k);
				circle(cir[k].x, cir[k].y, 20);
				outtextxy(cir[k].x, cir[k].y-5, ch);
				if(k==5)
				{
					line(cir[k].x,cir[k].y,cir[0].x,cir[0].y);
					sprintf(&ch,"%d",edges[k].weight);
					pos1=cir[k].x/2+cir[0].x/2;
					pos2=cir[k+1].y/2+cir[0].y/2;
					outtextxy(pos1, pos2, ch);
				}
				else
				{
					line(cir[k].x,cir[k].y,cir[k+1].x,cir[k+1].y);
					sprintf(&ch,"%d",edges[k].weight);
					
					pos1=cir[k].x/2+cir[k+1].x/2;
					pos2=cir[k+1].y/2+cir[k+1].y/2;
					outtextxy(pos1, pos2, ch);
				}
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
				t.begin = Edges[j].begin;
				t.end = Edges[j].end;
				t.weight = Edges[j].weight;
				Edges[j].begin = Edges[j + 1].begin;
				Edges[j].end = Edges[j + 1].end;
				Edges[j].weight = Edges[j + 1].weight;
				Edges[j + 1].begin = t.begin;
				Edges[j + 1].end = t.end;
				Edges[j + 1].weight = t.weight;
				change = true;
			}
		}
	}
}

//判断是否形成环
int judge_Loop(int parent[], int pos)
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
	int i, len, m, n, k = 0;
	int parent[MAX_VERTEXES] = { 0 };
	Edge edges[MAX_EDGE];

	len = createEdges(G, edges);

	sortEdges(edges, len);

	for (i = 0; i < G.edges_num; i++)
	{
		n = judge_Loop(parent, edges[i].begin);
		m = judge_Loop(parent, edges[i].end);
		if (n != m)
		{
			parent[n] = m;
			printf("(%d,%d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}

}