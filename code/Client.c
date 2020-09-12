#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Header.h"

int main()
{

int M, N, key;
float NZperc, NGperc;
struct Matrix *COOMatrix=NULL, *CSRMatrix=NULL, *CSCMatrix=NULL, *MulCOOMatrix=NULL;
int CountOfNZE, CountOfNGE, NZCountInMultipl;
int r1, k1, r2, k2;
srand(time(0));
do
{
	printf("\n----MENU----\n1 Generate Matrix in COO format (Problem a)\n2 Transform the COO format matrix to CSR format (Problem b)\n");
	printf("3 Transform the COO format matrix to CSC format (Problem b)\n");
	printf("4 Multiplication of matrix in CSR format with matrix in CSC format (Problem c)\n");
	printf("5 Row Transformation on CSC matrix (Problem d)\n6 Print Matrix (Problem e)\n7 Quit\nEnter your choice: ");
	scanf("%d", &key);
	switch(key)
	{
		case 1:
			printf("\nEnter no. of rows and no. of columns in matrix: ");
			scanf("%d %d", &M, &N);
			printf("Enter density of non-zero entries in matrix: ");
			scanf("%f", &NZperc);
			printf("Enter percentage of negative elements in matrix: ");
			scanf("%f", &NGperc);
			if(0<M && M<=150 && 0<N && N<=100 && 0<=NZperc && NZperc<=100 && 0<=NGperc && NGperc<=NZperc) //Input validation
			{
				GenerateCOOMatrix((struct Matrix**) &COOMatrix, M, N, NZperc, NGperc);
				if(COOMatrix!=NULL) PrintCOOMatrixInCOO(COOMatrix);
			}
			else
			{
				printf("\nInvalid input! Input constraints violated.\n");
			}
			break;
		case 2:
			if(COOMatrix!=NULL)
			{
				COOto_CSR_CSC((struct Matrix**) &CSRMatrix, (struct Matrix*)COOMatrix, 1);
				if(CSRMatrix!=NULL) PrintCSRMatrixInCSR((struct Matrix*) CSRMatrix);
			}
			else
				printf("\nCOO matrix does not exist! Please generate COO matrix.\n");
			break;
		case 3:
			if(COOMatrix!=NULL)
			{
				COOto_CSR_CSC((struct Matrix**) &CSCMatrix, (struct Matrix*)COOMatrix, 0);
				if(CSCMatrix!=NULL) PrintCSCMatrixInCSC((struct Matrix*) CSCMatrix);
			}
			else
				printf("\nCOO matrix does not exist! Please generate COO matrix.\n");
			break;
		case 4:
			if(CSRMatrix!=NULL && CSCMatrix!=NULL)
			{
				MultiplyCSRandCSC((struct Matrix**) &MulCOOMatrix, (struct Matrix*) CSRMatrix, (struct Matrix*) CSCMatrix);
				if(MulCOOMatrix!=NULL) PrintCOOMatrixInCOO((struct Matrix*) MulCOOMatrix);
			}
			else
				printf("\nEither CSR matrix or CSC matrix or both matrices do not exist! Please generate CSR and CSC matrices.\n");
			break;
		case 5:
				if(CSCMatrix!=NULL)
				{
					printf("Enter row indices (starts from 0) and multiplication factors < k1 r1 k2 r2 >: ");
					scanf("%d %d %d %d", &k1, &r1, &k2, &r2);
					if(0<=r1 && r1<=CSCMatrix->M && 0<=r2 && r2<=CSCMatrix->M)  //Input validation
					{
						CSCMatrix=RowTransformation(CSCMatrix, r1, k1, r2, k2);
						if(CSCMatrix!=NULL) PrintCSCMatrixInCSC((struct Matrix*) CSCMatrix);
					}
					else
						printf("\nRow index out of bound! Please enter the valid row indices (row index starts from 0).\n");
				}
				else
					printf("\nCSC matrix does not exist! Please generate CSC matrix.\n");
						break;
		case 6:
			do
			{
				printf("\n----PRINT MENU----\n61 Original COO Matrix\n62 CSR Matrix\n63 CSC Matrix\n64 Multipication Result COO Matrix\n");
				printf("65 Back to Main Menu\n");
				printf("Enter your choice: ");
				scanf("%d", &key);
				switch(key)
				{
					case 61:
									if(COOMatrix==NULL) printf("\nCannot print! Matrix does not exist.\n");
									else if(COOMatrix->M<20 && COOMatrix->N<20) PrintCOOMatrix(COOMatrix);
									else printf("\nCannot print! Matrix size should be smaller than 20X20.\n");
									break;
					case 62:
									if(CSRMatrix==NULL) printf("\nCannot print! Matrix does not exist.\n");
									else if(CSRMatrix->M<20 && CSRMatrix->N<20) PrintCSRMatrix(CSRMatrix);
									else printf("\nCannot print! Matrix size should be smaller than 20X20.\n");
									break;
					case 63:
									if(CSCMatrix==NULL) printf("\nCannot print! Matrix does not exist.\n");
									else if(CSCMatrix->M<20 && CSCMatrix->N<20) PrintCSCMatrix(CSCMatrix);
									else printf("\nCannot print! Matrix size should be smaller than 20X20.\n");
									break;
					case 64:
									if(MulCOOMatrix==NULL) printf("\nCannot print! Matrix does not exist.\n");
									else if(MulCOOMatrix->M<20 && MulCOOMatrix->N<20) PrintCOOMatrix(MulCOOMatrix);
									else printf("\nCannot print! Matrix size should be smaller than 20X20.\n");
					 				break;
					case 65: break;
					default: printf("\nInvalid choice!\n");
				}
			}while(key!=65);
			break;
		case 7:
				Matrix_free(COOMatrix);
				Matrix_free(CSRMatrix);
				Matrix_free(CSCMatrix);
				Matrix_free(MulCOOMatrix);
			break;
		default:
			printf("\nInvalid choice!\n");
	}
}while(key!=7);
return 0;
}
