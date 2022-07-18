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
//���Ƴ������Ҫ���̰���������
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
		<< "�����ߵķ���Ѱ�ҳԵĶ�����ע�ⲻҪײ��ǽ��ҧ���Լ���" << endl
		<< "  W: ����" << endl << "  S: ����" << endl << "  A: ����" << endl << "  D: ����"
		<< "                                      "
		<< "�Ե�ʳ���õ���Ӧ�Ļ��֡�" << endl
		<< "                                            "
		<< " ���ΨһĿ���Ǳ��һ����������!" << endl;

}
void prepare() { cout << "   10��֮����Ϸ��ʼ,�����������" << endl; }
void time() {
	cout << "                                    ";
	for (int i = 10; i >= 0; i--) {
		cout << " " << i << " ";  Sleep(1000);
		if (_kbhit() != 0) break;
	}
}
void name() {
	cout << endl << endl << "                                            "
		<< "�����ˣ�Yiliya" << endl;
}
//����
enum MyEnum
{
	Up = 0, Down, Left, Right
};
 //�ƶ����
void gotxy(int i, int j)       
{
	COORD position = { short(j),short(i) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
//ǽ������ǽ�ͻ�ǽ
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
				w.M[i][j] = 1;//1Ϊǽ
			}
			else  w.M[i][j] = 0;//0��Ϊ0
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

//�ߵĶ��󣬰����˳��Ⱥͷ���ÿһ��Coordinate��������һ�����꣬�����г�ʼ����ÿ������ʱ������ֵ��
struct Snake {
	int direction = 0;
	int length = 4;//4����Ϊmove������ȥβ�͡������ߵĳ��ȴ�ӡ����Ϊ3
	int Coordinate[ROW * COL][2] = { 0,0 };
};
void fuclength(Snake& s)
{
	s.length++;
}
void Initsnake(Snake& s) {
	s.Coordinate[0][0] = ROW / 2;//0Ϊ������
	s.Coordinate[0][1] = COL / 2;//1Ϊ������
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
void Move(Snake& s) {//��β����ʼ����ĵ���ǰ�������

	gotxy(s.Coordinate[s.length - 1][0], s.Coordinate[s.length - 1][1]);
	cout << " ";
	for (int i = s.length - 1; i > 0; i--)
	{
		s.Coordinate[i][0] = s.Coordinate[i - 1][0];//������
		s.Coordinate[i][1] = s.Coordinate[i - 1][1];//������
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
				gotxy(ROW, 0);        //������ƶ�������
				system("pause");
				gotxy(ROW, 0);
				cout << "                   ";
				break;

		}
	}
}
bool death(Snake& s){
	bool isGameOver = false;
	int sX = s.Coordinate[0][0], sY = s.Coordinate[0][1];      //��ͷ��x�����y����
	if (sX == 0 || sX == ROW - 1 || sY == 0 || sY == COL - 1)
		isGameOver = true;
	for (int i = 1; i < s.length; i++)    //�ж���û�гԵ��Լ�
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
		int i = rand() % ROW;               //����0~ROW-1֮���һ����
		int j = rand() % COL;
		if (w.M[i][j] != 1) flag1 = 1;//û��������ǽ��
		int k;
		for (k = 0; k < s.length; k++)
		{
			if (i == s.Coordinate[k][0] && j == s.Coordinate[k][1])
				flag2 = -1;//û��������������
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
	cout << "  ̰������Ϸ";
	gotxy(2, COL + 2);
	cout << "  Yiliya����";
	gotxy(4, COL + 2);
	cout << "   P��ͣ    ";
	gotxy(6, COL + 2);
	cout << "To move,please press wsad ";
	gotxy(8, COL + 2);
	cout << "  �÷�: " << score;
}


int main()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    //���ع��
	welcome(); rule(); name();
	prepare();
	time();
	Wall w;
	Snake s;
//	Food f;
	system("cls");
	{//��ʼ�����桢�ߺ�ʳ��
		Initmap(w);
		Initsnake(s);
		Drawmap(w);
		Drawsnake(s);
		//f.Init();
		srand((unsigned)time(NULL));
		Drawfood(w, s);
	}
	while (1)//ѭ������ʳ��
	{
		directioncontrol(s);
		Move(s);
		Sleep(100);
		Drawsnake(s);
		PrintScore();
		if (death(s))
		{
			system("cls");          //�����Ļ����
			cout << "Game Over" << endl;
			system("pause");
			break;
		}
		if (w.M[s.Coordinate[0][0]][s.Coordinate[0][1]] == -1)
		{
			eated = true;
			if (eated == true)               //����Ե���ʳ��
			{
				fuclength(s);
				eated = false;        //����Ϊfalse����Ȼ���ޱ䳤
			}
			score += 10;
			Drawfood(w, s);
			w.M[s.Coordinate[0][0]][s.Coordinate[0][1]] = 0;
		}
	}
	return 0;
}