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


	HeadX = Col * 0.2f + TailCount;
	HeadY = Row * 0.5f;

	State[HeadY * Col + HeadX] = HEAD;


	TailsX = (uint32_t*)malloc(sizeof(uint32_t) * Row * Col);
	TailsY = (uint32_t*)malloc(sizeof(uint32_t) * Row * Col);

	for (uint32_t i = 0; i < TailCount; i++) {
		TailsX[i] = HeadX - i - 1;
		TailsY[i] = HeadY;

		State[TailsY[i] * Col + TailsX[i]] = TAIL;
	}

	

	MakeFruit();
	
	return true;
}

void UpdateSnake(int* rp)
{
	if (_kbhit()) {
		int key = _getch();

		if (key == 224) {
			key = _getch();
			switch (key)
			{
			case 72: //UP
				if (Dir != DOWN) {
					Dir = UP;
				}
				break;
			case 80: //DOWN
				if (Dir != UP) {
					Dir = DOWN;
				}
				break;
			case 77: //RIGHT
				if (Dir != LEFT) {
					Dir = RIGHT;
				}
				break;
			case 75: //LEFT
				if (Dir != RIGHT) {
					Dir = LEFT;
				}
				break;
			}
		}

		switch (key)
		{
		case 'w':
		case 'W':
			if (Dir != DOWN) {
				Dir = UP;
			}
			break;
		case 's':
		case 'S':
			if (Dir != UP) {
				Dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
			if (Dir != RIGHT) {
				Dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
			if (Dir != LEFT) {
				Dir = RIGHT;
			}
			break;
		}
	}

	for (int i = TailCount - 1; i >= 0; i--) {
		if (i == 0) {
			State[TailsY[i] * Col + TailsX[i]] = SPACE;
			TailsX[i] = HeadX;
			TailsY[i] = HeadY;
		}
		
		else {
			State[TailsY[i] * Col + TailsX[i]] = SPACE;
			TailsX[i] = TailsX[i - 1];
			TailsY[i] = TailsY[i - 1];
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

	if (WALL == State[HeadY * Col + HeadX]) {
		*rp = 0;
		printf("score = %d \n", TailCount - 2);
	}
	for (uint32_t i = 0; i < TailCount; i++) {
		if (HeadX == TailsX[i] && HeadY == TailsY[i]) {
			*rp = 0;
			printf("score = %d \n", TailCount - 2);
		}
	}

	if (FRUIT == State[HeadY * Col + HeadX]) {
		MakeFruit();
		TailsY[TailCount] = TailsY[TailCount - 1];
		TailsX[TailCount] = TailsX[TailCount - 1];
		TailCount++;
	}


	State[HeadY * Col + HeadX] = HEAD;
	for (uint32_t i = 0; i < TailCount; i++) {
		State[TailsY[i] * Col + TailsX[i]] = TAIL;
	}

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