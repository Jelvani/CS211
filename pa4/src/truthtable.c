/* CS 211 PA4
 * Created for: aj654
 */

/*************************
*	Alborz Jelvani		 *
*	 2020 Rutgers		 *
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

int main(int argc, char **argv)
{
	
	FILE* fc;
	char directive [12];
	int numIn =0; //# of input variables
	variable* inputs;
	int numOut = 0;
	variable* outputs;
	variable temps;
	strcpy(temps.name,"");
	temps.value = 0;
	temps.next = NULL;
	variable* head = &temps;
	/****************************************INITILIZATION***********************************/
	fc = fopen(argv[1],"r");//dont forget to close file
	if(fc==NULL){
		printf("No Valid File Specified!\n");
		return EXIT_FAILURE;
	}
	
	if(fscanf(fc,"%s",directive)==EOF){
		printf("Error\n");
	}
	
	if(strcmp(directive,"INPUT")==0){
		fscanf(fc,"%d",&numIn);
	}
	
		inputs = (variable*) malloc(numIn*sizeof(variable)); //allocate memory for variables
		reset(inputs,numIn); //initialize values to 0
		
	for(int i=0;i<numIn;i++){ //add input variable names into struct array
		fscanf(fc,"%16s",inputs[i].name);
		
	}
	
	if(fscanf(fc,"%s",directive)==EOF){//scan for output
		printf("Error\n");
	}
	
	if(strcmp(directive,"OUTPUT")==0){
		fscanf(fc,"%d",&numOut);
	}
	outputs = (variable*) malloc(numOut*sizeof(variable)); //allocate memory for output variables
	
	for(int i=0;i<numOut;i++){ //add output variable names into struct array
		fscanf(fc,"%16s",outputs[i].name);
		outputs[i].value = 0;
	}
	/***********************************END INITILIZATION***********************************/
	
	gate* gCurr = NULL;
	gate* gHead = NULL;
	gate* gPrev = NULL;

	char tempName1[17];
	char tempName2[17];
	char tempName3[17];
	int toggle = 1;
	int numGates = 0;
	while(fscanf(fc,"%s",directive)!=EOF){
	
		while(1){
			if(gCurr==NULL){
						gCurr = (gate*)malloc(sizeof(gate));
						if(!toggle){gPrev->next=gCurr;
						}
						gCurr->next=NULL;
						if(toggle){
							toggle=0;
							gHead=gCurr;
						}
						break;
					}else{
					
						gCurr=gCurr->next;
					}
				}
	
		if(strcmp(directive,"NOT")==0){
				gCurr->type = NOT;
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
			gCurr->inputs = (variable**)malloc(sizeof(variable*));
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				
				gCurr->outputs= returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
				
			}else if(strcmp(directive,"AND")==0){
				gCurr->type=AND;
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
				fscanf(fc,"%s",tempName3);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*2);
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->inputs[1] = returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->outputs= returnVar(tempName3,inputs,outputs,&temps, numIn,numOut,head);
					
				
			}else if(strcmp(directive,"OR")==0){
			gCurr->type=OR;
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
				fscanf(fc,"%s",tempName3);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*2);
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->inputs[1] = returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->outputs= returnVar(tempName3,inputs,outputs,&temps, numIn,numOut,head);
				
			}else if(strcmp(directive,"NAND")==0){
			gCurr->type=NAND;
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
				fscanf(fc,"%s",tempName3);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*2);
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->inputs[1] = returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->outputs= returnVar(tempName3,inputs,outputs,&temps, numIn,numOut,head);
				
			}else if(strcmp(directive,"NOR")==0){
			gCurr->type=NOR;
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
				fscanf(fc,"%s",tempName3);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*2);
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->inputs[1] = returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->outputs= returnVar(tempName3,inputs,outputs,&temps, numIn,numOut,head);
				
			}else if(strcmp(directive,"XOR")==0){	
			gCurr->type=XOR;								
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
				fscanf(fc,"%s",tempName3);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*2);
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->inputs[1] = returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
				gCurr->outputs= returnVar(tempName3,inputs,outputs,&temps, numIn,numOut,head);
				
			}else if(strcmp(directive,"DECODER")==0){
			gCurr->type=DECODER;
				char _temp[17];
				int __index = 0;
				
				fscanf(fc,"%d",&__index);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*__index);
				gCurr->size = __index;
				for(int i=0;i<__index;i++){
					fscanf(fc,"%s",_temp);
					gCurr->inputs[i] = returnVar(_temp,inputs,outputs,&temps, numIn, numOut,head);	//insert inputs of multiplexer into array
				}	
				
				gCurr->selectors = (variable**)malloc(sizeof(variable*)*pow(2,__index));
				for(int i=0;i<(int)pow(2,__index);i++){
					fscanf(fc,"%s",_temp);
					gCurr->selectors[i] = returnVar(_temp,inputs,outputs,&temps, numIn, numOut,head);	//insert selectors of multiplexer into array
				}	
				
			}else if(strcmp(directive,"MULTIPLEXER")==0){
				gCurr->type=MULTIPLEXER;
				char _temp[17];
				int __index = 0;
				
				fscanf(fc,"%d",&__index);
				gCurr->inputs = (variable**)malloc(sizeof(variable*)*pow(2,__index));
				gCurr->size = __index;
				for(int i=0;i<(int)pow(2,__index);i++){
					fscanf(fc,"%s",_temp);
					gCurr->inputs[i] = returnVar(_temp,inputs,outputs,&temps, numIn, numOut,head);	//insert inputs of multiplexer into array
				}	
				
				gCurr->selectors = (variable**)malloc(sizeof(variable*)*__index);
				for(int i=0;i<__index;i++){
					fscanf(fc,"%s",_temp);
					gCurr->selectors[i] = returnVar(_temp,inputs,outputs,&temps, numIn, numOut,head);	//insert selectors of multiplexer into array
				}	
				
				fscanf(fc,"%s",_temp);
				
				gCurr->outputs=returnVar(_temp,inputs,outputs,&temps, numIn, numOut,head);
				
			}else if(strcmp(directive,"PASS")==0){
				gCurr->type = PASS;
				fscanf(fc,"%s",tempName1);
				fscanf(fc,"%s",tempName2);
			gCurr->inputs = (variable**)malloc(sizeof(variable*));
				gCurr->inputs[0] = returnVar(tempName1,inputs,outputs,&temps, numIn,numOut,head);
				
				gCurr->outputs= returnVar(tempName2,inputs,outputs,&temps, numIn,numOut,head);
			}
			
			gPrev=gCurr;
			
			gCurr=gCurr->next;
			numGates=numGates+1;
			
		}
	
	gCurr=gHead;
	//printf("Num of Gates: %d\n",numGates);
	
	
	for(int i=0;i<(int)pow(2,numIn);i++){
		tobinary(inputs,numIn,i);
		/* Enter Computation functions for for inputs array*/
		
	for(int z=0;z<numGates;z++){
		
		switch (gCurr->type){
			case AND: 
				
				and(gCurr->inputs[0],gCurr->inputs[1],gCurr->outputs);
				break;
			case OR:
				
				or(gCurr->inputs[0],gCurr->inputs[1],gCurr->outputs);
				break;
			case NAND:
				
				nand(gCurr->inputs[0],gCurr->inputs[1],gCurr->outputs);
				break;
			case NOR:
				
				nor(gCurr->inputs[0],gCurr->inputs[1],gCurr->outputs);
				break;
			case XOR:
				
				xor(gCurr->inputs[0],gCurr->inputs[1],gCurr->outputs);
				break;
			case NOT:
				
				not(gCurr->inputs[0],gCurr->outputs);
				break;
			case PASS:
				
				pass(gCurr->inputs[0],gCurr->outputs);
				break;
			case DECODER:
				
				decoder(gCurr);
				break;
			case MULTIPLEXER:
				
				multiplexer(gCurr);
				break;
		}
		gCurr=gCurr->next;
		
		
	}
	gCurr=gHead;
		
		/***************END COMPUTATION*********************/
		ptable(inputs,numIn,outputs,numOut);		
	}
	
    return EXIT_SUCCESS;
}


void ptable(variable* inputs, int numIn,variable* outputs, int numOut){//prints line of values

	for(int i=0;i<numIn;i++){
		printf("%d ",inputs[i].value);
		
	}
	printf("|");
	for(int i=0;i<numOut;i++){
		printf(" %d",outputs[i].value);
		
	}
	printf("\n");
}

void reset(variable* inputs,int numIn){ //initialize all variable to value 0
	for(int i=0;i<numIn;i++){
		inputs[i].value=0;
	
	}
}
void tobinary(variable* inputs, int numIn, int index){ //convert all variables to binary of index number
	
	for(int i=numIn-1; i>=0;i--){
		inputs[i].value = index%2;
		
		
		index=index/2;
	}
}

int searchInputVars(variable* inputs, int numIn, char* input){ //returns index of input if found, -1
	for(int i = 0;i<numIn;i++){
		if(strcmp(inputs[i].name,input)==0){
		
			return i;
		}
	}
	return -1;
}
int searchOutputVars(variable* outputs, int numOut, char* output){ //returns index of input if found, -1
	for(int i = 0;i<numOut;i++){
		if(strcmp(outputs[i].name,output)==0){
			return i;
		}
	}
	return -1;
}
variable* returnVar(char* name,variable* inputs,variable* outputs,variable* temps, int numIn, int numOut,variable* head){

	temps = head;
	variable* prev = temps;
	int index = searchInputVars(inputs,numIn,name);
	
	if(index!=-1){//found variable
	
		return &inputs[index];
	}
	index = searchOutputVars(outputs,numOut,name);
	
	if(index!=-1){
		return &outputs[index];
	}
	//Else search temporary vars
	
	while(temps!=NULL){
	
		if(strcmp(temps->name,name)==0){	
			return temps;
		}
		prev = temps;
		temps = temps->next;
	}
	temps = (variable*) malloc(sizeof(variable));
	prev->next = temps;
	strcpy(temps->name,name);
	temps->next = NULL;
	temps->value = 0;
	
	return temps;
}
void not(variable* input,variable* output){
	if(strcmp(input->name,"1")==0){
		input->value = 1;
		
	}
	if(strcmp(input->name,"0")==0){
		input->value = 0;
		
	}
	if(strcmp(output->name,"_")!=0){
		
		if(input->value==0){
			output->value=1;
		}else{
			output->value=0;
		}
	}
	
}
void pass(variable* input,variable* output){
	if(strcmp(input->name,"1")==0){
		input->value = 1;
		
	}
	if(strcmp(input->name,"0")==0){
		input->value = 0;
		
	}
	if(strcmp(output->name,"_")!=0){
		
		output->value=input->value;
	}
	
}

void and(variable* input1,variable* input2,variable* output){

	if(strcmp(input1->name,"1")==0){
		input1->value = 1;
	}
	if(strcmp(input1->name,"0")==0){
		input1->value = 0;
	}
	if(strcmp(input2->name,"1")==0){
		input2->value = 1;
	}
	if(strcmp(input2->name,"0")==0){
		input2->value = 0;
	}
	if(strcmp(output->name,"_")!=0){
		
		output->value = input1->value*input2->value;
	}
	
}
void or(variable* input1,variable* input2,variable* output){

	if(strcmp(input1->name,"1")==0){
		input1->value = 1;
	}
	if(strcmp(input1->name,"0")==0){
		input1->value = 0;
	}
	if(strcmp(input2->name,"1")==0){
		input2->value = 1;
	}
	if(strcmp(input2->name,"0")==0){
		input2->value = 0;
	}
	if(strcmp(output->name,"_")!=0){
		
		if(input1->value+input2->value==2){
			output->value = 1;
		}else{
			output->value = input1->value+input2->value;
		}
	}
	
}
void nand(variable* input1,variable* input2,variable* output){

	if(strcmp(input1->name,"1")==0){
		input1->value = 1;
	}
	if(strcmp(input1->name,"0")==0){
		input1->value = 0;
	}
	if(strcmp(input2->name,"1")==0){
		input2->value = 1;
	}
	if(strcmp(input2->name,"0")==0){
		input2->value = 0;
	}
	if(strcmp(output->name,"_")!=0){
	
		if(input1->value*input2->value==1){
			output->value = 0;
		}else{
			output->value = 1;
		}
	}
}
void nor(variable* input1,variable* input2,variable* output){
	
	if(strcmp(input1->name,"1")==0){
		input1->value = 1;
	}
	if(strcmp(input1->name,"0")==0){
		input1->value = 0;
	}
	if(strcmp(input2->name,"1")==0){
		input2->value = 1;
	}
	if(strcmp(input2->name,"0")==0){
		input2->value = 0;
	}	
	if(strcmp(output->name,"_")!=0){
		
		if(input1->value+input2->value==0){
			output->value = 1;
		}else{
			output->value = 0;
		}
	}
}

void xor(variable* input1,variable* input2,variable* output){
	
	if(strcmp(input1->name,"1")==0){
		input1->value = 1;
	}
	if(strcmp(input1->name,"0")==0){
		input1->value = 0;
	}
	if(strcmp(input2->name,"1")==0){
		input2->value = 1;
	}
	if(strcmp(input2->name,"0")==0){
		input2->value = 0;
	}
	
	if(strcmp(output->name,"_")!=0){
		
		if(input1->value!=input2->value){
			output->value = 1;
		}else{
			output->value = 0;
		}
	}
	
}

int bintodec(variable** selectors,int size){
	int sum = 0;
	
	for(int i=0;i<size;i++){
		sum+=selectors[i]->value*(int)pow(2,size-1-i);
	}
	return sum;
	
}

void multiplexer(gate* gate){
	int size = gate->size;
	for(int i=0;i<(int)pow(2,size);i++){
		
		if(strcmp(gate->inputs[i]->name,"0")==0){
			gate->inputs[i]->value = 0;
		}
		if(strcmp(gate->inputs[i]->name,"1")==0){
			gate->inputs[i]->value = 1;
		}
	}
	for(int i=0;i<size;i++){
		
		if(strcmp(gate->selectors[i]->name,"0")==0){
			gate->selectors[i]->value = 0;
		}
		if(strcmp(gate->selectors[i]->name,"1")==0){
			gate->selectors[i]->value = 1;
		}
	}
	int select = bintodec(gate->selectors, size);
	if(strcmp(gate->outputs->name,"_")!=0){
	
		gate->outputs->value = gate->inputs[select]->value;
	}
}
void decoder(gate* gate){
	int size = gate->size;
	for(int i=0;i<size;i++){
		if(strcmp(gate->inputs[i]->name,"0")==0){
			gate->inputs[i]->value = 0;
		}
		if(strcmp(gate->inputs[i]->name,"1")==0){
			gate->inputs[i]->value = 1;
		}	
	}
	for(int i=0;i<(int)pow(2,size);i++){
		if(strcmp(gate->selectors[i]->name,"0")==0){
			gate->selectors[i]->value = 0;
		}
		if(strcmp(gate->selectors[i]->name,"1")==0){
			gate->selectors[i]->value = 1;
		}	
	}
	int select = bintodec(gate->inputs, size);
	for(int i=0;i<(int)pow(2,size);i++){
		if(strcmp(gate->selectors[i]->name,"_")!=0){
			
			gate->selectors[i]->value = 0;
		}
	}
	if(strcmp(gate->selectors[select]->name,"_")!=0){
			
			gate->selectors[select]->value =1;	
		}
	
}
