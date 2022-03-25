#include<iostream>
#include<windows.h>
#include<conio.h>
#include<deque>
#include<ctime>
#include<stdexcept>
using namespace std;

struct Snake { //����ṹ��
    char image;
    short x, y; //����
};

class snakeGame {
	public:
	snakeGame();
	void printMap();
	// ���ƹ���ƶ�
	void gotoxy(short x, short y) {
		hOut = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���
		pos = {x, y};
		SetConsoleCursorPosition(hOut, pos); //�ƶ����
	}
	//���ع��
	void HideCursor()
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
		CursorInfo.bVisible = false; //���ؿ���̨���
		SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	}
	// ��ʼ���������ɸ�����Ҫ���ĳ�ʼ����
	void initSnake() {
		snake.push_front({'@', width / 2, height / 2});
		for (int i=0; i<2;++i)
			snake.push_back({'+', width/2,static_cast<short>(height/2+i+1)});
	}
	// �ж��Ƿ�ʳ�����λ����������ͻ
	int WrongLocation() {
		for (Snake body : snake)
			if(body.x == food_x && body.y == food_y) return 0;
		return 1;
	}
	// ����ʳ�����ӡ
	void createFood() {
		do {
			food_x = rand() % (width - 4) + 2;
			food_y = rand() % (height - 2) + 1;
		} while (!WrongLocation());//������ͻ
		gotoxy(food_x,food_y); cout << '*' << endl; //��ӡʳ��
	}
	void printSnake();
	// �����β
	inline void clearSnake(Snake &tail) {
    	gotoxy(tail.x, tail.y); cout << ' '; //������β����ʹ��������������������˸
	}
	void judgeCrash();
	void foodEaten();
	// ����û���������
	void userInput() {
		char ch;
		switch(ch=getch()) {
			case 'w':if (dir != 's') dir = ch;break;
			case 'a':if (dir != 'd') dir = ch;break;
			case 's':if (dir != 'w') dir = ch;break;
			case 'd':if (dir != 'a') dir = ch;break;
			case 'v':speed*=0.8;break; case 'b':speed*=1.5;break;
			case ' ':gotoxy(width / 2, height); cout << "��Ϸ����ͣ�����������"; getch();
            gotoxy(width / 2, height); cout << "                     "; break;
			default:break;
		}
	}
	private:
	// �����ǳ������е�����Ҫ�õ���һЩ�м�������������ݱ�����
	enum MapSize {height = 40,width = 120}; //��ͼ�ߴ�
	HANDLE hOut; COORD pos;
	char dir; //direction
	bool beg,eatFood=false;
	double speed=200;
	deque<Snake> snake;
	int food_x,food_y;
	int score=0;
};
// �����Ե�ʳ������
void snakeGame::foodEaten() {
	createFood();
	eatFood=true;
	speed*=.8;
	++score;
}
// �ж����Ƿ�ײǽ���߳Ե��Լ���β��
void snakeGame::judgeCrash() {
	int flag=0;
	if (snake.size()>=5) {
		deque<Snake>::iterator iter = snake.begin() + 1;
		int x = (iter-1)->x, y = (iter-1)->y;
		for (; iter != snake.end(); ++iter) {
			if (iter->x == x && iter->y == y) flag=1;
		}}
	if (flag || snake.front().x == 1 || snake.front().x == width - 2 || snake.front().y == 0 || snake.front().y == height - 1)//����Ƿ�ײǽ�����Ƿ�Ե�����
    {
        gotoxy(width / 2 - 10, height /2);
        cout << "��Ϸ���������ķ�����: " << score << "�֣��س�������"<<endl;
        while(1) {
            dir = getch();
            if (dir == '\r') break;}
		runtime_error quit("��Ϸ�����������˳�"); throw quit;
    }
}
// ��������ӡ����
void snakeGame::printSnake() {
    deque<Snake>::const_iterator iter = snake.begin();
    for (; iter <= snake.begin() + 1 && iter < snake.end(); ++iter) {
        gotoxy(iter->x, iter->y); cout << iter->image;
    }
}
// ��ӡ���߿�
void snakeGame::printMap() {
	int i;
    for (i = 0; i != width; i += 2) cout << "��"; //���ͼ������ռ2���߶�ռ1
    gotoxy(0, 1);
    for (i = 1; i != height; ++i) cout << "��" << endl;
    for (i = 1; i != height; ++i) {
        gotoxy(width - 2, i); cout << "��";}
    gotoxy(0, height - 1);
    for (i = 0; i != width; i += 2) cout << "��";
    cout << "̰���ߣ�1.�������ʼ��Ϸ 2.*����ʳ�� 3.�ո����ͣ��Ϸ\n        4.����'v'����    5.����'b'����";
}
// ��Ĺ��캯����
// �����˳���ĳ�ʼ������ͼ���ƣ�������ʼ�������������У��������������
// �ǳ�����ؼ��Ĳ���
snakeGame::snakeGame() {
	HideCursor(); // ���ع��
	srand(static_cast<unsigned int>(time(NULL)));
	beg=true;
	Snake tmp1,tmp2;
	while (1) {
		if(beg) { // �ж��ǲ��ǵ�һ�����г�����Ϊ��һ��������Ҫ��ӡ�߿�
			printMap();
			dir = getch();
			initSnake();
			createFood();
			beg = eatFood=false;
		}
		tmp2=snake.back();
		tmp1=snake.front();
		snake.pop_back();
		if (eatFood) { // ����Ե�ʳ��...
			tmp2.image='+';
			snake.push_back(tmp2);
			eatFood=false;
		}
		else clearSnake(tmp2);
		if      (dir == 's') ++tmp1.y;
        else if (dir == 'a') --tmp1.x;
        else if (dir == 'd') ++tmp1.x;
        else  --tmp1.y;
		try{
			judgeCrash();
		}
		catch(runtime_error &quitSignal) {
			throw quitSignal;
		}
		snake.front().image='+';
		snake.push_front(tmp1);
		printSnake();
		Sleep(speed+30);
		if (tmp1.x == food_x && tmp1.y == food_y) 
			foodEaten();
		if(kbhit()) userInput();
	}
}
int main() {
	system("mode con cols=120 lines=42");
	try{
		snakeGame game;
	}
	catch(runtime_error &gameEnd) {
		system("cls");
		cout<<gameEnd.what();
		getch();
	}
}