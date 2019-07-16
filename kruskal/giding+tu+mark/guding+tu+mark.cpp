// k.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define MAX_EDGE 20
#define MAX_VERTEXES 20
#define INFINITY 99999
#define R 20

typedef  int VertexType;

//����ߵĽṹ��
typedef struct
{
	VertexType begin;
	VertexType end;
	int weight;
}Edge;

//����ͼ�Ľṹ��
typedef struct
{
	VertexType Matrix[MAX_VERTEXES][MAX_VERTEXES];
	int vertexes_num, edges_num;	//ͼ�ĵ�ǰ�������ͱ���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
}MGraph;


typedef struct
{
	int x;
	int y;
}circleType[MAX_VERTEXES];

typedef struct
{
	int sign[MAX_VERTEXES];
	int num;
}MarkType;

//��������
void initMGraph(MGraph *G);
void createMGraph(MGraph *G);
void sortEdges(Edge Edges[], int num);
int createEdges(MGraph G, Edge edges[MAX_EDGE]);
int findMark(int parent[],int pos);
void createMST(MGraph G);
void judgeLoop(Edge edges[],  int len, MarkType mark);


int main()
{
	initgraph(800,480);
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(242, 179, 255));
	cleardevice();
	MGraph G;
	initMGraph(&G);
	createMGraph(&G);
	printf("�������С������Ϊ:\n");
	createMST(G);
	system("pause");
    return 0;
}

//��ʼ��ͼ
void initMGraph(MGraph *G)
{
	int i, j;
	/*printf("������ͼ�������Ŀ��");
	scanf("%d", &G->vertexes_num);
	printf("������ͼ�ߵ���Ŀ��");
	scanf("%d", &G->edges_num);*/

	G->edges_num = 10;
	G->vertexes_num = 6;
	for (i = 0; i < G->vertexes_num; i++)
	{
		for (j = 0; j < G->vertexes_num; j++)
		{
			if (i == j)
			{
				G->Matrix[i][j] = 0;		//��ʼ���Խ����ϵ�ȨֵΪ0���Լ����Լ���
			}
			else
			{
				G->Matrix[i][j] = INFINITY;	//��ʼ�����˶Խ����ϵ�ȨֵΪ�����
			}
		}
	}
}

//����ͼ
void createMGraph(MGraph *G)
{
	int i, j/*, begin, end, weight*/;
	/*printf("������ߵĸ��������Լ�Ȩֵ(a,b,weight)\n");
	for (i = 0; i < G->edges_num; i++) 
	{
		scanf("%d%d%d", &begin, &end, &weight);
		G->Matrix[begin][end] = weight;
	}*/

	/*G->Matrix[0][1] = 6;
	G->Matrix[0][2] = 1;
	G->Matrix[0][3] = 5;
	G->Matrix[1][2] = 5;
	G->Matrix[1][4] = 3;
	G->Matrix[2][3] = 5;
	G->Matrix[2][4] = 6;
	G->Matrix[2][5] = 4;
	G->Matrix[3][5] = 2;
	G->Matrix[4][5] = 6;*/


	for (i = 0; i < G->vertexes_num; i++)
	{
		for (j = i; j < G->vertexes_num; j++)
		{
			G->Matrix[j][i] = G->Matrix[i][j];
		}
	}



}

//�����߼�����
int createEdges(MGraph G, Edge edges[MAX_EDGE])
{
	int i, j, k = 0;
	int pos1, pos2;
	char ch;

	circleType cir;
	cir[0].x = 200;
	cir[0].y = 20;
	cir[1].x = 50;
	cir[1].y = 150;
	cir[2].x = 200;
	cir[2].y = 220;
	cir[3].x = 350;
	cir[3].y = 150;
	cir[4].x = 50;
	cir[4].y = 300;
	cir[5].x = 350;
	cir[5].y = 300;

	for (i = 0; i < G.vertexes_num; i++)
	{
		for (j = i+1; j < G.vertexes_num; j++)
		{
			if (G.Matrix[i][j] < INFINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.Matrix[i][j];

				sprintf(&ch,"%d",k);
				setfillcolor(RGB(24, 255, 0));
				fillcircle(cir[k].x,cir[k].y,R);
				settextcolor(RGB(255, 0, 0)); 
				outtextxy(cir[k].x,cir[k].y-5,ch);

				setlinecolor(RGB(24, 255, 0));
				line(cir[i].x,cir[i].y,cir[j].x,cir[j].y);

				pos1 = (cir[i].x+cir[j].x)/2;
				pos2 = (cir[i].y+cir[j].y)/2;

				sprintf(&ch,"%d",edges[k].weight);
				outtextxy(pos1,pos2,ch);

				k++;
			}
		}
	}
	return k;	//���ر߼�����ĳ���
}

//�Ա߰���С�����˳������
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


//������С������
void createMST(MGraph G)
{
	char str[]="�������������С�������Ķ�̬չʾ";
	int len, i;

	MarkType mark;
	mark.num=G.vertexes_num;
	for(i=0;i<mark.num;i++)
	{
		mark.sign[i]=i;
	}

	Edge edges[MAX_EDGE];

	len = createEdges(G,edges);

	sortEdges(edges, len);
	outtextxy(10,450,str);
	getch();
	judgeLoop(edges,len,mark);
}

void judgeLoop(Edge edges[],  int len, MarkType mark)
{
	int i, k;
	int pos1, pos2;
	circleType cir;
	char ch;
	int px=400,py=350;

	cir[0].x = 600;
	cir[0].y = 20;
	cir[1].x = 450;
	cir[1].y = 150;
	cir[2].x = 600;
	cir[2].y = 220;
	cir[3].x = 750;
	cir[3].y = 150;
	cir[4].x = 450; 
	cir[4].y = 300;
	cir[5].x = 750;
	cir[5].y = 300;

	for(i=0;i<6;i++)
	{
		setfillcolor(RGB(0, 119, 255));
		fillcircle(cir[i].x,cir[i].y,R);
		sprintf(&ch,"%d",i);
		outtextxy(cir[i].x,cir[i].y-5,ch);
	}


	for(i=0;i<len;i++)
	{
				sprintf(&ch,"%d",edges[i].begin);
				outtextxy(px,py,ch);
				sprintf(&ch,"%d",edges[i].end);
				outtextxy(px+14,py,ch);
		if (mark.sign[edges[i].begin]!=mark.sign[edges[i].end])
		{
				
			for(k=0;k<mark.num;k++)
			{
				if(mark.sign[k] == mark.sign[edges[i].end])
				{
					mark.sign[k] = mark.sign[edges[i].begin];
				}
				
				sprintf(&ch,"%d",mark.sign[k]);
				outtextxy(px+20+10*k,py,ch);
				
			}
			
			pos1 = (cir[edges[i].begin].x+cir[edges[i].end].x)/2;
			pos2 = (cir[edges[i].begin].y+cir[edges[i].end].y)/2;
			setlinecolor(RGB(0, 119, 255));
			Sleep(2500);
			line(cir[edges[i].begin].x,cir[edges[i].begin].y,cir[edges[i].end].x,cir[edges[i].end].y);
			sprintf(&ch,"%d",edges[i].weight);
			outtextxy(pos1,pos2,ch);
		}
		else
		{
			for(k=0;k<mark.num;k++)
			{
				sprintf(&ch,"%d",mark.sign[k]);
				outtextxy(px+20+10*k,py,ch);
			}
			
		}
		py+=14;
	}
	

}