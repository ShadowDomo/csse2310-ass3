#include "2310A.h"


/** Player A program. **/
int main(int argc, char **argv) {
    check_player_args(argc, argv);

    char *trash;
    int numPlayers = (int) strtol(argv[1], &trash, 10);
    int playerID = (int) strtol(argv[2], &trash, 10);

    printf("^");
    fflush(stdout);

    // check path
    char *givenPath = read_line(stdin);
    check_map_file(givenPath, PLAYER);

    Path *path = allocate_path(givenPath, numPlayers);
    path->players = malloc(sizeof(Player *) * numPlayers);

    for (int i = 0; i < numPlayers; ++i) {
        path->players[i] = init_player(path, i);
    }
    arrange_order_of_players(path);

    start_player(numPlayers, playerID, path, 'B');

}