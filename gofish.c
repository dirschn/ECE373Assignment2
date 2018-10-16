#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "card.h"
#include "player.h"
#include "gofish.h"


int main(int args, char *argv[]) {
    int booleanVal = 1; //variable to help with deciding whether or not to play the game again or not

    //initialize_player(&user);
    //initialize_player(&computer); 
    

    while (booleanVal == 1) {
        
        user.player_number = 1; //set the player number for user
        computer.player_number = 2; //set the player number for computer
        user.card_list = (struct hand *) malloc(50 * sizeof(struct hand)); //allocate space for the user's hand
        computer.card_list = (struct hand *) malloc(50 * sizeof(struct hand)); //allocate space for the computer's hand
/*set book sizes and hand sizes to 0 at beginning of game*/
        user.book_size = 0;
        computer.book_size = 0;
	user.hand_size = 0;
	computer.hand_size = 0;

/*shuffle deck and deal cards to players*/
        shuffle();
        deal_player_cards(&user);
        deal_player_cards(&computer);
	
	

	/*actual game begins*/
        while (game_over(&user) == 0 && game_over(&computer) == 0) { //loop while neither user has 7 books

            printUsers(); //print the hand and books of the users
            userTurn(&user); //user's turn

            if (user.hand_size == 0 && deck_size() != 0) {
                struct card nextCard = *(next_card());
                add_card(&user, &nextCard);
            }
            if (computer.hand_size == 0 && deck_size() != 0) {
                struct card nextCard = *(next_card());
                add_card(&computer, &nextCard);
            }

            printUsers(); //print the hand and books of the users
            computerTurn(&computer); //computer's turn


            if (user.hand_size == 0 && deck_size() != 0) {
                struct card nextCard = *(next_card());
                add_card(&user, &nextCard);
            }
            if (computer.hand_size == 0 && deck_size() != 0) {
                struct card nextCard = *(next_card());
                add_card(&computer, &nextCard);
            }
        }

        if (game_over(&user)) { //if the user wins
            printf("Player %d Wins! %d-%d\n", user.player_number, user.book_size, computer.book_size); //print that the user wins and what the score is
        } else if (game_over(&computer)) { //if the computer wins
            printf("Player %d Wins! %d-%d\n", computer.player_number, computer.book_size, user.book_size); //print that the computer wins and what the score is

        }
	char yesOrNo; //variable used at end of game to decide if we play again or not
        printf("Do you want to play again [Y/N]: "); //ask user if the want to play again after end of game
        scanf("%c", &yesOrNo); //read input
        
        
            if (yesOrNo == 'Y') {
                resetGame(); //reset the game
            } else if (yesOrNo == 'N') {
                printf("Exiting."); //print the statement given in the examples
                booleanVal = 0; //break the while loop condition
            }
    }
    exit(0); //exit with code 0
}

/*function to print all the user information*/
int printUsers() {
    print_card_list(&user); //print the user's card list
    print_book(&user); //print the user's book list
    print_book(&computer); //print the computer's book list
}

/*function to facilitate resetting the game when playing again*/
int resetGame() {
    reset_player(&user); //reset the user
    reset_player(&computer); //reset the computer
}

/*function to perform the actions in the event of the user's turn*/
int userTurn(struct player *target) {

    char *userRank; //rank that the user uses
    userRank = user_play(target); //call user_play to find out what the user wants for their rank
    int compCard = search(&computer, userRank); //search to see if the computer has the rank 
    if (compCard > 0) { //if the computer has it
        int countSrc = playerTransferCards(&user, userRank); //find out how many cards the player has of that rank
        int count = transfer_cards(&computer, target, userRank); //find out how many cards the computer has of that rank
        printf("\t- Player 2 has ");
/*print out the list of cards the computer has of that rank*/
        for (int i = 0; i < count - 1; i++) {
            printf("%s%c, ", fish[i].rank, fish[i].suit);
        }
        printf("%s%c\n", fish[count - 1].rank, fish[count - 1].suit);

/*now print out the list of cards the user has for that rank*/
        printf("\t- Player 1 has ");
        for (int i = 0; i < countSrc - 1; i++) {
            printf("%s%c, ", fishSrc[i].rank, fishSrc[i].suit);
        }
        printf("%s%c\n", fishSrc[countSrc - 1].rank, fishSrc[countSrc - 1].suit);
    }
    else { //if the computer doesn't have the cards
        printf("\t- Player %d has no %s's\n", computer.player_number, userRank); //tell the player that the computer doesn't have the card
        gofish(target, userRank); //tell the player to go fish
    }
    check_add_book(&user);//check to see if the player has a book
    printf("\t- Player 2's turn\n\n"); 
    return 0; //return 0 upon successful completion of hte function
}

/*function to perform the actions in the event of the computer's turn*/
int computerTurn(struct player *target) {
    char *compRank; //rank that the computer chooses
    compRank = computer_play(target); //find out what rank the computer wants
    int userCardCount = search(&user, compRank); //search to see if the user has the rank
    if (userCardCount > 0) { //if the user has it
        int countSrc = playerTransferCards(&computer, compRank); //find out how many the computer has

        int count = transfer_cards(&user, target, compRank); //find out how many cards the user has
/*print out the cards the user had*/
        printf("\t- Player 1 has ");
        for (int i = 0; i < count - 1; i++) {
            printf("%s%c, ", fish[i].rank, fish[i].suit);
        }
        printf("%s%c\n", fish[count - 1].rank, fish[count - 1].suit);

/*print out the cards the computer has*/
        printf("\t- Player 2 has ");
        for (int i = 0; i < countSrc - 1; i++) {
            printf("%s%c, ", fishSrc[i].rank, fishSrc[i].suit);
        }
        printf("%s%c\n", fishSrc[countSrc - 1].rank, fishSrc[countSrc - 1].suit);
    } else { //if the user doesn't have any cards of that rank
        printf("\t- Player %d has no %s's\n", user.player_number, compRank); //tell the computer the user didn't have any
        gofish(target, compRank); //tell the computer to go fish
    }
    check_add_book(&computer); //check if the computer has any books
    printf("\t- Player 1's turn\n\n");
    return 0; //return 0 upon successful completion of the function
}

/*function to perform the actions of a gofish*/
int gofish(struct player *target, char *rankDesire) {
    printf("\t- Go Fish, Player %d draws ", target->player_number); //print that the player is going fish
    struct card nextCard = *(next_card()); //create the next card the player gets
    add_card(target, &nextCard); //add the card to the player's hand
    if (strcmp(nextCard.rank, rankDesire) == 0) { //if the card's rank is the same as what the player wanted
        printf("the card they wanted! %s%c. Go again.\n", nextCard.rank, nextCard.suit);
        if (target->player_number == computer.player_number){ //if the player is the computer
	    printUsers();
            computerTurn(target); //computer gets to go again
	}
        else if (target->player_number == user.player_number){ //if the player is the user
	    printUsers();
            user_play(target); //user gets to go again
	}
    }

    if (target->player_number == user.player_number) //if the user went fish
        printf("%s%c\n", nextCard.rank, nextCard.suit); //print out the card that was drawn
    else if (target->player_number == computer.player_number) //if the computer went fish
        printf("a card\n"); //only print "a card"

    return 0; //return 0 upon successful completion of the function
}

/*function to find the card the player taking cards has when the player takes cards from the other player*/
int playerTransferCards(struct player* target, char rank[2]){
    int count = 0;//cunt how many cards the player has
    struct player *temp; //temporary player 
    temp = (struct player *) malloc(sizeof(struct player)); //allocate space for the player
    temp->card_list = (struct card *) malloc(sizeof(struct card)); //allocate space for the player's card_list
    *temp = *target;//temp is now the same as target
    while (temp->card_list != NULL) {//loop until all the cards have been seen 
        if (strncmp(temp->card_list->top.rank, rank, 2 * sizeof(char)) == 0) {//if the card has the same rank

            fishSrc[count] = temp->card_list->top; //add it to an array of cards 
            count++; //increase the count
        }
        temp->card_list = temp->card_list->next; //go to the next card in the card list
    }
    return count;//return the count of cards
}
