#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

typedef enum state {
	SPACE,
	WALL,
	HEAD,
	TAIL,
	FRUIT
} state_t;

typedef enum direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
} direction_t;

bool InitSnake();
void UpdateSnake();
void DrawSnake();