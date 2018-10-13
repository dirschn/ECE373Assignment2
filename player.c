#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include <time.h>
#include <string.h>

char cardArray[13] = {'2','3','4','5','6','7','8','9','1','J','Q','K','A'};
char card10[2] = {'1','0'};

int add_card(struct player* target, struct card* new_card){

   /* Allocate space for new element */
   struct player* temp;  
   temp = (struct player*)malloc(sizeof(struct player));
   if (temp->card_list == NULL) { return -1; }

   /* Initialize new element */
   temp->card_list->top = *new_card;
   temp->card_list->next = target->card_list;
   
   /* Set list to temp, the new front of list*/
   target->card_list = temp->card_list;
   target->hand_size++;
   return 0;
}

int remove_card(struct player* target, struct card* old_card){

  struct hand* iterator = target->card_list;
  struct hand* previous = NULL; 
 

  if (iterator == NULL) { return -1; } /* Return false; list is empty */
   
   while (iterator->top.rank != *old_card->rank) { /* Check if we found the item */
     
     previous = iterator;               /* Store pointer to previous item */
     iterator = iterator->next;        /* Look at next item in list */
     
     if (iterator == NULL)             /* Check if end of list */
        return -1;                       /* Return false; didnâ€™t find item */
    }
    
    /* Found item; break out of loop */
    if (previous != NULL) 
       previous->next = iterator->next;	/* Remove item from list*/
    else {  
       target->card_list = iterator->next;         /* Set new front of list */
       
    }
    /* Free memory of item we are removing */
    free(iterator);
    return 0; /* Return true; we found and removed the item */
  
}

void print_card_list(struct player* target) {
     int a = target->player_number;
     printf("Player %d's Hand - ",a);
     for(int i =0; i<target->hand_size;i++) {
       printf("%s%c ",target->card_list->top.rank,target->card_list->top.suit);
       target->card_list = target->card_list->next;
     }
     printf("/n");
}

void print_book(struct player* target) {
  struct player* temp;
  temp = target;
  int a=temp->player_number;
  printf("Player %d's Book - ",a);
  for(int i=0;i<target->book_size;i++){
    printf("%c ",temp->book[i]);
  }
  printf("/n");
}

char check_add_book(struct player* target){

  struct player* temp;
  temp=target;
  for(int i=0;i<13;i++){

    int count = search(target,*(cardArray+i));
    if(count == 4){
      for(int j = 0;j<4;j++){
	remove_card(target,*(cardArray+i));
      }
      target->book[target->book_size]=cardArray[i];
      target->book_size++;
      if(cardArray[i]=='1')
	return card10;
      else
	return cardArray[i];
    }

  }
  return 0;
  
}

int search(struct player* target, char rank){

  struct player* temp;
  temp = target;
  int count = 0;
  while(temp->card_list != NULL){
 
    if(temp->card_list->top.rank[0] = rank){
      count++;
    }
    temp->card_list->top = temp->card_list->next->top;
  }
  if(count>0)
    return count;
  else
    return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank){

  struct player* from;
  from = src;
  int count = 0;

  while(from->card_list != NULL){
    if(from->card_list == NULL)
      return -1;
    if(from->card_list->top.rank[0] = rank){
      add_card(dest,rank);
      count++;
    }
    from->card_list->top = from->card_list->next->top;
  }
  return count;
  
}

int game_over(struct player* target){

  if(target->book[6] != (0 || NULL))
    return 1;
  else
    return 0;

}

int reset_player(struct player* target){

  free(target->card_list);
  memset(&target->book,0,sizeof(target->book));
  
}

char computer_play(struct player* target){

  srand(time(NULL));
  int invalidrank=0;
  char rank;
  while(invalidrank==0){

    rank=cardArray[rand()%13];

    if(search(target,rank)>=0);
    invalidrank=1;
  }
  return rank;

}

char user_play(struct player* target){

  char c;
  printf("Player 1's turn, enter a Rank:");
  c = getchar();

  while(search(target,c)==0){
    printf("Error-must have at least one card from rank to play\n");
    printf("Player 1's turn, enter a Rank:");
    c = getchar();
  }
   
  return c;

}
