/*
CEC14 Test Function Suite for Single Objective Optimization
Jane Jing Liang (email: liangjing@zzu.edu.cn; liangjing@pmail.ntu.edu.cn) 
Dec. 12th 2013
*/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "cec15_test_func.h"
#include "jkiss.h"
#include <math.h>
#include <stdlib.h>

#define NO_RECORDING



void test_stdin_stdout(int n)
{
	double *x;
	double fx;
	int i;
	x = (double*)malloc(sizeof(double)*n);

	while (1)
	{
		printf("\nX=[");
		for (i=0; i<n; i++)
		{
			if (EOF==scanf("%lf", &(x[i])))
				return;
			printf("%f ", x[i]);
		}
		printf("]\nEvaluated with F1-F15:\n");
		for (i=1; i<=15; i++)
		{
			cec15_test_func(x, &fx, n, 1, i);
			printf("F%d(x) = %.8f\n", i,fx);
		}
		printf("\n");

	}

	free(x);

}

int main(int argc, char* argv[])
{
	int dim;

	if (argc<=1)
		dim = 10;
	else
		dim = atoi(argv[1]);

	if (dim!=10)
		dim = 30;
	test_stdin_stdout(dim);
	return 0;
}

void test_randomsample()
{
	int run, fun_num, i,j;
	double x10[10];
	double x30[30];
	double f;
	cec15_reseed(10,20,30,40);
	//srand(100);
	for (run =1; run <=20; run++)
	{
		set_number_of_run(run);
		for (fun_num=1; fun_num<=15; fun_num++)
		{
			for (i = 1; i<= 50 * 10; i++)
			{
				for (j=0; j<10; j++)
					x10[j] = -100.0 + 200.0 * cec15_rand();
				cec15_test_func(x10, &f, 10, 1,fun_num);
			}
			for (i=1; i<= 50 * 30; i++)
			{
				for (j=0; j<30; j++)
					x30[j] = -100.0 + 200.0 * cec15_rand();
				cec15_test_func(x30, &f, 30, 1, fun_num);
			}

		}
	}

	write_result_statistics_to_file("result/randomsampling", "result");

}
