/* CS 211 PA1: rle
 * Created for: aj654
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
	int length = strlen(argv[1]);
	char c;
	//int newlength =0;
	int currentcount = 0;
	int curpos =0;
	char *compressed = (char*) malloc(length+1);

	if(compressed==NULL){
		printf("Oh no! Failed to allocate memory!!!!!!!!");
		return EXIT_FAILURE;
	}

	for(int i =0;i<length;i++){
		c = argv[1][i];
		//printf("%c\n",c);
		currentcount=0;

		if(argv[1][i]>47 && argv[1][i]<58){
		printf("error\n");
		return EXIT_SUCCESS;
		}
		if(curpos+2>length){
			printf("%s\n",argv[1]);

			return EXIT_SUCCESS;
		}
		for(int j=i;j<length;j++){
			if(c!=argv[1][j]){
				i=j-1;
				compressed[curpos]=c;
				curpos++;
				curpos+=sprintf(compressed+curpos, "%d", currentcount);

				break;
			}else{
				currentcount++;
				if((j+1)>=length){
					compressed[curpos]=c;

					curpos++;
					curpos+=sprintf(compressed+curpos, "%d", currentcount);
					compressed[curpos]='\0';
					printf("%s\n",compressed);
					return EXIT_SUCCESS;
				}
			}
		}
	}
	compressed[curpos]='\0';
	printf("%s\n",compressed);
	return EXIT_SUCCESS;
}
