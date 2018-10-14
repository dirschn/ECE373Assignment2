#include <stdio.h>
#include "deck.h"
#include "card.h"
#include "player.h"
#include "gofish.h"



int main(int args, char* argv[]) {
    int booleanVal=1;

    while (booleanVal==1) {
        shuffle();
        char yesOrNo;


        while ( !game_over(&user) || !game_over(&computer)) {
            printUsers();
            userTurn();
            printUsers();
            computer_play(&computer);

        }

        if (game_over(&user)) {
            printf("Player %d Wins! %d-%d", user.player_number, user.book_size, computer.book_size);
        } else if (game_over(&computer)) {
            printf("Player %d Wins! %d-%d", computer.player_number, computer.book_size, user.book_size);

        }

        printf("Do you want to play again [Y/N]: ");
        scanf("%c", &yesOrNo);
        _Bool finish = 1;
        while (finish) {
            if (yesOrNo == 'Y') {
                finish = 0;
                resetGame();
            } else if (yesOrNo == 'N') {
                printf("Exiting.");
                booleanVal=0;
            } else
                printf("Please enter 'Y' or 'N'.");
        }
    }
    exit(0);
}


int printUsers(){
    print_card_list(&user);
    print_book(&user);
    print_book(&computer);
}

int resetGame(){
    reset_player(&user);
    reset_player(&computer);
}

int userTurn(){
    char userRank=user_play(&user);
    int compCardIndex=search(&computer,userRank);
    if(compCardIndex>=0){
    transfer_cards(&computer, &user, userRank);
    }
    else{
        struct card newCard=gofish(&user);
        if(newRank==userRank){
            printf("Player %d got the card they wanted! %s%c. Go again.\n", user.player_number, );
        }
        else{

        }
    }
}

struct card gofish(struct player* target){

}