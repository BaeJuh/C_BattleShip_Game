#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define UP 1 // �� 
#define DOWN 2 // �Ʒ� 
#define LEFT 3 // ���� 
#define RIGHT 4 // ������ 
#define SPACE 5 // �Է� 

using namespace std;

// ���� 
int KeyControl();
void gotoxy(int x, int y);
void init();

// ���� 
void title();
int Menu();
void inGame();
void drawMap(int);
void Manual();

// ��������
int remark = 28; // ���� �Ʒ� ���� �� 
 
int main() {
	while (true) {
		init();
		title();
		int MenuCode = Menu();
		
		if (MenuCode == 0) {
			inGame();
		}
		else if (MenuCode == 1) {
			Manual();
		}
		else if (MenuCode == 2) {
			system("cls");
			gotoxy(38, 5);
			printf("[ ���� ���� ]");
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		system("cls");
	}
	
	return 0;
}

void title() { // ����ȭ���� ����ϴ� �Լ�
	printf("\n\n\n\n\n");
	printf("				****BATTLESHIP GAME****"); // ���� 32 ���� 23
	printf("\n\n");
}

int Menu() {
	int x=38;
	int y=9;
	gotoxy(x-2, y);
	printf(">");
	gotoxy(x, y);
	printf("GAME START"); // line 8, code 0
	gotoxy(x, y+1);
	printf("MANUAL"); // line 9, code 1
	gotoxy(x, y+2);
	printf("EXIT"); // line 10, code 2
	printf("\n\n\n");
	
	gotoxy(0, remark);
	printf("�̵� : W, A, S, D Ȯ�� : SPACE BAR");
	
	while(true) {
		int key = KeyControl();
		switch(key) { // y�� 8~10 
			case UP: {
				if (y > 9) {
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, --y);
					printf(">");
				}
				break;
			}
			case DOWN: {
				if (y < 11) {
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			case SPACE: {
				return y-9;
				break;
			}
		}
	}
}

void inGame() {
	system("cls");
	srand(time(NULL));
	int map_size = 0;
	int map_x, map_y; 
	
	printf("���� ũ�⸦ �Է����ּ���. \nũ�� : ");
	scanf("%d", &map_size);
	
	map_x = map_size; // �ӽ�************************************************** 
	map_y = map_size;
	
	int Map[map_size][map_size]; // �� ���� = 0, �� ���� = 1
	
	for (int i=0; i<map_size; i++) { // 2���� �迭 0���� �ʱ�ȭ 
		for (int j=0; j<map_size; j++) {
			Map[i][j] = 0;
		}
	}
	
	// random
	int ship_size; // rand()%(map_size-2);
	int ship_locate_x; // rand()%map_size;
	int ship_locate_y; // rand()%map_size;
	int ship_direct; // rand()%2; // 0�̸� ���η� 1�̸� ���η� 
	int ship_count = 3; // ���� ���� 
	
	for (int i=0; i<ship_count; i++) {
		ship_size = rand()%(map_size-2);
		while(ship_size == 0) {
			ship_size = rand()%(map_size-2);
		}
		
		ship_direct = rand()%2;
		if (ship_direct == 0) { // ���� ���� ���� 
			ship_locate_x = rand()%(map_size - ship_size);
			ship_locate_y = rand()%map_size;
			
		} else { // ���� ���� ���� 
			ship_locate_x = rand()%map_size;
			ship_locate_y = rand()%(map_size - ship_size);
		}
		cout << ship_locate_x << " " << ship_locate_y << " " << ship_direct << " " << ship_size << endl;
		for (int j=0; j<ship_size; j++) {
			// �� �ֱ� 
			if (ship_direct == 0) { // ���� ���� ���� 
				Map[ship_locate_y][ship_locate_x + j] = 1;
			} else { // ���� ���� ���� 
				Map[ship_locate_y + j][ship_locate_x] = 1;
			}
		}
	}
	
	printf("\n\n------------------------------\n");
	for (int i=0; i<map_size; i++) { // 2���� �迭 0���� �ʱ�ȭ 
		for (int j=0; j<map_size; j++) {
			if (Map[i][j] == 0) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
		printf("\n");
	}
	printf("\n------------------------------\n");

	while(true) {
		int key = KeyControl();
		if (key == SPACE) {
			break;
		}
	}
}

void drawMap(int size) { // �� �� 
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			printf("��");
		}
		printf("\n");
	}
}

void Manual() {
	system("cls");
	gotoxy(38, 5);
	printf("[ ���۹� ]");
	gotoxy(26, 8);
	printf("��ǥ�� �Է��ϸ� ������ �߻��մϴ�.");
	gotoxy(32, 11);
	printf("��ǥ �Է� ���� : 7 7");
	gotoxy(0, remark);
	printf("SPACEBAR�� ������ �������� ���ư��ϴ�.");
	
	while(true) {
		int key = KeyControl();
		if (key == SPACE) {
			break;
		}
	}
}

void gotoxy(int x,int y) {
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

int KeyControl() { // w, a, s, d�� ���� �̵�, spacebar�� ���� �Է� 
	char key = getch();
	
	if (key == 'w' || key == 'W') {
		return UP;
	}
	else if (key == 'a' || key == 'A') {
		return LEFT;
	}
	else if (key == 's' || key == 'S') {
		return DOWN;
	}
	else if (key == 'd' || key == 'D') {
		return RIGHT;
	}
	else if (key == ' ') {
		return SPACE;
	}
}

void init() { 
	system("mode con cols=87 lines=30 | title BattleShip Game");
}
