#ifndef PATH_H
#define PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include "util.h"
#include "deck.h"

#define MO "Mo"
#define V1 "V1"
#define V2 "V2"
#define DO "Do"
#define RI "Ri"
#define BARRIER "::"
#define NUM_CARDS 5


/** Enumeration of a hand of cards.*/
typedef enum Cards {
    A,
    B,
    C,
    D,
    E
} Cards;

/** Represents whether the process is a player or Dealer. **/
typedef enum ProcessType {
    PLAYER = 0,
    DEALER = 1
} ProcessType;


/** Represents a player and their state. **/
typedef struct Player {
    // how much money the player has
    int money;

    // the player ID
    int id;

    // which site the player is at
    int siteNumber;

    // how many times the player has visited the sites
    int countV1;
    int countV2;

    // the player's points
    int points;

    // the cards the player has collected
    int *cards;

    // the players position relative to the rest of the players
    // eg for 5 players, 0 means the player is in the front
    // 4 means the player is last so their move is next
    int position;

    // pipes containing file descriptors for communication
    int sendPipes[2];
    int receivePipes[2];

    // to communicate with players
    FILE *reader;
    FILE *writer;
} Player;

/** Representation of a site on the path.
 */
typedef struct Site {
    // type of site
    char *type;

    // max number of players the site can have
    int playerLimit;

    // array of playerIDs.
    int *playerIDs;

    // the number of players currently at the site
    int numPlayersCurrently;
} Site;

/** Represents the game path.
 */
typedef struct Path {
    // size of the path
    int size;

    // the number of players in the game
    int playersInGame;

    // array of sites on the path
    Site *sites;

    // array of player pointers
    Player **players;

    // the deck of cards for which the dealer can deal.
    // Only dealer has access.
    Deck *deck;
} Path;

int check_map_file(char *line, ProcessType processType);
int check_player_args(int argc, char **argv);
int next_player_to_move(Path *path);
void sig_handler(int signal);
int find_next_barrier(Path *path, int currentSiteID);
int check_if_most_cards(Path *path, Player *player);
int check_empty_cards(Path *path);
int player_b_next_move(Path *path, int playerId);
int check_input(char *line, Path *path, int playerId, char playerType);
int sum_cards(Player *player);
int player_a_next_move(Path *path, int playerId);
int check_if_last_player(Path *path, Player *player);
void game_over(Path *path, FILE *location);
int find_earliest(Path *path, int currentSiteID);
void start_player(int numPlayers, int id, Path *path, char playerType);
void print_player_details(Path *path, int playerId, FILE *location);
int do_ri(Deck *deck, Player *player);
int do_action(Path *path, int playerId);
int get_highest_score(Path *path, int siteNum);
void print_path(Path *path, FILE *file);
Path *allocate_path(char *line, int numPlayers);
int check_game_over(Path *path);
int calculate_total_score(Player *player);
Player *init_player(Path *path, int id);
void move_player(Path *path, int playerId, int steps, ProcessType processType);
int available(Site site);
void arrange_order_of_players(Path *path);
int next_player_to_move(Path *path);
#endif