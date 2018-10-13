#include "deck.h"
#include <stdio.h>

int shuffle(){
	printf("Shuffling deck...\n\n");
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
