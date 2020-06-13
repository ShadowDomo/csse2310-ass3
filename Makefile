.fake: all_targets
all_targets: 2310A 2310B 2310dealer

2310A: 2310A.c deck.c path.c util.c
	gcc -g 2310A.c deck.c path.c util.c -Wall -pedantic -std=gnu99 -o 2310A
2310B: 2310B.c deck.c path.c util.c
	gcc -g 2310B.c deck.c path.c util.c -Wall -pedantic -std=gnu99 -o 2310B
2310dealer: 2310dealer.c deck.c path.c util.c
	gcc -g 2310dealer.c deck.c path.c util.c -Wall -pedantic -std=gnu99 -o 2310dealer
