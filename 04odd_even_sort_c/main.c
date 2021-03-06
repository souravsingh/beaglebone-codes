/***************************************************************
 * C Source code for Parallel Odd-Even Sort Algorithm using
 * openMP on Beaglebone Black running Debian 7 Linux distribu_tion
 ****************************************************************

 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <string.h>

#define NO_OF_THREADS	2
#define ARR_SIZE		10
#define DIVIDER			10000

int num_arr[ARR_SIZE];


void print_sorted_arr(int *a)
{
	int i;
	printf("\nSorted Array is: [");
	for(i=0; i<ARR_SIZE; i++)
	{
		if(i+1 == ARR_SIZE)
			break;
		printf("%d, ", a[i]);
	}
	printf("%d]\n", a[i]);

}


void get_random_arr()
{
	int i;
	printf("\nElements to Sort are: [");
	for(i=0; i<ARR_SIZE; i++)
	{
		num_arr[i] = rand()%DIVIDER;
		if(i+1 == ARR_SIZE)
			break;
		printf("%d, ", num_arr[i]);
	}
	printf("%d]\n", num_arr[i]);

}


void odd_even_sort_openmp(int* a, int n)
{
  int phase, i, temp;
  for(phase=0;phase<n;++phase)
  {
    if(phase%2==0) //even phase
    {
#pragma omp parallel for num_threads(NO_OF_THREADS) default(none) shared(a,n) private(i,temp)
      for(i=1;i<n;i+=2)
			if(a[i-1] > a[i])
			{
			  temp = a[i];
			  a[i] = a[i-1];
			  a[i-1] = temp;
			}
    }
    else //odd phase
    {
#pragma omp parallel for num_threads(NO_OF_THREADS) default(none) shared(a,n) private(i,temp)
      for(i=1;i<n-1;i+=2)
			if(a[i] > a[i+1])
			{
				  temp = a[i];
			  a[i] = a[i+1];
			  a[i+1] = temp;
			}
    }
  }
}


int main (void)
{
	int i;
	int* arr1;
	double start_time_omp, end_time_omp, elapsed_time_omp;

	printf("\nParallel Odd-Even Sort using OpenMP:");
	printf("\n------------------------------------------\n");

	/* Prepare data to sort */
	printf("\nData Array:");
	printf("\n-------------");
	get_random_arr();

	/* Allocate memory for new array */
	arr1 = (int*) malloc(sizeof(int)*ARR_SIZE);

	/* Copy data to sort in the new array */
	memcpy(arr1, num_arr, sizeof(int)*ARR_SIZE);

	/* Call function to sort the array. Also record the start and end time */
	printf("\nOpenMP Method:");
	printf("\n-----------------");
	printf("\nSorting the data parallely with OpenMP ...");
	start_time_omp = omp_get_wtime();
	odd_even_sort_openmp(arr1, ARR_SIZE);
	end_time_omp = omp_get_wtime();
	elapsed_time_omp = end_time_omp - start_time_omp;
	printf("[Done]\n");

	/* Print the result which is a sorted array */
	printf("\nResult of OpenMP:");
	printf("\n-----------------");
	print_sorted_arr(arr1);

	/* Print the result (Sorted Array) */
	printf("\nTime Info:");
	printf("\n-----------------");
	printf("\nTime taken to Run Algorithm\t: %lf (s)\n",elapsed_time_omp);

	/* Free the memory allocated by maclloc() */
	free(arr1);

	return 0;
}

