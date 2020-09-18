/* CS 211 PA1: mexp
 * Created for: aj654
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>


long int** makematrix(int n){//function returns nxn matrix
	long int **original = (long int **)malloc(n*sizeof(long int *)); //allocate for first dimension
	if(original==NULL){
	printf("Error allocating memory!");
	return NULL;
	}
	
    for(int i =0;i<n;i++){ //allocate for second dimension
    	original[i] = (long int *)malloc(n*sizeof(long int));
    	if(original[i]==NULL){
		printf("Error allocating memory!");
		return NULL;
	}
    }
    
    return original;
}

int main(int argc, char **argv)
{
    FILE *file;
    file = fopen(argv[1], "r"); //open file in arg 1
   int n;
   int exp;
   
   fscanf(file,"%d",&n);//size of square matrix
    long int **original = makematrix(n); //allocate memory
    long int **buffer = makematrix(n); //allocate memory
    long int **answer = makematrix(n);
    if(original==NULL){ //if failed return
	printf("Error allocating memory!");
	return EXIT_FAILURE;
	}
	
    for(int i =0;i<n;i++){ //put data into matrix
    	for(int j=0;j<n;j++){
    		fscanf(file," %ld ",&original[i][j]);
    		answer[i][j] = original[i][j];
    		buffer[i][j] = 0;
    	}
    }
    fscanf(file," %d",&exp);


for(int z=0;z<exp-1;z++){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				buffer[i][k]+= answer[j][k]*original[i][j]; 	
			}	
		}
	}
	
	for(int i = 0;i<n;i++){ //print answers
	    for(int j=0;j<n;j++){
	    	answer[i][j]= buffer[i][j];
	    	buffer[i][j] = 0;
	    		
	    }
    }
}


for(int i = 0;i<n;i++){ //print answers
    	for(int j=0;j<n;j++){
			if(j==n-1){
			printf("%ld",answer[i][j]);
			break;
			}
    		printf("%ld ",answer[i][j]);
    		
    	}
	printf("\n");
    }
    return EXIT_SUCCESS;
}
