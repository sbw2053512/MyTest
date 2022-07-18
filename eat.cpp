#include<iostream>
#include<windows.h>
#include<conio.h>
#include <stdlib.h>
#include<time.h>

using namespace std;
#define ROW 26
#define COL 60
int score = 0;
bool eated = false;
//控制程序的主要过程包括描绘界面
void welcome() {
	cout << endl << endl << endl;
	cout << "   * * * * * * * * * * * * * *" << endl;
	cout << "                               " << endl;
	cout << "   *        WELCOME!         *" << endl;
	cout << "                               " << endl;
	cout << "   * * * * * * * * * * * * * *" << endl;
}
void rule() {
	cout << "                                       "
		<< "Rule:" << endl
		<< "                                            "
		<< "控制蛇的方向，寻找吃的东西，注意不要撞到墙和咬到自己！" << endl
		<< "  W: 向上" << endl << "  S: 向下" << endl << "  A: 向左" << endl << "  D: 向右"
		<< "                                      "
		<< "吃到食物会得到相应的积分。" << endl
		<< "                                            "
		<< " 你的唯一目标是变成一条长长的蛇!" << endl;

}
void prepare() { cout << "   10秒之后游戏开始,按任意键继续" << endl; }
void time() {
	cout << "                                    ";
	for (int i = 10; i >= 0; i--) {
		cout << " " << i << " ";  Sleep(1000);
		if (_kbhit() != 0) break;
	}
}
void name() {
	cout << endl << endl << "                                            "
		<< "制作人：Yiliya" << endl;
}
//方向
enum MyEnum
{
	Up = 0, Down, Left, Right
};
 //移动光标
void gotxy(int i, int j)       
{
	COORD position = { short(j),short(i) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
//墙，生成墙和画墙
struct Wall {
	int M[ROW][COL];
};
void Initmap(Wall& w) {
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
			{
				w.M[i][j] = 1;//1为墙
			}
			else  w.M[i][j] = 0;//0不为0
		}

	}
}
void Drawmap(Wall& w) {
	gotxy(0, 0);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (w.M[i][j] == 1) { cout << '*'; }
			else cout << " ";
		}
		cout << endl;
	}
}

//蛇的对象，包括了长度和方向，每一个Coordinate都包含了一个坐标，不进行初始化，每次增长时赋予新值。
struct Snake {
	int direction = 0;
	int length = 4;//4是因为move函数消去尾巴。这样蛇的长度打印出来为3
	int Coordinate[ROW * COL][2] = { 0,0 };
};
void fuclength(Snake& s)
{
	s.length++;
}
void Initsnake(Snake& s) {
	s.Coordinate[0][0] = ROW / 2;//0为横坐标
	s.Coordinate[0][1] = COL / 2;//1为纵坐标
	for (int i = 1; i < s.length; i++)
	{
		s.Coordinate[i][0] = s.Coordinate[0][0] + i;
		s.Coordinate[i][1] = s.Coordinate[0][1];
	}
}
void Drawsnake(Snake& s) {

	for (int i = 0; i < s.length; i++)
	{
		gotxy(s.Coordinate[i][0], s.Coordinate[i][1]);
		if (i == 0)cout << '@';
		else cout << '#';

	}
}
void Move(Snake& s) {//从尾部开始后面的等于前面的坐标

	gotxy(s.Coordinate[s.length - 1][0], s.Coordinate[s.length - 1][1]);
	cout << " ";
	for (int i = s.length - 1; i > 0; i--)
	{
		s.Coordinate[i][0] = s.Coordinate[i - 1][0];//行坐标
		s.Coordinate[i][1] = s.Coordinate[i - 1][1];//列坐标
	}

	switch (s.direction)
	{
		case Up:
			s.Coordinate[0][0]--;
			break;
		case Down:
			s.Coordinate[0][0]++;
			break;
		case Left:
			s.Coordinate[0][1]--;
			break;
		case Right:
			s.Coordinate[0][1]++;
			break;

	}
}
void directioncontrol(Snake& s) {
	if (_kbhit() != 0)
	{
		char in;
		while (_kbhit() != 0)
		{
			in = _getch();
		}
		switch (in)
		{
			case 'W':
			case 'w':
				if (s.direction != Down)
					s.direction = Up;
				break;
			case 'S':
			case 's':
				if (s.direction != Up)
					s.direction = Down;
				break;
			case 'A':
			case 'a':
				if (s.direction != Right)
					s.direction = Left;
				break;
			case 'D':
			case 'd':
				if (s.direction != Left)
					s.direction = Right;
				break;
			case 'p':
			case 'P':
				gotxy(ROW, 0);        //将光标移动到下面
				system("pause");
				gotxy(ROW, 0);
				cout << "                   ";
				break;

		}
	}
}
bool death(Snake& s){
	bool isGameOver = false;
	int sX = s.Coordinate[0][0], sY = s.Coordinate[0][1];      //蛇头的x坐标和y坐标
	if (sX == 0 || sX == ROW - 1 || sY == 0 || sY == COL - 1)
		isGameOver = true;
	for (int i = 1; i < s.length; i++)    //判断有没有吃到自己
	{
		if (s.Coordinate[i][0] == sX && s.Coordinate[i][1] == sY)
			isGameOver = true;
	}
	return isGameOver;
}
int flag1 = 0, flag2 = 0, flag3 = 0;
void Drawfood(Wall& w, Snake& s) {
	do {
		flag1 = 0, flag2 = 0;
		int i = rand() % ROW;               //生成0~ROW-1之间的一个数
		int j = rand() % COL;
		if (w.M[i][j] != 1) flag1 = 1;//没有生成在墙内
		int k;
		for (k = 0; k < s.length; k++)
		{
			if (i == s.Coordinate[k][0] && j == s.Coordinate[k][1])
				flag2 = -1;//没有生成在蛇身上
		}
		if (flag1 == 1 && flag2 != -1) {
			w.M[i][j] = -1;
			gotxy(i, j);
			cout << '&';

		}
	} while (flag1 != 1 || flag2 == -1);
}
void PrintScore()
{
	gotxy(0, COL + 2);
	cout << "  贪吃蛇游戏";
	gotxy(2, COL + 2);
	cout << "  Yiliya制作";
	gotxy(4, COL + 2);
	cout << "   P暂停    ";
	gotxy(6, COL + 2);
	cout << "To move,please press wsad ";
	gotxy(8, COL + 2);
	cout << "  得分: " << score;
}


int main()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //隐藏光标
	welcome(); rule(); name();
	prepare();
	time();
	Wall w;
	Snake s;
//	Food f;
	system("cls");
	{//初始化界面、蛇和食物
		Initmap(w);
		Initsnake(s);
		Drawmap(w);
		Drawsnake(s);
		//f.Init();
		srand((unsigned)time(NULL));
		Drawfood(w, s);
	}
	while (1)//循环生成食物
	{
		directioncontrol(s);
		Move(s);
		Sleep(100);
		Drawsnake(s);
		PrintScore();
		if (death(s))
		{
			system("cls");          //清除屏幕内容
			cout << "Game Over" << endl;
			system("pause");
			break;
		}
		if (w.M[s.Coordinate[0][0]][s.Coordinate[0][1]] == -1)
		{
			eated = true;
			if (eated == true)               //如果吃到了食物
			{
				fuclength(s);
				eated = false;        //设置为false，不然无限变长
			}
			score += 10;
			Drawfood(w, s);
			w.M[s.Coordinate[0][0]][s.Coordinate[0][1]] = 0;
		}
	}
	return 0;
}