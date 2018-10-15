#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include <time.h>
#include <string.h>

char cardArray[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K', 'A'};
char suitArray[4] = {"SCHD"};
char card10[2] = {'1', '0'};
struct card fish[3];

/*
int initialize_player(struct player* target){
  target = (struct player*)malloc(sizeof(struct player));
  target->card_list = (struct hand*)malloc(50*sizeof(struct hand));
  return 0;
  }*/

int add_card(struct player *target, struct card *new_card) {

    /* Allocate space for new element */
    //if (temp->card_list == NULL) { return -1; }
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));

    /* Initialize new element */
    temp->card_list->top = *new_card;
    temp->card_list->next = target->card_list;

    /* Set list to temp, the new front of list*/
    target->card_list = temp->card_list;
    target->hand_size++;
    return 0;
}

int remove_card(struct player *target, struct card *old_card) {

    struct hand *iterator = target->card_list;
    struct hand *previous = NULL;


    if (iterator == NULL) { return -1; } /* Return false; list is empty */

    while (strcmp(iterator->top.rank, old_card->rank)) { /* Check if we found the item */

        previous = iterator;               /* Store pointer to previous item */
        iterator = iterator->next;        /* Look at next item in list */

        if (iterator == NULL)             /* Check if end of list */
            return -1;                       /* Return false; didnâ€™t find item */
    }

    /* Found item; break out of loop */
    if (previous != NULL)
        previous->next = iterator->next;    /* Remove item from list*/
    else {
        target->card_list = iterator->next;         /* Set new front of list */

    }
    /* Free memory of item we are removing */
    free(iterator);
    target->hand_size--;
    return 0; /* Return true; we found and removed the item */

}

void print_card_list(struct player *target) {
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *target;
    int a = target->player_number;
    printf("Player %d's Hand - ", a);
    for (int i = 0; i < target->hand_size; i++) {
        printf("%s%c ", temp->card_list->top.rank, temp->card_list->top.suit);
        temp->card_list = temp->card_list->next;
    }
    printf("\n");
}

void print_book(struct player *target) {
    struct player *temp = target;
    int a = temp->player_number;
    printf("Player %d's Book - ", a);
    for (int i = 0; i < target->book_size; i++) {
        printf("%s ", temp->book[i]);
    }
    printf("\n");
}

char *check_add_book(struct player *target) {

    struct card book;
    static char rank[2];
    for (int i = 0; i < 13; i++) {
        if (cardArray[i] == '1')
            sprintf(rank, "%d", 10);
        else
            sprintf(rank, "%c", cardArray[i]);


        int count = search(target, rank);
        if (count == 4) {
            strcpy(book.rank, rank);
            for (int j = 0; j < 4; j++) {
                book.suit = suitArray[j];
                remove_card(target, &book);
            }
            sprintf(target->book[target->book_size],"%s", &book.rank);

            target->book_size++;
            return rank;
        }

    }
    return '0';
}


int search(struct player *target, char rank[2]) {

    int count = 0;
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *target;

    while (temp->card_list != NULL) {

        if (strncmp(temp->card_list->top.rank, rank, 2 * sizeof(char)) == 0) {
            count++;
        }
        temp->card_list = temp->card_list->next;
    }
    if (count > 0)
        return count;
    else
        return 0;
}

int transfer_cards(struct player *src, struct player *dest, char rank[2]) {

    int count = 0;
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *src;

    if (temp->card_list == NULL)
        return -1;

    while (temp->card_list != NULL) {
        if (strncmp(temp->card_list->top.rank, rank, 2 * sizeof(char)) == 0) {

            add_card(dest, &temp->card_list->top);
            fish[count] = temp->card_list->top;
            remove_card(src, &temp->card_list->top);
            count++;
        }
        temp->card_list = temp->card_list->next;
    }

    return count;

}

int game_over(struct player *target) {

    if (target->book_size==7)
        return 1;
    else
        return 0;

}

int reset_player(struct player *target) {

    free(target->card_list);
    memset(&target->book, 0, sizeof(target->book));

}

char *computer_play(struct player *target) {

    printf("Player 2's turn, enter a Rank:");
    srand(time(NULL));
    int invalidrank = 0;
    char rank;
    static char rankReal[2];
    while (invalidrank == 0) {

        rank = cardArray[rand() % 13];
        if (rank == '1') {
            sprintf(rankReal, "%d", 10);
            if (search(target, rankReal) > 0) { invalidrank = 1; }
        } else {
            sprintf(rankReal, "%c", rank);
            if (search(target, rankReal) > 0) { invalidrank = 1; }
        }

    }
    printf("%s\n", rankReal);
    return rankReal;
}

char *user_play(struct player *target) {

    static char c[2];

    printf("Player 1's turn, enter a Rank:");
    //fgets(c,sizeof(c),stdin);
    scanf("%s", &c);

    while (search(target, c) == 0) {
        printf("Error-must have at least one card from rank to play\n");
        printf("Player 1's turn, enter a Rank:");
        //fgets(c,sizeof(c),stdin);
        scanf("%s", &c);
    }
    return c;

}
