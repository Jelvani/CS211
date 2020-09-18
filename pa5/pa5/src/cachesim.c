/* CS 211 PA4
 * Created for: aj654
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum Policys {FIFO,LRU} policy;
typedef enum Types {direct,nway,full} type;

typedef struct node{
	long int address;
	struct node* next;
} Node;
typedef struct cachetype{
	long int cachesize; //num of bytes in cache
	long int blocksize; //num of bytes in a block
	long int setsize; //num of cachlines in a set aka "n"
	int blockoffset; //numbers of bits for block offset
	Node* fifo;//pointer to top of stack
	policy Policy;
	type Type;
} Cache;

/****FUNCTION PROTOTYPES*******/
int pow2check(long int num);
void directPrefetch0(FILE* fp,Cache* cache);
int logb2(long int n);
void initialize(Cache* cache);
int find(long int address, Cache* cache);
/*****************************/
long int address;
char operation;
int read=0;
int write=0;
int hit=0;
int miss=0;

int main(int argc, char **argv)
{
	/***DECLARE VARIABLES***/
	Cache cache;
	FILE *fp;
	/****PARSE INPUTS******/
	sscanf(argv[1],"%ld",&cache.cachesize);
	if(strcmp(argv[2],"direct")==0){
		cache.Type=direct;
	}else if(strcmp(argv[2],"assoc")==0){
		cache.Type=full;
	}else if(argv[2][5]==':'){
		sscanf(&argv[1][6],"%ld",&cache.setsize);
		cache.Type=nway;
	}
	
	if(strcmp(argv[3],"fifo")==0){
		cache.Policy=FIFO;
	}
	sscanf(argv[4],"%ld",&cache.blocksize);
	fp=fopen(argv[5],"r");
	/*********************************************/
	/************CHECK IF POWER OF 2**************/
	if(!(pow2check(cache.cachesize)||pow2check(cache.blocksize))){
		printf("Cachesize or blocksize not power of 2!");
		return 0;
	}
	if((cache.Type==nway)&&(pow2check(cache.setsize)==0)){
		printf("Setsize not power of 2!");
		return 0;
	}
	
	/********************************************/
	cache.blockoffset = logb2(cache.blocksize);
	cache.fifo = NULL;
	
	initialize(&cache);
	switch(cache.Type){
		case direct:
			directPrefetch0(fp,&cache);
			break;
		case nway:
			break;
		case full:
			break;
	}
    
    return EXIT_SUCCESS;
}

int pow2check(long int num){//returns 1 if power of 2, else 0;
	if((num!=0)&&(num&(num-1))==0){
		return 1;
	}
	return 0;
}
int logb2(long int n){//returns log base 2 of n
	int count = 0;
	while(n>1){
		n =n >> 1;
		count++;
	}
	return count;
}
void directPrefetch0(FILE* fp,Cache* cache){
	while(fscanf(fp,"%*s %c %lx",&operation,&address)!=EOF){
		if(find(address,cache)){//if found in cache
			hits++;
			printf("found\n");
		}else{
			miss++;
			reads++;
			
			printf("not found\n");
		}
		
	}
}
void initialize(Cache* cache){//initalizes cacheline addresses to 0
	for(int i=0;i<cache->cachesize/cache->blocksize;i++){
		cache->lines[i] = 0;
	}
}
int find(long int address, Cache* cache){//checks if address is in cacheline
	
	Node* pointer = NULL;
	address = address >> cache->blockoffset;
	if(cache->fifo==NULL){
		return 0;
	}
	pointer = cache->fifo;
	for(int i=0;i<cache->cachesize/cache->blocksize;i++){
		if(pointer->address==address){
			return 1;
		}else{
			
		}
	}
	return 0;
}
