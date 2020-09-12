
#### ABOUT THE FILES IN THIS FOLDER
----------------------------------------------------

There are ten files in this folder. Files are README.md, makefile, Header.c, 
Client.c, Impl.C and five files containing test cases for program.

- README.txt file contains the information about the program that helps to 
run the program and to understand the outputs.
 
- makefile contains the commands to compiles the program with other 
necessary file and generate single executable object file.

- Header.c file contains the definition of structure data types and 
prototypes of all user defined functions in this program. This file is 
inclueded as a header file in Client.c and Impl.c.

- Client.c file contains main() function and all the functions for the 
given problems are called in main() function.

- Impl.c file contains the definitions of all the user defined functions 
in this program.   

- There is one test cases file for each problem in assignment. Each test 
cases file contain five test cases (see section `ABOUT TEST CASES` for 
details). 

 
#### ABOUT THE PROGRAM
----------------------------------------------------

This program is implemented is an interactive program, because solution of one 
problem is kept in memory and used as input to some problem. Its interactive 
behaviour helps to test the functions with different cases. 

All arrays used in the program start with index 0.


#### HOW TO COMPILE AND RUN THIS PROGRAM
----------------------------------------------------

1. Open Terminal
2. Navigate to this folder
3. Type `make` command and press enter. This command will generate object 
	file for the program.
4. To run the program, type `./a.out` command and press enter.


#### PROGRAM INPUTS AND OUTPUTS
----------------------------------------------------

All inputs to program are provided through terminal and all outputs are 
printed on the terminal.

When program starts execution, a menu of options in printed on the terminal. 
To select the option enter the serial number assigned to that option.

1. To generate the matrix in COO format. Give the required 
  inputs (see section `CONSTRAINTS Problem (a)`). Generated 
  matrix is printed in COO format.
2. To transform the COO format matrix in CSR format. New CSR 
  matrix is generated from the latest instance of COO matrix. 
  Newly generated matrix is printed in CSR format.
3. To transform the COO format matrix in CSC format. New CSC 
  matrix is generated from the latest instance of COO matrix. 
  Newly generated matrix is printed in CSC format.
4. To multiply CSR format matrix with CSC format matrix. New 
  COO matrix is generated as the result of multiplication of 
  latest instances of the CSR format matrix and CSC format 
  matrix. Newly generated matrix is printed in COO format.
5. To do row transformation on CSC format matrix. Give the 
  required inputs k1 r1 k2 r2 such that row transformation 
  performed on matrix A is A[r2] = k1* A[r1] + k2 * A[r2] 
  (see section `CONSTRAINTS Problem 1(d)`). Row transformation 
  operation is performed on input CSC format matrix and the 
  resultant matrix is copied back in input matrix. The 
  transformed matrix is printed in CSC format.
6. To print the matrix in normal matrix (rectangle) format. 
  A Print Menu is displayed listing the results of different 
  matrix operations.

    61.To print the latest generated COO format matrix. 
    
    62.To print the latest CSR format matrix generated 
      from COO format matrix. 
      
    63.To print the latest CSC format matrix generated 
      from COO format matrix or CSC format matrix after row 
      transformations. 
      
    64.To print the COO format matrix which is the result 
      of latest matrix multiplication. 
      
    65.To go back to main menu. 

7. To quit the program. User can select different options from 
  menu and can perform matrix operations any no. of times until 
  he/she selects Option 7.


#### INPUT CONSTRAINTS: 
----------------------------------------------------

Following constraints (as specified in problem statements or assumed 
by the programmer) are assumed about the input while implementing the 
functions.

- Problem (a):	Following are the constraints on the input taken from user:	
	- 0 < M <= 150 , where M is no. of rows in the matrix
	- 0 < N <= 100 , where N is no. of columns in the matrix
	- 0 <= Density <= 100 , where Density is the percentage of 
				total no. of non zero entries in the matrix.
	- 0 <= NegativePercent <=100 
	- NegativePercent <= Density, 
				where NegativePercent is the 
				percentage of total no. of negative entries 
				in the matrix.
	- -999 <= V <= 999, where V is any value in the matrix generated 
				randomly (this constraint is assumed to get the 
				results that are printable in specific width of 
				characters).

- Problem (b):	Output of the Problem (a) will be input to Problem (b). 
		There is no any provision to give specific matrix as input to 
		Problem (b). 	

- Problem (c):	Outputs of the Problem (b) will be inputs to Problem (c).
		There is no any provision to give specific matrices as input to 
		Problem (c).	

- Problem (d):	Output of the Problem (b) will be one of the inputs 
		to Problem (d). Others are user inputs.
		Following are the constraints on the input taken from user:
	- -999 <= k1, k2 <=999 , where k1, k2 are interger multiplication 
				factors (this constraint is assumed to get the 
				results that are printable in specific width of 
				characters)
	- 0 <= r1 < M, where M is no. of rows in the matrix and r1 is the 
				row index.
	- 0 <= r2 < M, where M is no. of rows in the matrix and r2 is the 
				row index.
		
- Problem (e)	Output from any of the Problems (a), (b), (c), (d) can be input 
		to Problem (e).


#### ABOUT TEST CASES
----------------------------------------------------

Test cases for each problem are named as `Test cases <Serial_Number>`. 

Each test case contains 'INPUT' section and 'OUTPUT' section.
INPUT section contains all the user inputs and/or pre-generated matrices given as 
input to functions. The matrices shown in INPUT section of test case are not 
actually printed as input on terminal but they are shown in test case to check the
results of the functions.
Statement 'INPUT: Output of TEST CASE X of Problem (Y)' in test case means output 
obtained in TEST CASE X of problem Y is used as input here.

The matrix formats specificied in paranthesis in INPUT/OUTPUT section of test case 
indicate the format of the input/output matrix.

Data in the INPUT/OUTPUT sections of test cases is copied from terminal after running the test cases.
Menu and selected choices are not included in test cases for the purpose of brevity.


#### UNRESOLVED BUGS
----------------------------------------------------

There exists a bug in memory allocation/deallocation code which sometimes throws 
memory related exception. This bug is unresolved.
