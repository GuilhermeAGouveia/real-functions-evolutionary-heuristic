1. Intro

This software package contain the C version code for "Problem Definitions and Evaluation Criteria for CEC 2015 Special Session on Bound Constrained Single-Objective Numerical Optimization Competition Part B: Computationally Expensive Single Objective Optimization".

For detail of the problems, please check out the related technical report.

2. Usage

The main interface of the software package defined in cec15_test_func.h. To use the functions, just include the file cec15_test_func.h, and compile your file with cec15_test_func.c, ecr_iml.c, evaluation_count_iml.c, record_result_iml.c and rp_iml.c. 

If you don't want to use the result recording and statistics functionalities, just define NO_RECORDING before you include cec15_test_func.h as follows

#defeine NO_RECORDING
#inlcude "cec15_test_func.h"

The two files named as jkiss.h and jkiss.c are for the test progam only. Please find the test program main.c with detail usage.


3. Interface

The main part of them are three functions as follows:

/*
 * evaluate specific function
 */
void cec15_test_func(double *x, double *f, int nx, int mx,int func_num);

x will contain the values need to be evaluated, f will hold the return value, nx is the dimension of the problem, can be 10 and 30 here; mx is the number of the values to be evaluated, thus the length of the x will be mx * nx, and f must be longer than mx * sizeof(double), func_num defines the function you want to evaluate, can be 1,2,3,..., 15.


#ifndef NO_RECORDING
/*
 *  Number of run
 */
void set_number_of_run(int run);
/* 
 * output to file
 */
// dir can only like test/resultdir
void write_result_statistics_to_file(char* dir, char * file_prefix);

These two functions can be turned of by define NO_RECORDING. 

When using these functions, just set the number of run as 

set_number_of_run(n);

All the evaluations after this call and before the next call of it will be recorded as the nth run of your algorithm. The data that are specified to be recorded for statistical analysis in the Technical Report will be recorded automatically in memory.

After all 20 run of the algorithm finished, or part of the running are done, you can use write_result_statistics_to_file(char* dir, char * file_prefix) to dump all the recorded result into directory specified as the first argument, and all the result fills will have the same prefix as the second argument specified. 

The first argument can be in the format like "result/randomsampling", "randomsampling", or "d:/result/myaogorithm" under Windows, "/home/username/algorithm" under Linux. The main constrains is the sub-directory seperator "/" and no "/" for the lowerest level. Directory names like "result\\algorithm" or "result/algorithm/" are not accepted now.


4. Contact

If you find anything does not work, have any difficulty to use the package, or have better ideas about the package, please don't hesitate to contact Qin Chen (email:chenqin1980@gmail.com) for further information.
