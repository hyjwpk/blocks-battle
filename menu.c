void menu()
{
	SetConsoleOutputCP(437);
	SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD  dwCursorPosition);
	COORD coord;
	coord.X = 3; //第3行
	coord.Y = 3; //第3列
    system("cls");//清屏
	system("title blocks-battle");//设置cmd窗口标题
	system("mode con cols=48 lines=25");//窗口宽度高度
	system("COLOR 02");
}
////初始菜单，检测键盘输入  

