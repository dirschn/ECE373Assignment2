#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include <time.h>
#include <string.h>

char cardArray[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K', 'A'}; //array of each rank 
char suitArray[4] = {"SCHD"}; //array of each suit
char card10[2] = {'1', '0'}; //array to handle 10 card
struct card fish[3]; //array to store transferred cards


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

    struct hand *iterator = target->card_list; //iterator to iterate through linked list
    struct hand *previous = NULL; //holds spot in linked list previous to that of iterator


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
    /* Creates and mallocs temporary player structure equal to target */
    struct player *temp; 
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *target;
    /* sets player number and prints it */
    int a = target->player_number;
    printf("Player %d's Hand - ", a);
    /* iterates through players hand and prints it out */
    for (int i = 0; i < target->hand_size; i++) {
        printf("%s%c ", temp->card_list->top.rank, temp->card_list->top.suit);
        temp->card_list = temp->card_list->next;
    }
    printf("\n");
}

void print_book(struct player *target) {
    /* creates temp target structure */
    struct player *temp = target;
    int a = temp->player_number;
    printf("Player %d's Book - ", a);
    /* iterates through target's book and prints it out */
    for (int i = 0; i < target->book_size; i++) {
        printf("%s ", temp->book[i]);
    }
    printf("\n");
}

char *check_add_book(struct player *target) {
    /* defines a card structure and char array of 2 */
    struct card book;
    static char rank[2];
    /* iterates through each card in the cardArray and then checks to see if there is four matches by using the search function */
    for (int i = 0; i < 13; i++) {
        /* if statement to check if cardArray is at the 1 then uses sprintf to make it into a 10 */
        if (cardArray[i] == '1')
            sprintf(rank, "%d", 10);
        else
            sprintf(rank, "%c", cardArray[i]);

        int count = search(target, rank);
       /*if it finds 4 of a kind then it copies the rank to the card structure and iterates 4 times to remove each suit for the found rank */
        if (count == 4) {
            strcpy(book.rank, rank);
            for (int j = 0; j < 4; j++) {
                book.suit = suitArray[j];
                remove_card(target, &book);
            }
	    /*copies the temporary card to the target card*/
            sprintf(target->book[target->book_size],"%s", &book.rank);
		
	    /*increases the target's book size*/
            target->book_size++;
            return rank;
        }

    }
    return '0';
}


int search(struct player *target, char rank[2]) {
    /*defining count and making temporary player structure*/
    int count = 0;
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *target;
    /*while the card list still has cards left if it finds a match then it increases the count and continues to the next card*/
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
    /*defining count and making temporary player structure*/
    int count = 0;
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *src;
    /*returns -1 if the card list is empty at the start*/
    if (temp->card_list == NULL)
        return -1;
   /*while the card list is not empty adds cards to destination and removes cards from source, increments count, and adds the cards to the fish array to be printed out*/
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
    /*if the target has a full book (7) then it triggers a game over*/
    if (target->book_size==7)
        return 1;
    else
        return 0;

}

int reset_player(struct player *target) {

    /*frees the malloc'd card list and sets the book array to 0*/
    free(target->card_list);
    memset(&target->book, 0, sizeof(target->book));

}

char *computer_play(struct player *target) {

    printf("Player 2's turn, enter a Rank: ");
    srand(time(NULL));
    int invalidrank = 0;
    char rank;
    static char rankReal[2];
    /*while the rank has not been validated it picks a random card from cardArray then searches to see if it is in the computers hand*/
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
    /*get input from user*/
    printf("Player 1's turn, enter a Rank: ");
    //fgets(c,sizeof(c),stdin);
    scanf("%s", &c);
    /*checks to see if input from user is valid*/
    while (search(target, c) == 0) {
        printf("Error-must have at least one card from rank to play \n");
        printf("Player 1's turn, enter a Rank: ");
        //fgets(c,sizeof(c),stdin);
        scanf("%s", &c);
    }
    return c;

}
