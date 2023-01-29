

#include "cec15_test_func.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



static int current_number_of_run = 1;
static int number_of_runs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int dims_to_eval[] = { 10, 30 };

int* get_current_evaluated_count(int number_of_run, int func_number, int dim);
double *getx(int number_of_run, int func_number, int dim, int evaluate_number);
double *getfx(int number_of_run, int func_number, int dim, int evaluate_number);
void getbest(double** x, double** fx, int dim, int run, int func_num);

void record(int number_of_run, int func_number, int dim, double* x, double fx)
{
	int *ec = get_current_evaluated_count(number_of_run, func_number, dim);
	double *rx, *rfx;

	double* best = NULL;// = GETBEST(dim, number_of_run - 1, func_number - 1);
	double * bestx = NULL;// = GETBESTX(dim, number_of_run - 1, func_number - 1);

	getbest(&bestx, &best, dim, number_of_run , func_number);
	if (fx < *best)
	{
		*best = fx;
		memcpy(bestx, x, sizeof(double)* dim);
	}

	*ec += 1;

	rx = getx(number_of_run, func_number, dim, *ec);
	rfx = getfx(number_of_run, func_number, dim, *ec);
	if (rx != NULL  && rfx != NULL) 
	{
		memcpy(rx, bestx, dim*sizeof(double));
		*rfx = *best;
		//if (rfx==get_add())
			//printf("%d, %d, %d, %d\n", number_of_run, func_number, dim, *ec);
	}

}



void set_number_of_run(int run)
{
	current_number_of_run = run;
	number_of_runs[run - 1] = 1;
}

int get_number_of_run()
{
	return current_number_of_run;
}

int get_all_number_of_run()
{
	int i;
	int sum = 0;
	for (i = 0; i < MAX_OF_RUNS; i++)
		sum += number_of_runs[i];
	return sum;
}
//this method calculates the average value of all of the elements in the array
double calculateMean(double* raw, int length);
//this method calculates the maximum value in the array
double calculateMax(double* raw, int length);
//this method calculates the minimum value in the array
double calculateMin(double* raw, int length);
//this method calculates the middle value of the 
//array once it has been sorted, or (in the case of
//an array with an even number of elements) the 
//average of the middle two values after sorting
double calculateMedian(double* raw, int length);
//this method calculats the standard deviation of the values in the array
//recall, if x represents a value in the array, then the standard deviation 
//is defined as the square root of the quotient of (x-mean)^2 summed over all 
//possible values of x, and the quantity (n-1) 
double calculateStandardDeviation(double* raw, int length);

void make_stat(double *raw, double* stat, int length)
{
	// "Best",	"Worst",	"Median","Mean","Std"
	stat[0] = calculateMin(raw, length);
	stat[1] = calculateMax(raw, length);
	stat[2] = calculateMedian(raw, length);
	stat[3] = calculateMean(raw, length);
	stat[4] = calculateStandardDeviation(raw, length);

}
int get_record_point(int dim, int index);
int mkdirs(char *path);
void write_result_statistics_to_file(char * dir, char * file_prefix)
{
	char filename_x[FILENAME_MAX];
	char filename_fx[FILENAME_MAX];
	char filename_hist[FILENAME_MAX];
	char filename_stat[FILENAME_MAX];
	FILE *file_x, *file_fx, *file_hist, *file_stat;
	int func_num, dim, number_of_run, rpn, evaluate_number;
	double *x;
	double *fx;
	int dimi;
	double stat[5];


	double hist_fx[MAX_OF_RUNS][RECORDING_POINTS_NUM];
	double statistics_raw[DIMS][MAX_FUNCTION_NUMBER][MAX_OF_RUNS];

	mkdirs(dir);



	for (func_num = 1; func_num <= MAX_FUNCTION_NUMBER; func_num++)
	{
		for (dim = 10; dim <= 30; dim += 20)
		{

			for (number_of_run = 1; number_of_run <= MAX_OF_RUNS; number_of_run++)	{
				// have run
				if (number_of_runs[number_of_run - 1] == 0)
					continue;
				// resultfile-fx-dx-rx-x.txt 
				sprintf(filename_x, "%s/%s-f%d-d%d-r%d-x.txt", dir, file_prefix, func_num, dim, number_of_run);
				// resultfile-fx-dx-rx-fx.txt
				sprintf(filename_fx, "%s/%s-f%d-d%d-r%d-fx.txt", dir, file_prefix, func_num, dim, number_of_run);
				file_x = fopen(filename_x, "w");
				file_fx = fopen(filename_fx, "w");
				fprintf(file_x, "%%count\tx\n");
				fprintf(file_fx, "%%count\tfx\n");

				for (rpn = 0; rpn < RECORDING_POINTS_NUM; rpn++)
				{
					evaluate_number = get_record_point(dim, rpn);
					x = getx(number_of_run, func_num, dim, evaluate_number);
					fx = getfx(number_of_run, func_num, dim, evaluate_number);


					fprintf(file_x, "%d\t", evaluate_number);
					fprintf(file_fx, "%d\t", evaluate_number);
					for (dimi = 0; dimi < dim; dimi++)
						fprintf(file_x, "%f\t", x[dimi]);
					fprintf(file_x, "\n");
					fprintf(file_fx, "%f\n", *fx);
					hist_fx[number_of_run - 1][rpn] = *fx;
					//if (rpn == RECORDING_POINTS_NUM-1)
					//	statistics_raw[(dim - 10) / 20][func_num - 1][RECORDING_POINTS_NUM-1] = hist_fx[number_of_run-1][RECORDING_POINTS_NUM-1];
				}

				fclose(file_x);
				fclose(file_fx);
				
				statistics_raw[(dim - 10) / 20][func_num - 1][number_of_run-1] = hist_fx[number_of_run-1][RECORDING_POINTS_NUM-1];
			}
			
			// resultfile-hist-fx-dx.txt
			sprintf(filename_hist, "%s/%s-hist-f%d-d%d.txt", dir, file_prefix, func_num, dim);
			file_hist = fopen(filename_hist, "w");
			fprintf(file_hist, "%10s\t", "% Run");
			for (rpn = 0; rpn < RECORDING_POINTS_NUM; rpn++)
			{
				evaluate_number = get_record_point(dim, rpn);
				fprintf(file_hist, "%20d\t", evaluate_number);
			}
			fprintf(file_hist, "\n");
			for (number_of_run = 1; number_of_run <= MAX_OF_RUNS; number_of_run++)	{
				// have run
				if (number_of_runs[number_of_run - 1] == 0)
					continue;
				fprintf(file_hist, "%10d\t", number_of_run);
				for (rpn = 0; rpn < RECORDING_POINTS_NUM; rpn++)
				{

					fprintf(file_hist, "%20e\t", hist_fx[number_of_run - 1][rpn]);
				}
				fprintf(file_hist, "\n");
			}
			fclose(file_hist);
		}
	}


	if (get_all_number_of_run() < 20)
		return;
	for (dim = 10; dim <= 30; dim += 20)
	{
		// resultfile-stat-dx.txt
		sprintf(filename_stat, "%s/%s-stat-d%d.txt", dir, file_prefix, dim);
		file_stat = fopen(filename_stat, "w");
		fprintf(file_stat, "%s %dD\n", "%% Statistics result of", dim);
		fprintf(file_stat, "%10s\t%20s\t%20s\t%20s\t%20s\t%20s\n", "% Func.", "Best", "Worst", "Median", "Mean", "Std");

		for (func_num = 1; func_num <= MAX_FUNCTION_NUMBER; func_num++)
		{
			make_stat(statistics_raw[(dim - 10) / 20][func_num - 1], stat, MAX_OF_RUNS);
			fprintf(file_stat, "%10d\t%20f\t%20f\t%20f\t%20f\t%20f\n", func_num, stat[0], stat[1], stat[2], stat[3], stat[4]);
		}
		fclose(file_stat);
	}

}














#include <errno.h>
#ifdef _WINDOWS
#include <direct.h>
#define MKDIR(p) mkdir(p)
#else
#include <sys/stat.h>
#define MKDIR(p) mkdir(p, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif


// helper functions
int mkdirs(char *path)
{
	int retval;
	while (0 != (retval = MKDIR(path)) && (errno != EEXIST))
	{
		char subpath[FILENAME_MAX] = "", *delim;

		if (NULL == (delim = strrchr(path, '/')))
			return retval;
		strncat(subpath, path, delim - path);     /* Appends NUL    */
		mkdirs(subpath);
	}
	return retval;
}



//this method calculates the average value of all of the elements in the array
double calculateMean(double* raw, int length) {

	//add up the values in the array
	double sum = 0;
	int i;
	for (i = 0; i < length; i++) {
		sum += raw[i];
	}

	//divide the total by the number of elements in the array to find the mean
	return sum / length;
}

//this method calculates the maximum value in the array
double calculateMax(double* raw, int length) {

	//assume the max is the first value, but then step through the array
	//and each time you encounter a bigger value, update the max value assumed
	double maxSeenSoFar = raw[0];
	int i;
	for (i = 1; i < length; i++) {
		if (raw[i] > maxSeenSoFar) {
			maxSeenSoFar = raw[i];
		}
	}

	//return the max value seen
	return maxSeenSoFar;
}

//this method calculates the minimum value in the array
double calculateMin(double* raw, int length) {

	//assume the max is the first value, but then step through the array
	//and each time you encounter a bigger value, update the max value assumed
	double minSeenSoFar = raw[0];
	int i;
	for (i = 1; i < length; i++) {
		if (raw[i] < minSeenSoFar) {
			minSeenSoFar = raw[i];
		}
	}

	//return the max value seen
	return minSeenSoFar;
}

//this method sorts the array given (so the contents of array are altered)
void selectionSort(double* raw, int length) {
	int tail;
	double maxSeen;
	int i;
	int posMaxSeen;

	for (tail = length - 1; tail > 0; tail--) {

		//find max element between positions 1 and tail 
		//(inclusive on both)
		maxSeen = raw[0];
		posMaxSeen = 0;
		for (i = 1; i <= tail; i++) {
			if (maxSeen < raw[i]) {
				maxSeen = raw[i];
				posMaxSeen = i;
			}
		}

		//swap max and last element
		raw[posMaxSeen] = raw[tail];
		raw[tail] = maxSeen;
	}
}


//this method calculates the middle value of the 
//array once it has been sorted, or (in the case of
//an array with an even number of elements) the 
//average of the middle two values after sorting
double calculateMedian(double* raw, int length) {

	//make a copy of the array to sort 
	//(otherwise original order would be affected)
	double median;
	double* copy = (double*)malloc(length*sizeof(double));
	memcpy(copy, raw, sizeof(double)*length);

	//sort the copy of the array
	selectionSort(copy, length);



	//if array has an odd number of elements, 
	//the median is the central one,
	//while if it has an even number of elements, 
	//the median is the average of the central two
	if (length % 2 == 1) {
		median = copy[length / 2];
	}
	else {
		median = (copy[length / 2 - 1] + copy[length / 2]) / 2.0;
	}

	return median;
}


//this method calculats the standard deviation of the values in the array
//recall, if x represents a value in the array, then the standard deviation 
//is defined as the square root of the quotient of (x-mean)^2 summed over all 
//possible values of x, and the quantity (n-1) 
double calculateStandardDeviation(double* raw, int length) {

	//the mean of the data is used in the formula for the standard deviation
	//in several places, so calculate it once, and store it in a variable
	double mean = calculateMean(raw, length);

	//find sum of the squared differences between the data values and the mean
	double sum = 0;
	int i;
	double variance = 0.0;

	for (i = 0; i < length; i++) {
		sum += (raw[i] - mean)*(raw[i] - mean);
	}

	//calculate the variance (which is a bias-corrected "average" of the
	//sum of the squared differences between the data values and the mean)

	if (length > 1)
		variance = sum / (length - 1);

	//calculate the standard deviation (which is the square root of the variance)
	return sqrt(variance);

}