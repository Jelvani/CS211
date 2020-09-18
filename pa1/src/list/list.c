/* CS 211 PA1: list
 * Created for: aj654
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

	struct Node { 
		int num; 
		struct Node* next; 
	}; 

	char *str; 
	char command;
	int amtnums = 0;

	int current;
	struct Node* head = NULL;
	struct Node* curnode = NULL;
	struct Node* prevnode = NULL;
	struct Node* buffer = NULL;



	while(1){
		str= (char *) malloc(50);
		if(fgets(str,20,stdin)==NULL){
			break;
		}
		str[1] = '\0'; //add null char after first space
		command = str[0];
		str = str+2; //moves string to only integer

		current=atoi(str);


		if(command=='i'){	
			if(curnode==NULL){
				head = (struct Node*)malloc(sizeof(struct Node)); 
				head->num=current;
				head->next=NULL;
				curnode=head;
				prevnode=head;
				amtnums++;
			}else{

				if(amtnums==1){ //if 1 item is in linked list
					amtnums++;
					if(head->num==current){
						amtnums--;
						
					}else if(head->num>current){
						buffer= (struct Node*)malloc(sizeof(struct Node));
						buffer->num = current;
						buffer->next = head;
						head->next = NULL;
						head = buffer;

					}else if (head->num<current){
						buffer = (struct Node*)malloc(sizeof(struct Node));
						buffer->num = current;
						buffer->next = NULL;
						head->next = buffer;
					}

				}else{
				amtnums++;
					while(curnode!=NULL){
						
						if(curnode->num==current){ //if number exists break
							amtnums--;
							break;
						}else{
							if(curnode->num>current){ //if curnode is larger, then place number behind it
								if(curnode==head){ //if first place in linked list
								buffer = (struct Node*)malloc(sizeof(struct Node));
								buffer->num = current;
								head = buffer;
								head->next = curnode;
								}else{
								buffer = (struct Node*)malloc(sizeof(struct Node));
								buffer->num = current;
								buffer->next = curnode;
								prevnode->next = buffer;
								}
								break;
								
							}else{
								if(prevnode!=curnode){ //used only for first advancement
									prevnode=prevnode->next;	
								}
								curnode=curnode->next;
								if(curnode==NULL){ //if last node of list, append to end
									curnode = (struct Node*)malloc(sizeof(struct Node));
									curnode->num = current;
									curnode->next = NULL;
									prevnode->next = curnode;
									break;
								}
							}
							
						
						
						}
					}


				}
			}

		}else if(command=='d'){
		
		
		if(amtnums == 1){
			if(head->num==current){
				free(head);
				head=NULL;
				amtnums--;
			}
		}else{
			while(curnode!=NULL){
			
			
				if(curnode->num==current){
					if(prevnode==curnode){//if removing head
					
						head = curnode->next;
						free(prevnode);
						amtnums--;
						break;
						
					}
					prevnode->next = curnode->next;
					free(curnode);
					amtnums--;
					break;
				
				}else{
					if(prevnode!=curnode){ //used only for first advancement
							prevnode=prevnode->next;	
					}
					curnode=curnode->next;
				}
			
			}
}
		}
		
		curnode=head;
		prevnode=head;
		buffer = NULL;
		printf("%d :",amtnums);
		while(curnode!=NULL){
			printf(" %d",curnode->num);
			curnode=curnode->next;
		}
		prevnode=head;
		curnode=head;
		printf("\n");

	}
	return EXIT_SUCCESS;
}
