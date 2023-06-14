#include "Pied_Piper.h"


HANDLE musicThread;
HANDLE controlThread;

int score = 0; //점수
double beginTime;
double endTime;
double thisTime; //begin-end;
int showMN = 0;
double chktime = 0; // 플레이어 움직임 체크
int answer[160]; //문제 저장
int answer_len = 160;
int heart = 5; //목숨값
int input = 1;





//좌표
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//커서 숨기기
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//커서 제어
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

//제목
void title() {
	 
	int x = 9;
	int y = 4;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
	gotoxy(x, y++);  printf(" _______  ___   _______  ______     _______  ___   _______  _______  ______   ");
	gotoxy(x, y++);  printf("|       ||   | |       ||      |   |       ||   | |       ||       ||    _ |  ");
	gotoxy(x, y++);  printf("|    _  ||   | |    ___||  _    |  |    _  ||   | |    _  ||    ___||   | ||  ");
	gotoxy(x, y++);  printf("|   |_| ||   | |   |___ | | |   |  |   |_| ||   | |   |_| ||   |___ |   |_||_ ");
	gotoxy(x, y++);  printf("|    ___||   | |    ___|| |_|   |  |    ___||   | |    ___||    ___||    __  |");
	gotoxy(x, y++);  printf("|   |    |   | |   |___ |       |  |   |    |   | |   |    |   |___ |   |  | |");
	gotoxy(x, y++);  printf("|___|    |___| |_______||______|   |___|    |___| |___|    |_______||___|  |_|");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	x = 15, y = 15;
	gotoxy(x, y);
	printf(" ---||-------||-------||----||------||-------||-----");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf("|         이번 게임은 피리부는 사나이 입니다        |");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf("|   화면에 나오는 화살표가 같은 화살표를 클릭하고   |");
	gotoxy(x, ++y);
	printf("|     총 3번의 기회 안에 도착지에 도착하세요!!      |");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf("|       스페이스키(space key)를 눌러 시작하세요     |");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf(" ---||-------||-------||----||------||-------||-----");


	x = 3, y = 15;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x, ++y);
	printf("　　ｏ");
	gotoxy(x, ++y);
	printf("　°");
	gotoxy(x, ++y);
	printf("　┳┳   ∩∩");
	gotoxy(x, ++y);
	printf("　┃┃ (0 ㅁ 0)");
	gotoxy(x, ++y);
	printf("┏┻┻┷━Ｏ┏┷┓┏┷┓");
	gotoxy(x, ++y);
	printf("┃ 　　  　 ┠┨○┠┨○┃");
	gotoxy(x, ++y);
	printf("┗◎━━◎┛┗◎┛┗◎┛");
	
}






void showMenu() {
	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(x - 1, y);  printf("▶ 게 임 시 작");
	gotoxy(x, y += 2);  printf(" 게 임 종 료");

	gotoxy(30, y -= 2);
}
//메뉴선택
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
				gotoxy(x - 1, y -= 2); printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy(x - 1, y); printf("  ");
				gotoxy(x - 1, y += 2); printf("▶");
			}

			break;
		}
		case SPACE: {
			return y - 22;
		}	break;
		}
	}

}

//완료 체크
void checkFinish(int x, int y) {
	if (x >= 50 && y >= 1 && y <= 23) {
		system("cls");
		gotoxy(30, 13); printf("완주");
	}
}

int m_x = 3; //화살표 처음 위치

//캐릭터 움직이기


unsigned _stdcall character_control() {
	int x = 4;
	int y = 6;

	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	gotoxy(x, y); printf("■");
	while (input) {

		int n = _getch();

		//게임종료
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
		case 1: gotoxy(x++, y); printf("  "); break;
		case 2: gotoxy(x, y++); printf("  "); break;
		case 3: gotoxy(x++, y); printf("  "); break;
		case 4: gotoxy(x, y--); printf("  "); break;
		case 5: gotoxy(x++, y); printf("  "); break;
		case 6: gotoxy(x, y++); printf("  "); break;
		case 7: gotoxy(x++, y); printf("  "); break;
		case 8: gotoxy(x, y++); printf("  "); break;
		case 9: gotoxy(x++, y); printf("  "); break;
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





//맵
void map() {

	int show = 0; // 1 = show, 0 - hide
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 60; i++) {
		gotoxy(i, 0); printf("■0");
	}

	for (int i = 0; i < 60; i++) {
		gotoxy(i, 29); printf("■");
	}
	



}



//미션출력
void mission() {
	srand(time(NULL));
	char m[4][10] = { "→","←","↓","↑" };
	
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

		//화살표 출력
	}
}








//게임 시작
void game() {
	system("cls");
	CursorView(); //커서 숨기기

	mission(); //미션
	map(); //맵 그리기


	system("pause>null\n");
}


void main() {


	CursorView();
	system("mode con: cols=120 lines=30");
	system("title 피리부는 사나이");

	title();
	showMenu();

	while (1) {
		switch (menu()) {
		case 0: 	input = 1;  game(); break; //게임시작
		case 2: exit(0);  break; // 게임종료
		//case esc: main() break;
		}

	}
	system("pause>null\n");
}
