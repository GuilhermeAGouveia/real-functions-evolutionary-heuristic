#include <stdio.h>
#include <stdlib.h>

#include "cec15_test_func.h"

static double *recorded_x10 = NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER][RECORDING_POINTS_NUM][10];
static double *recorded_fx10 = NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER][RECORDING_POINTS_NUM];
static double *recorded_x30 = NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER][RECORDING_POINTS_NUM][30];
static double *recorded_fx30 = NULL;//[MAX_OF_RUNS][MAX_FUNCTION_NUMBER][RECORDING_POINTS_NUM];

int record_index(int evaluate_number, int dim);

// index start from 0
double* lazy_multi_dim_array4(int i, int j, int k, int l, double**orig, int imax, int jmax, int kmax, int lmax)
{
	int index;
	if (*orig == NULL)
	{
		*orig = (double*)malloc(sizeof(double)*imax*jmax*kmax*lmax);
		for (index = 0; index < imax*jmax*kmax*lmax; index ++)
			*(*orig) = INF;
	}
	if (i >= 0 && i < imax &&j >= 0 && j < jmax && k >= 0 && k < kmax && l >= 0 && l < lmax) {
		return (*orig) + i * jmax*kmax*lmax + j * kmax *lmax + k * lmax + l;
	}
	return NULL;
}
// index start from 0
double* lazy_multi_dim_array3(int i, int j, int k, double**orig, int imax, int jmax, int kmax)
{
	int index;
	if (*orig == NULL)
	{
		*orig = (double*)malloc(sizeof(double)*imax*jmax*kmax);
		for (index = 0; index < imax*jmax*kmax; index ++)
			*(*orig) = INF;
	}
	if (i >= 0 && i < imax &&j >= 0 && j < jmax && k >= 0 && k < kmax) {
		return (*orig) + i * jmax * kmax + j * kmax + k;
	}
	return NULL;
}


double *getx(int number_of_run, int func_number, int dim, int evaluate_number)
{
	// record_index start from 0
	int index_record = record_index(evaluate_number, dim);
	if (index_record != -1)
	{
		if (dim == 10)
			return lazy_multi_dim_array4(number_of_run - 1, func_number - 1, index_record, 0,
				&recorded_x10, MAX_OF_RUNS, MAX_FUNCTION_NUMBER, RECORDING_POINTS_NUM, dim);		
		else if (dim == 30)
			return lazy_multi_dim_array4(number_of_run - 1, func_number - 1, index_record, 0,
			&recorded_x30, MAX_OF_RUNS, MAX_FUNCTION_NUMBER, RECORDING_POINTS_NUM, dim);

	}
	return NULL;

}
double *getfx(int number_of_run, int func_number, int dim, int evaluate_number)
{

	int index_record = record_index(evaluate_number, dim);
	if (index_record != -1)
	{
		if (dim == 10)
			return lazy_multi_dim_array3(number_of_run - 1, func_number - 1, index_record,
			&recorded_fx10, MAX_OF_RUNS, MAX_FUNCTION_NUMBER, RECORDING_POINTS_NUM);

		else if (dim == 30)
			return lazy_multi_dim_array3(number_of_run - 1, func_number - 1, index_record,
			&recorded_fx30, MAX_OF_RUNS, MAX_FUNCTION_NUMBER, RECORDING_POINTS_NUM);

	}
	return NULL;

}
