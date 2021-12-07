#include "stm32f4xx_hal.h"
#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

void game();
int lightsAndButtons();
int * get_sequence(int size);
bool check_sequence(int * array, int size);
void endGame(bool gameWon);
void read_sequence(int* array, int size);