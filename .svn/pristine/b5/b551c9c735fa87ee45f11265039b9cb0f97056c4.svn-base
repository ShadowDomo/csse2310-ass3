#include "util.h"

/** Exits the game with the error code.
 *
 * @param errorCode The error code to exit with.
 * @exit code 0 - No error
 * @exit code 1 - Incorrect number of args
 * @exit code 2 - Player count is invalid
 * @exit code 3 - Invalid player ID
 * @exit code 4 - Invalid path
 * @exit code 5 - Early game over
 * @exit code 6 - Communications error
 */
void player_exit(PlayerErrorCode errorCode) {
    switch (errorCode) {
        case INVALID_NUM_ARGS_PLAYER:
            fprintf(stderr, "Usage: player pcount ID");
            break;
        case INVALID_PLAYER_COUNT:
            fprintf(stderr, "Invalid player count");
            break;
        case INVALID_ID:
            fprintf(stderr, "Invalid ID");
            break;
        case PATH_ERROR:
            fprintf(stderr, "Invalid path");
            break;
        case EARLY_GAME_OVER:
            fprintf(stderr, "Early game over");
            break;
        case PLAYER_COMMUNICATION_ERROR:
            fprintf(stderr, "Communications error");
            break;
        case NO_ERROR_PLAYER:
            exit(0);
    }

    fprintf(stderr, "\n");
    fflush(stderr);

    exit(errorCode);
}

/** Exits the game with the error code. Reaps all children process attached.
 *
 * @param errorCode The error code to exit with.
 * @exit code 0 - no error
 * @exit code 1 - Incorrect number of args
 * @exit code 2 - Invalid deck file or contents
 * @exit code 3 - Invalid path file or contents
 * @exit code 4 - Error starting one of the players
 * @exit code 5 - Communications error
 */
void dealer_exit(DealerErrorCode errorCode) {
    switch (errorCode) {
        case INVALID_NUM_ARGS:
            fprintf(stderr, "Usage: 2310dealer deck path p1 {p2}");
            break;
        case INVALID_DECK_FILE:
            fprintf(stderr, "Error reading deck");
            break;
        case INVALID_PATH_FILE:
            fprintf(stderr, "Error reading path");
            break;
        case ERROR_STARTING_PLAYER:
            fprintf(stderr, "Error starting process");
            break;
        case COMMUNICATION_ERROR:
            fprintf(stderr, "Communications error");
            break;
        case NO_ERROR:
            break;
        case NORMAL_END:
            exit(NORMAL_END);
            break;
    }
    fprintf(stderr, "\n");
    fflush(stderr);

    wait(NULL);
    exit(errorCode);
}

/** Counts the number of chars for an int
 * param integer: the integer to have its characters counted.
 * Returns: the number of characters in the integer */
int count_chars(int integer) {
    int isNeg = 0;
    if (integer < 0) {
        isNeg = 1;
    }
    int real = abs(integer);
    if (real < 10) {
        return 1 + isNeg;
    } else if (real > 9) {
        return 2 + isNeg;
    } else if (real > 99) {
        return 3 + isNeg;
    } else if (real > 999) {
        return 4 + isNeg;
    } else if (real > 9999) {
        return 5 + isNeg;
    }

    return 0;
}

/** Reads a line from given file.
 *
 * @param file File to read from.
 * @return returns the string which the file read.
 */
char *read_line(FILE *file) {
    char *result = malloc(sizeof(char) * 1);
    int position = 0;
    int next = 0;
    int len = 0;
    while (true) {
        next = fgetc(file);
        if (next == EOF || next == '\n') {
            if (len == 0) {
                return "\a";
            }
            result[position] = '\0';
            return result;
        } else {

            len += 1;
            result = realloc(result, (len + 1) * sizeof(char));
            result[position++] = (char) next;

        }
    }
}


/** Creates lines with given size.
 *
 * @param numLines The number of lines to create.
 * @param width How wide to make the strings.
 * @return An array of created lines.
 * **/
char **make_empty_strings(int numLines, int width) {
    char **lines = malloc(sizeof(char *) * numLines);
    for (int i = 0; i < numLines; ++i) {
        lines[i] = malloc(sizeof(char) * 3 * width + 1);

        // we use 3 * width because each site is 3 characters
        for (int j = 0; j < 3 * width; ++j) {
            lines[i][j] = ' ';
        }
        lines[i][3 * width] = 0;
    }

    return lines;
}
