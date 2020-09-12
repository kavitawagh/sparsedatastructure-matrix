#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Header.h"

//Get integer count from percentage
int GetCountFromPerc(float Perc, int Total)
{
  return (int)((Perc/100.0)*Total+0.5);
}

//Select element randomly from array and replace it with element at the end of array.
int ShuffleSequence(int * Seq, int RangeStart, int RangeEnd, int ReqCount)
{
  int TotalCount=RangeEnd-RangeStart+1;
  int temp=0,i;
  int j=0, l=0;
  for(i=RangeEnd;i>RangeEnd-ReqCount;i--)
  {
      int RandomNum=rand()%(TotalCount-l);
      temp=Seq[RangeStart+RandomNum];
      Seq[RangeStart+RandomNum]=Seq[i];
      Seq[i]=temp;
      l++;
  }
  return RangeEnd-ReqCount+1;
}

//Get distinct random numbers within specified range of integers.
int GetDistinctRandomNumbers(int * Seq, int RangeStart, int RangeEnd, int ReqCount)
{
  int TotalCount=RangeEnd-RangeStart+1;
  int i;
  for(i=0;i<TotalCount;i++)
      Seq[i]=RangeStart+i;
  return ShuffleSequence(Seq, RangeStart, RangeEnd, ReqCount);
}

//Set non zero entries in matrix
void SetMatrixEntries(struct Matrix* COOMatrix, int *NZElemIndex, int StartIndex, int EndIndex, int m)
{
	int i, j=0;
	for(i=StartIndex;i<=EndIndex;i++)
	{
		COOMatrix->RowIndx[j]=NZElemIndex[i]/m;
		COOMatrix->ColIndx[j]=NZElemIndex[i]%m;
		COOMatrix->Data[j]=rand()%1000;
		j++;
	}
}

//Make some entries in matrix negative
void SetNGEntriesInMatrix(struct Matrix * COOMatrix, int* NZElemIndex, int StartIndex, int CountOfNGE, int CountOfNZE, int m)
{
	int i, j;
	for(i=StartIndex;i<StartIndex+CountOfNGE;i++)
	{
	    for(j=0;j<CountOfNZE;j++)
	    {
    		if(COOMatrix->RowIndx[j]==NZElemIndex[i]/m && COOMatrix->ColIndx[j]==NZElemIndex[i]%m)
    		{
    		   COOMatrix->Data[j]=COOMatrix->Data[j]*(-1);
    		   break;
    		}
	    }
	}
}

//Sort matrix entries on the indices of Row/Column.
void BubbleSortCOO(struct Matrix* COOMatr, int* indx)
{
  int i,j, temp;
  for(i=0; i<COOMatr->CountOfNZE;i++)
  	for(j=0; j<COOMatr->CountOfNZE-1; j++)
  		if(indx[j]>indx[j+1])
  		{
  			temp=COOMatr->Data[j];
  			COOMatr->Data[j]=COOMatr->Data[j+1];
  			COOMatr->Data[j+1]=temp;

  			temp=COOMatr->RowIndx[j];
  			COOMatr->RowIndx[j]=COOMatr->RowIndx[j+1];
  			COOMatr->RowIndx[j+1]=temp;

  			temp=COOMatr->ColIndx[j];
  			COOMatr->ColIndx[j]=COOMatr->ColIndx[j+1];
  			COOMatr->ColIndx[j+1]=temp;
  		}
}

//Generate matrix in COO format
void GenerateCOOMatrix(struct Matrix **COOMatrix, int M, int N, float NZperc, float NGperc)
{
	int *NZElemIndex=NULL;
	int CountOfNZE, CountOfNGE;
	CountOfNZE=GetCountFromPerc(NZperc, M*N);
	CountOfNGE=GetCountFromPerc(NGperc, M*N);

	if(NZElemIndex!=NULL) free(NZElemIndex);
	NZElemIndex=(int*)malloc((M*N)*sizeof(int));
	int StartIndex=GetDistinctRandomNumbers(NZElemIndex, 0, M*N-1, CountOfNZE);

  (*COOMatrix)=Matrix_alloc((*COOMatrix), CountOfNZE, CountOfNZE, CountOfNZE);
	(*COOMatrix)->M=M;
	(*COOMatrix)->N=N;
	(*COOMatrix)->CountOfNZE=CountOfNZE;
	SetMatrixEntries((*COOMatrix), (int*) NZElemIndex, StartIndex, StartIndex+CountOfNZE-1, N);
	StartIndex=ShuffleSequence(NZElemIndex, (M*N)-CountOfNZE, M*N-1, CountOfNGE);
	SetNGEntriesInMatrix((*COOMatrix), (int*) NZElemIndex, StartIndex, CountOfNGE, CountOfNZE, N);
	BubbleSortCOO((*COOMatrix), (*COOMatrix)->ColIndx); //check  if sorting is stable and optimize the sort
	BubbleSortCOO((*COOMatrix), (*COOMatrix)->RowIndx);
}

//Convert COO format matrix in CSR or CSC
void COOto_CSR_CSC(struct Matrix **CSR_CSC_Matrix, struct Matrix *COOMatrix, int CSR /*1:Convert to CSR  0: Convert to CSC*/)
{
  int *ResultIndx1, *ResultIndx2, *COOIndex1, *COOIndex2, CountRC;
  struct Matrix *CSRMatrix, *CSCMatrix;

  if(CSR)
  {
    CSRMatrix=Matrix_alloc(*CSR_CSC_Matrix, COOMatrix->CountOfNZE, CountRC+1, COOMatrix->CountOfNZE);
    (*CSR_CSC_Matrix)=CSRMatrix;
    ResultIndx1=(*CSR_CSC_Matrix)->ColIndx;
    ResultIndx2=(*CSR_CSC_Matrix)->RowIndx;
    CountRC=COOMatrix->M;
    COOIndex1=COOMatrix->ColIndx;
    COOIndex2=COOMatrix->RowIndx;
  }
  else
  {
    CSCMatrix=Matrix_alloc(*CSR_CSC_Matrix, COOMatrix->CountOfNZE, COOMatrix->CountOfNZE, CountRC+1);
    (*CSR_CSC_Matrix)=CSCMatrix;
    ResultIndx1=(*CSR_CSC_Matrix)->RowIndx;
    ResultIndx2=(*CSR_CSC_Matrix)->ColIndx;
    CountRC=COOMatrix->N;
    COOIndex1=COOMatrix->RowIndx;
    COOIndex2=COOMatrix->ColIndx;
  }
  if(COOMatrix->CountOfNZE>0)
  {
    BubbleSortCOO(COOMatrix, COOIndex1);
    BubbleSortCOO(COOMatrix, COOIndex2);

  	int i=0, j=0;
  	ResultIndx2[0]=0;
  	for(j=1;j<CountRC;j++)
  	{
  		while(COOIndex2[i]<=j-1 && i<COOMatrix->CountOfNZE) i++;
    			ResultIndx2[j]=i;
  	}
  	for(i=0;i<COOMatrix->CountOfNZE;i++)
  	{		(*CSR_CSC_Matrix)->Data[i]=COOMatrix->Data[i];
  			ResultIndx1[i]=COOIndex1[i];
  	}
  	ResultIndx2[CountRC]=COOMatrix->CountOfNZE;
  }
	(*CSR_CSC_Matrix)->M=COOMatrix->M;
	(*CSR_CSC_Matrix)->N=COOMatrix->N;
	(*CSR_CSC_Matrix)->CountOfNZE=COOMatrix->CountOfNZE;
}

//Get maximum count of non zero entries in multiplication of matrices
int GetNZCountInMultipl(struct Matrix* CSRMatrix, struct Matrix* CSCMatrix)
{
	int i, j, c, r, CountOfNZResult=0;

	for(i=0;i<CSRMatrix->M;i++)
	{
		for(j=0;j<CSCMatrix->N;j++)
		{
			c=CSRMatrix->RowIndx[i];
			r=CSCMatrix->ColIndx[j];

			while(c<CSRMatrix->RowIndx[i+1] && r<CSCMatrix->ColIndx[j+1])
			{
				if(CSRMatrix->ColIndx[c]==CSCMatrix->RowIndx[r])
				{
					CountOfNZResult++; break;
				}
				else if(CSRMatrix->ColIndx[c]<CSCMatrix->RowIndx[r])
				{
					c++;
				}
				else
				{
					r++;
				}
			}
		}

	}
	return CountOfNZResult;
}

//Multiply matrix in CSR format with matrix in CSC format
void MultiplyCSRandCSC(struct Matrix **MulCOOMatrix, struct Matrix *CSRMatrix, struct Matrix *CSCMatrix)
{
  if(CSRMatrix->N!=CSCMatrix->M){printf("Input matrices are not conformable for matrix multiplication!"); return;}
	int i, j, c, r, sum;

  int NZCountInMultipl;
  if(CSRMatrix->Data==NULL || CSCMatrix->Data==NULL)
  {
    NZCountInMultipl=0;
    (*MulCOOMatrix)=Matrix_alloc((*MulCOOMatrix), NZCountInMultipl, NZCountInMultipl, NZCountInMultipl);
  }
  else
  {
    NZCountInMultipl=GetNZCountInMultipl(CSRMatrix, CSCMatrix);
    (*MulCOOMatrix)=Matrix_alloc((*MulCOOMatrix), NZCountInMultipl, NZCountInMultipl, NZCountInMultipl);
    NZCountInMultipl=0;
    for(i=0;i<CSRMatrix->M;i++)
  	{
  		for(j=0;j<CSCMatrix->N;j++)
  		{
  			c=CSRMatrix->RowIndx[i];
  			r=CSCMatrix->ColIndx[j];

  			sum=0;
  			while(c<CSRMatrix->RowIndx[i+1] && r<CSCMatrix->ColIndx[j+1])
  			{
  				if(CSRMatrix->ColIndx[c]==CSCMatrix->RowIndx[r])
  				{
  					sum=sum+(CSRMatrix->Data[c]*CSCMatrix->Data[r]);
  					r++; c++;
  				}
  				else if(CSRMatrix->ColIndx[c]<CSCMatrix->RowIndx[r])
  				{
  					c++;
  				}
  				else
  				{
  					r++;
  				}
  			}

        if(sum!=0)
        {
    			(*MulCOOMatrix)->Data[NZCountInMultipl]=sum;
    			(*MulCOOMatrix)->RowIndx[NZCountInMultipl]=i;
    			(*MulCOOMatrix)->ColIndx[NZCountInMultipl]=j;
    			NZCountInMultipl++;
        }
  		}
  	}
  }
  (*MulCOOMatrix)->M=CSRMatrix->M;
  (*MulCOOMatrix)->N=CSCMatrix->N;
  (*MulCOOMatrix)->CountOfNZE=NZCountInMultipl;
}

//Perform row transformation on matrix in CSC format:  A[r2] = k1 * A[r1] + k2 * A[r2]
struct Matrix * RowTransformation(struct Matrix* CSCMatrix, int r1, int k1, int r2, int k2)
{
  if(CSCMatrix->CountOfNZE==0)
    return CSCMatrix;
  int i, j, k, l;
  struct Matrix* RTMatrix;
  RTMatrix=Matrix_alloc(NULL, CSCMatrix->CountOfNZE+CSCMatrix->N, CSCMatrix->CountOfNZE+CSCMatrix->N, CSCMatrix->N);

	RTMatrix->M=CSCMatrix->M;
	RTMatrix->N=CSCMatrix->N;

  int p=0, result;
  for(i=0;i<CSCMatrix->N;i++)
  {
    k=l=-1; result=0;
    for(j=CSCMatrix->ColIndx[i];j<CSCMatrix->ColIndx[i+1];j++)
    {
      if(CSCMatrix->RowIndx[j]==r1)
      {
        k=j;
      }
      if(CSCMatrix->RowIndx[j]==r2)
      {
        l=j;
      }
      if(k>=0 && l>=0) break;
    }
    if(k>=0 && l>=0)
    {
      result=k1*CSCMatrix->Data[k]+k2*CSCMatrix->Data[l];
    }
    else if(k<0)
    {
      result=k2*CSCMatrix->Data[l]; //k1*0+k2*CSCMatrix->Data[l]
    }
    else if(l<0)
    {
      result=k1*CSCMatrix->Data[k];  //k1*CSCMatrix->Data[k]+k2*0
    }
    else
    {
      result=0;  //k1*0+k2*0
    }
    RTMatrix->ColIndx[i]=p;
    k=0;
    for(j=CSCMatrix->ColIndx[i];j<CSCMatrix->ColIndx[i+1];j++)
    {
      if(CSCMatrix->RowIndx[j]!=r2)
      {
        if(CSCMatrix->RowIndx[j]>r2 && k==0)
        {
          if(result!=0)
          {
            k=1;
            RTMatrix->Data[p]=result;
            RTMatrix->RowIndx[p]=r2;
            p++;
          }
        }
        RTMatrix->Data[p]=CSCMatrix->Data[j];
        RTMatrix->RowIndx[p]=CSCMatrix->RowIndx[j];
        p++;
      }
      else
      {
        if(result!=0)
        {
          k=1;
          RTMatrix->Data[p]=result;
          RTMatrix->RowIndx[p]=r2;
          p++;
        }
      }
    }
  }
  RTMatrix->ColIndx[CSCMatrix->N]=p;
  RTMatrix->CountOfNZE=p;
  Matrix_free(CSCMatrix);
  return RTMatrix;
}

//Print COO format matrix in normal matrix format
void PrintCOOMatrix(struct Matrix *COOMatrix)
{
	int i, j, k=0;
  printf("\n");
  BubbleSortCOO(COOMatrix, COOMatrix->ColIndx);
  BubbleSortCOO(COOMatrix, COOMatrix->RowIndx);
  for(i=0;i<COOMatrix->M;i++)
	{
		for(j=0; j<COOMatrix->N;j++)
		{
			if(k<COOMatrix->CountOfNZE && COOMatrix->RowIndx[k]==i && COOMatrix->ColIndx[k]==j)
			{
				printf("%12d ", COOMatrix->Data[k]);
				k++;
			}
			else
			{
				printf("%12d ", 0);
			}
		}
		printf("\n");
	}
}

//Print CSR format matrix in normal matrix format
void PrintCSRMatrix(struct Matrix *CSRMatrix)
{
	int i, j, k=0;
  printf("\n");
	for(i=0;i<CSRMatrix->M;i++)
	{
    k=0;
		for(j=0; j<CSRMatrix->N;j++)
		{
      if(CSRMatrix->Data!=NULL)
      {
  			if(j==CSRMatrix->ColIndx[CSRMatrix->RowIndx[i]+k] && CSRMatrix->RowIndx[i]+k<CSRMatrix->RowIndx[i+1])
  			{
  				printf("%12d ", CSRMatrix->Data[CSRMatrix->RowIndx[i]+k]);
  				k++;
  			}
  			else
  			{
  				printf("%12d ", 0);
  			}
      }
      else
      {
        printf("%12d ", 0);
      }
		}
		printf("\n");
	}
}

//Print CSC format matrix in normal matrix format
void PrintCSCMatrix(struct Matrix *CSCMatrix)
{
	int i, j, k=0;
  printf("\n");
	for(i=0;i<CSCMatrix->M;i++)
	{
    k=0;
		for(j=0; j<CSCMatrix->N;j++)
		{
      if(CSCMatrix->Data!=NULL)
      {
        for(k=CSCMatrix->ColIndx[j];k<CSCMatrix->ColIndx[j+1];k++)
    			if(i==CSCMatrix->RowIndx[k])
    			{
    				printf("%12d ", CSCMatrix->Data[k]);
            break;
          }
  			if(k==CSCMatrix->ColIndx[j+1])
  			{
  				printf("%12d ", 0);
  			}
      }
      else
      {
          printf("%12d ", 0);
      }
		}
		printf("\n");
	}
}

//Print COO format matrix in COO format
void PrintCOOMatrixInCOO(struct Matrix* COOMatrix)
{
	printf("\n%12s %12s %12s\n", "Data", "Row Index", "Col Index");
  printf("%12s %12s %12s\n", "----", "---------", "---------");
	int i=0;
	for(i=0;i<COOMatrix->CountOfNZE;i++)
	{
		printf("%12d %12d %12d\n", COOMatrix->Data[i], COOMatrix->RowIndx[i], COOMatrix->ColIndx[i]);
	}
	printf("\n");
}

//Print CSR format matrix in CSR format
void PrintCSRMatrixInCSR(struct Matrix* CSRMatrix)
{
	printf("\n%12s %12s %12s\n", "Data", "Row Pointer", "Col Index");
  printf("%12s %12s %12s\n", "----", "-----------", "---------");
	int i=0, k;
	k=((CSRMatrix->M+1)<CSRMatrix->CountOfNZE)?(CSRMatrix->M+1):CSRMatrix->CountOfNZE;
	for(i=0;i<k;i++)
	{
		printf("%12d %12d %12d\n", CSRMatrix->Data[i], CSRMatrix->RowIndx[i], CSRMatrix->ColIndx[i]);
	}
	for(;i<CSRMatrix->CountOfNZE;i++)
		printf("%12d %12s %12d\n", CSRMatrix->Data[i], " ", CSRMatrix->ColIndx[i]);
  if(CSRMatrix->CountOfNZE>0)
    for(;i<=CSRMatrix->M;i++)
  		printf("%12s %12d %12s\n", " ", CSRMatrix->RowIndx[i], " ");
	printf("\n");

}

//Print CSC format matrix in CSC format
void PrintCSCMatrixInCSC(struct Matrix* CSCMatrix)
{
	printf("\n%12s %12s %12s\n", "Data", "Row Index", "Col Pointer");
  printf("%12s %12s %12s\n", "----", "---------", "-----------");
	int i=0, k;
	k=((CSCMatrix->N+1)<CSCMatrix->CountOfNZE)?(CSCMatrix->N+1):CSCMatrix->CountOfNZE;
	for(i=0;i<k;i++)
	{
		printf("%12d %12d %12d\n", CSCMatrix->Data[i], CSCMatrix->RowIndx[i], CSCMatrix->ColIndx[i]);
	}
	for(;i<CSCMatrix->CountOfNZE;i++)
		printf("%12d %12d %12s\n", CSCMatrix->Data[i], CSCMatrix->RowIndx[i], " ");
  if(CSCMatrix->CountOfNZE>0)
    for(;i<=CSCMatrix->N;i++)
  		printf("%12s %12s %12d\n", " ", " ", CSCMatrix->ColIndx[i]);
	printf("\n");
}

//Allocate the memory for matrix
struct Matrix* Matrix_alloc(struct Matrix* OldMtr, int LengthOfData, int LengthOfRow, int LengthOfCol)
{
  Matrix_free(OldMtr);

  struct Matrix* Mtr;
  Mtr=(struct Matrix*)malloc(sizeof(struct Matrix));

  if(LengthOfData>0)
    Mtr->Data=(int*)malloc(LengthOfData*sizeof(int));
  else
    Mtr->Data=NULL;

  if(LengthOfRow>0)
    Mtr->RowIndx=(int*)malloc(LengthOfRow*sizeof(int));
  else
    Mtr->RowIndx=NULL;

  if(LengthOfCol>0)
    Mtr->ColIndx=(int*)malloc(LengthOfCol*sizeof(int));
  else
    Mtr->ColIndx=NULL;

  return Mtr;
}

//Free the memory allocated for matrix
void Matrix_free(struct Matrix *Mtr)
{
  if(Mtr!=NULL)
  {
    if(Mtr->Data!=NULL) free(Mtr->Data);
    if(Mtr->RowIndx!=NULL) free(Mtr->RowIndx);
    if(Mtr->ColIndx!=NULL) free(Mtr->ColIndx);
    free(Mtr);
    Mtr=NULL;
  }
}
