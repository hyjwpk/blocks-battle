#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

#define LENGTH 50
#define WIDTH 30
#define INITIAL_X 25
#define INITIAL_Y 15
#define BOARDLENGTH 50
#define CHARACTER {printf("%c%c", 0xa8, 0x84);}

char map[WIDTH][LENGTH];

void print(void);
void position(int x,int y);
void boardmove(int *board);
void ballmove(int *x,int *y,int x_move,int y_move);
void crash(int x,int y,int *x_move,int *y_move);


int main(void)
{
    int board=0;
    int x=INITIAL_X,y=INITIAL_Y;
    int x_move=1,y_move=1;
    for(int i=0; i<LENGTH; i++)
    {
        map[0][i]=1;       
    }
    for(int i=0; i<WIDTH; i++)
    {
        map[i][0]=1;
        map[i][LENGTH-1]=1;       
    }
    for(int i=board; i<board+BOARDLENGTH; i++)
    {
        map[WIDTH-1][i]=1;       
    }
    for(int i=2;i<=8;i+=3)
    {
        for(int k=10;k<=39;k++)
        {
            map[i][k]=2;
        }
    }
    map[INITIAL_Y][INITIAL_X]=1;
    print();
    int i=1;
    while(i<=10)
    {
        Sleep(100);
        boardmove(&board);
        crash(x,y,&x_move,&y_move);
        ballmove(&x,&y,x_move,y_move);
    }
    return 0;
}

void print(void)
{
    system("cls");
    for(int i=0; i<WIDTH; i++)
    {
        for(int j=0; j<LENGTH; j++)
        {
            if(map[i][j]!=0)
                CHARACTER
            if(map[i][j]==0)
                printf(" ");
        }
        printf("\n");
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

void crash(int x,int y,int *x_move,int *y_move)
{
    if(map[y][x+*x_move]!=0||map[y+*y_move][x]!=0)
    {
        switch(map[y][x+*x_move])
        {
            case 2:
            position(x+*x_move,y);
            printf(" ");
            map[y][x+*x_move]=0;
            case 1:
            *x_move=-*x_move;
            default:;
        }
        switch(map[y+*y_move][x])
        {
            case 2:
            position(x,y+*y_move);
            printf(" ");
            map[y+*y_move][x]=0;  
            case 1:
            *y_move=-*y_move;
            default:;
        }
    }
    else
    {
        switch(map[y+*y_move][x+*x_move])
        {
            case 2:
            position(x+*x_move,y+*y_move);
            printf(" ");
            map[y+*y_move][x+*x_move]=0;
            case 1:
            *x_move=-*x_move;
            *y_move=-*y_move;
            default:;
        }
    }
    if(y+*y_move==WIDTH)
        abort();
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
    CHARACTER
}

void boardmove(int *board)
{
    if(kbhit())
        switch(getch())
        {
            case'a':case'A':
            if(*board>1) 
            {
                map[WIDTH-1][BOARDLENGTH-1+*board]=0;
                *board-=1;
                map[WIDTH-1][*board]=1;
                position(*board,WIDTH-1);
                CHARACTER
                position(*board+BOARDLENGTH,WIDTH-1);
                printf(" ");
            }
            break;

            case'd':case'D':
            if(*board+BOARDLENGTH<LENGTH-1) 
            {
                map[WIDTH-1][*board]=0;
                *board+=1;
                map[WIDTH-1][BOARDLENGTH-1+*board]=1;
                position(*board-1,WIDTH-1);
                printf(" ");
                position(*board+BOARDLENGTH-1,WIDTH-1);
                CHARACTER
            }
            break;
        }
}
