#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkMagicSquare(const int square[3][3]);
void printSquare(const int square[3][3]);

int main() {
    int testSquare[3][3] = {{4, 9, 2}, {3, 5, 7}, {8, 1, 6}};
    int result = checkMagicSquare(testSquare);
    printf("Testing square:\n");
    printSquare(testSquare);
    if (result == 0) {
        printf("This is not a Lo Shu Magic Square\n");
    } else if (result == 1) {
        printf("This is a Lo Su Magic Square\n");
    }

    printf("\n");
    int count = 0;
    result = 0;
    time_t t;
    srand((unsigned) time(&t));
    int square[3][3];
    int used[9];
    while (result == 0) {
        for (int i = 0; i < 9; i++) { // reset unique numbers
            used[i] = 0;
        }
        // populate square
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = rand() % 9 + 1; // random number from 1-9
                while (used[val - 1] != 0) { // generate until found unique
                    val = rand() % 9 + 1;
                }
                used[val - 1]++;
                square[i][j] = val;
            }
        }
        result = checkMagicSquare(square);
        count++;
    }
    printf("Generating square...\n");
    printf("Took %d tries to generate a Lo Shu Magic Square:\n", count);
    printSquare(square);
}

// if magic square return 1
// else return 0
int checkMagicSquare(const int square[3][3]) {
    int used[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int currSum = square[0][0] + square[1][1] + square[2][2]; // left diagonal
    if (currSum != square[2][0] + square[1][1] + square[0][2]) return 0; // right diagonal
    // rows and columns
    for (int i = 0; i < 3; i++) {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < 3; j++) {
            rowSum += square[i][j];
            colSum += square[j][i];

            int val = square[i][j];
            if (val < 1 || val > 9) return 0; // checks if between 1 and 9
            used[val - 1]++; // increments unique number
        }
        if (rowSum != currSum || colSum != currSum) return 0;
    }
    for (int i = 0; i < 9; i++) { // checks if each number used once
        if (used[i] != 1) return 0;
    }
    return 1;
}

// prints square
void printSquare(const int square[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("[ ");
        for (int j = 0; j < 3; j++) {
            printf("%d ", square[i][j]);
        }
        printf("]\n");
    }
}