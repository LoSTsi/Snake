#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>

using namespace std;
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}


string map[] =
{
{"#######################" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#                     #" },
{"#######################" }
};
bool alive = true;
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

const int MAP_X = 22;
const int MAP_Y = 12;

const int MAX_LEN_SNAKE = (MAP_X - 2) * (MAP_Y - 3);// площадь 
int spawn_x[MAX_LEN_SNAKE] = { 0 };
int spawn_y[MAX_LEN_SNAKE] = { 0 };

const char snake = 'O';
int snake_dir = UP;
int snake_len = 1;

int food_y = 1 + (rand() % (MAP_X - 2));
int food_x = 1 + (rand() % (MAP_Y - 3));
char food = '*';
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	spawn_x[0] = MAP_X / 2;
	spawn_y[0] = MAP_Y / 2;
	double time = clock();


	while (alive) //генерация карты
	{
		if (GetKeyState('W') & 0x8000)
		{
			if (snake_dir != DOWN)
			{
				snake_dir = UP;
			}
		}
		if (GetKeyState('S') & 0x8000)
		{
			if (snake_dir != UP)
			{
				snake_dir = DOWN;
			}
		}
		if (GetKeyState('A') & 0x8000)
		{
			if (snake_dir != RIGHT)
			{
				snake_dir = LEFT;
			}
		}
		if (GetKeyState('D') & 0x8000)
		{
			if (snake_dir != LEFT)
			{
				snake_dir = RIGHT;
			}
		}

		if ((clock() - time) / CLOCKS_PER_SEC >= 0.3)
		{
			time = clock();
			if (spawn_x[0] == food_x && spawn_y[0] == food_y)//спавн еды
			{
				++snake_len;
				food_x = 1 + (rand() % (MAP_X - 2));
				food_y = 1 + (rand() % (MAP_Y - 3));
			}

			for (int i = snake_len - 1; i >= 0; --i) //увеличене змеии 
			{
				spawn_x[i + 1] = spawn_x[i];
				spawn_y[i + 1] = spawn_y[i];
			}

			if (snake_dir == UP)
			{
				--spawn_y[0];
			}
			if (snake_dir == DOWN)
			{
				++spawn_y[0];
			}
			if (snake_dir == LEFT)
			{
				--spawn_x[0];
			}
			if (snake_dir == RIGHT)
			{
				++spawn_x[0];
			}
			if (spawn_x[0] == 0 || spawn_y[0] == 0 || spawn_x[0] == MAP_X - 1 || spawn_y[0] == MAP_Y - 2)
			{
				alive = false;
			}

			for (int i = 1; i < snake_len; i++)
			{
				if (spawn_y[i] == spawn_y[0] && spawn_x[i] == spawn_x[0])
				{
					alive = false;
				}
			}

			gotoxy(0, 0);
			for (int i = 0; i < snake_len; i++)
			{
				map[spawn_y[i]][spawn_x[i]] = 'O';// находим центр
			}
			map[food_y][food_x] = food;
			cout << "Длинна: " << snake_len;
			for (int i = 0; i < MAP_Y; i++)//рендер карты
			{
				cout << endl << map[i];
			}

			for (int i = 0; i < snake_len; i++)
			{
				map[spawn_y[i]][spawn_x[i]] = ' ';// находим центр
			}

		}
	}
	gotoxy(1, MAP_Y / 2);
	cout << "\tGeme Over";

}