#include "philos.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int left(int pos, int players) { //finds index of left player
    return ((pos + players - 1) % players);
}

int right(int pos, int players) { // finds index of right player
    return ((pos + 1) % players);
}

void diceSw(int arr[14], int rollNum, int numPlayers,
    int indx) { //caseswitch that takes dice roll and give money to where is needed.
    switch (rollNum) {
    case 0: printf(" gets a pass"); break; //Pass
    case 1: //Left
        arr[indx] = arr[indx] - 1;
        arr[left(indx, numPlayers)] = arr[left(indx, numPlayers)] + 1;
        printf(" give $1 to ");
        printf("%s", philosophers[left(indx, numPlayers)]);
        break;
    case 2: //Right
        arr[indx] = arr[indx] - 1;
        arr[right(indx, numPlayers)] = arr[right(indx, numPlayers)] + 1;
        printf(" give $1 to ");
        printf("%s", philosophers[right(indx, numPlayers)]);
        break;
    case 3: //Center
        arr[indx] = arr[indx] - 1;
        arr[14] = arr[14] + 1;
        printf(" puts $1 in the pot");
        break;
    }
}

int main() {
    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
    int moneyArray[15]
        = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 }; //array of cash the fourteented is center
    int seed;
    int playerNum;
    int index = 0;
    bool whileCondition = true;
    printf("Random seed: ");
    scanf("%d", &seed);
    printf("How many players? ");
    scanf("%d", &playerNum);
    if (playerNum < 1) { //error check
        printf("Number of players must be from 1 to 14.\n");
        return 0;
    }
    if (playerNum > 14) { //error check
        printf("Number of players must be from 1 to 14.\n");
        return 0;
    }
    if (playerNum == 1) {
        whileCondition = false;
    }
    srandom(seed);
    while (whileCondition == true) { //while loop until only one player has cash money
        if (moneyArray[index] >= 3) { // if money for current player is at or above three dollars
            printf("%s", philosophers[index]);
            printf(" rolls...");
            faces dice1 = die[random() % 6];
            faces dice2 = die[random() % 6];
            faces dice3 = die[random() % 6];
            diceSw(moneyArray, dice1, playerNum, index);
            diceSw(moneyArray, dice2, playerNum, index);
            diceSw(moneyArray, dice3, playerNum, index);
            printf("\n");

        } else if (moneyArray[index] == 2) { //if money for current player is at two dollars
            printf("%s", philosophers[index]);
            printf(" rolls...");
            faces dice1 = die[random() % 6];
            faces dice2 = die[random() % 6];
            diceSw(moneyArray, dice1, playerNum, index);
            diceSw(moneyArray, dice2, playerNum, index);
            printf("\n");
        } else if (moneyArray[index] == 1) { //if money for current player is at one dollar
            printf("%s", philosophers[index]);
            printf(" rolls...");
            faces dice1 = die[random() % 6];
            diceSw(moneyArray, dice1, playerNum, index);
            printf("\n");
        }
        int out = 0;
        for (int i = 0; i < playerNum; ++i) { //checks how many players has no cash
            if (moneyArray[i] == 0) {
                ++out;
            }
        }
        if (out
            == (playerNum
                - 1)) { //if only one player has chas sets up so this is last loop of while
            whileCondition = false;
        }
        ++index;
        if (index == playerNum) { //resets index if it goes over number of players playing.
            index = 0;
        }
    }
    for (int i = 0; i < playerNum; ++i) { //goes to current player and ends game
        if (moneyArray[i] != 0) {
            printf("%s", philosophers[i]);
            printf(" wins the $%i", moneyArray[14]);
            printf(" pot with $%i", moneyArray[i]);
            printf(" left in the bank!\n");
        }
    }
}
