struct Matrix
{
int M, N, CountOfNZE;
int *Data, *RowIndx, *ColIndx;
};

int GetCountFromPerc(float Perc, int Total);
int ShuffleSequence(int * Seq, int RangeStart, int RangeEnd, int ReqCount);
int GetDistinctRandomNumbers(int * Seq, int RangeStart, int RangeEnd, int ReqCount);
void SetMatrixEntries(struct Matrix* COOMatrix, int *NZElemIndex, int StartIndex, int EndIndex, int m);
void SetNGEntriesInMatrix(struct Matrix*  COOMatrix, int* NZElemIndex, int StartIndex, int CountOfNZE, int CountOfNGE, int m);
void BubbleSortCOO(struct Matrix* COOMatr, int* indx);
int GetNZCountInMultipl(struct Matrix* CSRMatrix, struct Matrix* CSCMatrix);

//Primary functions for the problems
void GenerateCOOMatrix(struct Matrix **COOMatrix, int M, int N, float NZperc, float NGperc); //Problem a
void COOto_CSR_CSC(struct Matrix **CSR_CSC_Matrix, struct Matrix *COOMatrix, int CSR); //Problem b
void MultiplyCSRandCSC(struct Matrix **MulCOOMatrix, struct Matrix *CSRMatrix, struct Matrix *CSCMatrix); //Problem c
struct Matrix * RowTransformation(struct Matrix* CSCMatrix, int r1, int k1, int r2, int k2); //Problem d

//Matrix printing in normal rectangle format (Problem e)
void PrintCOOMatrix(struct Matrix *COOMatrix);
void PrintCSRMatrix(struct Matrix *CSRMatrix);
void PrintCSCMatrix(struct Matrix *CSCMatrix);

//Matrix printing in specific sparse matrix format
void PrintCOOMatrixInCOO(struct Matrix* COOMatrix);
void PrintCSRMatrixInCSR(struct Matrix* CSRMatrix);
void PrintCSCMatrixInCSC(struct Matrix* CSCMatrix);

//Memory management functions
struct Matrix* Matrix_alloc(struct Matrix* OldMtr, int LengthOfData, int LengthOfRow, int LengthOfCol);
void Matrix_free(struct Matrix *Mtr);
