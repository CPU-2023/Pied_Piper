#include "Pied_Piper.h"


HANDLE musicThread;
HANDLE controlThread;

double beginTime;
double endTime;
double thisTime; //begin-end;
int showMN = 0;
double chktime = 0; // �÷��̾� ������ üũ
int answer[160]; //���� ����
int answer_len = 160;
int heart = 5; //�����
int input = 1;





//��ǥ
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//Ŀ�� �����
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//Ŀ�� ����
int keyControl() {
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				switch (c) {
				case 27:
					return ESC; break;
				case 72:
					return UP; break;
				case 80:
					return DOWN;  break;
				case 75:
					return LEFT; break;
				case 77:
					return RIGHT; break;
				}
			}
			else if (c == ' ')
				return SPACE;
		}
	}
}

//����
void title() {

	int x = 9;
	int y = 9;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
	gotoxy(x, y++);  printf(" _______  ___   _______  ______     _______  ___   _______  _______  ______   ");
	gotoxy(x, y++);  printf("|       ||   | |       ||      |   |       ||   | |       ||       ||    _ |  ");
	gotoxy(x, y++);  printf("|    _  ||   | |    ___||  _    |  |    _  ||   | |    _  ||    ___||   | ||  ");
	gotoxy(x, y++);  printf("|   |_| ||   | |   |___ | | |   |  |   |_| ||   | |   |_| ||   |___ |   |_||_ ");
	gotoxy(x, y++);  printf("|    ___||   | |    ___|| |_|   |  |    ___||   | |    ___||    ___||    __  |");
	gotoxy(x, y++);  printf("|   |    |   | |   |___ |       |  |   |    |   | |   |    |   |___ |   |  | |");
	gotoxy(x, y++);  printf("|___|    |___| |_______||______|   |___|    |___| |___|    |_______||___|  |_|");



}



//����
void manual() {




}

void showMenu() {
	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x - 1, y);  printf("�� �� �� �� ��");
	gotoxy(x, y += 2);  printf(" �� �� �� ��");

	gotoxy(30, y -= 2);
}
//�޴�����
int  menu() {

	int x = 45;
	int y = 22;
	int show = 0;

	//if (++showMN == 1) showMenu();

	while (1) {
		int n = keyControl();
		switch (n)
		{

		case UP: {
			if (y > 22) {

				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y -= 2); printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y += 2); printf("��");
			}

			break;
		}
		case SPACE: {
			return y - 22;
		}	break;
		}
	}

}

//�Ϸ� üũ
void checkFinish(int x, int y) {
	if (x >= 50 && y >= 1 && y <= 23) {
		system("cls");
		gotoxy(30, 13); printf("����");
	}
}

int m_x = 3; //ȭ��ǥ ó�� ��ġ
//ĳ���� �����̱�


unsigned _stdcall character_control() {
	int x = 4;
	int y = 6;

	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y); printf("��");
	while (input) {

		int n = _getch();

		//��������
		if (n == 27) {
			score = 0;
			heart = 5;
			PlaySound(NULL, 0, 0);
			system("cls");
			main();
		}
		n = keyControl();
		switch (n)
		{


		case RIGHT: {

			if (answer[i] == 0) { score += 10; }
			else heart--;
			break;


		}
		case LEFT: {

			if (answer[i] == 1) { score += 10; }
			else heart--;
			break;


		}
		case UP: {

			if (answer[i] == 3) { score += 10; }
			else heart--;


			break;
		}

		case DOWN: {

			if (answer[i] == 2) { score += 10; }
			else heart--;
			break;
		}


		}
		switch (i / 5)
		{
		case 0: gotoxy(x, y++); printf("  "); break;
		case 1:  gotoxy(x++, y); printf("  "); break;
		case 2:  gotoxy(x, y++); printf("  "); break;
		case 3: gotoxy(x++, y); printf("  "); break;
		case 4: gotoxy(x, y--);  printf("  "); break;
		case 5: gotoxy(x++, y); printf("  "); break;
		case 6:  gotoxy(x, y++); printf("  "); break;
		case 7:  gotoxy(x++, y); printf("  "); break;
		case 8:  gotoxy(x, y++); printf("  "); break;
		case 9:  gotoxy(x++, y);  printf("  "); break;
		case 10:  gotoxy(x, y--); printf("  "); break;
		case 11:  gotoxy(x, y--); printf("  "); break;
		case 12:  gotoxy(x, y--); printf("  "); break;
		case 13:  gotoxy(x--, y); printf("  "); break;
		case 14:  gotoxy(x--, y); printf("  "); break;
		case 15:  gotoxy(x, y--); printf("  "); break;
		case 16:  gotoxy(x++, y); printf("  "); break;
		case 17:  gotoxy(x++, y); printf("  "); break;
		case 18:  gotoxy(x++, y); printf("  "); break;
		case 19:  gotoxy(x, y++); printf("  "); break;
		case 20:  gotoxy(x, y++); printf("  "); break;
		case 21:  gotoxy(x, y++); printf("  "); break;
		case 22:  gotoxy(x++, y); printf("  "); break;
		case 23:  gotoxy(x, y++); printf("  "); break;
		case 24:  gotoxy(x++, y); printf("  "); break;
		case 25:  gotoxy(x, y--); printf("  "); break;
		case 26:  gotoxy(x, y--); printf("  "); break;
		case 27:  gotoxy(x++, y); printf("  "); break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		i++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(20, 29); printf(" % d", score);
		gotoxy(46, 29); printf(" %d", heart);

	}

}





//��
void map() {

	int show = 0; // 1 = show, 0 - hide
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 60; i++) {
		gotoxy(i, 0); printf("��");
	}

	for (int i = 0; i < 60; i++) {
		gotoxy(i, 24); printf("��");
	}
	



}



//�̼����
void mission() {
	srand(time(NULL));
	char m[4][10] = { "��","��","��","��" };
	int color[6] = { 9,10,11,12,13,14 }; //�÷� ����
	int x = 4, y = 6;

	for (int i = 0; i < 160; i++) {
		int rn = (rand() % 4);
		answer[i] = rn;

		switch (i / 5)
		{
		case 0: gotoxy(x, y++); printf("%s", m[rn]); break;
		case 1:  gotoxy(x++, y); printf("%s", m[rn]);   break;
		case 2:  gotoxy(x, y++); printf("%s", m[rn]);   break;
		case 3: gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 4: gotoxy(x, y--);  printf("%s", m[rn]);  break;
		case 5: gotoxy(x++, y); printf("%s", m[rn]); break;
		case 6:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 7:  gotoxy(x++, y);  printf("%s", m[rn]);  break;
		case 8:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 9:  gotoxy(x++, y);  printf("%s", m[rn]);  break;
		case 10:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 11:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 12:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 13:  gotoxy(x--, y); printf("%s", m[rn]);  break;
		case 14:  gotoxy(x--, y); printf("%s", m[rn]);  break;
		case 15:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 16:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 17:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 18:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 19:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 20:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 21:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 22:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 23:  gotoxy(x, y++); printf("%s", m[rn]);  break;
		case 24:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		case 25:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 26:  gotoxy(x, y--); printf("%s", m[rn]);  break;
		case 27:  gotoxy(x++, y); printf("%s", m[rn]);  break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[rn]);
		//ȭ��ǥ ���
	}
}








//���� ����
void game() {
	system("cls");
	CursorView(); //Ŀ�� �����

	mission(); //�̼�
	map(); //�� �׸���


	system("pause>null\n");
}


void main() {


	CursorView();
	system("mode con: cols=120 lines=30");
	system("title �Ǹ��δ� �糪��");

	title();
	showMenu();

	while (1) {
		switch (menu()) {
		case 0: 	input = 1;  game(); break; //���ӽ���
		case 2: exit(0);  break; // ��������
		//case esc: main() break;
		}

	}
	system("pause>null\n");
}
