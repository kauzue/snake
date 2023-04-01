#include <Windows.h>

#include "setting.h"

int main(void)
{
	int* repeat = 1;
	InitSnake();
	
	while (repeat) {
		system("cls");

		UpdateSnake(&repeat);
		DrawSnake();

		Sleep(100);
	}
}