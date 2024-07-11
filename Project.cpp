/*
* Klievett Nicarlo Abrahams - 217061141
*/
#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>




#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 75

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int obsticleY[3];
int obsticleX[3];
int banner[3];
char car[4][4] = { ' ','^','^',' ',
					'@','O','O','@',
					' ','*','*',' ',
					'@','*','*','@' };

//pointers
int* obsticleYY = obsticleY ;
int* obsticleXX = obsticleX;
int* banners = banner;
 
int carLoci = WIN_WIDTH / 2;
int score = 0;

void transition(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
void makeObsticle(int ind) {
	obsticleXX[ind] = 17 + rand() % (33);
}
void designObsticle(int ind) {
	if (banners[ind] == true) {
		transition(obsticleXX[ind], obsticleYY[ind]);   cout << "####";
		transition(obsticleXX[ind], obsticleYY[ind] + 1); cout << " ** ";
		transition(obsticleXX[ind], obsticleYY[ind] + 2); cout << "####";
		transition(obsticleXX[ind], obsticleYY[ind] + 3); cout << " ** ";
	}
}
void borderLines() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < 17; j++) {
			transition(0 + j, i); cout << "=";
			transition(WIN_WIDTH - j, i); cout << "=";
		}
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		transition(SCREEN_WIDTH, i); cout << "=";
	}
}
void designCar() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transition(j + carLoci, i + 22); cout << car[i][j];
		}
	}
}
void removeCar() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transition(j + carLoci, i + 22); cout << " ";
		}
	}
}
void removeObsticle(int ind) {
	if (banners[ind] == true) {
		transition(obsticleXX[ind], obsticleYY[ind]); cout << "    ";
		transition(obsticleXX[ind], obsticleYY[ind] + 1); cout << "    ";
		transition(obsticleXX[ind], obsticleYY[ind] + 2); cout << "    ";
		transition(obsticleXX[ind], obsticleYY[ind] + 3); cout << "    ";
	}
}
void rebootObsticle(int ind) {
	removeObsticle(ind);
	obsticleYY[ind] = 1;
	makeObsticle(ind);
}



int Accident() {
	if (obsticleYY[0] + 4 >= 23) {
		if (obsticleXX[0] + 4 - carLoci >= 0 && obsticleXX[0] + 4 - carLoci < 9) {
			return 1;
		}
	}
	return 0;
}
void gameover() {
	system("cls");
	cout << endl;
	cout << "\t\t$%$%$%$%$%$%$%$$%$%$$%$%$%" << endl;
	cout << "\t\t******** Game Over *******" << endl;
	cout << "\t\t##########################" << endl << endl;
	cout << "\t\tPress any key to go back to menu.";
	_getch();
}
void newScore() {
	transition(WIN_WIDTH + 7, 5);cout << "Score: " << score << endl;
}

void instructions() {

	system("cls");
	cout << "Instructions";
	cout << "\n----------------";
	cout << "\n Dodge cars by shifting left or right! ";
	cout << "\n\n Press the 'a' key to move left";
	cout << "\n Press the 'd' key to move right";
	cout << "\n Press the 'escape' key to exit";
	cout << "\n\nPress any key to go back to menu";
	_getch();
}

void Start() {
	carLoci = -1 + WIN_WIDTH / 2;
	score = 0;
	banners[0] = 1;
	banners[1] = 0;
	obsticleYY[0] = obsticleYY[1] = 1;

	system("cls");
	borderLines();
	newScore();
	makeObsticle(0);
	makeObsticle(1);

	transition(WIN_WIDTH + 7, 2);cout << "NUST RACER GAME";
	transition(WIN_WIDTH + 6, 4);cout << "*****************";
	transition(WIN_WIDTH + 6, 6);cout << "-----------------";
	transition(WIN_WIDTH + 7, 12);cout << "CONTROLS ";
	transition(WIN_WIDTH + 7, 13);cout << "--------------- ";
	transition(WIN_WIDTH + 2, 14);cout << " A Key TURNS Left";
	transition(WIN_WIDTH + 2, 15);cout << " D Key TURNS Right";

	transition(18, 5);cout << "Press any key to start";
	_getch();
	transition(18, 5);cout << "                      ";

	while (1) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'a' || ch == 'A') {
				if (carLoci > 18)
					carLoci -= 4;
			}
			if (ch == 'd' || ch == 'D') {
				if (carLoci < 50)
					carLoci += 4;
			}
			if (ch == 27) {
				break;
			}
		}

		designCar();
		designObsticle(0);
		designObsticle(1);
		if (Accident() == 1) {
			gameover();
			return;
		}
		Sleep(50);
		removeCar();
		removeObsticle(0);
		removeObsticle(1);

		if (obsticleYY[0] == 10)
			if (banners[1] == 0)
				banners[1] = 1;

		if (banners[0] == 1)
			obsticleYY[0] += 1;

		if (banners[1] == 1)
			obsticleYY[1] += 1;

		if (obsticleYY[0] > SCREEN_HEIGHT - 4) {
			rebootObsticle(0);
			score++;
			newScore();
		}
		if (obsticleYY[1] > SCREEN_HEIGHT - 4) {
			rebootObsticle(1);
			score++;
			newScore();
		}
	}
}

int main()
{
	
	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do {
		system("cls");
		transition(10, 5); cout << " ################################# ";
		transition(10, 6); cout << "        NUST RACER GAME         ";
		transition(10, 7); cout << " ##################################";
		transition(10, 8);cout << "Select Options: " ;
		transition(10, 9);cout << "1. PLAY";
		
		
		
		transition(10, 10); cout << "2. INSTRUCTIONS";
		transition(10, 11); cout << "3. EXIT";
		transition(10, 13);
		char choice = _getch();

		if (choice == '1') Start();
		else if (choice == '2') instructions();
		else if (choice == '3') exit(0);

	} while (1);
	
	return 0;
}
