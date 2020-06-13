#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** ERROR CODES
 */
#define INCORRECT_NUM_OF_ARGS 1
#define INVALID_PLAYER_TYPE 2
#define CANT_READ_FROM_FILE 3
#define INVALID_FILE_CONTENTS 4
#define END_OF_FILE 5
#define FULL_BOARD_ON_LOAD 6

#define EMPTY -1

/** Edges */
#define TOP_EDGE 1
#define RIGHT_EDGE 2
#define BOTTOM_EDGE 3
#define LEFT_EDGE 4

/** Represents a Cell of the Grid
 */
typedef struct Cell {
    int pointValue;
    char occupancy;
} Cell;

/** Represents the game board.
 */
typedef struct Grid {
    Cell **cells;
    int rows;
    int columns;
    char xType;
    char oType;
    char currentPlayer;

    char *oldRow;
    char *oldColumn;
    int oldRowIndex;
    int oldColumnIndex;

} Grid;


int place_highest(Grid *grid, bool placed, char currentPlayer);
int check_valid_board(FILE *file, int rows, int columns);
bool move_zero_placer(Grid *grid, char currentPlayer, bool valid, int row,
        int col);

void alloc_grid(Grid *grid, FILE *file, char **argv);


void draw_grid(Grid *grid, FILE *file);


int get_score(Grid *grid, char player);

int is_edge(Grid *grid, int row, int column);

int move_type_zero(Grid *grid, char currentPlayer);

bool move_one_check_optimal(Grid *grid, int row, int col, char opponent,
        char player, int opponentCurrentScore);

int move_type_one(Grid *grid, char currentPlayer);

int place_move(Grid *grid, int row, int column, char player);

void revert_move(Grid *grid);

char *read_line(FILE *file);

char next_player(char currentPlayer);
bool check_if_full(Grid *grid);

char get_player_type(Grid *grid, char player);

int count_chars(int integer);
int check_valid_file(char *fileName);

int check_game_over(Grid *grid);
int main(int argc, char **argv);
