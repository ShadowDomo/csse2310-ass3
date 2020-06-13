#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "push2310.h"


/** Saves the game state
 *
 * @param grid The board
 * @param fileName File to be saved to. Will be created if non existent
 * @param nextPlayer The player who has the next turn
 * @return 0 if success, 1 if fail
 */
int save_game(Grid *grid, char *fileName, char nextPlayer) {
    FILE *saveFile = fopen(fileName, "w");

    if (saveFile == NULL) {
        fprintf(stderr, "Save failed\n");
        return 1;
    }

    fprintf(saveFile, "%d %d\n", grid->rows, grid->columns);
    fprintf(saveFile, "%c\n", nextPlayer);

    draw_grid(grid, saveFile);
    fclose(saveFile);
    return 0;
}

/** Set the corners of the board to be empty
 *
 * @param grid The board
 */
void set_empty_corners(Grid *grid) {
    grid->cells[0][0].pointValue = EMPTY;
    grid->cells[0][0].occupancy = ' ';
    grid->cells[0][grid->columns - 1].pointValue = EMPTY;
    grid->cells[0][grid->columns - 1].pointValue = EMPTY;
    grid->cells[0][grid->columns - 1].occupancy = ' ';
    grid->cells[grid->rows - 1][0].pointValue = EMPTY;
    grid->cells[grid->rows - 1][0].occupancy = ' ';
    grid->cells[grid->rows - 1][grid->columns - 1].pointValue = EMPTY;
    grid->cells[grid->rows - 1][grid->columns - 1].occupancy = ' ';
}

/** Initializes the game board
 *
 * @param grid The board
 * @param file The save file to read the board from
 * @param argv argv
 */
void alloc_grid(Grid *grid, FILE *file, char **argv) {
    char *line = read_line(file);

    sscanf(line, "%d %d", &(grid->rows), &(grid->columns));
    grid->currentPlayer = read_line(file)[0];

    Cell **cells = malloc(sizeof(Cell *) * grid->rows);
    char *oldrow = malloc(sizeof(char) * grid->columns);
    char *oldcol = malloc(sizeof(char) * grid->rows);

    // initialize all cells to empty
    for (int i = 0; i < grid->rows; ++i) {
        cells[i] = malloc(sizeof(Cell) * grid->columns);
        for (int j = 0; j < grid->columns; ++j) {
            cells[i][j].pointValue = 0;
            cells[i][j].occupancy = '.';
        }
    }

    grid->cells = cells;
    grid->oldColumn = oldcol;
    grid->oldRow = oldrow;
    grid->oldRowIndex = -1;
    grid->oldColumnIndex = -1;
    // set player types
    grid->oType = argv[1][0];
    grid->xType = argv[2][0];

    set_empty_corners(grid);

    // set the cells according to save file
    for (int row = 0; row < grid->rows; ++row) {
        char *line = read_line(file);
        for (int col = 0; col < 2 * grid->columns; ++col) {
            if (line[col] != ' ') {
                // if its not a corner
                if (col % 2 == 0) { // if its a point value
                    grid->cells[row][col / 2].pointValue = line[col] - '0';
                } else {
                    grid->cells[row][col / 2].occupancy = line[col];
                }
            }
        }
    }
}

/** Draws the game board
 *
 * @param grid The board
 * @param file Where to draw the board to
 */
void draw_grid(Grid *grid, FILE *file) {
    for (int row = 0; row < grid->rows; ++row) {
        for (int column = 0; column < grid->columns; ++column) {
            Cell *cell = &(grid->cells[row][column]);
            if (cell->pointValue == EMPTY) {
                fprintf(file, " %c", cell->occupancy);
            } else {
                fprintf(file, "%d%c", cell->pointValue, cell->occupancy);
            }
            if (column == grid->columns - 1) {
                fprintf(file, "\n");
            }
        }
    }
}


/** Gets the score for the selected player
 *
 * @param grid The board
 * @param player The selected player
 * @return The player's score
 */
int get_score(Grid *grid, char player) {
    int score = 0;
    for (int row = 0; row < grid->rows; ++row) {
        for (int column = 0; column < grid->columns; ++column) {
            Cell *cell = &(grid->cells[row][column]);
            if (cell->occupancy == player) {
                score += cell->pointValue;
            }
        }
    }

    return score;
}

/** Checks if the cell at the given row/col is an edge
 *
 * @param grid The game board
 * @param row The row to be checked
 * @param column The column to check
 * @return The edge if it is an edge, or false otherwise
 */
int is_edge(Grid *grid, int row, int column) {
    if (row == 0) {
        return TOP_EDGE;
    }
    if (row == grid->rows - 1) {
        return BOTTOM_EDGE;
    }
    if (column == 0) {
        return LEFT_EDGE;
    }
    if (column == grid->columns - 1) {
        return RIGHT_EDGE;
    }

    return false;
}

/** Make a move for player type 0
 *
 * @param grid The board
 * @param currentPlayer The player to make the move
 * @return 0 if successful, 1 otherwise
 */
int move_type_zero(Grid *grid, char currentPlayer) {
    bool valid = false;
    // player 0 looks from top left
    if (currentPlayer == 'O') {
        for (int row = 1; row < grid->rows - 1; ++row) {
            for (int col = 1; col < grid->columns - 1; ++col) {
                valid = move_zero_placer(grid, currentPlayer, valid, row, col);
            }
        }
        // player X looks from bottom right
    } else if (currentPlayer == 'X' && valid == false) {
        for (int row = grid->rows - 2; row > 0; --row) {
            for (int col = grid->columns - 2; col > 0; --col) {
                valid = move_zero_placer(grid, currentPlayer, valid, row, col);
            }
        }
    }

    return valid;
}

/** Places a move for player type zero
 *
 * @param grid The board
 * @param currentPlayer The current player
 * @param valid True if a move has been placed already
 * @param row The row to be placed in
 * @param col The column to be placed in
 * @return True if the move was successfully made
 */
bool move_zero_placer(Grid *grid, char currentPlayer, bool valid, int row,
        int col) {
    if (grid->cells[row][col].occupancy == '.' && valid == false) {
        place_move(grid, row, col, currentPlayer);
        printf("Player %c placed at %d %d\n", currentPlayer, row, col);
        valid = true;
    }

    return valid;
}

/** Checks if a move is optimal, if not, will revert
 *
 * @param grid The board
 * @param row Row to be placed in
 * @param col Column to be placed in
 * @param opponent The opponent
 * @param player The current player
 * @param opponentCurrentScore The current score of the opponent
 * @return true if the move is optimal, false otherwise
 */
bool move_one_check_optimal(Grid *grid, int row, int col, char opponent,
        char player, int opponentCurrentScore) {
    int newScore = get_score(grid, opponent);
    if (newScore < opponentCurrentScore) {
        printf("Player %c placed at %d %d\n", player, row, col);
        return true;
    } else {
        revert_move(grid);
        return false;
    }
}

/** Makes a move for the currentPlayer
 *
 * @param grid The game grid
 * @param currentPlayer The current player
 * @return 0 if successful, 1 otherwise
 */
int move_type_one(Grid *grid, char currentPlayer) {
    char opponent = next_player(currentPlayer);
    int enemyScore = get_score(grid, opponent);
    bool placed = false;

    // top edge
    for (int col = 1; col < grid->columns - 1; ++col) {
        if (!placed && place_move(grid, 0, col, currentPlayer) == 0) {
            placed = move_one_check_optimal(grid, 0, col, opponent,
                    currentPlayer, enemyScore);
        }
    }
    //right edge
    for (int row = 1; row < grid->rows - 1; ++row) {
        if (!placed &&
                place_move(grid, row, grid->columns - 1, currentPlayer)
                == 0) {
            placed = move_one_check_optimal(grid, row, grid->columns - 1,
                    opponent, currentPlayer, enemyScore);
        }
    }
    // bottom edge
    for (int col = grid->columns - 2; col > 0; --col) {
        if (!placed &&
                place_move(grid, grid->rows - 1, col, currentPlayer)
                == 0) {
            placed = move_one_check_optimal(grid, grid->rows - 1, col,
                    opponent, currentPlayer, enemyScore);
        }
    }
    // left edge
    for (int row = grid->rows - 2; row > 0; --row) {
        if (!placed && place_move(grid, row, 0, currentPlayer) == 0) {
            placed = move_one_check_optimal(grid, row, 0, opponent,
                    currentPlayer, enemyScore);
        }
    }

    placed = place_highest(grid, placed, currentPlayer);
    return placed;
}

/** Plays a move for player type one at the highest valued cell
 *
 * @param grid The board
 * @param placed Has a move been made
 * @param currentPlayer The current player
 * @return True if a move has been played, False otherwise
 */
int place_highest(Grid *grid, bool placed, char currentPlayer) {
    int highest = -1;
    int temp[] = {-1, -1};
    // find cell with highest value
    if (!placed) {
        for (int row = 1; row < grid->rows; ++row) {
            for (int column = 1; column < grid->columns; ++column) {
                Cell *cell = &(grid->cells[row][column]);
                if (cell->occupancy == '.' && cell->pointValue > highest) {
                    highest = cell->pointValue;
                    temp[0] = row;
                    temp[1] = column;
                }
            }
        }
        place_move(grid, temp[0], temp[1], currentPlayer);
        printf("Player %c placed at %d %d\n",
                currentPlayer, temp[0], temp[1]);
        placed = true;
    }

    return placed;
}

/** Shuffles cells along the vertical when a move is placed at a top edge
 *
 * @param grid The board
 * @param column The column to be placed in
 */
void do_top_edge(Grid *grid, int column) {
    int emptyCellIndex = 0;
    for (int row = 0; row < grid->rows; ++row) {
        if (grid->cells[row][column].occupancy == '.') {
            emptyCellIndex = row;
            break;
        }
    }
    for (int i = emptyCellIndex; i > 0; --i) {
        grid->cells[i][column].occupancy =
                grid->cells[i - 1][column].occupancy;
    }
}

/** Shuffles cells along the vertical when a move is placed on the bottom edge
 *
 * @param grid The board
 * @param column The column to be placed in
 */
void do_bottom_edge(Grid *grid, int column) {
    int emptyCellIndex = 0;
    for (int row = grid->rows - 1; row >= 0; --row) {
        if (grid->cells[row][column].occupancy == '.') {
            emptyCellIndex = row;
            break;
        }
    }
    for (int i = emptyCellIndex; i < grid->rows - 1; ++i) {
        grid->cells[i][column].occupancy =
                grid->cells[i + 1][column].occupancy;
    }
}

/** Shuffles cells along the horizontal when a move is placed on the left edge
 *
 * @param grid The board
 * @param column The row to be placed in
 */
void do_left_edge(Grid *grid, int row) {
    int emptyCellIndex = 0;
    for (int column = 0; column < grid->columns; ++column) {
        if (grid->cells[row][column].occupancy == '.') {
            emptyCellIndex = column;
            break;
        }
    }
    for (int i = emptyCellIndex; i > 0; --i) {
        grid->cells[row][i].occupancy =
                grid->cells[row][i - 1].occupancy;
    }
}


/** Shuffles cells along the horizontal when a move is placed on the right edge
 *
 * @param grid The board
 * @param column The row to be placed in
 */
void do_right_edge(Grid *grid, int row) {
    int emptyCellIndex = 0;
    for (int columns = grid->columns - 1; columns >= 0; --columns) {
        if (grid->cells[row][columns].occupancy == '.') {
            emptyCellIndex = columns;
            break;
        }
    }
    for (int i = emptyCellIndex; i < grid->columns - 1; ++i) {
        grid->cells[row][i].occupancy =
                grid->cells[row][i + 1].occupancy;
    }
}

/** Check if a move can be made in the cell given by row/column
 *
 * @param grid The board
 * @param row The row to be checked
 * @param column The column to be checked
 * @return True if a move can be made, False otherwise
 */
bool check_column_validity(Grid *grid, int row, int column) {
    int emptyCellsCount = 0;
    bool firstPassed = false;
    bool secondPassed = false;
    // check if adjacent cell contains a stone
    if (grid->cells[abs(row - 1)][column].occupancy != '.') {
        firstPassed = true;
    }
    // check there is empty cell on the line
    for (int rowEmpty = 0; rowEmpty < grid->rows; ++rowEmpty) {
        if (grid->cells[rowEmpty][column].occupancy == '.') {
            emptyCellsCount++;
        }
    }
    if (emptyCellsCount > 1) {
        secondPassed = true;
    }
    if (firstPassed && secondPassed) {
        return true;
    }

    return false;
}

/** Check if a move can be made in the cell given by row/column
 *
 * @param grid The board
 * @param row The row to be checked
 * @param column The column to be checked
 * @return True if a move can be made, False otherwise
 */
bool check_row_validity(Grid *grid, int row, int column) {
    int emptyCellCount = 0;
    bool firstPassed = false;
    bool secondPassed = false;

    // check if adjacent cell contains a stone
    if (grid->cells[row][abs(column - 1)].occupancy != '.') {
        firstPassed = true;
    }
    // check there is empty cell on the line
    for (int cols = 0; cols < grid->columns; ++cols) {
        if (grid->cells[row][cols].occupancy == '.') {
            emptyCellCount++;
        }
    }
    if (emptyCellCount > 1) {
        secondPassed = true;
    }
    if (firstPassed && secondPassed) {
        return true;
    }

    return false;
}

/** Saves the current column state
 *
 * @param grid The board
 * @param column The column to be saved
 * @param player The current player
 * @param cell The cell to be moved into
 */
void save_old_column(Grid *grid, int column, char player, Cell *cell) {
    grid->oldRowIndex = -1;
    for (int i = 0; i < grid->columns; ++i) {
        grid->oldRow[i] = ' ';
    }
    for (int i = 0; i < grid->rows; ++i) {
        grid->oldColumn[i] = grid->cells[i][column].occupancy;
    }
    grid->oldColumnIndex = column;
    cell->occupancy = player;
}

/** Saves the current row state
 *
 * @param grid The board
 * @param row The row to be saved
 * @param player The current player
 * @param cell The cell to be moved into
 */
void save_old_row(Grid *grid, int row, char player, Cell *cell) {
    grid->oldColumnIndex = -1;
    for (int i = 0; i < grid->rows; ++i) {
        grid->oldColumn[i] = ' ';
    }
    for (int i = 0; i < grid->columns; ++i) {
        grid->oldRow[i] = grid->cells[row][i].occupancy;
    }
    grid->oldRowIndex = row;
    cell->occupancy = player;
}

/** Places a move on the board.
 *
 * @param grid The game grid
 * @param row The row to be placed in
 * @param column The column to be placed in
 * @param player The player who is placing the move
 * @return 0 if valid move, 1 otherwise
 */
int place_move(Grid *grid, int row, int column, char player) {
    // check inputs are valid
    if (row < 0 || row > grid->rows) {
        return 1;
    }
    if (column < 0 || column > grid->columns) {
        return 1;
    }
    int edge = is_edge(grid, row, column);
    Cell *cell = &(grid->cells[row][column]);
    if (cell->pointValue == EMPTY) {
        return 1;
    }
    if (!edge) {
        // is in center
        if (cell->occupancy == '.') {
            cell->occupancy = player;
            return 0;
        }
        return 1;
    } else {
        // is edge
        if (edge == TOP_EDGE || edge == BOTTOM_EDGE) {
            if (check_column_validity(grid, row, column)) {
                save_old_column(grid, column, player, cell);
                if (edge == TOP_EDGE) {
                    do_top_edge(grid, column);
                } else { // must be bottom edge
                    do_bottom_edge(grid, column);
                }
                cell->occupancy = '.';
                return 0;
            }
            return 1;
        } else {
            if (check_row_validity(grid, row, column)) {
                save_old_row(grid, row, player, cell);
                if (edge == LEFT_EDGE) {
                    do_left_edge(grid, row);
                } else {
                    do_right_edge(grid, row);
                }
                cell->occupancy = '.';
                return 0;
            }
            return 1;
        }
    }
}

/** Reverts the board to the state before the edge move was placed
 *
 * @param grid The game grid
 */
void revert_move(Grid *grid) {
    if (grid->oldColumnIndex != -1) {
        // last move was a vertical move
        for (int row = 0; row < grid->rows; ++row) {
            grid->cells[row][grid->oldColumnIndex].occupancy =
                    grid->oldColumn[row];
        }

    } else if (grid->oldRowIndex != -1) {
        // last move was a horizontal move
        for (int column = 0; column < grid->columns; ++column) {
            grid->cells[grid->oldRowIndex][column].occupancy =
                    grid->oldRow[column];
        }
    }
}

/** Reads a line from given file.
 *
 * @param file File to read from
 * @return returns the string which the file read
 */
char *read_line(FILE *file) {
    char *result = malloc(sizeof(char) * 1);
    int position = 0;
    int next = 0;
    int len = 0;
    while (true) {
        next = fgetc(file);
        if (next == EOF || next == '\n') {
            result[position] = '\0';
            return result;
        } else {
            len += 1;
            result = realloc(result, (len + 1) * sizeof(char));
            result[position++] = (char) next;
        }
    }
}

/** Returns the next player given the current.
 *
 * @param currentPlayer The current player
 * @return The next player
 */
char next_player(char currentPlayer) {
    if (currentPlayer == 'O') {
        return 'X';
    }

    return 'O';
}

/** Checks if the center of the grid is full
 *
 * @param grid The game grid
 * @return True if the game grid is full. False otherwise
 */
bool check_if_full(Grid *grid) {
    bool currentlyFull = true;
    for (int row = 1; row < grid->rows - 1; ++row) {
        for (int column = 1; column < grid->columns - 1; ++column) {
            Cell *cell = &(grid->cells[row][column]);
            if (cell->occupancy == '.') {
                currentlyFull = false;
            }
        }
    }

    return currentlyFull;
}

/** Gets the player type for a character
 *
 * @param grid The game board
 * @param player X or O
 * @return 0, 1 for computer players and H for human
 */
char get_player_type(Grid *grid, char player) {
    if (player == 'X') {
        return grid->xType;
    } else {
        return grid->oType;
    }
}

/** Counts the number of chars for an int */
int count_chars(int integer) {
    if (integer < 10) {
        return 1;
    } else if (integer > 9) {
        return 2;
    } else if (integer > 99) {
        return 3;
    } else if (integer > 999) {
        return 4;
    }

    return 0;
}

/** Checks whether a given save file is valid
 *
 * @param fileName The file to be checked
 * @return True if the savefile is valid, False otherwise
 */
int check_valid_file(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char *line = read_line(file);
    bool isValid = true;
    int rows;
    int columns;
    char nextPlayer;

    // checking length of row/col line
    if (sscanf(line, "%d %d", &rows, &columns) != 2) {
        return 1;
    } else if (strlen(line) > count_chars(rows) + count_chars(columns) + 1) {
        return 1;
    }

    // check row and col values
    if (rows == 0 || columns == 0 || rows < 3 || columns < 3) {
        return 1;
    }

    // check next player value
    line = read_line(file);
    if (sscanf(line, "%c", &nextPlayer) != 1) {
        return 1;
    } else if (strlen(line) > 1) {
        return 1;
    } else if (nextPlayer != 'X' && nextPlayer != 'O') {
        return 1;
    }

    isValid = check_valid_board(file, rows, columns);

    // ensure there are no more lines
    if (strlen(read_line(file)) > 0 && isValid == true) {
        return 1;
    }

    return isValid;
}

/** Checks if the board part of a save file is valid
 *
 * @param file The save file
 * @param rows The number of rows the board is supposed to have
 * @param columns The number of columns the board is supposed to have
 * @return 0 if the save file is valid, 1 otherwise
 */
int check_valid_board(FILE *file, int rows, int columns) {
    // check actual board
    for (int row = 0; row < rows; ++row) {
        char *line = read_line(file);
        // check line length
        if (strlen(line) != 2 * columns) {
            return 1;
        }

        for (int halfcol = 0; halfcol < 2 * columns; ++halfcol) {
            // need the corners to be empty
            if (halfcol == 0 || halfcol == 1 ||
                    halfcol == 2 * columns - 1 || halfcol == 2 * columns - 2) {
                if (row == 0 || row == rows - 1) {
                    if (line[halfcol] != ' ') {
                        return 1;
                    }
                }
            } else { //no corners
                if (halfcol % 2 == 0) { // is pointvalue
                    if (line[halfcol] - '0' < 0 || line[halfcol] - '0' > 9) {
                        return 1;
                    }
                } else { // is occupancy
                    if (line[halfcol] != '.' && line[halfcol] != 'O' &&
                            line[halfcol] != 'X') {
                        return 1;
                    }
                }
            }

        }
    }

    return 0;
}

/** Checks if the game is over, and displays the winner accordingly
 *
 * @param grid The game board
 * @param currentplayer The current player
 * @return True if the game is not over, False otherwise
 */
int check_game_over(Grid *grid) {
    bool notOver = true;

    if (check_if_full(grid)) {
        int playerXScore = get_score(grid, 'X');
        int playerOScore = get_score(grid, 'O');
        if (playerXScore > playerOScore) {
            fprintf(stdout, "Winners: X\n");
        } else if (playerXScore < playerOScore) {
            fprintf(stdout, "Winners: O\n");
        } else {
            fprintf(stdout, "Winners: O X\n");
        }
        fflush(stdout);
        notOver = false;
    }

    return notOver;
}

/** Check the number of args supplied are valid
 *
 * @param argc Number of args
 * @exit code 1 if number of args are not correct
 */
void check_num_of_args(int argc) {
    if (argc != 4) {
        fprintf(stderr, "Usage: push2310 typeO typeX fname\n");
        exit(INCORRECT_NUM_OF_ARGS);
    }
}

/** Checks if args contain correct player types
 *
 * @param argv argv
 * @exit code 2 if invalid player types supplied
 */
void check_player_types(char **argv) {
    char validCharacters[] = {'0', '1', 'H'};
    int playerOneValid = 0;
    int playerTwoValid = 0;

    for (int i = 0; i < 3; i++) {
        if (argv[1][0] == validCharacters[i]) {
            playerOneValid = 1;
        }
        if (argv[2][0] == validCharacters[i]) {
            playerTwoValid = 1;
        }
    }

    if (playerOneValid + playerTwoValid != 2) {
        fprintf(stderr, "Invalid player type\n");
        exit(INVALID_PLAYER_TYPE);
    }

}

/** Check if the argv args contains a valid file
 *
 * @param file The supplied file
 * @param argv argv
 * @exit code 3 if file is null
 * @exit code 4 if file contents are not valid
 */
void check_file_errors(FILE *file, char **argv) {
    if (file == NULL) {
        fprintf(stderr, "No file to load from\n");
        exit(CANT_READ_FROM_FILE);
    }

    if (check_valid_file(argv[3])) {
        fprintf(stderr, "Invalid file contents\n");
        exit(INVALID_FILE_CONTENTS);
    }
}

/** Handles human user input
 *
 * @param grid The game board
 * @return String of characters inputted by user
 * @exit code 5 if EOF encountered
 */
char *handle_user_input(Grid *grid) {
    printf("%c:(R C)> ", grid->currentPlayer);
    char *result = malloc(sizeof(char) * 1);
    int position = 0;
    int next = 0;
    int length = 0;

    while (true) {
        next = fgetc(stdin);
        if (next == EOF) {
            fprintf(stderr, "End of file\n");
            exit(END_OF_FILE);
        } else if (next == '\n') {
            result[position] = '\0';
            break;
        } else {
            length += 1;
            result = realloc(result, (length + 1) * sizeof(char));
            result[position++] = (char) next;
        }
    }

    return result;
}

/** Handles player movement
 *
 * @param grid The game board
 */
void move_human(Grid *grid) {
    int row;
    int column;

    while (true) {
        char *result = handle_user_input(grid);

        // for save game
        if (result[0] == 's' && strlen(result) != 1) {
            char filename[80];
            sscanf(result + 1, "%s", filename);
            save_game(grid, filename, grid->currentPlayer);
        } else if (sscanf(result, "%d %d", &row, &column) == 2) {
            break;
        }
    }

    if (!place_move(grid, row, column, grid->currentPlayer)) {
        grid->currentPlayer = next_player(grid->currentPlayer);
        draw_grid(grid, stdout);
    }
}


int main(int argc, char **argv) {
    check_num_of_args(argc);
    check_player_types(argv);
    FILE *file = fopen(argv[3], "r");
    check_file_errors(file, argv);

    // initialize the grid with values from the file
    Grid grid;
    alloc_grid(&grid, file, argv);

    if (check_if_full(&grid)) {
        fprintf(stderr, "Full board in load\n");
        return FULL_BOARD_ON_LOAD;
    }

    draw_grid(&grid, stdout);

    bool stillPlaying = true;

    // main game loop
    while (stillPlaying) {

        switch (get_player_type(&grid, grid.currentPlayer)) {
            case 'H':
                move_human(&grid);
                break;

            case '0':
                move_type_zero(&grid, grid.currentPlayer);
                grid.currentPlayer = next_player(grid.currentPlayer);
                draw_grid(&grid, stdout);
                break;

            case '1':
                move_type_one(&grid, grid.currentPlayer);
                grid.currentPlayer = next_player(grid.currentPlayer);
                draw_grid(&grid, stdout);
                break;
        }
        stillPlaying = check_game_over(&grid);
    }
    int c;
    while ((c = fgetc(stdin) != EOF)) {
        // run until EOF
    }
}
