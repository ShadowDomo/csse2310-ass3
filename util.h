#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>


/** All error codes the dealer can send. **/
typedef enum ErrorCodes {
    NORMAL_END = 0,
    INVALID_NUM_ARGS = 1,
    INVALID_DECK_FILE = 2,
    INVALID_PATH_FILE = 3,
    ERROR_STARTING_PLAYER = 4,
    COMMUNICATION_ERROR = 5,

    NO_ERROR = -1
} DealerErrorCode;


/** All error codes the players can send. **/
typedef enum PlayerErrorCodes {
    INVALID_NUM_ARGS_PLAYER = 1,
    INVALID_PLAYER_COUNT = 2,
    INVALID_ID = 3,
    PATH_ERROR = 4,
    EARLY_GAME_OVER = 5,
    PLAYER_COMMUNICATION_ERROR = 6,

    NO_ERROR_PLAYER = -1
} PlayerErrorCode;

int count_chars(int integer);
void player_exit(int errorCode);
void dealer_exit(DealerErrorCode errorCode);

char *read_line(FILE *file);
char **make_empty_strings(int numLines, int width);

#endif
