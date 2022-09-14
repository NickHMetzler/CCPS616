/* 
# lab1.cpp
# Nicolas Metzler
# Student ID: 501050712
# Lab #1 - Sorting and problem Size
# CPS 616 Section BA0
# Instructor: A. Ufkes
# Purpose: Test three sorting algorithms, including a hybrid.
#
# I hereby attest that I am the sole owner and author of this code (except where referenced) and that to the best of my knowledge, this code has not infringed on anyone’s copyright. 
# Credit for any ideas, coding, and other materials used to develop this code has been given to the owners of the sources used in accordance to the rules of Ryerson's Academic Integrity Policy.
*/


#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std::chrono; // Namespace for fancy ms timing

bool verify_sorted(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
		if (arr[i] > arr[i + 1])
			return false;
	return true;
}

// SELECTION SORT FUNCTION
// Reference for Selection Sort Algorithm
// https://www.tutorialspoint.com/cplusplus-program-to-implement-selection-sort
void selection_sort(int *array, int size) {
   int i, min, index = 0;
   while(index < size - 1) {
      min = index;   //get index of minimum data
      for(i = index+1; i<size; i++)
         if(array[i] < array[min])
            min = i;
         //placing in correct position
         std::swap(array[index], array[min]);
     index++;
   }
}

// MERGE FUNCTION
// Reference for Merge/Merge Sort Algorithm
// https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort
void merge(int *array, int l, int m, int r) {
   int i, j, k, nl, nr;
   //size of left and right sub-arrays
   nl = m-l+1; nr = r-m;
   int larr[nl], rarr[nr];
   //fill left and right sub-arrays
   for(i = 0; i<nl; i++)
      larr[i] = array[l+i];
   for(j = 0; j<nr; j++)
      rarr[j] = array[m+1+j];
   i = 0; j = 0; k = l;
   //merge temp arrays to real array
   while(i < nl && j<nr) {
      if(larr[i] <= rarr[j]) {
         array[k] = larr[i];
         i++;
      }else{
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nl) {       //extra element in left array
      array[k] = larr[i];
      i++; k++;
   }
   while(j<nr) {     //extra element in right array
      array[k] = rarr[j];
      j++; k++;
   }
}

// MERGE SORT FUNCTION
void merge_sort(int *array, int l, int r) {
   int m;
   if(l < r) {
      int m = l+(r-l)/2;
      // Sort first and second arrays
      merge_sort(array, l, m);
      merge_sort(array, m+1, r);
      merge(array, l, m, r);
   }
}

// MERGE-SEL FUNCTION
void merge_sel(int *array, int l, int r, int axVal) {
   int m;
   if(l < r) {
      // When m is less than ax switch to Selection Sort
     if(r < axVal) {
       selection_sort(array, r + 1);
     }
     else{
       int m = l+(r-l)/2;
      // Sort first and second arrays
      merge_sel(array, l, m, axVal);
      merge_sel(array, m+1, r, axVal);
      merge(array, l, m, r);
     }
   }
}





  
int main()
{
  int n2avg = 10;
	char name[] = "Nicolas Metzler";
  int ax = 13;

	printf("\nCCPS616 - Lab 1 – %s\n", name);
	printf("Each result is the average of %d trials\n\n", n2avg);

	/****************************************/
	/************ SELECTION SORT ************/
	/****************************************/
	{
		// Feel free to tinker with these sizes. 
		// Simply add new value(s) to the array sel_test_sizes[]
		int sel_test_sizes[] = { 2000, 4000, 8000, 16000 };
	
		// for every array size in sel_test_sizes...
		for (int n : sel_test_sizes)
		{
			// Create arrays of size n for each trial
			int *nums = new int[n];
			int *sel_nums = new int[n];

			// Seed RNG, fill nums with random values between 1 and 4n
			srand(time(NULL));
			for (int i = 0; i < n; i++)
				nums[i] = rand() % (n * 4) + 1;


			printf("SELECTION    %5d nums: ", n);
			int time_sum = 0;
			// Sadly, replit is very noisy. Average over n2avg trials
      		for (int k = 0; k < n2avg; k++)
			{
				// copy unsorted array into sel_nums
				// ensures we start with the same unsorted array for each trial
				std::copy(nums, nums + n, sel_nums);

				// Fancy C++11 code for timing in milliseconds
				auto begin = high_resolution_clock::now();

				/********** CALL SELECTION SORT HERE **********/
				// Implement this function however you want with one constraint:
				// The input (sel_nums) must be sorted. Don't return a new array.
				// selection_sort( ... )
        
        //int n = sizeof(sel_nums) / sizeof(sel_nums[0]);

        //printf("\nBEFORE SORT\n");
        //display(sel_nums, n);
        
        selection_sort(sel_nums, n);

        //printf("\nAFTER SORT\n");
        //display(sel_nums, n);
				//*********************************************/

				// More fancy C++11 code for timing in milliseconds
				auto dur = high_resolution_clock::now() - begin;
				time_sum += (int)duration_cast<milliseconds>(dur).count();

				// Verify list is sorted, see verify_sort() above
				assert(verify_sorted(sel_nums, n));
				std::cout << "." << std::flush;
			}
			printf(" Avg: %dms\n", time_sum / n2avg);


      delete[] nums;
      delete[] sel_nums;
		}
	}
	/****************************************/
	/********** END SELECTION SORT **********/
	/****************************************/


	/****************************************/
	/******* MERGE & MERGE-SEL SORT *********/
	/****************************************/
	{
		// Feel free to tinker with these sizes. 
		// Simply add new value(s) to the array merge_test_sizes[]
		int merge_test_sizes[] = { 128000, 256000, 512000, 1024000 };
		for (int n : merge_test_sizes)
		{
			// Create arrays of size n for each trial
			int *nums = new int[n];
			int *merge_nums = new int[n];
			int *merge_sel_nums = new int[n];

			// Seed RNG, fill nums with random values between 1 and 4n
			srand(time(NULL));
			for (int i = 0; i < n; i++)
				nums[i] = rand() % (n * 4) + 1;


			printf("MERGE      %7d nums: ", n);
			int time_sum = 0;
			for (int k = 0; k < n2avg; k++)
			{
				std::copy(nums, nums + n, merge_nums);
				auto begin = high_resolution_clock::now();

				/********** CALL MERGE SORT HERE **********/
				// Implement this function however you want with one constraint:
				// The input (merge_nums) must be sorted. Don't return a new array.
				// merge_sort( ... );
        merge_sort(merge_nums, 0, n-1);
        

        
				//*****************************************/

				auto dur = high_resolution_clock::now() - begin;
				time_sum += (int)duration_cast<milliseconds>(dur).count();
				assert(verify_sorted(merge_nums, n));
				std::cout << "." << std::flush;
			}
			printf(" Avg: %dms\n", time_sum / n2avg);
		

			printf("MERGE-SEL  %7d nums: ", n);
			time_sum = 0;
			for (int k = 0; k < n2avg; k++)
			{
				std::copy(nums, nums + n, merge_sel_nums);
				auto begin = high_resolution_clock::now();

				/********** CALL MERGE-SEL SORT HERE **********/
				// Implement this function however you want with one constraint:
				// The input (merge_sel_nums) must be sorted. Don't return a new array.
				// merge_sel_sort( ... );


        merge_sel(merge_sel_nums, 0, n-1, ax);


        
				//**********************************************/

				auto dur = high_resolution_clock::now() - begin;
				time_sum += (int)duration_cast<milliseconds>(dur).count();

				assert(verify_sorted(merge_sel_nums, n));
				std::cout << "." << std::flush;
			}
			printf(" Avg: %dms\n", time_sum / n2avg);
		

      delete[] nums;
      delete[] merge_nums;
      delete[] merge_sel_nums;
		}
	}
	/****************************************/
	/****** END MERGE & MERGE-SEL SORT ******/
	/****************************************/

  printf("\nThe value of ax being tested here is: %d\n\n", ax);
  printf("\nThe values of ax tested were: 2, 3, 5, 7, 8, 9, 11, 13, 20, 100, 1000, 10000\n");
  printf("The value of ax that yielded the best results was: 9 seemed to produce the best results, outpacing Merge on it's own\nThe rest produced similar results after multiple runs, or were less efficient than just Merge sort.\n");

}