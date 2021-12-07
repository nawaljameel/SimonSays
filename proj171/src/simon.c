#include "simon.h"
#include <stdlib.h>



void game() {
    // Initialiizes LED Pins as outputs
    InitializePin(GPIOA, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // Blue, number 0
    InitializePin(GPIOB, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // Yellow, number 1
    InitializePin(GPIOB, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // Red, number 2
    InitializePin(GPIOB, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // Green, number 3
    //rand() % 5 for 0 to 4
    // Button Pins
    // PB13 // GPIOB, GPIO_PIN_13 // Button 1 for blue LED
    // PB14 // GPIOB, GPIO_PIN_14 // Button 2 for yellow LED
    // PB15 // GPIOB, GPIO_PIN_15 //  Button 3 for red LED
    // PB1 // GPIOB, GPIO_PIN_1 // 4 for green LED

    //HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) gets data from ppin, 1 is on, 0 is off (port, pin)
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true); output pin, turn led on or off
    //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10) changes state

    // HAL_Delay(1000)
    // HAL_GetTick() Gets current time of run in milliseconds

    bool game_won = true;
    while(true){
        int *sequence1 = get_sequence(2);
        read_sequence(sequence1, 2);
        game_won = check_sequence(sequence1, 2);
        free(sequence1);
        if(game_won == false){
            break;
        }

        else{
            HAL_Delay(1000);
            int *sequence2 = get_sequence(3);
            read_sequence(sequence2, 3);
            game_won = check_sequence(sequence2, 3);
            free(sequence2);
            if(game_won == false){
                break;
            }
            else{
                HAL_Delay(1000);
                int *sequence3 = get_sequence(4);
                read_sequence(sequence3, 4);
                game_won = check_sequence(sequence3, 4);
                free(sequence3);
                if(game_won == false){
                    break;
                }else{
                    HAL_Delay(1000);
                    int *sequence4 = get_sequence(5);
                    read_sequence(sequence4, 5);
                    game_won = check_sequence(sequence4, 5);
                    free(sequence4);
                    break;
                }
            }
        }


    }

    endGame(game_won);



   
}



int* get_sequence(int size){

    srand(HAL_GetTick());

    int* seq;
    seq = (int*)malloc( size * sizeof(int));

    for(int i = 0; i < size; ++i){
        seq[i] = rand() % 4;
    }

    return seq;


}

 bool check_sequence(int * array, int size){

    for(int i = 0; i < size; ++i){
        int start_timer = HAL_GetTick();
        int light = lightsAndButtons();
        //end game is user does not input under 5 seconds.
        if((HAL_GetTick() - start_timer) > 5000){
            return false;
        }
        else if(light != array[i]){
            return false;
        }
        HAL_Delay(10);
    }
    return true;

} 

void read_sequence(int* array, int size){
    for(int i = 0; i < size; ++i){
        if (array[i] == 0){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true); // Turn blue on
            HAL_Delay(100);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false); 
        }
        else if (array[i] == 1){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true); // Turn yellow on
            HAL_Delay(100);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false); 
        }
        else if(array[i] == 2){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true); // red
            HAL_Delay(100);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);

        }
        else if (array[i] == 3){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true); //green
            HAL_Delay(100);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);

        }
        else{
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true);

        }
        HAL_Delay(300);
    }
}

int lightsAndButtons() {

    while(true) {

        // button 1, blue LED
        if ( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) ) // If Button 1 is being press
        {
            while( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) ){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true); // Turn blue on
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false); // Else Turn Blue off
            return 0;
        }

        // button 2, yellow light
        if ( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)) )
        {
            while( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)) ){
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true); // Turn yellow on
            }
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false); // Else Turn yellow off
            return 1;
        }

        // button 3, red light
        if ( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)) )
        {
            while ( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)) ){
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
            }
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
            return 2;
        }

        // button 4, green light

        if ( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)) )
        {
            while( (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)) ){
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true);
            }

            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);
            return 3;
        }

    }
}


void endGame(bool gameWon){
    if(gameWon == true){
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true);
        HAL_Delay(1000);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);
        
    }else if (gameWon == false){
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);


        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);
    }

}