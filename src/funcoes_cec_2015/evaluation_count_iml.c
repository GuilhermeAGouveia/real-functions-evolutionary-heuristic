#include "cec15_test_func.h"

#include <string.h>
#include <stdlib.h>

static double *currentBest10=NULL;
static double *currentBest10x=NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER][10];
static double *currentBest30=NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER];
static double *currentBest30x=NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER][30];
static int *evaluate_counter_10=NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER];
static int *evaluate_counter_30=NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER];

#define GETBEST(dim,i,j) (dim)==10? (currentBest10+(i)*MAX_FUNCTION_NUMBER+(j)):(currentBest30+(i)*MAX_FUNCTION_NUMBER+(j))
#define GETBESTX(dim,i,j) (dim)==10? (currentBest10x+(i)*MAX_FUNCTION_NUMBER*10+(j)*10):(currentBest30x+(i)*MAX_FUNCTION_NUMBER*30+(j)*30)


#define GETEC(dim,run,fn) (dim)==10? (evaluate_counter_10+(run-1)*MAX_FUNCTION_NUMBER+fn-1) : (evaluate_counter_30+(run-1)*MAX_FUNCTION_NUMBER+fn-1)


void getbest(double** x, double** fx, int dim, int run, int func_num)
{
	int i;
	if (currentBest10==NULL)
	{
		currentBest10 = (double*)malloc(sizeof(double)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER);
		for (i=0; i<MAX_OF_RUNS*MAX_FUNCTION_NUMBER; i++)
			currentBest10[i] = INF;
	}
	if (currentBest10x ==NULL)
	{
		currentBest10x = (double*)malloc(sizeof(double)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER*10);
	}
	if (currentBest30==NULL)
	{
		currentBest30 = (double*)malloc(sizeof(double)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER);
		for (i=0; i<MAX_OF_RUNS*MAX_FUNCTION_NUMBER; i++)
			currentBest30[i] = INF;
	}
	if (currentBest30x ==NULL)
		currentBest30x = (double*)malloc(sizeof(double)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER*30);	

	*x = GETBESTX(dim, run-1, func_num-1);
	*fx = GETBEST(dim, run-1, func_num-1);
}


int* get_current_evaluated_count(int number_of_run, int func_number, int dim)
{
	if (evaluate_counter_10==NULL)
	{
		evaluate_counter_10 = (int*) malloc(sizeof(int)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER);
		memset(evaluate_counter_10, 0 , sizeof(int)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER);
	}
	if (evaluate_counter_30==NULL)
	{

		evaluate_counter_30 = (int*) malloc(sizeof(int)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER);
		memset(evaluate_counter_30, 0 , sizeof(int)*MAX_OF_RUNS*MAX_FUNCTION_NUMBER);
	}

	return GETEC(dim,number_of_run, func_number);
}

