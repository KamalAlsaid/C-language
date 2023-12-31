#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOYUT 10
#define MAYIN_ORANI 5

void showBoard(char board[][BOYUT], char visited[][BOYUT], int playerRow, int playerCol);
void movePlayer(char board[][BOYUT], char visited[][BOYUT], int *playerRow, int *playerCol, char direction);
int checkWin(int playerRow, int playerCol);
void placeMines(char board[][BOYUT]);

int main() {
    char gameBoard[BOYUT][BOYUT];
    char visited[BOYUT][BOYUT];
    int playerRow = 0, playerCol = 0;

    for (int i = 0; i < BOYUT; i++) {
        for (int j = 0; j < BOYUT; j++) {
            gameBoard[i][j] = '*';
            visited[i][j] = 0;
        }
    }

    placeMines(gameBoard);

    showBoard(gameBoard, visited, playerRow, playerCol);

    char direction;

    printf("(w, s, a, d) = ");
    while (1) {
        scanf(" %c", &direction);
        movePlayer(gameBoard, visited, &playerRow, &playerCol, direction);
        showBoard(gameBoard, visited, playerRow, playerCol);

        if (gameBoard[playerRow][playerCol] == 'o') {
            printf("You hit a mine Game over\n");
            break;
        } else if (checkWin(playerRow, playerCol)) {
            printf("Congratulations You won the game\n");
            break;
        }
    }

    return 0;
}

void showBoard(char board[][BOYUT], char visited[][BOYUT], int playerRow, int playerCol) {
    system("cls");

    for (int i = 0; i < BOYUT; i++) {
        for (int j = 0; j < BOYUT; j++) {
            if (i == playerRow && j == playerCol) {
                printf("G ");
            } else if (i == BOYUT - 1 && j == BOYUT - 1) {
                printf("C ");
            } else if (visited[i][j]) {
                printf(". ");
            } else {
                printf("%c ", board[i][j]);
            }
        }
        printf("\n");
    }
}

void movePlayer(char board[][BOYUT], char visited[][BOYUT], int *playerRow, int *playerCol, char direction) {
    int newRow = *playerRow;
    int newCol = *playerCol;

    switch (direction) {
        case 'w':
            if (*playerRow > 0) {
                newRow = *playerRow - 1;
            }
            break;
        case 's':
            if (*playerRow < BOYUT - 1) {
                newRow = *playerRow + 1;
            }
            break;
        case 'a':
            if (*playerCol > 0) {
                newCol = *playerCol - 1;
            }
            break;
        case 'd':
            if (*playerCol < BOYUT - 1) {
                newCol = *playerCol + 1;
            }
            break;
        default:
            printf("Invalid direction\n");
            return;
    }

    visited[newRow][newCol] = 1;
    *playerRow = newRow;
    *playerCol = newCol;
}

int checkWin(int playerRow, int playerCol) {
    return (playerRow == BOYUT - 1 && playerCol == BOYUT - 1);
}

void placeMines(char board[][BOYUT]) {
    srand(time(NULL));

    int mineCount = (BOYUT * BOYUT * MAYIN_ORANI) / 100;

    for (int i = 0; i < mineCount; i++) {
        int row, col;
        do {
            row = rand() % BOYUT;
            col = rand() % BOYUT;
        } while (board[row][col] == 'o');

        board[row][col] = 'o';
    }
}
