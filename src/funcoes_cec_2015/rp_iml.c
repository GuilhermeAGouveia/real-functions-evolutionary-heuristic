#include <math.h>
#include <stdio.h>

#include "cec15_test_func.h"

static float percent_of_record[] = { 0.01f, 0.02f, 0.03f, 0.04f, 0.05f, 0.06f, 0.07f, 0.08f,
0.09f, 0.10f, 0.20f, 0.30f, 0.40f, 0.50f, 0.60f, 0.70f, 0.80f, 0.90f, 1.00f };


int get_record_point(int dim, int index)
{
	return (int)floor(0.5 + (percent_of_record[index] * TIMES_OF_EVAL*dim));
}

// evaluate_number --  [1,2,3,4,5...]
// dim -- 10,30
int record_index(int evaluate_number, int dim)
{
	int i;
	for (i = 0; i < RECORDING_POINTS_NUM; i++)
	{
		if (get_record_point(dim, i) == evaluate_number)
			return i;
	}
	return -1;
}

