#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

void intro();
void background(int);
int keypad(int,int);
int column_cell(int);
void Method_1(int,int);
void Method_2(int,int);
int flag_counter();
void get_sudoku();
void solve_sudoku();
void highlight(int,int);
void fill_cells();
void cell_index_finder(int&,int&);
void unable();
void mode_chooser();
void play_now();
void admin_mode();

/*
/////////////////////////////////////////Explanation of class cells/////////////
1. About class:
  1.1. each cell has an array of possible values from 1 to 9 and can be found in array pos_val by subtracting 1
	   from the number and using it as an index.
  1.1. Each cell has flag set to 0 implies no final value is assigned

////////////////////////////////////////////////////////////////////////////////
*/
class cells
{
	public:
		int flag, pos_val[9], final_val,colour;
		int been_to;
		cells();
}s[9][9];

cells::	cells ()
	{
		flag=been_to=0;
		for(int index=0;index<9;index++)
			pos_val[index]=index+1;
	}

void main()
{
	int gd=DETECT, gm;
	initgraph( &gd, &gm, "C:\\TURBOC3\\bgi");
	intro();
	mode_chooser();
	get_sudoku();
	solve_sudoku();
	getch();
	cleardevice();
	closegraph();
}

//////////////////////////////////First page that gives instructions//////////////////////

void intro()
{
	int value_x=(getmaxx()/4);
	background(1);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(value_x,100,3*value_x,175,0,0);
	settextstyle(TRIPLEX_FONT,0,0);
	outtextxy(value_x+54,118,"INSTRUCTIONS");
	setfillstyle(SOLID_FILL,BLACK);
	bar(value_x+54,160,value_x+265,165);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(45,250,550,320,0,0);
	settextstyle(3,0,1);
	outtextxy(50,250,"* Left click on any button/cell to select it.");
	outtextxy(50,270,"* The choice is made for the highlighted(selected) cell.");
	outtextxy(50,290,"* This program can't solve every sudoku.");
	bar3d(getmaxx()-200,getmaxy()-80,getmaxx()-25,getmaxy()-50,0,0);
	outtextxy(getmaxx()-192,getmaxy()-78,"By :- Yash Grover");
	getch();
}

///////////////////////////////////////////////////////////////////////////////////////////

void mode_chooser()
{
	int value_x=(getmaxx()/4);
	background(1);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(value_x,100,3*value_x,175,0,0);
	settextstyle(TRIPLEX_FONT,0,0);
	outtextxy(value_x+40,113,"MAKE A CHOICE");
	setfillstyle(SOLID_FILL,BLACK);
	bar(value_x+43,160,value_x+280,165);
	setfillstyle(SOLID_FILL,RED);
	value_x/=2;
	bar3d(value_x-45,210,(getmaxx()/2)-45,360,0,0);
	settextstyle(DEFAULT_FONT,0,5);
	outtextxy(value_x-25,240,"PLAY");
	outtextxy(value_x+55,299,"NOW");
	bar3d((getmaxx()/2)+50,210,(getmaxx()/2)+290,360,0,0);
	outtextxy((getmaxx()/2)+70,240,"ADMIN");
	outtextxy((getmaxx()/2)+120,299,"MODE");
	setfillstyle(SOLID_FILL,BROWN);
	bar3d((getmaxx()/2)-65,400,(getmaxx()/2)+70,430,0,0);
	settextstyle(DEFAULT_FONT,0,2);
	outtextxy((getmaxx()/2)-50,408,"GO BACK");
	/////////////////Mouse code//////////////////////////////////////////////////////
	back:
	union REGS in,out;
	int x=0,y=0;
	in.x.ax=1;
	int86(0X33,&in,&out);
	delay(500);
	while(out.x.bx!=1)
	{
		in.x.ax=3;
		int86(0X33,&in,&out);
		x=out.x.cx;
		y=out.x.dx;
	}
	in.x.ax=2;
	int86(0X33,&in,&out);
	//////////////////////////////////////////////////////////////////////////////////
	//////////decides what choice is made based on the values of x and y/////////////
	if(x>value_x-45&&x<=(getmaxx()/2)-45&&y>210&&y<=360)
	{
		play_now();
		goto back;
	}
	else if(x>(getmaxx()/2)+50&&x<=(getmaxx()/2)+290&&y>210&&y<=360)
	{
		admin_mode();
		goto back;
	}
	else if(x>(getmaxx()/2)-65&&x<=(getmaxx()/2)+70&&y>400&&y<=430)
		return;
	else
	{
		settextstyle(2,0,0);
		setfillstyle(SOLID_FILL,YELLOW);
		bar3d((getmaxx()/2)+100,33,getmaxx()-70,50,0,0);
		outtextxy((getmaxx()/2)+105,36,"CLICK A TILE");
		goto back;
	}
}

void play_now()
{
}

void admin_mode()
{
	int value_x=(getmaxx()/4);
	background(1);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(value_x,100,3*value_x,175,0,0);
	settextstyle(TRIPLEX_FONT,0,0);
	outtextxy(value_x+40,113,"MAKE A CHOICE");
	setfillstyle(SOLID_FILL,BLACK);
	bar(value_x+43,160,value_x+280,165);
	setfillstyle(SOLID_FILL,RED);
	value_x/=2;
	bar3d(value_x-45,210,(getmaxx()/2)-45,360,0,0);
	settextstyle(DEFAULT_FONT,0,4);
	outtextxy(value_x+35,240,"ADD");
	outtextxy(value_x-20,299,"SUDOKU");
	bar3d((getmaxx()/2)+50,210,(getmaxx()/2)+290,360,0,0);
	outtextxy((getmaxx()/2)+70,240,"DELETE");
	outtextxy((getmaxx()/2)+80,299,"SUDOKU");
	setfillstyle(SOLID_FILL,BROWN);
	bar3d((getmaxx()/2)-65,400,(getmaxx()/2)+70,430,0,0);
	settextstyle(DEFAULT_FONT,0,2);
	outtextxy((getmaxx()/2)-50,408,"GO BACK");
	/////////////////Mouse code//////////////////////////////////////////////////////
	back:
	union REGS in,out;
	int x=0,y=0;
	in.x.ax=1;
	int86(0X33,&in,&out);
	delay(500);
	while(out.x.bx!=1)
	{
		in.x.ax=3;
		int86(0X33,&in,&out);
		x=out.x.cx;
		y=out.x.dx;
	}
	in.x.ax=2;
	int86(0X33,&in,&out);
  //////////////////////////////////////////////////////////////////////////////////
	//////////decides what choice is made based on the values of x and y/////////////
	if(x>value_x-45&&x<=(getmaxx()/2)-45&&y>210&&y<=360)
	{
		play_now();
		goto back;
	}
	else if(x>(getmaxx()/2)+50&&x<=(getmaxx()/2)+290&&y>210&&y<=360)
	{
		admin_mode();
		goto back;
	}
	else if(x>(getmaxx()/2)-65&&x<=(getmaxx()/2)+70&&y>400&&y<=430)
		return;
	else
	{
		settextstyle(2,0,0);
		setfillstyle(SOLID_FILL,YELLOW);
		bar3d((getmaxx()/2)+100,33,getmaxx()-70,50,0,0);
		outtextxy((getmaxx()/2)+105,36,"CLICK A TILE");
		goto back;
	}
}
////////////////////////////////Makes background and sudoku box///////////////////////////
void background(int dec)
{
	////////////code for background and heading//////////////////
	int x_value;
	setcolor(BLACK);
	setlinestyle(SOLID_LINE,1,3);
	setfillstyle(INTERLEAVE_FILL,BLUE);
	bar3d(0,0,getmaxx(),getmaxy(),0,0);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(10,10,getmaxx()-10,getmaxy()-10,0,0);
	setfillstyle(INTERLEAVE_FILL,BLUE);
	bar3d(20,20,getmaxx()-20,getmaxy()-20,0,0);
	settextstyle(1,0,0);
	x_value=(getmaxx()/2)-60;
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(x_value-20,33,x_value+130,80,0,0);
	outtextxy(x_value,30,"SUDOKU");
	setfillstyle(SOLID_FILL,BLACK);
	bar(x_value,70,x_value+115,75);
	//////////////////////////////////////////////
	if(dec==0)
	{
	//////////////code for sudoku////////////////
		setfillstyle(SOLID_FILL,WHITE);
		bar(75,125,345,395);//cells are 30 by 30
		setlinestyle(SOLID_LINE,1,3);
		setcolor(BLACK);
		for(int j=125;j<396;j=j+30)
		{
			if(j==215||j==305||j==125||j==395)
				setcolor(RED);
			else
				setcolor(BLACK);
			line(75,j,345,j);
		}
		for(int i=75;i<346;i=i+30)
		{
			if(i==165||i==255||i==75||i==345)
				setcolor(RED);
			else
				setcolor(BLACK);
			line(i,125,i,395);
		}
		setcolor(RED);
		line(75,125,75,395);
		line(75,215,345,215);
		line(75,305,345,305);
		line(345,125,345,395);
		line(75,125,345,125);
		line(75,395,345,395);
	//////////////////////////////////////////////

		fill_cells();//description at function defination
	}
}
///////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////gets values from user////////////////////////////////////////

	//////makes keypad and returns the value selected by the user///////

int keypad(int index_1,int index_2)
{
	////////code for keypad///////////////////////////////////////////////////////////

	setfillstyle(SOLID_FILL,RED);
	setcolor(BLACK);
	int count=0,flag[9]={0,0,0,0,0,0,0,0,0};
	char string[50];
	for(int g=0;g<151;g+=75)
		for(int k=0;k<151;k+=75)
		{
			if(s[index_1][index_2].pos_val[count]!=0)
			{
				flag[count]=1;
				bar3d(375+k,125+g,435+k,185+g,2,0);
				sprintf(string,"%d",count+1);
				outtextxy(398+k,135+g,string);
			}
			count++;
		}

	bar3d(375,350,585,410,2,0);
	outtextxy(394,360,"Don't Know");
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar3d(559,430,609,450,0,0);
	settextstyle(2,0,0);
	outtextxy(570,432,"EXIT");
	/////////////////////////////////////////////////////////////////////////////////

	/////////////////Mouse code//////////////////////////////////////////////////////
	union REGS in,out;
	int x,y;
	back:
	in.x.ax=1;
	int86(0X33,&in,&out);
	delay(500);
	while(out.x.bx!=1)
	{
		in.x.ax=3;
		int86(0X33,&in,&out);
		x=out.x.cx;
		y=out.x.dx;
	}
	in.x.ax=2;
	int86(0X33,&in,&out);
	//////////////////////////////////////////////////////////////////////////////////

	//////////decides what should be returned based on the values of x and y/////////////

	count=1;
	for(g=0;g<151;g+=75)
		for(k=0;k<151;k+=75)
		{
			if(x>375+k&&y>125+g&&x<435+k&&y<185+g&&flag[count-1]==1)
				return count;
			count++;
		}
	if(x>375&&x<585&&y>350&&y<410)
		return 0;
	else if(x>559&&x<609&&y>430&&y<450)
		return -1;
	else
	{
		settextstyle(2,0,0);
		setfillstyle(SOLID_FILL,YELLOW);
		bar3d((getmaxx()/2)+100,33,getmaxx()-70,50,0,0);
		outtextxy((getmaxx()/2)+105,36,"CLICK A TILE");
		goto back;
	}
	/////////////////////////////////////////////////////////////////////////////////
}
	//////assigns the value returned by function keypad to the cells type variable that it was called for or exit if that is what the choice user made///////

void get_sudoku()
{
	int ctr=0;
	int out_i,x,y;
	int index_1=0,index_2=0;
	char choice='y';
	cells value_reset[9][9];
	while(choice=='y')
	{
	///////////resets the value of array s///////////////
		for(int a=0;a<9;a++)
			for(int b=0;b<9;b++)
				s[a][b]=value_reset[a][b];
	////////////////////////////////////////////////////

	////////////calls keypad function for array s/////////
		while(ctr!=81)
		{
			ctr=0;
			for(index_1=0;index_1<9;index_1++)
				for(index_2=0;index_2<9;index_2++)
					if(s[index_1][index_2].been_to==1)
						ctr++;
			index_1=index_2=0;
			cell_index_finder(index_1,index_2);
			s[index_1][index_2].been_to=1;
			highlight(index_1,index_2);
			Method_1(index_1,index_2);//see description below
			out_i=keypad(index_1,index_2);
			if(out_i==-1)
				exit(0);
			s[index_1][index_2].final_val=out_i;
			if(s[index_1][index_2].final_val!=0)
				s[index_1][index_2].flag=s[index_1][index_2].colour=1;
			background(0);
			delay(100);
		 }
	/////////////////////////////////////////////////////

	///////asks if user want to enter values again///////
		bar3d(100,100,getmaxx()-100,getmaxy()-200,0,0);
		settextstyle(1,0,0);
		outtextxy(150,125,"Do you want to enter");
		outtextxy(200,150,"values again?");
		setfillstyle(SOLID_FILL,YELLOW);
		bar3d(150,243,250,210,0,0);
		outtextxy(172,207,"YES");
		bar3d(400,243,500,210,0,0);
		outtextxy(430,207,"NO");
		union REGS in,out;
		back_2:
		in.x.ax=1;
		int86(0X33,&in,&out);
		delay(500);
		while(out.x.bx!=1)
		{
			in.x.ax=3;
			int86(0X33,&in,&out);
			x=out.x.cx;
			y=out.x.dx;
		}
		in.x.ax=2;
		int86(0X33,&in,&out);
		if(x>400&&x<500&&y<243&&y>210)
			choice='n';
		else if(x>150&&x<250&&y<243&&y>210)
				choice='y';
		else
		{
			settextstyle(2,0,0);
			setfillstyle(SOLID_FILL,YELLOW);
			bar3d((getmaxx()/2)+100,33,getmaxx()-70,50,0,0);
			outtextxy((getmaxx()/2)+105,36,"CLICK A TILE");
			goto back_2;
		}
	}
	/////////////////////////////////////////////////////////////

	cleardevice();
	background(0);
}

	////////highlights the cell whose value is being entered/////////
void highlight(int index_1,int index_2)
{
	cleardevice();
	background(0);
	setfillstyle(SLASH_FILL,YELLOW);
	bar(75+(30*index_2),125+(30*index_1),105+(30*index_2),155+(30*index_1));
}

///////////////////////////////////////////////////////////////////////////////////////////

/////////////////solves sudoku/////////////////////////////////////////////////////////////

	/////////decides which function to call Method1 or Method2//////////
	/////////Method1 is called in every iteration///////////////////////
	/////////Method2 is called if after 2 iterations if no new cell is assigned a final value///
void solve_sudoku()
{
	int flag_count=55,count_=0,flag_=0,index_1,index_2;
	cells s_pseudo[9][9];
	time_t t1,t2;
	t1=time(NULL);
	///////while loop is run till every cell is assigned a final value///////
	///////the loop breaks after 2 seconds(to prevent getting in an infinite loop if the program is unable to solve the sudoku////
	while(flag_count!=0&&difftime(t2,t1)!=2)
	{

		for(index_1=0;index_1<9;index_1++)
			for(index_2=0;index_2<9;index_2++)
				if(s[index_1][index_2].flag==0)
					Method_1(index_1,index_2);

		///////checks if a new cell is assigned a final value or not////////////
		for(index_1=0;index_1<9;index_1++)
			for(index_2=0;index_2<9;index_2++)
				if(s[index_1][index_2].final_val!=s_pseudo[index_1][index_2].final_val)
					count_++;
		if(count_==0)
			flag_=1;

		if(flag_==1)
			for(index_1=0;index_1<9;index_1++)
				for(index_2=0;index_2<9;index_2++)
					if(s[index_1][index_2].flag==0)
						Method_2(index_1,index_2);


		for(index_1=0;index_1<9;index_1++)
			for(index_2=0;index_2<9;index_2++)
				s_pseudo[index_1][index_2]=s[index_1][index_2];
		flag_=count_=0;
		flag_count=flag_counter();
		t2=time(NULL);
	}
	if(difftime(t2,t1)==2)
	{
		cleardevice();
		unable();
	}
	else
	fill_cells();
}
/*
///////////////Explanation of Method 1(used in every iteration)///////////////

1. Checks if cell has flag set to 0
  1.1. shows no final value is assigned
2. Compares the cell with all cells that are in same row, column and block and have flag set to 1
  2.1. How possibilities are removed:
	  2.1.1. let s be the cell whose possible values we are removing and s2 be any arbitrary cell in the same row, column or block that
			 has flag set to 1
	  2.1.2. Use expression s.pos_val(s2.final_val-1)=0 to remove possibilities
3. Sees how many non zero possibilities are left
  3.1. if only one is left it assigns it to final_val and changes flag to 1
//////////////////////////////////////////////////////////////////////////////////
*/
void Method_1(int index_1,int index_2)
{
	int index_a=0,index_b=0,limit_a=0,limit_b=0,index_a_set,index_b_set;

	for(index_a=0;index_a<9;index_a++)
		if(s[index_1][index_a].flag==1)
			s[index_1][index_2].pos_val[s[index_1][index_a].final_val-1]=0;

	for(index_a=0;index_a<9;index_a++)
		if(s[index_a][index_2].flag==1)
			s[index_1][index_2].pos_val[s[index_a][index_2].final_val-1]=0;

	index_a_set=column_cell(index_1);
	index_b_set=column_cell(index_2);
	limit_a=index_a_set+3;
	limit_b=index_b_set+3;

	for(index_a=index_a_set;index_a<limit_a;index_a++)
		for(index_b=index_b_set;index_b<limit_b;index_b++)
			if(s[index_a][index_b].flag==1)
				s[index_1][index_2].pos_val[s[index_a][index_b].final_val-1]=0;

	int count_=0,index,index_pos;
	for(index=0;index<9;index++)
		if(s[index_1][index_2].pos_val[index]!=0)
		{
			count_++;
			index_pos=index;
		}
	if(count_==1)
	{
		s[index_1][index_2].final_val=s[index_1][index_2].pos_val[index_pos];
		s[index_1][index_2].flag=1;
	}
}

/*
///////////Explanation of Method 2(used if after 2 iterations no new cell is assigned a final value////

1. Taking possible values of a cell one by one, counts how many cells with flag set to 0 in same row, column or block have that value in their pos_val array
  1.1. if it is the only cell that has that possible value in its pos_val array then it assigns it to final value and set flag to 1.
///////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void Method_2(int index_1,int index_2)
{
	int index_a,index_b,limit_a,limit_b,values,val_count=0,index_a_set,index_b_set,condition=0;

	index_a_set=column_cell(index_1);
	index_b_set=column_cell(index_2);
	limit_a=index_a_set+3;
	limit_b=index_b_set+3;
	for(values=1;values<10;values++)
	{
		for(index_a=index_a_set;index_a<limit_a;index_a++)        //for block
			for(index_b=index_b_set;index_b<limit_b;index_b++)
				if(s[index_a][index_b].final_val==values)
					condition=1;
		if(s[index_1][index_2].pos_val[values-1]!=0&&condition==0)
		{
			for(index_a=index_a_set;index_a<limit_a;index_a++)
				for(index_b=index_b_set;index_b<limit_b;index_b++)
					if(s[index_a][index_b].pos_val[values-1]!=0&&s[index_a][index_b].flag==0)
						val_count++;
			if(val_count==1)
			{
				s[index_1][index_2].final_val=s[index_1][index_2].pos_val[values-1];
				s[index_1][index_2].flag=1;
			}
			val_count=0;
			if(s[index_1][index_2].flag==1)
				return;
		}
		condition=0;

		for(index_a=0;index_a<9;index_a++)        //for column
			if(s[index_a][index_2].final_val==values)
				condition=1;
		if(s[index_1][index_2].pos_val[values-1]!=0&&condition==0)
		{
			for(index_a=0;index_a<9;index_a++)
					if(s[index_a][index_2].pos_val[values-1]!=0&&s[index_a][index_2].flag==0)
						val_count++;
			if(val_count==1)
			{
				s[index_1][index_2].final_val=s[index_1][index_2].pos_val[values-1];
				s[index_1][index_2].flag=1;
			}
			val_count=0;
			if(s[index_1][index_2].flag==1)
				return;
		}
		condition=0;

		 for(index_b=0;index_b<9;index_b++)        //for row
			if(s[index_1][index_b].final_val==values)
				condition=1;
		if(s[index_1][index_2].pos_val[values-1]!=0&&condition==0)
		{
			for(index_b=0;index_b<9;index_b++)
				if(s[index_1][index_b].pos_val[values-1]!=0&&s[index_1][index_b].flag==0)
					val_count++;
			if(val_count==1)
			{
				s[index_1][index_2].final_val=s[index_1][index_2].pos_val[values-1];
				s[index_1][index_2].flag=1;
			}
			val_count=0;
			if(s[index_1][index_2].flag==1)
				return;
		}
		condition=0;
	}
}

int column_cell(int index_1)
{
	if(index_1<3)
		return 0;
	else if(index_1<6&&index_1>=3)
		return 3;
	else if(index_1>=6)
		return 6;
	else return 0;
}

////////counts how many cells have not been assigned a final value//////////
int flag_counter()
{
	int count_=0;
	for(int index_1=0;index_1<9;index_1++)
		for(int index_2=0;index_2<9;index_2++)
			if(s[index_1][index_2].flag==0)
				count_++;
	return count_;
}
///////////////////////////////////////////////////////////////////////////////////////////

///////////fills cells with their final value///////////////////////////////
void fill_cells()
{
	int index_1=0,index_2=0,count=0;
	char string[50];
	for(int i=0;i<241;i+=30)
	{
		index_2=0;
		for(int j=0;j<241;j+=30)
		{
			int ff;
			ff=getcolor();
			if(s[index_1][index_2].flag==1)
			{
				count++;
				sprintf(string,"%d",s[index_1][index_2].final_val);
			}
			else
				sprintf(string,"");
			if(s[index_1][index_2].colour==1)
				setcolor(RED);
			else
				setcolor(BLACK);
			outtextxy(82+j,119+i,string);
			setcolor(ff);
			index_2++;
		}
		index_1++;
	}
	if(count==81)
	{
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,YELLOW);
		bar3d(375,150,550,200,0,0);
		outtextxy(380,155,"SOLVED IT");
	}
}

void cell_index_finder(int & index_a,int & index_b)
{
	////////////////////////////////////////////////////
	union REGS in,out;
	int x,y;
	back:
	in.x.ax=1;
	int86(0X33,&in,&out);
	delay(500);
	while(out.x.bx!=1)
	{
		in.x.ax=3;
		int86(0X33,&in,&out);
		x=out.x.cx;
		y=out.x.dx;
	}
	in.x.ax=2;
	int86(0X33,&in,&out);
	//////////////////////////////////////////////////////////////////////////////////

	//////////decides what should be value of index_a and index_b based on the values of x and y/////////////
	int i,j;
	for(j=0;j<9;j++)
	{
		if(y>=125+(30*j)&&y<125+(30*(j+1)))
		{
			index_a=j;
			break;
		}
	}
	for(i=0;i<9;i++)
	{
		if(x>=75+(30*i)&&x<75+(30*(i+1)))
		{
			index_b=i;
			break;
		}
	}

	if(i>8||j>8)
	{
		settextstyle(2,0,0);
		setfillstyle(SOLID_FILL,YELLOW);
		bar3d((getmaxx()/2)+100,33,getmaxx()-70,50,0,0);
		outtextxy((getmaxx()/2)+105,36,"CLICK A CELL");
		goto back;
	}

}

//////////////////tells the user the program was unable to solve the sudoku///////////////////
void unable()
{
	int value_x;
	value_x=(getmaxx()/4);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE,1,3);
	setfillstyle(INTERLEAVE_FILL,BLUE);
	bar3d(0,0,getmaxx(),getmaxy(),0,0);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(value_x,50,3*value_x,125,0,0);
	settextstyle(1,0,0);
	outtextxy(value_x+54,68,"Cant Solve This");
	setfillstyle(SOLID_FILL,BLACK);
	bar(value_x+54,110,value_x+265,115);
	setfillstyle(SOLID_FILL,YELLOW);
	bar3d(45,150,500,220,0,0);
	settextstyle(3,0,1);
	outtextxy(50,150,"Possible Reasons:- ");
	outtextxy(50,170,"* You might have entered wrong values.");
	outtextxy(50,190,"* The sudoku requires use of advanced techniques");
}