/* 
# lab5.cpp
# Yiran Zhu and Nicolas Metzler
# Student ID's: 500571811 and 501050712
# Lab #5 - Dynamic 0-1 Knapsack
# CPS 616 Section BA0
# Instructor: A. Ufkes
# Purpose: C++ program that finds an optimal solution to the 0-1 knapsack problem discussed in class.
#
# We hereby attest that we are the sole owners and authors of this code (except where referenced) and that to the best of our knowledge, this code has not infringed on anyone’s copyright. 
# Credit for any ideas, coding, and other materials used to develop this code has been given to the owners of the sources used in accordance to the rules of Ryerson's Academic Integrity Policy.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;

int getWeight(vector<pair<int, int>> & knapsack);
int getValue(vector<pair<int, int>> & knapsack);
void generateItems(int n, vector<pair<int, int>> & items);
void printItems(vector<pair<int, int>> & items);


/**
 * Calculates best value and pair in a vector using brute force.
 * 
 * @param weight maximum weight knapsack can hold
 * @param items vector of items to choose from
 * @param taken vector to hold chosen items
 * @return best value, sum of all values in 'taken'
 */
int knapsackBF(int weight, vector<pair<int, int>> & items, vector<pair<int, int>> & taken)
{
   // pow_set_size is (2^n-1) where n is size of items
	unsigned int pow_set_size = 1;
	for (size_t i = 0; i < items.size(); i++) {
		pow_set_size *= 2;
	}
   unsigned int counter;
   vector< vector< pair<int, int> > > itemCombinations;
   // Run from counter 000..0 to 111..1
   for (counter = 0; counter < pow_set_size; counter++) {
      int currentWeight = 0;
      vector< pair<int, int> > tempVector;
      for (size_t j = 0; j < items.size(); j++) {
         // Check if jth bit in the counter is set
         // If set then push pair into vector
         if (counter & (1 << j)) {
            currentWeight += items[j].first;
            tempVector.push_back(make_pair(items[j].first, items[j].second));
         }
      }
      if (currentWeight <= weight) {
         itemCombinations.push_back(tempVector);
      }
   }
	// Find and return max value and pairs
   int bestValue = 0;
   vector<pair<int, int>> maxPairs;
   for (size_t i = 0; i < itemCombinations.size(); i++) {
      int value = 0;
      for (size_t j = 0; j < itemCombinations[i].size(); j++) {
         value += itemCombinations[i][j].second;
      }
      if (value > bestValue){
         bestValue = value;
         maxPairs = itemCombinations[i];
      }
   }
	taken = maxPairs;
	sort(taken.begin(), taken.end());
	return bestValue;
}

/**
 * Calculates best value and pair in a vector using dynamic programming.
 * 
 * @param weight maximum weight knapsack can hold
 * @param items vector of items to choose from
 * @param taken vector to hold chosen items
 * @return best value, sum of all values in 'taken'
 */
// Credit to: https://www.youtube.com/watch?v=zRza99HPvkQ for the basic algorithm concept and understanding dynamic programming
int knapsackDYN(int weight, vector<pair<int, int>> & items, vector<pair<int, int>> & taken)
{
  // Declare indexing variables
	size_t i;
	int j;
  // Set up a chart of values based on index and weight
   int K[items.size() + 1][weight + 1];

  // Move through the chart to find the max values
   for (i = 0; i <= items.size(); i++) {
      for (j = 0; j <= weight; j++) {
         if (i == 0 || j == 0)
           K[i][j] = 0;
         else if (items[i - 1].first <= j){
            K[i][j] = max(items[i - 1].second + K[i - 1][j - items[i - 1].first], K[i - 1][j]);
           }
         else{
            K[i][j] = K[i - 1][j];
        }
      }
   }

  // Set the variables so we can move back through the chart to find which entries are in the backpack
  i = items.size();
  j = weight;
  while(i > 0 && j > 0){
    if(K[i][j] == K[i-1][j]){
      i--;
      }
    else{
      // Add backpack entry to the taken vector
      taken.push_back(items[i-1]);
      i--;
      j = j - items[i].first; 
      }
  }
  // Sort the taken vector to prevent any errors
   sort(taken.begin(), taken.end());
   
  // set the bestValue and Return
    int bestValue = K[items.size()][weight];
    return bestValue;
}


int main()
{
	char name[] = "Yiran Zhu and Nicolas Metzler";
	srand((int)time(NULL));
	printf("\nCCPS616 - Lab 5 - %s\n\n", name);


	/*********************************************************/
	/* First, test algorithm on example from lecture slides  */
	/* You should create your own additional examples here!  */
	/*********************************************************/
	{
		// Example from lecture slides:
		// 5 items: [(1, 1), (2, 6), (5, 18), (6, 22), (7, 28)]
		int weight = 11, bestValue = 40;
		vector<pair<int, int>> items;
		items.push_back(pair<int, int>(1, 1));
		items.push_back(pair<int, int>(2, 6));
		items.push_back(pair<int, int>(5, 18));
		items.push_back(pair<int, int>(6, 22));
		items.push_back(pair<int, int>(7, 28));

		int bfValue, dynValue;
		vector<pair<int, int>> bfTaken, dynTaken;

		printf("Testing simple class example... \n");
		printf("Items: ");
		printItems(items);

		bfValue = knapsackBF(11, items, bfTaken);
		dynValue = knapsackDYN(11, items, dynTaken);

		printf("  Brute force picked: ");
		printItems(bfTaken);
		printf("  Dynamic picked:     ");
		printItems(dynTaken);
		printf("  Should be:          [ (5, 18) (6, 22) ]\n");

		int bfWeight = getWeight(bfTaken);
		int dynWeight = getWeight(dynTaken);

		if (bfWeight > weight || dynWeight > weight) {
			printf("  Weight limit exceeded!\n");
			printf("  Brute force weight: %d\n", bfWeight);
			printf("  Dynamic weight:     %d\n", dynWeight);
			printf("  Target weight:      %d\n\n", weight);
		}
		if (bfValue != bestValue || dynValue != bestValue) {
			printf("  Value discrepancy!\n");
			printf("  Brute force value:  %d\n", bfValue);
			printf("  Dynamic value:      %d\n", dynValue);
			printf("  Both should be:     %d\n\n", bestValue);
		}
		else
			printf("  Passed!\n\n");
	}

	/******************************************************************/
	/* Next, test algorithm on several larger, random samples         */
	/* Veryify correctness by comparing brute force to dynamic result */
	/******************************************************************/
	{
		int numItems[] = { 5, 10, 15, 20 };

		for (int n : numItems)
		{
			vector<pair<int, int>> items;
			generateItems(n, items);
			int weight = n * 2;
			vector<pair<int, int>> bfTaken, dynTaken;

			printf("%d items, weight = %d... \n", n, weight);

			printf("Items: ");
			printItems(items);

			int bfValue = knapsackBF(weight, items, bfTaken);
			int dynValue = knapsackDYN(weight, items, dynTaken);

			// Make sure value returned matches value of items taken
			assert(bfValue == getValue(bfTaken));
			assert(dynValue == getValue(dynTaken));

			printf("  Brute force picked: ");
			printItems(bfTaken);
			printf("  Dynamic picked:     ");
			printItems(dynTaken);

			int bfWeight = getWeight(bfTaken);
			int dynWeight = getWeight(dynTaken);

			if (bfWeight > weight || dynWeight > weight) {
				printf("  Weight limit exceeded!\n");
				printf("  Brute force weight: %d\n", bfWeight);
				printf("  Dynamic weight:     %d\n", dynWeight);
				printf("  Target weight:      %d\n", weight);
				printf("  Breaking...\n\n");
				break;
			}
			else if (bfValue != dynValue) {
				printf("  Value discrepancy!\n");
				printf("  Brute force value: %d\n", bfValue);
				printf("  Dynamic value:     %d\n", dynValue);
				printf("  Breaking...\n\n");
				break;
			}
			else
				printf("  Total value: %d\n\n", bfValue);


		}
	}

  printf("Thank you Alex for being such a great Professor over this course. We appreciate you :)");
	printf("\n");
}

// Function for getting weight of items in knapsack. 
int getWeight(vector<pair<int, int>> & knapsack)
{
	int total = 0;
	for (pair<int, int> item : knapsack)
		total += item.first;
	return total;
}

// Function for getting value of items in knapsack. 
int getValue(vector<pair<int, int>> & knapsack)
{
	int total = 0;
	for (pair<int, int> item : knapsack)
		total += item.second;
	return total;
}

// Function for generating a random vector of items. 
void generateItems(int n, vector<pair<int, int>> & items)
{
	for (int i = 0; i < n; i++)
	{
		int weight = rand() % n + 1;
		int value = (rand() % n + 1) * 3;
		items.push_back(pair<int, int>(weight, value));
	}
}

void printItems(vector<pair<int, int>> & items)
{
	cout << "[ ";
	for (pair<int, int> p : items)
		cout << "(" << p.first << ", " << p.second << ") ";
	cout << "]" << endl;
}