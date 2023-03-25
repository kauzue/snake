#include "setting.h"

state_t* State = NULL;

uint32_t Row = 0;
uint32_t Col = 0;

uint32_t HeadX;
uint32_t HeadY;

uint32_t* TailsX = NULL;
uint32_t* TailsY = NULL;
uint32_t TailCount = 2;

uint32_t FruitX = 0;
uint32_t FruitY = 0;

direction_t Dir = RIGHT;

bool InitSnake()
{
	Row = 10;
	Col = 20;
	State = (state_t*)malloc(sizeof(state_t) * Row * Col);

	memset(State, SPACE, sizeof(state_t) * Row * Col);

	for (uint32_t i = 0; i < Row; i++) {
		State[i * Col + 0] = WALL;
		State[i * Col + Col - 1] = WALL;
	}

	for (uint32_t i = 0; i < Col; i++) {
		State[i] = WALL;
		State[(Row - 1) * Col + i] = WALL;
	}


	uint32_t HeadX = Col * 0.2f + TailCount;
	uint32_t HeadY = Row * 0.5f;

	State[HeadY * Col + HeadX] = HEAD;


	TailsX = (uint32_t*)malloc(sizeof(uint32_t) * Row * Col);
	TailsY = (uint32_t*)malloc(sizeof(uint32_t) * Row * Col);

	for (uint32_t i = 0; i < TailCount; i++) {
		uint32_t TailX = HeadX - i - 1;
		uint32_t TailY = HeadY;

		State[TailY * Col + TailX] = TAIL;
	}

	

	MakeFruit();
	
	return true;
}

void UpdateSnake()
{
	if (_kbhit()) {
		int key = _getch();

		if (key == 224) {
			switch (key)
			{
			case 72:
				Dir = UP;
				break;
			case 80:
				Dir = DOWN;
				break;
			case 75:
				Dir = LEFT;
				break;
			case 77:
				Dir = RIGHT;
				break;
			}
		}

		switch (key)
		{
		case 'w':
		case 'W':
			Dir = UP;
			break;
		case 's':
		case 'S':
			Dir = DOWN;
			break;
		case 'a':
		case 'A':
			Dir = LEFT;
			break;
		case 'd':
		case 'D':
			Dir = RIGHT;
			break;
		}
	}

	switch (Dir)
	{
	case UP:
		HeadY -= 1;

		break;
	case DOWN:
		HeadY += 1;

		break;
	case LEFT:
		HeadX -= 1;

		break;
	case RIGHT:
		HeadX += 1;

		break;
	}

	State[HeadY * Col + HeadX] = HEAD;

}

void DrawSnake()
{
	for (uint32_t y = 0; y < Row; ++y)
	{
		for (uint32_t x = 0; x < Col; ++x)
		{
			char texture;

			switch (State[y * Col + x])
			{
			case SPACE:
				texture = ' ';
				break;
			case WALL:
				texture = '0';
				break;
			case HEAD:
				texture = 'H';
				break;
			case TAIL:
				texture = 'T';
				break;
			case FRUIT:
				texture = 'F';
				break;
			default:
				break;
			}

			printf("%c", texture);
		}
		printf("\n");
	}
}

void MakeFruit()
{
	srand(time(NULL));

	int same;

	do {
		same = 0;

		FruitX = rand() % (Col - 2) + 1;
		FruitY = rand() % (Row - 2) + 1;

		if(FruitX == HeadX && FruitY == HeadY) {
			same = 1;
			break;
		}

		for (int i = 0; i < TailCount; i++) {
			if(FruitX == TailsX[i] && FruitY == TailsY[i]) {
				same = 1;
				break;
			}
		}
	}while(same);

	State[FruitY * Col + FruitX] = FRUIT;
}