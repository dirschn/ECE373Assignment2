#include "deck.h"
#include "player.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 51
/*
int main(void){
    shuffle();

    for(int i=0; i<=MAX; i++){
        printf("%s%c\n", deck_instance.list[i].rank, deck_instance.list[i].suit);
    }

    deal_player_cards(&user);
    deal_player_cards(&computer);
    return 0;
}
*/
int shuffle(){
	printf("Shuffling deck...\n\n");
	int i, random[MAX*2+1];
	initializeDeck();

    srand(time(NULL));

    for(i =0; i < MAX*2+1; i++) {
        random[i] = rand() % MAX;
    }
    moveCards(random);
    return 0;
}

int initializeDeck(){
    deck_instance.top_card=51;
    int count, i,suitIndex;
    char suits[]={"CHSD"};
    count=0;
    for(i=0; i<52; i++){
        suitIndex=count/13;
        deck_instance.list[i].suit=suits[suitIndex];
        if(i>1 && i<11){
            sprintf(deck_instance.list[i].rank, "%d", i);
        }
        else if(i>14 && i<24){

            sprintf(deck_instance.list[i].rank, "%d", i-13);
        }
        else if(i>27 && i<37){

            sprintf(deck_instance.list[i].rank, "%d", i-26);
        }
        else if(i>40 && i<50){

            sprintf(deck_instance.list[i].rank, "%d", i-39);
        }

        else{
            switch(i) {

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
        count++;
    }
}

int moveCards(int numbers[]){
    struct card temp;
    for(int i=0; i<MAX*2; i++){
        temp=deck_instance.list[numbers[i]];
        deck_instance.list[numbers[i]]=deck_instance.list[numbers[i+1]];
        deck_instance.list[numbers[i+1]]=temp;
    }

}

int deal_player_cards(struct player* target){
    for(int i=0; i<7; i++){
        add_card(target, &deck_instance.list[deck_instance.top_card]);
        deck_instance.top_card--;
    }
}

struct card* next_card(){
    struct card* nextCard;
    nextCard=&deck_instance.list[deck_instance.top_card];
    return nextCard;
}

size_t deck_size(){
    return deck_instance.top_card+1;
}


