/* CS 211 PA1: palindrome
 * Created for: aj654
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	int length = strlen(argv[1]);
	int count = 0;

	for(int j=0;j<length;j++){ //get length of valid chars
	argv[1][j]=tolower(argv[1][j]);
		if(argv[1][j]<97||argv[1][j]>122){

		}else{
			count++;
		}
	}

char *original = (char*) malloc(count+1); //allocate memory for new string and null character
if(original==NULL){//Check of malloc succeeded in memory allocation
		printf("Oh no! Failed to allocate memory!!!!!!!!");
		return EXIT_FAILURE;
	}

int i = 0;
	
	
for(int j=0;j<length;j++){
		if(argv[1][j]<97||argv[1][j]>122){

		}else{
			original[i] = argv[1][j];
		i++;
		}
	}

original[i]= '\0';

i=0;
		
	int k = strlen(original)-1;
	while(i<k){
		if(original[i]!=original[k]){
			printf("no\n");
free(original);
			return EXIT_SUCCESS;
		}
		i++;
		k--;
	}
	printf("yes\n");
free(original);
	return EXIT_SUCCESS;
}
