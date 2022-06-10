
		
		if (MenuCode == 0) {
			inGame();
		}
		else if (MenuCode == 1) {
			Manual();
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define UP 1 // 위 
#define DOWN 2 // 아래 
#define LEFT 3 // 왼쪽 
#define RIGHT 4 // 오른쪽 
#define SPACE 5 // 입력 

using namespace std;

// 세팅 
int KeyControl();
void gotoxy(int x, int y);
void init();

// 게임 
void title();
int Menu();
void inGame();
void drawMap(int);
void Manual();

// 전역변수
int remark = 28; // 왼쪽 아래 설명 줄 
 
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
			printf("[ 게임 종료 ]");
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		system("cls");
	}
	
	return 0;
}

void title() { // 메인화면을 출력하는 함수
	printf("\n\n\n\n\n");
	printf("				****BATTLESHIP GAME****"); // 여백 32 제목 23
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
	printf("이동 : W, A, S, D 확인 : SPACE BAR");
	
	while(true) {
		int key = KeyControl();
		switch(key) { // y는 8~10 
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
	
	printf("맵의 크기를 입력해주세요. \n크기 : ");
	scanf("%d", &map_size);
	
	map_x = map_size; // 임시************************************************** 
	map_y = map_size;
	
	int Map[map_size][map_size]; // 배 없음 = 0, 배 있음 = 1
	
	for (int i=0; i<map_size; i++) { // 2차월 배열 0으로 초기화 
		for (int j=0; j<map_size; j++) {
			Map[i][j] = 0;
		}
	}
	
	// 맵에 배 넣기 
	int ship_size; // rand()%(map_size-2);
	int ship_locate_x; // rand()%map_size;
	int ship_locate_y; // rand()%map_size;
	int ship_direct; // rand()%2; // 0이면 가로로 1이면 세로로 
	int ship_count = 3; // 배의 개수
	bool isShiphere = false; // 배가 겹치는 것을 제거하기 위한 플래그 
	
	for (int i=0; i<ship_count; i++) { // 맵에 배 넣기 
		isShiphere = false;
		ship_size = rand()%(map_size-2)+1;
		
		ship_direct = rand()%2;
		if (ship_direct == 0) { // 배의 방향 가로 
			ship_locate_x = rand()%(map_size - ship_size + 1);
			ship_locate_y = rand()%map_size;
			
		} else { // 배의 방향 세로 
			ship_locate_x = rand()%map_size;
			ship_locate_y = rand()%(map_size - ship_size + 1);
		}
		
		for (int j=0; j<ship_size; j++) {
			if (ship_direct == 0 && Map[ship_locate_y][ship_locate_x + j] == 1) { 
				isShiphere = true;
				break;
			} else if (ship_direct == 1 && Map[ship_locate_y + j][ship_locate_x] == 1) {
				isShiphere = true;
				break;
			}
		}	
		if (isShiphere == false) {
			for (int j=0; j<ship_size; j++) {
				 
				if (ship_direct == 0) { // 배의 방향 가로 
					Map[ship_locate_y][ship_locate_x + j] = 1;
				} else { // 배의 방향 세로 
					Map[ship_locate_y + j][ship_locate_x] = 1;
				}
			}
			cout << ship_locate_x << " " << ship_locate_y << " " << ship_direct << " " << ship_size << endl;
		} else {
			i--;
		}
	}
	
	printf("\n\n------------------------------\n");
	for (int i=0; i<map_size; i++) { // 2차월 배열 0으로 초기화 
		for (int j=0; j<map_size; j++) {
			if (Map[i][j] == 0) {
				printf("■");
			}
			else {
				printf("□");
			}
		}
		printf("\n");
	}
	printf("\n------------------------------\n");
	
	// 게임플레이 
	
	bool isShipAlive = true;
	int flag = 0;
	int x, y;
	int BattleField[map_size][map_size];
	for (int i=0; i<map_size; i++) { 
		for (int j=0; j<map_size; j++) {
			BattleField[i][j] = 0;
		}
	}
	
	while(isShipAlive) {
		system("cls");
		flag = 0;
		printf("turn start\n");
		for (int i=0; i<map_size; i++) { 
			for (int j=0; j<map_size; j++) {
				printf("%d ", BattleField[i][j]);
			}
			printf("\n");
		}
		printf("좌표를 입력하세요 : ");
		scanf("%d %d", &x, &y);
		
		y = y-1;
		x = x-1;
		
		if (Map[y][x]) {
			BattleField[y][x] = 1;
			Map[y][x] = 0;
		} else {
			BattleField[y][x] = 2;
		}
		
		for (int i=0; i<map_size; i++) { 
			for (int j=0; j<map_size; j++) {
				if (Map[i][j] == 1) {
					flag ++;
					Sleep(100);
				}
			}
		}
		if (flag == 0) {
			isShipAlive = false;
		}
	}
	
	printf("게임 종료");
	
	while(true) {
		int key = KeyControl();
		if (key == SPACE) {
			break;
		}
	}
}

void drawMap(int size) { // □ ■ 
	string Map[size][size];
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			Map[i][j] = "■";
		}
	}
}

void Manual() {
	system("cls");
	gotoxy(38, 5);
	printf("[ 조작법 ]");
	gotoxy(26, 8);
	printf("좌표를 입력하면 대포를 발사합니다.");
	gotoxy(32, 11);
	printf("좌표 입력 예시 : 7 7");
	gotoxy(0, remark);
	printf("SPACEBAR를 누르면 메인으로 돌아갑니다.");
	
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

int KeyControl() { // w, a, s, d를 통해 이동, spacebar를 통해 입력 
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
