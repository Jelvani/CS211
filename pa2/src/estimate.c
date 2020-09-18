/* PA2 estimate */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------Matrix Struct Here-----------------------------*/
typedef struct Matrix{//Struct for matrix
	int rows;
	int cols;
	long double** data;
}Matrix;
/*----------------------------Function Prototypes Here--------------------------*/
void makematrix(Matrix* mat);
void printmat(Matrix mat);
Matrix invert(Matrix* mat);
void multiplymat(Matrix* mat1,Matrix* mat2, Matrix* result );
void transpose(Matrix* mat);
void fillmatrixtrain(Matrix* matX,Matrix* matY,FILE* file);
void divide(Matrix *mat, int row, long double coeff);
void multiply(Matrix *mat, int row, long double coeff);
void subtract(Matrix *mat1,Matrix *mat2, int row1, int row2);
void cpystruct(Matrix* mat1,Matrix* mat2);
void fillmatrixdata(Matrix* matX,FILE* file);
/*------------------------------Main Method Here--------------------------------*/

int main(int argc, char **argv)
{
	FILE *ftrain;
	FILE *fdata;
	int k=0;
	int n=0;
	ftrain = fopen(argv[1], "r"); //open file of training data
	fdata = fopen(argv[2], "r"); //open file of attribute data
	char *cmd = malloc(6*sizeof(char));
	fscanf(ftrain, "%5s",cmd);
	if(strcmp(cmd,"train")==0){
		fscanf(ftrain,"%d",&k);
		fscanf(ftrain,"%d",&n);	
	}
	free(cmd);
	
	Matrix matX= {n,k+1};
	
	Matrix matY	= {n,1};
	Matrix inversed;
	Matrix ans1;
	Matrix matW;
	Matrix temp;
	makematrix(&matX); //matrix for attriutes. form: y= w0+x1w1+x2w2+...+xkwk
	makematrix(&matY); //nx1 matrix containing prices
	fillmatrixtrain(&matX,&matY,ftrain);//fill X and Y matrix with correct data
	Matrix matXt = matX;
	transpose(&matXt);
	
	multiplymat(&matXt,&matX,&temp);

	inversed = invert(&temp);
	
	multiplymat(&inversed,&matXt,&ans1);
	
	multiplymat(&ans1,&matY,&matW);
	
	/*********************/
	
	cmd = malloc(5*sizeof(char));
	fscanf(fdata, "%4s",cmd);
	
	if(strcmp(cmd,"data")==0){
		fscanf(fdata,"%d",&k);
		fscanf(fdata,"%d",&n);	
	}
	free(cmd);
	matX.rows=n;
	matX.cols=k+1;
	fillmatrixdata(&matX,fdata);
	Matrix answer;
	multiplymat(&matX,&matW,&answer);
	printmat(answer);
	
	
	for(int i =0;i<matX.rows;i++){ //free memory
		free(matX.data[i]);
	}
	for(int i =0;i<matW.rows;i++){ //free memory
		free(matW.data[i]);
	}
	for(int i =0;i<temp.rows;i++){ //free memory
		free(temp.data[i]);
	}
	for(int i =0;i<matY.rows;i++){ //free memory
		free(matY.data[i]);
	}
	for(int i =0;i<answer.rows;i++){ //free memory
		free(answer.data[i]);
	}
	for(int i =0;i<inversed.rows;i++){ //free memory
		free(inversed.data[i]);
	}
	for(int i =0;i<matXt.rows;i++){ //free memory
		free(matXt.data[i]);
	}
	
	fclose(ftrain);
	fclose(fdata);
	free(matXt.data);
	free(inversed.data);
	free(matW.data);
	free(matX.data);
	free(matY.data);
	free(answer.data);
	free(temp.data);
	
	return EXIT_SUCCESS;
}

/**********************/
/*  Functions Start  */
/*********************/

/*------------------------------------------------------------------------------*/


Matrix invert(Matrix* mat){//Inverts a matrix
	int n = mat->rows;
	Matrix identity = {n,n};
	makematrix(&identity);
	Matrix temp = {0,0};
	long double current1 = 0;
	long double current2 = 0;

	for(int i=0;i<n;i++){//initialize identity matrix with diagonal 1's
		identity.data[i][i] = 1;
	}

	for(int p=0;p<n;p++){
		current1 = mat->data[p][p];
		divide(mat,p,current1);
		divide(&identity,p,current1);

		for(int i=p+1;i<n;i++){
			current2 = mat->data[i][p];
			cpystruct(mat,&temp);
			multiply(&temp,p,current2);
			subtract(&temp,mat,p,i);
			cpystruct(&identity,&temp);

			multiply(&temp,p,current2);
			subtract(&temp,&identity,p,i);			
		}

	}
	for(int p=n-1;p>=0;p--){
		for(int i=p-1;i>=0;i--){
			current2 = mat->data[i][p];
			cpystruct(mat,&temp);
			multiply(&temp,p,current2);
			subtract(&temp,mat,p,i);
			cpystruct(&identity,&temp);
			multiply(&temp,p,current2);
			subtract(&temp,&identity,p,i);
		}
	}
	for(int i =0;i<temp.rows;i++){ //free memory
		free(temp.data[i]);
	}
	free(temp.data);
	return identity;

}
/*------------------------------------------------------------------------------*/
void cpystruct(Matrix* mat1,Matrix* mat2){//copies mat1 into mat2
	mat2->cols = mat1->cols;
	mat2->rows = mat1->rows;
	
	free(mat2->data);
	makematrix(mat2);
	for(int i =0;i<mat1->rows;i++){
		for(int j=0;j<mat1->cols;j++){
			mat2->data[i][j] = mat1->data[i][j];
			
		
		}
	}
}

/*------------------------------------------------------------------------------*/

void divide(Matrix *mat, int row, long double coeff){

	for(int i=0;i<mat->cols;i++){
		mat->data[row][i] = mat->data[row][i]/coeff;

	}
}

/*------------------------------------------------------------------------------*/
void multiply(Matrix *matrix, int row, long double coeff){

	for(int i=0;i<matrix->cols;i++){
		matrix->data[row][i] = matrix->data[row][i]*coeff;

	}
}

/*------------------------------------------------------------------------------*/
void subtract(Matrix *mat1,Matrix *mat2, int row1, int row2){//subtract row1 of mat1 from row2 of mat2

	for(int i=0;i<mat2->cols;i++){
		mat2->data[row2][i] = mat2->data[row2][i]-mat1->data[row1][i];

	}
}

/*------------------------------------------------------------------------------*/
void makematrix(Matrix* mat){//returns matrix of specified rows and cols in struct

	int n = mat->rows;
	int k = mat->cols;

	mat->data = (long double**) malloc(n*sizeof(long double*));
	if(mat->data==NULL){
		printf("Error allocating memory!");
		return;
	}

	for(int i =0;i<n;i++){ //allocate for second dimension
		mat->data[i] = (long double*)malloc(k*sizeof(long double));
		if(mat->data[i]==NULL){
			printf("Error allocating memory!");
			return;
		}
	}
}
/*------------------------------------------------------------------------------*/
void printmat(Matrix mat){//prints out matrix passed into parameter

	if(&mat==NULL){
		printf("Cannot print null matrix!");
		return;
	}
	int n = mat.rows;
	int k = mat.cols;

	for(int i=0; i<n;i++){
		for(int j=0;j<k;j++){
			printf("%.0Lf", mat.data[i][j]);

		}
		printf("\n");
	}
	

}

/*------------------------------------------------------------------------------*/
void multiplymat(Matrix* mat1,Matrix* mat2, Matrix* result ){//multiplies NxK with KxZ, returns NxZ matrix
	int n, k, z;
	long double temp = 0;
	n=mat1->rows;
	k=mat1->cols;
	z=mat2->cols;

	if(k!=mat2->rows){
		printf("Error! Matrix 1 and 2 cannot be multiplied!\n Matrix 1 has %d columns but Matrix 2 has %d rows. They must match!\n",k,mat2->rows);
		result = NULL; 
		return;
	}
	result->rows=n;
	result->cols=z;

	makematrix(result);//allocate memory for answer (KxZ matrix)

	for(int i=0;i<n;i++){
		for(int j=0; j<z;j++){
			for(int x =0; x<k;x++){
				temp+=(mat1->data[i][x])*(mat2->data[x][j]);
			}
			result->data[i][j] = temp;
			temp = 0;
		}
	}

}
/*------------------------------------------------------------------------------*/

void transpose(Matrix* mat){ //returns transposed KxN matrix
	int n = mat->rows;
	int k = mat->cols;
	Matrix temp = {k,n};
	makematrix(&temp);
	for(int i=0;i<k;i++){
		for(int j=0;j<n;j++){
			temp.data[i][j] = mat->data[j][i];
		}
	}
	*mat = temp;
	
}
/*------------------------------------------------------------------------------*/
void fillmatrixtrain(Matrix* matX,Matrix* matY,FILE* file){//inserts data from file into attributre matrix X and price vector Y

	int n = matX->rows;
	int k = matX->cols;

	for(int i=0; i<n;i++){
		for(int j=0;j<k;j++){
			if(j==0){
				matX->data[i][0] = 1;

			}else{
				fscanf(file, "%Lf",&matX->data[i][j]);
			}
		}

		fscanf(file, "%Lf",&matY->data[i][0]);
	}
}
/*------------------------------------------------------------------------------*/
void fillmatrixdata(Matrix* matX,FILE* file){//inserts data from file into attributre data matrix X

	int n = matX->rows;
	int k = matX->cols;
	
	for(int i=0; i<n;i++){
		for(int j=0;j<k;j++){
			if(j==0){
				matX->data[i][0] = 1;

			}else{
				fscanf(file, "%Lf",&matX->data[i][j]);
			}
		}

	}
}
/*------------------------------------------------------------------------------*/
