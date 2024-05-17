#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"
#include <time.h>
#include <stdbool.h>
// #include <curses.h>

void print_field(int rows, int columns, char field[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        printf("%d", i + 1);
        for (int j = 0; j < columns; j++) {
            if(j == columns - 1) {
                printf(" | %c", field[i][j]);
                printf(" |");
            } else {
                printf(" | %c", field[i][j]);
            }
        }
        printf("\n");
    }
    for(int i = 0; i < columns; i++) {
        if(i == 0) {
            printf("   ");
            printf("---");
        } else {
            printf(" ---");
        }
    }
    printf("\n");

    for(int i = 0; i < columns; i++) {
        if(i == 0) {
            printf("    %d", i + 1);
        } else {
            printf("   %d", i + 1);
        }
    }
    printf("\n");
}

void generator(const int rows, const int columns, char field[rows][columns]) {
    srand(time(NULL));

    int firstNullCol = rand() % columns + 1;
    int secondNullCol = rand() % columns + 1;
    // int symbolQuantity = columns - 2;
    while(firstNullCol == secondNullCol) {
        secondNullCol = rand() % columns;
    }

    char symbols[] = {'@', '*', '+', '^', '~', '$', '&', '#', '?', '!'};
    int arr[columns - 2];
    for(int i = 0; i < columns - 2; i++) {
        arr[i] = 0;
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(j == secondNullCol || j == firstNullCol) {
                field[i][j] = ' ';
                continue;
            }
            int temp = rand() % (columns - 2);
            while(arr[temp] == rows) {
                temp = rand() % (columns - 2);
            }

            if(arr[temp] < rows) {
                field[i][j] = symbols[temp];
                arr[temp] += 1;
            }
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    x--;
    y--;
    char temp;

    for(int i = 0; i < rows; i++) {
        if(field[i][x] != ' ') {
            temp = field[i][x];
            field[i][x] = ' ';
            break;
        }
    }
    for(int j = rows - 1; j >= 0; j--) {
        if(field[j][y] == ' ') {
            field[j][y] = temp;
            break;
        }
    }
}

bool is_col_null(int from, int rows, int columns, char field[rows][columns]) {
    for(int i = 0; i < rows; i++) {
        if(field[i][from - 1] != ' ') {
            return false;
        }
    }
    return true;
}

bool is_col_full(int to, int rows, int columns, char field[rows][columns]) {
    if(field[0][to - 1] == ' ') {
        return false;
    }
    
    return true;
}

bool check(const int rows, const int columns, char field[rows][columns]) {
    char temp;

    for(int i = 0; i < columns; i++) {
        temp = field[0][i];
        for(int j = 1; j < rows; j++) {
            if(temp != field[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// void game_field(const int rows, const int columns, char field[rows][columns]) {
//     initscr();
//     printw("Hello world\n");
//     refresh();
//     getch();
//     endwin();
// }


void ball_sort_puzzle() {
    int from, to;
    int rows, columns;

    printf("Hi, this is a game - ball sort puzzle\n");
    printf("Pls type a num of rows(but not greater that 10:-) ): ");
    scanf("%d", &rows);
    printf("Good, and now type a num of columns(same): ");
    scanf("%d", &columns);
    char field[rows][columns];
    printf("This is your playing field:\n");
    generator(rows, columns, field);
    print_field(rows, columns, field);

    while(true) {
        if(check(rows, columns, field)) {
            printf("Congratulations! You won!\n");
            break;
        }
        printf("Enter a num of column from which you would take a char: ");
        scanf("%d", &from);
        while(is_col_null(from, rows, columns, field)) {
            printf("This col is null, reenter: ");
            scanf("%d", &from);
        }

        printf("Enter a num of column to which you would to pick out a char: ");
        scanf("%d", &to);
        while(is_col_full(to, rows, columns, field)) {
            printf("Oh no, this col is full, reenter: ");
            scanf("%d", &to);
        }

        while(from == to) {
            printf("Enter another second column: ");
            scanf("%d", &to);
            while(is_col_full(to, rows, columns, field)) {
            printf("Oh no, this col is full, reenter: ");
            scanf("%d", &to);
        }
        }
        // game_field(rows, columns, field);
        
        down_possible(rows, columns, field, from, to);
        print_field(rows, columns, field);
    }
}