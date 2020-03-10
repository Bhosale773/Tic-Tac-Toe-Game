#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>

void welcome();
void rules();
void play();
void move(int color);
int check(int p[3][3]);
void blink();
void win(int w);
void p1remove();
void p2remove();
void p1set();
void p2set();

int r,c,x1,y1,x2,y2,x3,y3,xfill=200,yfill=130;
char p1name[15],p2name[15],p1symbol[2],p2symbol[2];

void main()
{
	int gd=DETECT,gm;
	clrscr();
	initgraph(&gd,&gm,"C://TC/BGI");
	welcome();
}

void welcome()
{
	int ch;
	char s1[15],s2[15];
	setcolor(WHITE);
	setbkcolor(9);
	setfillstyle(XHATCH_FILL,2);
	floodfill(1,1,15);
	rectangle(1,1,639,479);
	rectangle(15,15,624,464);
	setfillstyle(XHATCH_FILL,4);
	floodfill(2,2,WHITE);
	setcolor(12);
	settextstyle(1,0,6);
	outtextxy(160,20,"WELCOME TO");
	setcolor(4);
	settextstyle(1,0,8);
	outtextxy(80,70,"TIC TAC TOE");
	setcolor(15);
	settextstyle(1,0,4);
	outtextxy(25,180,"PLAYER 1:");
	setcolor(10);
	settextstyle(1,0,3);
	outtextxy(25,227,"Please Enter Your Name :");
	gotoxy(43,16);
	gets(p1name);
	gotoxy(43,16);
	puts(p1name);
	if(strlen(p1name)==0)
	{
		strcpy(p1name,"Player 1");
		gotoxy(43,16);
		puts(p1name);
	}
	sprintf(s1,"Hi %s,Choose Your Symbol [X/O] :",p1name);
	outtextxy(25,260,s1);
	gotoxy(48+strlen(p1name)*2,18);
	gets(p1symbol);
	gotoxy(48+strlen(p1name)*2,18);
	puts(p1symbol);
	if(!strcmpi(p1symbol,"X"))
	{
		strcpy(p1symbol,"X");
		strcpy(p2symbol,"O");
	}
	else if(!strcmpi(p1symbol,"O"))
	{
		strcpy(p1symbol,"O");
		strcpy(p2symbol,"X");
	}
	else
	{
		settextstyle(1,0,4);
		setcolor(14);
		outtextxy(25,320,"INVALID SYMBOL . . .");
		outtextxy(25,360,"PRESS ENTER TO REFRESH . . .");
		while(1)
		{
			ch=getch();
			if(ch==13)
			{
				cleardevice();
				welcome();
			}
		}
	}
	setcolor(15);
	settextstyle(1,0,4);
	outtextxy(25,300,"PLAYER 2:");
	setcolor(10);
	settextstyle(1,0,3);
	outtextxy(25,341,"Please Enter Your Name :");
	gotoxy(43,23);
	gets(p2name);
	gotoxy(43,23);
	puts(p2name);
	if(strlen(p2name)==0)
	{
		strcpy(p2name,"Player 2");
		gotoxy(43,23);
		puts(p2name);
	}
	sprintf(s2,"Hi %s,Your Symbol is %s",p2name,p2symbol);
	outtextxy(25,376,s2);
	setcolor(WHITE);
	rectangle(25,430,165,460);
	rectangle(474,430,619,460);
	setfillstyle(INTERLEAVE_FILL,4);
	floodfill(26,431,WHITE);
	floodfill(475,431,WHITE);
	settextstyle(7,0,2);
	outtextxy(32,432,"EXIT (Esc)");
	outtextxy(481,432,"NEXT (Tab)");
	while(1)
	{
		ch=getch();
		if(ch==27)
		{
			exit(0);
		}
		else if(ch==9)
		{
			cleardevice();
			rules();
		}
	}
}

void rules()
{
	int ch;
	setcolor(WHITE);
	setbkcolor(9);
	setfillstyle(XHATCH_FILL,2);
	floodfill(1,1,15);
	rectangle(1,1,639,479);
	rectangle(15,15,624,464);
	setfillstyle(XHATCH_FILL,4);
	floodfill(2,2,WHITE);
	setcolor(4);
	settextstyle(1,0,6);
	outtextxy(25,20,"LET'S SEE SOME RULES");
	setcolor(WHITE);
	settextstyle(8,0,3);
	outtextxy(25,100,"1.Board of 3X3 grid of squares will be given.");
	outtextxy(25,135,"2.One player at a time has to put his");
	outtextxy(25,170,"  symbol in any square alternatively.");
	outtextxy(25,205,"3.Use arrow keys to move between squares");
	outtextxy(25,240,"  and press Enter to put symbol.");
	outtextxy(25,275,"4.Player who first put 3 same symbols in");
	outtextxy(25,310,"  row,column or diagonal will win.");
	outtextxy(25,345,"5.If no one win then it is a draw.");
	setcolor(WHITE);
	rectangle(25,430,225,460);
	rectangle(280,430,420,460);
	rectangle(474,430,619,460);
	setfillstyle(INTERLEAVE_FILL,4);
	floodfill(26,431,WHITE);
	floodfill(475,431,WHITE);
	floodfill(281,431,WHITE);
	settextstyle(7,0,2);
	outtextxy(27,432,"BACK (Shift+Tab)");
	outtextxy(288,432,"EXIT (Esc)");
	outtextxy(482,432,"NEXT (Tab)");
	while(1)
	{
		ch=getch();
		if(ch==27)
		{
			exit(0);
		}
		else if(ch==9)
		{
			cleardevice();
			play();
		}
		else if(ch==15)
		{
			cleardevice();
			welcome();
		}
	}
}

void play()
{
	int ch,cnt=0,p[3][3],w;
	char s1[15],s2[2],s3[15],s4[2],s5[2],s6[2];
	r=0;
	c=0;
	setcolor(WHITE);
	setbkcolor(9);
	setfillstyle(XHATCH_FILL,2);
	floodfill(1,1,15);
	rectangle(1,1,639,479);
	rectangle(15,15,624,464);
	setfillstyle(XHATCH_FILL,4);
	floodfill(2,2,WHITE);
	rectangle(195,125,445,375);
	rectangle(192,122,448,378);
	setfillstyle(INTERLEAVE_FILL,2);
	floodfill(196,126,WHITE);
	rectangle(195,208,445,292);
	rectangle(278,125,362,375);
	circle(100,300,70);
	circle(100,300,67);
	circle(540,300,70);
	circle(540,300,67);
	setfillstyle(HATCH_FILL,8);
	settextstyle(1,0,4);
	outtextxy(57,257,"YOUR");
	outtextxy(57,307,"TURN");
	floodfill(100,300,WHITE);
	floodfill(540,300,WHITE);
	rectangle(25,430,225,460);
	rectangle(280,430,420,460);
	rectangle(467,430,619,460);
	setfillstyle(INTERLEAVE_FILL,4);
	floodfill(26,431,WHITE);
	floodfill(475,431,WHITE);
	floodfill(281,431,WHITE);
	settextstyle(7,0,2);
	outtextxy(27,432,"BACK (Shift+Tab)");
	outtextxy(288,432,"EXIT (Esc)");
	outtextxy(469,432,"REPLAY (Tab)");
	setcolor(4);
	settextstyle(1,0,6);
	outtextxy(25,20,"LET'S PLAY...");
	setcolor(14);
	settextstyle(1,0,5);
	sprintf(s1,"%s",p1name);
	outtextxy(29,130,s1);
	setcolor(WHITE);
	rectangle(195,125,445,375);
	rectangle(278,125,362,375);
	setcolor(14);
	sprintf(s2,"[ %s ]",p1symbol);
	outtextxy(54,175,s2);
	sprintf(s3,"%s",p2name);
	outtextxy(473,130,s3);
	sprintf(s4,"[ %s ]",p2symbol);
	outtextxy(494,175,s4);
	setfillstyle(INTERLEAVE_FILL,13);
	floodfill(xfill,yfill,WHITE);
	while(1)
	{
		ch=getch();
		if(ch==72)
		{
			if(r>0)
			{
				move(2);
				r--;
			}
		}
		else if(ch==80)
		{
			if(r<2)
			{
				move(2);
				r++;
			}
		}
		else if(ch==77)
		{
			if(c<2)
			{
				move(2);
				c++;
			}
		}
		else if(ch==75)
		{
			if(c>0)
			{
				move(2);
				c--;
			}
		}
		else if(ch==13)
		{
			sprintf(s5,"%s",p1symbol);
			sprintf(s6,"%s",p2symbol);
			if(cnt%2==0 && p[r][c]!=1 && p[r][c]!=2)
			{
				p1remove();
				p2set();
				settextstyle(3,0,9);
				outtextxy(xfill+(c*83)+14,yfill+(r*83)-27,s5);
				p[r][c]=1;
				cnt++;
			}
			else if(cnt%2==1 && p[r][c]!=1 && p[r][c]!=2)
			{
				p2remove();
				p1set();
				settextstyle(3,0,9);
				outtextxy(xfill+(c*83)+14,yfill+(r*83)-27,s6);
				p[r][c]=2;
				cnt++;
			}

		}
		else if(ch==27)
		{
			exit(0);
		}
		else if(ch==15)
		{
			cleardevice();
			rules();
		}
		else if(ch==9)
		{
			cleardevice();
			play();
		}
		move(13);
		w=check(p);
		if(w!=0)
		{
			win(w);
			while(1)
			{
				ch=getch();
				if(ch==27)
				{
					exit(0);
				}
				else if(ch==15)
				{
					cleardevice();
					rules();
				}
				else if(ch==9)
				{
					cleardevice();
					play();
				}
			}
		}
	}
}

void move(int color)
{
	setfillstyle(INTERLEAVE_FILL,color);
	floodfill(xfill+(c*83),yfill+(r*83),WHITE);
	floodfill(xfill+(c*83)+35,yfill+(r*83)+35,WHITE);
}

int check(int p[3][3])
{
	int w,flag=0,i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i][j]==1 || p[i][j]==2)
			{
				flag++;
			}
		}
	}
	if(p[0][0]==p[0][1] && p[0][1]==p[0][2])
	{
		x1=0;
		y1=0;
		x2=1;
		y2=0;
		x3=2;
		y3=0;
		blink();
		return(p[0][0]);
	}
	else if(p[1][0]==p[1][1] && p[1][1]==p[1][2])
	{
		x1=0;
		y1=1;
		x2=1;
		y2=1;
		x3=2;
		y3=1;
		blink();
		return(p[1][0]);
	}
	else if(p[2][0]==p[2][1] && p[2][1]==p[2][2])
	{
		x1=0;
		y1=2;
		x2=1;
		y2=2;
		x3=2;
		y3=2;
		blink();
		return(p[2][0]);
	}
	else if(p[0][0]==p[1][0] && p[1][0]==p[2][0])
	{
		x1=0;
		y1=0;
		x2=0;
		y2=1;
		x3=0;
		y3=2;
		blink();
		return(p[0][0]);
	}
	else if(p[0][1]==p[1][1] && p[1][1]==p[2][1])
	{
		x1=1;
		y1=0;
		x2=1;
		y2=1;
		x3=1;
		y3=2;
		blink();
		return(p[0][1]);
	}
	else if(p[0][2]==p[1][2] && p[1][2]==p[2][2])
	{
		x1=2;
		y1=0;
		x2=2;
		y2=1;
		x3=2;
		y3=2;
		blink();
		return(p[0][2]);
	}
	else if(p[0][0]==p[1][1] && p[1][1]==p[2][2])
	{
		x1=0;
		y1=0;
		x2=1;
		y2=1;
		x3=2;
		y3=2;
		blink();
		return(p[0][0]);
	}
	else if(p[0][2]==p[1][1] && p[1][1]==p[2][0])
	{
		x1=2;
		y1=0;
		x2=1;
		y2=1;
		x3=0;
		y3=2;
		blink();
		return(p[0][2]);
	}
	else if(flag==9)
	{
		return(3);
	}
	else
	{
		return(0);
	}
}

void blink()
{
	int i;
	for(i=0;i<2;i++)
	{
		setfillstyle(INTERLEAVE_FILL,12);
		floodfill(xfill+(x1*83),yfill+(y1*83),WHITE);
		floodfill(xfill+(x2*83),yfill+(y2*83),WHITE);
		floodfill(xfill+(x3*83),yfill+(y3*83),WHITE);
		floodfill(xfill+(x1*83)+35,yfill+(y1*83)+35,WHITE);
		floodfill(xfill+(x2*83)+35,yfill+(y2*83)+35,WHITE);
		floodfill(xfill+(x3*83)+35,yfill+(y3*83)+35,WHITE);
		delay(250);
		setfillstyle(INTERLEAVE_FILL,2);
		floodfill(xfill+(x1*83),yfill+(y1*83),WHITE);
		floodfill(xfill+(x2*83),yfill+(y2*83),WHITE);
		floodfill(xfill+(x3*83),yfill+(y3*83),WHITE);
		floodfill(xfill+(x1*83)+35,yfill+(y1*83)+35,WHITE);
		floodfill(xfill+(x2*83)+35,yfill+(y2*83)+35,WHITE);
		floodfill(xfill+(x3*83)+35,yfill+(y3*83)+35,WHITE);
		delay(200);
		setfillstyle(INTERLEAVE_FILL,12);
		floodfill(xfill+(x1*83),yfill+(y1*83),WHITE);
		floodfill(xfill+(x2*83),yfill+(y2*83),WHITE);
		floodfill(xfill+(x3*83),yfill+(y3*83),WHITE);
		floodfill(xfill+(x1*83)+35,yfill+(y1*83)+35,WHITE);
		floodfill(xfill+(x2*83)+35,yfill+(y2*83)+35,WHITE);
		floodfill(xfill+(x3*83)+35,yfill+(y3*83)+35,WHITE);
	}
}

void win(int w)
{
	if(w==1)
	{
		p2remove();
		setcolor(WHITE);
		settextstyle(1,0,5);
		outtextxy(60,250,"YOU");
		outtextxy(65,300,"WIN");
		outtextxy(497,250,"YOU");
		outtextxy(497,300,"LOSE");
	}
	else if(w==2)
	{
		p1remove();
		setcolor(WHITE);
		settextstyle(1,0,5);
		outtextxy(497,250,"YOU");
		outtextxy(502,300,"WIN");
		outtextxy(60,250,"YOU");
		outtextxy(57,300,"LOSE");
	}
	else if(w==3)
	{
		p1remove();
		p2remove();
		setcolor(WHITE);
		settextstyle(1,0,5);
		outtextxy(487,273,"DRAW");
		outtextxy(47,273,"DRAW");
	}
}

void p1remove()
{
	setcolor(9);
	settextstyle(1,0,4);
	outtextxy(57,257,"YOUR");
	outtextxy(57,307,"TURN");
	setfillstyle(SOLID_FILL,9);
	floodfill(100,300,WHITE);
	setfillstyle(HATCH_FILL,8);
	floodfill(100,300,WHITE);
}

void p2remove()
{
	setcolor(9);
	settextstyle(1,0,4);
	outtextxy(497,257,"YOUR");
	outtextxy(497,307,"TURN");
	setfillstyle(SOLID_FILL,9);
	floodfill(540,300,WHITE);
	setfillstyle(HATCH_FILL,8);
	floodfill(540,300,WHITE);
}

void p1set()
{
	setcolor(WHITE);
	settextstyle(1,0,4);
	outtextxy(57,257,"YOUR");
	outtextxy(57,307,"TURN");
}

void p2set()
{
	setcolor(WHITE);
	settextstyle(1,0,4);
	outtextxy(497,257,"YOUR");
	outtextxy(497,307,"TURN");
}

