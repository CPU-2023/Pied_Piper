#include "Pied_Piper.h"
// _getch() value of ESC key
#define ESC 27
#define UP 72
#define DOWN 80
#define SUBMIT 4
#define ENTER 13

/* 함수 선언 */
int keyControl();
int menuDraw();
void print_piano();
int MakeRandNote(int random);
int playGame(char** dp, int n);
void rule();
void guess_note(void);

char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시", "도", "레", "미" };

int score = 0; // 스코어 변수
int highestScore = 0; // 최고 점수 변수


int keyControl() {
	char temp;
	while (1) {
		if (_kbhit()) {
			temp = _getch();
			if (temp == -32) {
				temp = _getch();
				switch (temp) {
				case UP:
					return UP;
					break;
				case DOWN:
					return DOWN;
					break;
				}
			}
			else if (temp == 13) {
				return ENTER;
			}
			else if (temp == 27) {
				return ESC;
			}
		}
		return 0;
	}
}
int menuDraw() {
	system("cls");




	int x = 23;
	int y = 4;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	print_auto_y(&x, &y, " _______  ___   _______  ______     _______  ___   _______  _______  ______   ");
	print_auto_y(&x, &y, "|       ||   | |       ||      |   |       ||   | |       ||       ||    _ |  ");
	print_auto_y(&x, &y, "|    _  ||   | |    ___||  _    |  |    _  ||   | |    _  ||    ___||   | ||  ");
	print_auto_y(&x, &y, "|   |_| ||   | |   |___ | | |   |  |   |_| ||   | |   |_| ||   |___ |   |_||_ ");
	print_auto_y(&x, &y, "|    ___||   | |    ___|| |_|   |  |    ___||   | |    ___||    ___||    __  |");
	print_auto_y(&x, &y, "|   |    |   | |   |___ |       |  |   |    |   | |   |    |   |___ |   |  | |");
	print_auto_y(&x, &y, "|___|    |___| |_______||______|   |___|    |___| |___|    |_______||___|  |_|");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);



	gotoxy(41, 15);
	printf("들리는 음을 듣고 알맞은 음을 쓰세요~!");
	gotoxy(35, 17);
	printf("!게임 시작 전 한글로 설정되어 있는지 확인해주세요!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


	x = 86;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	gotoxy(x, ++y);
	printf("              ,-.");
	gotoxy(x, ++y);
	printf("             /  (  '");
	gotoxy(x, ++y);
	printf("     *  _.--'!   '--._");
	gotoxy(x, ++y);
	printf("      ,'              ''.");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(x, ++y);
	printf("'       최고 점수 : % d ", highestScore);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	gotoxy(x, ++y);
	printf("   _.'   O      ___      ! \\");
	gotoxy(x, ++y);
	printf("  (_.-^, __..-'  ''''--.   )");
	gotoxy(x, ++y);
	printf("      /,'        '    _.' /");
	gotoxy(x, ++y);
	printf("   '         *    .-''    |");
	gotoxy(x, ++y);
	printf("                 (..--^.  ' ");
	gotoxy(x, ++y);
	printf("                       | /");
	gotoxy(x, ++y);
	printf("                       '");



	x = 9;
	y = 20;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	gotoxy(x, ++y);
	printf("       .");
	gotoxy(x, ++y);
	printf("      '':''");
	gotoxy(x, ++y);
	printf("    ___:____     |'\\ /'| ");
	gotoxy(x, ++y);
	printf("  ,'        `.    \\   /");
	gotoxy(x, ++y);
	printf("  |  O        \\___/   |");
	gotoxy(x, ++y);
	printf("~^~^~^~^~^~^~^~^~^~^~^~^~");



	x = 50;
	y = 21;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(x - 2, y); // -2한 이유는 >를 출력하기 위해서
	printf(">     게 임 시 작 \n");
	gotoxy(x, y + 2);
	printf("    게 임 종 료 \n");
	print_by_name("윤소희");
	


	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 21) { //y는 12~14까지만 이동
				gotoxy(x - 2, y); // x-2하는 이유는 >를 두 칸 이전에 출력하기 위해서
				printf(" ");

				gotoxy(x - 2, y -= 2); //새로 이동한 위치로 이동하여
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(">"); //다시 그리기
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			break;
		}
		case DOWN: {
			if (y < 23) { //최대 20
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, y += 2);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf(">");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			break;
		}
		case ENTER: {
			return y - 21;
			break;
		}
		}
	}
	return 0;
}


void print_piano() {
	gotoxy(34, 11);
	puts("□□■■ ■■□□□■■ ■■ ■■□□□■■ ■■□□");
	gotoxy(34, 12);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 13);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 14);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 15);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 16);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 17);
	puts("□   □   □   □   □   □   □   □   □   □   □");
	gotoxy(34, 18);
	puts("□   □   □   □   □   □   □   □   □   □   □");
	gotoxy(34, 19);
	puts("□□□□□□□□□□□□□□□□□□□□□□□□□□");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	gotoxy(30, 21);
	printf("한글이 입력되지 않는다면 작성 후 스페이스바를 한 번 눌러주세요!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	// 스코어 출력 위치
	gotoxy(5, 2);
	printf("스코어: %d", score);


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	gotoxy(2, 20);
	printf("             ,-._");
	gotoxy(2, 21);
	printf("           _.-'  '--.");
	gotoxy(2, 22);
	printf("         .'      _  -`\_");
	gotoxy(2, 23);
	printf("        / .----.`_.'----'");
	gotoxy(2, 24);
	printf("        ;/     `");
	gotoxy(2, 25);
	printf("       /_;");
	gotoxy(2, 26);
	printf("    ._      ._      ._      ._");
	gotoxy(2, 27);
	printf("_.-._)`\\_.-._)`\\_.-._)`\\_.-._)`\\_.-._");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);



	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	gotoxy(80, 20);
	printf("                     /|");
	gotoxy(80, 21);
	printf("       =  =  =      / |");
	gotoxy(80, 22);
	printf("  ____| || || |____/  | -_-_-_-_-_-_");
	gotoxy(80, 23);
	printf("|)----| || || |____   |     ");
	gotoxy(80, 24);
	printf("  ((  | || || |  ))\\  | _-_-_-_-_-_-");
	gotoxy(80, 25);
	printf("   \\_|_||_||_|_//   \\ |");
	gotoxy(80, 26);
	printf("    \\___________/    \\|");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);*/
}



int pr_str_array(char** dp, int n) {
	while (1) {
		double frequency[] = { 523, 587, 659, 699, 784, 880, 988, 1047, 1175, 1319 };
		const int note_len = 600;

		srand((unsigned int)time(NULL));
		int random = (rand() % 7);

		for (int i = 0; i < 7; i++) {
			if (random == i + 1) {
				Sleep(1000);
			}
		}
		Beep(frequency[random], note_len);




		system("cls");

		char answer[10];

		print_piano();

		gotoxy(34, 9);
		printf("무슨 음일까요?: ");
		scanf("%s", answer);

		if (!strcmp(answer, *(dp + random))) {
			score += 50;

			if (score > highestScore) { // 현재 점수가 최고 점수보다 높으면 최고 점수 갱신
				highestScore = score;
			}

			gotoxy(76, 9);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (0 << 4));
			printf("정답입니다!\n");
		}

		else {
			gotoxy(67, 9);
			printf("땡! 정답은 %s입니다.\n", *(dp + random));
			gotoxy(82, 28);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | (0 << 4));
			for (int n = 3; n > 0; --n) {
				gotoxy(82, 29);
				printf("%d초 후에 메인화면으로 돌아갑니다...\n", n);
				Sleep(1000);
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (0 << 4));
			break;
		}
	}
	return 0;
}

int playGame() {
	score = 0;
	char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시" };
	while (1) {
		int n = keyControl();
		switch (n) {
		case SUBMIT: {
			if (score > highestScore) {
				highestScore = score;
			}
			return pr_str_array(p, SIZE);
		}
		}
	}
	return 0;
}

void main(void) {
	system("cls");
	char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시" };
	int x = 100, y = 20;
	char key;

	while (1) {
		int menuCode = menuDraw();
		system("cls");
		if (menuCode == 0) {
			score = 0; // score만 0으로 초기화
			pr_str_array(p, SIZE);
		}
		else if (menuCode == 2) {
			break;
		}
	}

	return 0;
}