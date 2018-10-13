#include <stdio.h>
#include "deck.h"
#include "card.h"
#include "player.h"
#include "gofish.h"



int main(int args, char* argv[]) 
{
  shuffle();
char yesOrNo;


  while(!game_over(&user) || !game_over(&computer)){
      printUsers();
      user_play(&user);
      printUsers();
      computer_play(&computer);

  }

  if(game_over(&user)){
      printf("Player %d Wins! %d-%d", user.player_number, user.book_size, computer.book_size);
  }

  else if(game_over(&computer)){
      printf("Player %d Wins! %d-%d", computer.player_number, computer.book_size, user.book_size);

  }

  printf("Do you want to play again [Y/N]: ");
  scanf("%c", &yesOrNo);
  _Bool finish=1;
  while(finish) {
      if (yesOrNo == 'Y') {
        finish=0;

      } else if (yesOrNo == 'N') {
          printf("Exiting.");
          exit(0);
      } else
          printf("Please enter 'Y' or 'N'.");
  }
}


int printUsers(){
    print_card_list(&user);
    print_book(&user);
    print_book(&computer);
}
