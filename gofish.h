#ifndef GOFISH_H
#define GOFISH_H

/*
   Define any prototype functions
   for gofish.h here.
*/
int printUsers();

int resetGame();

int userTurn();

int computerTurn();

int gofish(struct player* target, char* rankDesire);
#endif
