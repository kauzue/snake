#include "setting.h"

state_t* State = NULL;

uint32_t Row = 10;
uint32_t Col = 10;

uint32_t HeadX = 0;
uint32_t HeadY = 0;

uint32_t* TailsX = 0;
uint32_t* TailsY = 0;
uint32_t TailCount = 2;

uint32_t FruitX = 0;
uint32_t FruitY = 0;

bool InitSnake()
{
	State = (state_t*)malloc(sizeof(state_t) * Row * Col);


	int* map[10][10];

	for (uint32_t i = 0; i < Row; i++) {
		State[i * Col] = WALL;
		State[i * Col + Col] = WALL;
	}

	for (uint32_t i = 0; i < Col; i++) {
		State[i] = WALL;
		State[Row * Row - Row + i] = WALL;
	}


	uint32_t HeadX = Col * 0.2f + TailCount;
	uint32_t HeadY = Row * 0.5f;

	State[HeadY * Col + HeadX] = HEAD;


	TailsX = (uint32_t)malloc(sizeof(uint32_t) * Row * Col);
	TailsY = (uint32_t)malloc(sizeof(uint32_t) * Row * Col);

	for (uint32_t i = 0; i < TailCount; i++) {
		uint32_t TailX = HeadX - i - 1;
		uint32_t TailY = HeadY;

		State[TailY * Col + TailX] = TAIL;
	}

	srand(time(NULL));

	FruitX = rand() % 9;
	FruitY = rand() % 9;

	State[FruitY * Col + FruitX] = FRUIT;
}

void UpdateSnake()
{

}

void DrawSnake()
{

}