#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

char map[30][100] = {
" _________________________________________________________________________________________________ "
,"|=================================================================================================|"
,"|  SCORE : 0                          <<BRICK-BRACKER>>                                           |"
,"|=================================================================================================|"
,"|	                                                                                               |"
,"|	                                                                                               |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|                                                                                                 |"
,"|	                                                                                               |"
,"|                                                                                                 |"
,"|*************************************************************************************************|" };

// static definitions :
#define START_PLAYER_POINT_Y 26
#define START_PLAYER_POINT_X 50
#define PLAYER_ROCKET 12   //< 10
#define	BRICK_SIZE 5 
#define MAP_WIDTH 98
#define MAP_HEIGHT 23		
#define MENU_BOX 4			// 18 - 14 
#define MENU_BAR 3
#define BRICK_BOX_HEIGHT 12 // 30 - 18 
#define PlAYING_BOX_HEIGHT 14
#define BRICK_MARGIN 1
#define START_MARGIN_LEFT 5
#define START_MARGIN_TOP 5
#define fRAME_SPEED_UPDATE 5

// -------------------------------------------------------------------------------common function: 
void gotoxy(int x, int y)
{
	COORD coord; // coordinates
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void showMap(char map[][100]) {

	for (int i = 0; i < 30; i++) {
		gotoxy(START_MARGIN_LEFT, START_MARGIN_TOP + i);
		for (int j = 0; j < 100; j++)cout << map[i][j];

	}
}


// -------------------------------------------------------------------------------OBJECT's : 


class Brick
{
public:

	// Objective varibale : 
	int	x;
	int y;
	int speed = 0;

public: // FUNCTION >>>


	void update() {


	}
	void draw()
	{
		erase();
		gotoxy(START_MARGIN_LEFT + x - BRICK_SIZE / 2, START_MARGIN_TOP + y);
		for (int i = 0; i < BRICK_SIZE; i++)
			cout << (char)223;

		for (int i = 0; i < BRICK_SIZE; i++) {
			map[y][x + i] = (char)223;
		}

	}

	void erase()
	{
		for (int i = 0; i < BRICK_SIZE; i++) {
			map[y][x + i] = ' ';
		}
		gotoxy(START_MARGIN_LEFT + x - BRICK_SIZE / 2, START_MARGIN_TOP + y);
		for (int i = 0; i < BRICK_SIZE; i++)
			cout << " ";
	}
	/* requirment's:
		LOCAL STATIC SETUP FUNCTION
	*/
};
// static variable : 
short brickNum;
vector<Brick> brick;
vector<Brick> ::iterator bElement;
void BrickStartup() {

	srand(time(0));
	//
	int brickNum = (MAP_WIDTH / (BRICK_MARGIN + BRICK_SIZE));
	int step = BRICK_SIZE + BRICK_MARGIN;

	Brick obj;
	for (int i = MENU_BOX; i < BRICK_BOX_HEIGHT + MENU_BOX; i++)
	{

		for (int j = BRICK_MARGIN + 1 + BRICK_SIZE / 2; j < MAP_WIDTH + 1 - BRICK_SIZE / 2 - BRICK_MARGIN; j += step)
		{
			if (1)
			{

				obj.x = j;
				obj.y = i;
				obj.draw();
				brick.push_back(obj);
			}

		}
	}
	/*
	bElement = brick.begin();
	for (int i =0 ; i < BRICK_BOX_HEIGHT ; i++)
	{
		int delbrick = rand() % brickNum > brickNum / 2 ? 0 : rand() % brickNum > brickNum / 4 ? 1 : 2;
		while (delbrick != 0)
		{
			int random = brickNum * i + rand() % brickNum;
			brick[random].erase();
			brick.erase(bElement + random);
			delbrick--;
		}
	}
	*/
}
//STATIC --> short Brick::brickNum; and so more 



class Player {
public:
	int x;
	int y;
	float speed = 0;

public:
	Player() {
		x = START_PLAYER_POINT_X;
		y = START_PLAYER_POINT_Y;
		draw();

	}

	void draw()
	{	// screen 
		erase();

		gotoxy(START_MARGIN_LEFT + x - PLAYER_ROCKET / 2, START_MARGIN_TOP + y + 1);
		cout << (char)219;
		for (int i = 0; i < PLAYER_ROCKET - 2; i++)
			cout << (char)220;
		cout << (char)219;

		gotoxy(START_MARGIN_LEFT + x - PLAYER_ROCKET / 2, START_MARGIN_TOP + y);
		cout << (char)219;
		for (int i = 0; i < PLAYER_ROCKET - 2; i++)
			cout << (char)178;
		cout << (char)219;
		// map

		map[y][x] = (char)219;
		map[y + 1][x] = (char)219;
		map[y][x + PLAYER_ROCKET - 1] = (char)219;
		map[y + 1][x + PLAYER_ROCKET - 1] = (char)219;

		for (int i = 1; i < PLAYER_ROCKET - 1; i++) {
			map[y][x + i] = (char)178;
			map[y + 1][x + i] = (char)220;
		}


	}
	void erase()
	{
		for (int i = 0; i < PLAYER_ROCKET; i++) {
			map[y][x + i] = ' ';
			map[y + 1][x + i] = ' ';
		}
		gotoxy(START_MARGIN_LEFT + x - BRICK_SIZE / 2 - 1, START_MARGIN_TOP + y);
		for (int i = 0; i <= BRICK_SIZE + 1; i++)
			cout << " ";
	}

};
void PlayerStartup() {

}

class Ball {
public:
	int x;
	int y;
	float speedx;
	float speedy;
	int startPoint;
	Ball() {
		// we have four start point in the ideal stitation 
	//	int startPoint=rand()%2;
		startPoint = 0;




	}
	void ballUpdate() {
		x += speedx;
		y += speedy;
	}
	void draw()
	{	// screen 
		erase();
		gotoxy(START_MARGIN_LEFT + x, START_MARGIN_TOP + y);
		cout << (char)'@'; // ball character 
		map[y][x] = '@';


	}
	void erase()
	{

		gotoxy(START_MARGIN_LEFT + x, START_MARGIN_TOP + y);
		cout << (char)' ';
		map[y][x] = ' ';

	}


};
void BallStartup() {

}
void ballSimulator()
{

}
//------------------------------------------------------------------------------section's: 
void TIZER() {


}
void StartCount(Ball& ball) {
	switch (ball.startPoint) {

	case 0: // left _ top ; 

		for (int i = 0; i < 3; i++) {
			gotoxy(START_MARGIN_LEFT + 1 + i, START_MARGIN_TOP + i + 30 - PlAYING_BOX_HEIGHT);
			cout << '\\';
		}
		cout << "the ball is here ";
		// this two must be saved in the way that at first the ball conflict  with the player automaticly  
		ball.speedx = 1;
		ball.speedy = 2;

		break;
	case 1: // right_ top ; 
		gotoxy(99 - 1, 30 - PlAYING_BOX_HEIGHT);
		break;
	case 2: // right _ buttom
		break;
	case 3: // left _ buttom 
		break;

	}


}



// intial definitions...!






int main() {

	TIZER();
	Sleep(3000);
	system("cls");
	showMap(map);
	BrickStartup();
	Player player;
	Ball ball;
	StartCount(ball);
	int frame = 0;
	while (1) {


		if ((GetAsyncKeyState('a') || GetAsyncKeyState('A')))
			player.speed = -1;
		else if (GetAsyncKeyState('d') || GetAsyncKeyState('D'))
			player.speed = 1;
		else player.speed = 0;


		if (player.speed && !(frame % fRAME_SPEED_UPDATE)) {
			if ((player.x > (1 + PLAYER_ROCKET / 2)) && player.speed < 0) {
				player.x += player.speed;
				player.draw();
			}
			else if ((player.x < (98 - PLAYER_ROCKET / 2)) && player.speed > 0) {
				player.x += player.speed;
				player.draw();
			}

		}


		// it can be more with the menu item ... 




		gotoxy(0, 50);
		cout << "player.speed: " << player.speed << endl;
		cout << "player.x : " << player.x;




		frame++;
		if (frame == fRAME_SPEED_UPDATE - 1)frame = 0; // 3 is ust sample untill now ; a
		Sleep(10);



	}






	// end finish
	gotoxy(0, 50);


}
