/* 
# lab4.cpp
# Yiran Zhu and Nicolas Metzler
# Student ID's: 500571811 and 501050712
# Lab #4 - Greedy Interval Scheduling
# CPS 616 Section BA0
# Instructor: A. Ufkes
# Purpose: C++ program that determines if a hotel with N rooms can accommodate a series of room requests.
#
# We hereby attest that we are the sole owners and authors of this code (except where referenced) and that to the best of our knowledge, this code has not infringed on anyone’s copyright. 
# Credit for any ideas, coding, and other materials used to develop this code has been given to the owners of the sources used in accordance to the rules of Ryerson's Academic Integrity Policy.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <assert.h>

using namespace std;

void printRequests(vector<pair<int, int>> & roomReqs);
void printBookings(int nRooms, vector<pair<int, int>> bookings[]);

void generateIntervals(int n, vector<pair<int, int>> & intervals);
bool validateSchedule(int nRooms, vector<pair<int, int>> & intervals, vector<pair<int, int>> bookings[]);


/**************** OUR CODE HERE! ***********************************/

// Finds if the booking already is taken for another room
bool doesBookingExist(pair<int, int> room, vector<pair<int, int>> & schedule){
  std::vector<pair<int, int>>::iterator it;
    it = std::find(schedule.begin(), schedule.end(), room);
    if(it != schedule.end()){
        return true;
      }
    else
        return false;
}

// Check for start and end of booking time if any bookings collide or are inside/encompass another
bool doesBookingCollide(pair<int, int> room, vector<pair<int, int>> & schedule){
    for(int i = 0; i < schedule.size(); i++){
      if((schedule[i].first <= room.first == true && room.first < schedule[i].second == true) || (schedule[i].first <= room.second == true && room.second <= schedule[i].second == true) || (room.first <= schedule[i].first && room.second >= schedule[i].second)){
        return true;
      }
    }
  return false;
}

// Finds and adds times to room vector
void findTimes(int roomNum, vector<pair<int, int>> & schedule, vector<pair<int, int>> & roomReqs){
  // Create a Vector to store deleted values
  // This prevents us from deleting values that are copies in the requests
  vector<pair<int, int>> copies;

  for(int i = 0; i < roomReqs.size(); i++){
    // If No Room is chosen, add the rest
    if(roomNum == 0){
      schedule.push_back(roomReqs[i]);
    }
    // Check if the Booking will collide with one already added, or if it already exists in the schedule
    else if(doesBookingCollide(roomReqs[i], schedule) == false && doesBookingExist(roomReqs[i], schedule) == false){
      // Add request to schedule for given room
      schedule.push_back(roomReqs[i]);
    }
  }

  // Loop to delete entries that are added to schedule
  for(int j = 0; j < roomReqs.size(); j++){
    // Check if Booking exists in current room Schedule, and if it does not exist in copies
    if(doesBookingExist(roomReqs[j], schedule) != false && doesBookingExist(roomReqs[j], copies) == false){
      copies.push_back(roomReqs[j]);
      roomReqs.erase(roomReqs.begin() + j);
      // Must decrement j when removing an item since Vector changes      
      j--;
      }
  }
}

void scheduleRooms(int nRooms, vector<pair<int, int>> & roomReqs, vector<pair<int, int>> schedule[])
{
	/**************** YOUR CODE HERE! ***********************************/
	/* nRooms   = number of rooms available                             */
	/* roomReqs = vector of integer pairs. See test code in main()      */
	/* for an example of how to use vectors/pairs.                      */
	/* schedule = Array of vectors containing integer pairs.            */
	/* Your algorithm will fill this data structure.                    */
	/* Bookings placed in room #1 should be placed in schedule[1], etc. */
	/* Use schedule[0] to store requests that cannot be accommodated.   */
	/********************************************************************/
  
  // Create a copy so requests can be deleted when taken
  vector<pair<int, int>> requests = roomReqs;

  // Sort the requests since the result must be sorted (Had to figure this out by looking at the tester)
  sort(requests.begin(), requests.end());

  // Run the finder for each room
  for(int i = 1; i < nRooms + 1; i++){
    findTimes(i, schedule[i], requests);
  }
  // Run the finder to add the rest of the rooms to the No Room group
  findTimes(0, schedule[0], requests);

}
/**************** END OF OUR CODE! ***********************************/

int main()
{
	char name[] = "Nicolas Metzler and Yiran Zhu";
	srand((int)time(NULL));
	printf("\nCCPS616 - Lab 4 - %s\n\n", name);


	/*****************************************************************/
	/* First, test algorithm on simple example from lab description  */
	/* You should create your own additional examples here!          */
	/*****************************************************************/
	{
		// 5 requests: [(1, 2), (3, 6), (5, 8), (6, 7), (6, 8)]
		vector<pair<int, int>> requests;
		requests.push_back(pair<int, int>(1, 2));
		requests.push_back(pair<int, int>(3, 6));
		requests.push_back(pair<int, int>(5, 8));
		requests.push_back(pair<int, int>(6, 7));
		requests.push_back(pair<int, int>(6, 8));

		// Allocate array of vectors for three rooms.
		// nRooms+1 to account for bookings that can't be accommodated
		vector<pair<int, int>> three_rooms[4];
		vector<pair<int, int>> two_rooms[3];

		/** Call your scheduleRooms() function here **/
		scheduleRooms(3, requests, three_rooms);
		scheduleRooms(2, requests, two_rooms);
    
		/*********************************************/

		// Compare your results (printed below) with the optimal results
		// given in the lab description. No asserts or anything this time,
		// just verify your small-scale tests manually.
		cout << "Room request intervals:" << endl;
		printRequests(requests);
		cout << endl << "Scheduling with three rooms:" << endl;
		printBookings(3, three_rooms);
		cout << endl << "Scheduling with two rooms:" << endl;
		printBookings(2, two_rooms);
		cout << endl;
	}

	/*****************************************************************/
	/* Next, test algorithm on increasingly large random samples     */
	/*****************************************************************/
	{
		int numIntervals[] = { 4, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };
		for (int n : numIntervals)
		{
			vector<pair<int, int>> reqs;
			generateIntervals(n, reqs);

			// sqrt(n) seems like a reasonable number of rooms for n total bookings...
			int nRooms = (int) sqrt(n);
			vector<pair<int, int>> *n_rooms = new vector<pair<int, int>>[nRooms + 1];

			cout << "Testing " << n << " intervals... ";
      
      
			/** Call your scheduleRooms() function here **/
			scheduleRooms(nRooms, reqs, n_rooms);
			/*********************************************/
      
			// I will uncomment this assert when I test your code. You should too!
			assert(validateSchedule(nRooms, reqs, n_rooms));

			cout << "Passed!" << endl;
      
			delete[] n_rooms;
		}
	}

	printf("\n");
}

void printRequests(vector<pair<int, int>> & roomReqs)
{
	cout << "[ ";
	for (pair<int, int> p : roomReqs)
		cout << "(" << p.first << ", " << p.second << ") ";
	cout << "]" << endl;
}

void printBookings(int nRooms, vector<pair<int, int>> bookings[])
{
	for (int i = 1; i < nRooms + 1; i++) {
		cout << "Room #" << i << ": [ ";
		for (pair<int, int> p : bookings[i])
			cout << "(" << p.first << ", " << p.second << ") ";
		cout << "]" << endl;
	}
	cout << "No room: [ ";
	for (pair<int, int> p : bookings[0])
		cout << "(" << p.first << ", " << p.second << ") ";
	cout << "]" << endl;
}

// Function for generating random vectors of intervals. This function
// is very primitive, feel free to tweak it if you want to add more
// sophistication to the distribution of the intervals.
void generateIntervals(int n, vector<pair<int, int>> & intervals)
{
	for (int i = 0; i < n; i++)
	{
		int start = rand() % (i + 1) * 2 + 1;
		int dif = rand() % (i + 1) + 1;
		intervals.push_back(pair<int, int>(start, start + dif));
	}
}

// Function for validating scheduling. Does not check for optimal solution,
// Just verifies that no bookings overlap. Checks for feasible solution!
bool validateSchedule(int nRooms, vector<pair<int, int>> & intervals, vector<pair<int, int>> bookings[])
{
	for (int i = 1; i < nRooms + 1; i++)
	{
		// Check that intervals in each room don't overlap
		for (int j = 1; j < (int)bookings[i].size(); j++)
			if (bookings[i][j - 1].second > bookings[i][j].first){
        return false;
        }
	}

	int count = 0;
	for (int i = 0; i < nRooms + 1; i++)
	{
		// Check that interval in schedule exists in vector of intervals
		for (pair<int, int> p : bookings[i])
			if (std::find(intervals.begin(), intervals.end(), p) == intervals.end()){
				return false;
        }

		// Ensure all intervals are present in schedule (includes no room)
		count += bookings[i].size();
	}

	if (count != intervals.size()){
    return false;
    }

	return true;
}