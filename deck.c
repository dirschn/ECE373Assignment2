#include "deck.h"
#include "player.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 51

/*initializes deck_instance and shuffles it*/
int shuffle() {
    printf("Shuffling deck...\n\n"); //print line shown in the examples
    int i, random[MAX * 2 + 1]; //initiate iterator and an array of random numbers for the cards to be swapped
    initializeDeck(); //call the method that initializes the deck

    srand(time(NULL)); //seed the rand() function using the system time

    for (i = 0; i < MAX * 2 + 1; i++) {
        random[i] = rand() % MAX; //fill the array with all the random numbers
    }
    moveCards(random); //call the function that will actually move and shuffle the deck
    return 0;
}

/*initialize deck_instance*/
int initializeDeck() {
    deck_instance.top_card = 51; //set the top card to the top of the array
    int count, i, suitIndex; //initialize variables required for the initialization process
    char suits[] = {"CHSD"}; //create an array with the suit values stored in it
    count = 0; //variable to count how many cards are added to the deck_instance
    for (i = 0; i < 52; i++) {
        suitIndex = count / 13; //the index of the suitArray used to set the suit of the current card is set
        deck_instance.list[i].suit = suits[suitIndex]; //set the suit of the current card 

	/*These if statements deal with setting all the numbered ranks*/
        if (i > 1 && i < 11) {
            sprintf(deck_instance.list[i].rank, "%d", i); 
        } else if (i > 14 && i < 24) {
            sprintf(deck_instance.list[i].rank, "%d", i - 13);
        } else if (i > 27 && i < 37) {
            sprintf(deck_instance.list[i].rank, "%d", i - 26);
        } else if (i > 40 && i < 50) {
            sprintf(deck_instance.list[i].rank, "%d", i - 39);
        } 

	/*Now to set the letter ranks*/
	else {
            switch (i) {

                case 0 :
                    sprintf(deck_instance.list[i].rank, "%c", 'J');
                    break;

                case 1 :
                    sprintf(deck_instance.list[i].rank, "%c", 'Q');
                    break;

                case 11 :
                    sprintf(deck_instance.list[i].rank, "%c", 'K');
                    break;

                case 12 :
                    sprintf(deck_instance.list[i].rank, "%c", 'A');
                    break;

                case 13 :
                    sprintf(deck_instance.list[i].rank, "%c", 'J');
                    break;

                case 14 :
                    sprintf(deck_instance.list[i].rank, "%c", 'Q');
                    break;

                case 24 :
                    sprintf(deck_instance.list[i].rank, "%c", 'K');
                    break;

                case 25 :
                    sprintf(deck_instance.list[i].rank, "%c", 'A');
                    break;


                case 26 :
                    sprintf(deck_instance.list[i].rank, "%c", 'J');
                    break;

                case 27 :
                    sprintf(deck_instance.list[i].rank, "%c", 'Q');
                    break;

                case 37 :
                    sprintf(deck_instance.list[i].rank, "%c", 'K');
                    break;

                case 38 :
                    sprintf(deck_instance.list[i].rank, "%c", 'A');
                    break;

                case 39 :
                    sprintf(deck_instance.list[i].rank, "%c", 'J');
                    break;

                case 40 :
                    sprintf(deck_instance.list[i].rank, "%c", 'Q');
                    break;

                case 50 :
                    sprintf(deck_instance.list[i].rank, "%c", 'K');
                    break;

                case 51 :
                    sprintf(deck_instance.list[i].rank, "%c", 'A');
                    break;
            }
        }
        count++; //increment the count at the end of the current card's initialization
    }
    return 0; 
}

/*This function does the real work of shuffling the cards by moving them around based on random numbers*/
int moveCards(int numbers[]) {
    struct card temp; //temporary card for switching the cards
    for (int i = 0; i < MAX * 2; i++) {
        temp = deck_instance.list[numbers[i]]; //set temp equal to the first card to be moved
        deck_instance.list[numbers[i]] = deck_instance.list[numbers[i + 1]]; //move the second card into the spot of the first card
        deck_instance.list[numbers[i + 1]] = temp; //move the first card back into list at the spot of the second card
    }
    return 0; //return 0 upon successful completion of function

}

/*Function to deal the cards to the player passed as an argument*/
int deal_player_cards(struct player *target) {
    for (int i = 0; i < 7; i++) {
        add_card(target, next_card()); //add the card given by nextCard() to the hand of the player given to addCard()
    }
    return 0; //return 0 upon successful completion of function
}

/*Function to return the next card on the deck and then remove the card from the deck*/
struct card *next_card() {
    struct card *nextCard; //initialize the card to be returned
    nextCard = &deck_instance.list[deck_instance.top_card]; //set the card instance equal to the top card of the deck
    deck_instance.top_card--; //change the top card of the deck
    return nextCard; //return the card
}

/*function to return the size of the deck*/
size_t deck_size() {
    return deck_instance.top_card + 1; //return the size of the deck
}


