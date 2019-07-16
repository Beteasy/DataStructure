#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>

int main()
{
	int i=0;
	initgraph(800,800);
	MOUSEMSG m;
	while(1)
	{
		if(MouseHit())
		{
			m = GetMouseMsg();
			switch(m.uMsg)
			{
				case WM_LBUTTONDOWN:
				circle(m.x,m.y,20);
				i++;
				break;
			}
			
			char ch;
			sprintf(&ch,"%d",i);
			outtextxy(10,750,ch);
		}
		if(i==6)
		{
			break;
		}
	}
}