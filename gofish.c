#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "card.h"
#include "player.h"
#include "gofish.h"


int main(int args, char *argv[]) {
    int booleanVal = 1;

    //initialize_player(&user);
    //initialize_player(&computer); 
    user.player_number = 1;
    computer.player_number = 2;

    while (booleanVal == 1) {

        user.card_list = (struct hand *) malloc(50 * sizeof(struct hand));
        computer.card_list = (struct hand *) malloc(50 * sizeof(struct hand));

        user.book_size = 0;
        computer.book_size = 0;
        shuffle();
        char yesOrNo;
        deal_player_cards(&user);
        deal_player_cards(&computer);

        while (game_over(&user) == 0 && game_over(&computer) == 0) {

            printUsers();
            userTurn(&user);

            if (user.hand_size == 0) {
                struct card nextCard = *(next_card());
                add_card(&user, &nextCard);
            }
            if (computer.hand_size == 0) {
                struct card nextCard = *(next_card());
                add_card(&computer, &nextCard);
            }

            printUsers();
            computerTurn(&computer);


            if (user.hand_size == 0) {
                struct card nextCard = *(next_card());
                add_card(&user, &nextCard);
            }
            if (computer.hand_size == 0) {
                struct card nextCard = *(next_card());
                add_card(&computer, &nextCard);
            }
        }

        if (game_over(&user)) {
            printf("Player %d Wins! %d-%d\n", user.player_number, user.book_size, computer.book_size);
        } else if (game_over(&computer)) {
            printf("Player %d Wins! %d-%d\n", computer.player_number, computer.book_size, user.book_size);

        }

        printf("Do you want to play again [Y/N]: ");
        scanf("%c", &yesOrNo);
        int finish = 1;
        while (finish == 1) {
            if (yesOrNo == 'Y') {
                finish = 0;
                resetGame();
            } else if (yesOrNo == 'N') {
                printf("Exiting.");
                booleanVal = 0;
                finish = 0;
            } else
                printf("Please enter 'Y' or 'N'.");
            scanf("%c", &yesOrNo);

        }
    }
    exit(0);
}


int printUsers() {
    print_card_list(&user);
    print_card_list(&computer);
    print_book(&user);
    print_book(&computer);
}

int resetGame() {
    reset_player(&user);
    reset_player(&computer);
}

int userTurn(struct player *target) {

    char *userRank;
    userRank = user_play(target);
    int compCardIndex = search(&computer, userRank);
    if (compCardIndex > 0) {
        int countSrc = playerTransferCards(&user, userRank);
        int count = transfer_cards(&computer, target, userRank);
        printf("\t- Player 2 has ");
        for (int i = 0; i < count - 1; i++) {
            printf("%s%c, ", fish[i].rank, fish[i].suit);
        }
        printf("%s%c\n", fish[count - 1].rank, fish[count - 1].suit);

        printf("\t- Player 1 has ");
        for (int i = 0; i < countSrc - 1; i++) {
            printf("%s%c, ", fishSrc[i].rank, fishSrc[i].suit);
        }
        printf("%s%c\n", fishSrc[countSrc - 1].rank, fishSrc[countSrc - 1].suit);
    } else {
        printf("\t- Player %d has no %s's\n", computer.player_number, userRank);
        gofish(target, userRank);
    }
    check_add_book(&user);
    printf("\t- Player 2's turn\n\n");
    return 0;
}

int computerTurn(struct player *target) {
    char *compRank;
    compRank = computer_play(target);
    int userCardCount = search(&user, compRank);
    if (userCardCount > 0) {
        int countSrc = playerTransferCards(&computer, compRank);

        int count = transfer_cards(&user, target, compRank);
        printf("\t- Player 1 has ");
        for (int i = 0; i < count - 1; i++) {
            printf("%s%c, ", fish[i].rank, fish[i].suit);
        }
        printf("%s%c\n", fish[count - 1].rank, fish[count - 1].suit);

        printf("\t- Player 1 has ");
        for (int i = 0; i < countSrc - 1; i++) {
            printf("%s%c, ", fishSrc[i].rank, fishSrc[i].suit);
        }
        printf("%s%c\n", fishSrc[countSrc - 1].rank, fishSrc[countSrc - 1].suit);
    } else {
        printf("\t- Player %d has no %s's\n", user.player_number, compRank);
        gofish(target, compRank);
    }
    check_add_book(&computer);
    printf("\t- Player 1's turn\n\n");
    return 0;
}


int gofish(struct player *target, char *rankDesire) {
    printf("\t- Go Fish, Player %d draws ", target->player_number);
    struct card nextCard = *(next_card());
    add_card(target, &nextCard);
    if (strcmp(nextCard.rank, rankDesire) == 0) {
        printf("the card they wanted! %s%c. Go again.\n", target->player_number, nextCard.rank,
               nextCard.suit);
        if (target->player_number == computer.player_number)
            computerTurn(target);
        else if (target->player_number == user.player_number)
            user_play(target);
    }

    if (target->player_number == user.player_number)
        printf("%s%c\n", nextCard.rank, nextCard.suit);
    else if (target->player_number == computer.player_number)
        printf("a card\n");

    return 0;
}

int playerTransferCards(struct player* target, char rank[2]){
    int count = 0;
    struct player *temp;
    temp = (struct player *) malloc(sizeof(struct player));
    temp->card_list = (struct card *) malloc(sizeof(struct card));
    *temp = *target;
    while (temp->card_list != NULL) {
        if (strncmp(temp->card_list->top.rank, rank, 2 * sizeof(char)) == 0) {

            fishSrc[count] = temp->card_list->top;
            count++;
        }
        temp->card_list = temp->card_list->next;
    }
    return count;
}
