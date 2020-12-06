#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//#include <graphics.h> 
#define LENGTH 50
#define WIDTH 30
#define INITIAL_X 25
#define INITIAL_Y 15
#define BOARDLENGTH 20

//#define CHARACTER {cout  << "\033[32m修改\033[0m"<< endl ;}
//1--砖 2--左边框 3--底板 4--右边框 5--上边框 6--球 
int score=0,try=1,state=1,board=20;
char map[WIDTH][LENGTH];

void character(int i);
void initial(void);
void game(void);
void print(void);
void menu(void);
void position(int x,int y);
void boardmove(int *board);
void ballmove(int *x,int *y,int x_move,int y_move);
void crash(int x,int y,int *x_move,int *y_move);

int main(void)
{
    initial();
	menu();
    return 0;
}

void initial(void)
{
    SetConsoleOutputCP(437);
    system("title blocks-battle");//设置cmd窗口标题
	system("mode con cols=97 lines=40");//窗口宽度高度
    char title[100];
    HWND hwnd;
    GetConsoleTitle(title,100);
    hwnd=FindWindow(NULL,title);
    MoveWindow(hwnd,450,150,700,600,TRUE);
    HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.bVisible = 0;
    cinfo.dwSize = 1;
    SetConsoleCursorInfo(fd,&cinfo);
}

void menu()
{
    system("cls");
    system("color 54");
    HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出句柄
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN);
	printf("\t\t\t\t     A/a -> left,D/d -> right    \t\t\t\t\n");printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("\t\t\t\tPress any key to start your game!\t\t\t\t\n");printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
	getch();//用户键盘输入时开始游戏
	printf("\t\t\t\t           Game start!           \t\t\t\t\t");
	Sleep(1000);//等待1s
    game();
}

void game(void)
{
    int x=INITIAL_X,y=INITIAL_Y;
    int x_move=1,y_move=1;
    for(int i=0; i<LENGTH; i++)
    {
        map[0][i]=5;       
    }
    for(int i=0; i<WIDTH; i++)
    {
        map[i][0]=2;
        map[i][LENGTH-1]=4;       
    }
    for(int i=board; i<board+BOARDLENGTH; i++)
    {
        map[WIDTH-1][i]=3;       
    }
    for(int i=2;i<=8;i+=3)
    {
        for(int k=10;k<=39;k++)
        {
            map[i][k]=1;
        }
    }
    map[INITIAL_Y][INITIAL_X]=6;
    print();
    while(1)
    {
    	position(70,1);printf("State%d",state);
    	position(70,2);printf("Try%d",try);
        position(70,3);printf("score = %d",score);
	    Sleep(100);
        boardmove(&board);
        crash(x,y,&x_move,&y_move);
        ballmove(&x,&y,x_move,y_move);
        if(score==90)
	    {
            score=0;
		    state++;
            menu();
	    }
    }
}

void print(void)
{
    system("color 75");
    system("cls");
    for(int i=0; i<WIDTH; i++)
    {
        for(int j=0; j<LENGTH; j++)
        {
            character(map[i][j]);
        }
        printf("\n");
    }
}

void character(int i)
{
    switch(i)
    {
        case 1: printf("%c",219); break;
        case 2: printf("%c",221); break;
        case 3: printf("%c",220); break;
        case 4: printf("%c",222); break;
        case 5: printf("%c",223); break;
        case 6: printf("%c",254);break;
        default:printf(" ");
    } 
}

void position(int x,int y) 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void boardmove(int *board)
{
	if(kbhit())
	{
		switch (getch())
		{
			case 75: // left
				if(*board>1) 
		        {
		            map[WIDTH-1][BOARDLENGTH-1+*board]=0;
		            *board-=1;
		            map[WIDTH-1][*board]=3;
		            position(*board,WIDTH-1);
		            character(3);
		            position(*board+BOARDLENGTH,WIDTH-1);
		            printf(" ");
		        }
				break;
			case 77:
				if(*board+BOARDLENGTH<LENGTH-1) 
			    {
			        map[WIDTH-1][*board]=0;
			        *board+=1;
			        map[WIDTH-1][BOARDLENGTH-1+*board]=3;
			        position(*board-1,WIDTH-1);
			        printf(" ");
			        position(*board+BOARDLENGTH-1,WIDTH-1);
			        character(3);
			    }
				break;
		}
	}
}

void crash(int x,int y,int *x_move,int *y_move)
{
    if(map[y][x+*x_move]!=0||map[y+*y_move][x]!=0)
    {
        switch(map[y][x+*x_move])
        {
            case 1:
                score++;
                position(x+*x_move,y);
                printf(" ");
                map[y][x+*x_move]=0;
            case 5:case 4:case 3:case 2:
                *x_move=-*x_move;
            default:;
        }
        switch(map[y+*y_move][x])
        {
            case 1:
        	    score++;
                position(x,y+*y_move);
                printf(" ");
                map[y+*y_move][x]=0;  
            case 5:case 4:case 3:case 2:
                *y_move=-*y_move;
            default:;
        }
        crash(x,y,x_move,y_move);
    }
    else if(map[y+*y_move][x+*x_move]!=0)
    {
        switch(map[y+*y_move][x+*x_move])
        {
            case 1:
                score++;
                position(x+*x_move,y+*y_move);
                printf(" ");
                map[y+*y_move][x+*x_move]=0;
            case 5:case 4:case 3:case 2:
                *x_move=-*x_move;
                *y_move=-*y_move;
            default:;
        }
        crash(x,y,x_move,y_move);
    }
    if(y+*y_move==WIDTH)
    {	
    	try++;
    	map[y][x]=0;
    	score=0;
	    position(15,31);
		printf("HAVE LOST GAME!");
	    Sleep(2000);
    	menu();
	}
}

void ballmove(int *x,int *y,int x_move,int y_move)
{
    position(*x,*y);
    printf(" ");
    map[*y][*x]=0;
    *x+=x_move;
    *y+=y_move;
    map[*y][*x]=1;
    position(*x,*y);
    character(6);
}




/*
0 = 黑色1 = 蓝色2 = 绿色3 = 浅绿色4 = 红色
5 = 紫色6 = 黄色7 = 白色8 = 灰色9 = 淡蓝色
A = 淡绿色B = 淡浅绿色C = 淡红色D = 淡紫色
E = 淡黄色F = 亮白色

常用的ANSI控制码如下：
\033[0m 关闭所有属性
\033[1m 高亮
\033[2m 亮度减半
\033[3m 斜体
\033[4m 下划线
\033[5m 闪烁
\033[6m 快闪
\033[7m 反显
\033[8m 消隐
\033[9m 中间一道横线
10-19 关于字体的
21-29 基本与1-9正好相反
30-37 设置前景色
40-47 设置背景色
30:黑
31:红
32:绿
33:黄
34:蓝色
35:紫色
36:深绿
37:白色
38 打开下划线,设置默认前景色
39 关闭下划线,设置默认前景色
40 黑色背景
41 红色背景
42 绿色背景
43 棕色背景
44 蓝色背景
45 品红背景
46 孔雀蓝背景
47 白色背景
48 不知道什么东西
49 设置默认背景色
50-89 没用
90-109 又是设置前景背景的，比之前的颜色浅
\033[nA 光标上移n行
\033[nB 光标下移n行
\033[nC 光标右移n行
\033[nD 光标左移n行
\033[y;xH设置光标位置
\033[2J 清屏
\033[K 清除从光标到行尾的内容
\033[s 保存光标位置
\033[u 恢复光标位置
\033[?25l 隐藏光标
\033[?25h 显示光标
*/
//砖块被撞击后改变颜色，记录分值 
//缩小边框值，设置初始位置使其居中 


/*while(1)
	{
		system("color 15");Sleep(100);
		system("color 26");Sleep(100);
		system("color 37");Sleep(100);
		system("color 4A");Sleep(100);
		system("color 52");Sleep(100);
		system("color 6B");Sleep(100);
		system("color 7C");Sleep(100);
	}
*/
/*void boardmove(int *board)
{
    if(kbhit())
        switch(getch())
        {
            case'a':case'A':
            if(*board>1) 
            {
                map[WIDTH-1][BOARDLENGTH-1+*board]=0;
                *board-=1;
                map[WIDTH-1][*board]=3;
                position(*board,WIDTH-1);
                CHARACTER3
                position(*board+BOARDLENGTH,WIDTH-1);
                printf(" ");
            }
            break;

            case'd':case'D':
            if(*board+BOARDLENGTH<LENGTH-1) 
            {
                map[WIDTH-1][*board]=0;
                *board+=1;
                map[WIDTH-1][BOARDLENGTH-1+*board]=3;
                position(*board-1,WIDTH-1);
                printf(" ");
                position(*board+BOARDLENGTH-1,WIDTH-1);
                CHARACTER3
            }
            break;
        }
}*/

