/* CS 211 PA1: roman
 * Created for: aj654
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int val;
	val = atoi(argv[1]);
	while(val>0){

		if(val >=1000){
			printf("M");
			val = val - 1000;
		}
		if(val <1000 && val >=900){
			printf("CM");
			val = val - 900;
		}
		if(val<900 && val>=500){
			printf("D");
			val = val - 500;
		}
		if(val<500 && val>=400){
			printf("CD");
			val = val - 400;
		}
		if(val<400&&val>=100){
			printf("C");
			val = val - 100;
		}
		if(val<100&&val>=90){
			printf("XC");
			val = val - 90;
		}
		if(val<90&&val>=50){
			printf("L");
			val = val - 50;
		}
		if(val<50&&val>=40){
			printf("XL");
			val = val - 40;
		}
		if(val<40&&val>=10){
			printf("X");
			val=val-10;
		}
		if(val<10&&val>=9){
			printf("IX");
			val = val-9;
		}
		if(val<9&&val>=5){
			printf("V");
			val = val-5;
		}
		if(val<5&&val>=4){
			printf("IV");
			val=val-4;
		}
		if(val<4 && val>=1){
			printf("I");
			val=val-1;
		}


		

	}
printf("\n");

	return EXIT_SUCCESS;
}
