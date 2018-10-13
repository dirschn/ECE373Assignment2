#include "player.h"
#include <stdlib.h>
#include <stdio.h>

char cardArray[13] = {'2','3','4','5','6','7','8','9','10','J','Q','K','A'};

int add_card(struct player* target, struct card* new_card){

   /* Allocate space for new element */
   struct player* temp;  
   temp = (struct player.card_list*)malloc(sizeof(struct player.card_list));
   if (temp == NULL) { return -1; }

   /* Initialize new element */
   temp.card_list.top = new_card;
   temp.card_list.next = target.card_list.top;
   
   /* Set list to temp, the new front of list*/
   target.card_list = temp.card_list;
   target->card_list->size++;
   return 0;
}

int remove_card(struct player* target, struct card* old_card){

  struct player* iterator = target->card_list;
  struct player* previous = NULL; 
 

   if (iterator == NULL) { return -1; } /* Return false; list is empty */
   
   while (iterator->top != old_card) { /* Check if we found the item */
     
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
     struct player* temp;
     int a = temp->player_number;
     temp = target;
     while (temp != NULL) {
       printf("Player %d's Card_List -  %d", a, temp->card_list->top);
       temp = temp->card_list->next;
     }

}

void print_book(struct player* target) {
  struct player* temp;
  temp = target;
  int a=temp->player_number;
  for(int i=0;i<book_size;i++){
    printf("Player %d's Book - %d", a, temp->book[i]);
  }
}

char check_add_book(struct player* target){

  struct player* temp;
  temp=target;
  for(int i=0;i<13;i++){

    int count = search(target,cardArray[i]);
    if(count == 4){
      for(int j = 0;j<4;j++){
	remove_card(target,cardArray[i]);
      }
      target->book[book_size]=cardArray[i];
      target->book_size++;
    }

  }  
  
}

int search(struct player* target, char rank){

  struct player* temp;
  temp = target;
  int count = 0;
  while(temp->card_list->top != NULL){
 
    if(temp->card_list->top->rank = rank){
      count++;
    }
    temp->card_list->top = temp->card_list->next;
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

  while(from->card_list->top != NULL){
    if(from->card_list->top == NULL)
      return -1;
    if(temp->card_list->top->rank = rank){
      add_card(dest,rank);
      count++;
    }
    from->card_list->top = from->card_list->next;
  }
  return count;
  
}

int game_over(struct player* target){

  if(target->book[7] != NULL)
    return 1;
  else
    return 0;

}

int reset_player(struct player* target){

  for(int i=0;i<7;i++){
    target->book[i]==NULL:
  }

  free(target->card_list);

}

char computer_play(struct player* target){

  srand(time(NULL));
  boolean invalidrank = true;
  while(invalidrank){

    char=cardArray[rand()%13];

    if(search(target,char)>=0);
    invalidrank=false;
  }
  return rank;

}

char user_play(struct player* target){

  char c;
  printf("Player 1's turn, enter a Rank:")
  c = getchar();

  while(search(target,c)==0){
    printf("Error-must have at least one card from rank to play\n");
    printf("Player 1's turn, enter a Rank:");
    c = getchar();
  }
   
  return c;

}
