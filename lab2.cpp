/* 
# lab2.cpp
# Yiran Zhu and Nicolas Metzler
# Student ID's: 500571811 and 501050712
# Lab #1 - Divide and Conquer
# CPS 616 Section BA0
# Instructor: A. Ufkes
# Purpose: C++ program that performs large integer multiplication.
#
# I hereby attest that I am the sole owner and author of this code (except where referenced) and that to the best of my knowledge, this code has not infringed on anyone’s copyright. 
# Credit for any ideas, coding, and other materials used to develop this code has been given to the owners of the sources used in accordance to the rules of Ryerson's Academic Integrity Policy.
*/

#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <bits/stdc++.h>



using namespace std;
using namespace std::chrono; // Namespace for fancy ms timing

// Addition and subtraction of integer strings is provided for your convenience
string addBigInt(string s1, string s2);
string subBigInt(string s1, string s2);
bool isSmaller(string s1, string s2);

string mult4(string s1, string s2) {
  // Declare Variables
  int n1 = s1.size(), n2 = s2.size(), i1 = n1 - 1, i2, i3 = 0, m4i1, m4i2, tempDig;
  string m4(n1 + n2, 0);

   // Two loops since complexity is n^2
   while(i1 >= 0) {
     i2 = n2 - 1;
      while(i2 >= 0) {
            m4i1 = i1 + i2 + 1;
            m4i2 = i1 + i2;
            tempDig = m4[m4i1] + ((s1[i1] - '0') * (s2[i2] - '0'));
            m4[m4i2] += tempDig / 10;
            m4[m4i1] = tempDig % 10;
            
        i2--;
      }
     i1--;
   }
   // Add any additional 0's
   int m4size = m4.size();
   while(i3 < m4size) {
     m4[i3] += '0';
     i3++;
   }
  
   // Check for erroneous leading 0's
   if (m4[0] == '0') {
      return m4.substr(1);
   }
   return m4;
}



std::string stringPow (std::string s1, int x) {
   // Add zeros to the end of the string
   std::string zeros = "";
   for (int i = 0; i < x; i ++) {
      zeros = zeros + "0";
   }
   return s1 + zeros;
}

std::string mult3a(std::string xString, std::string yString) {
	//std::cout << "mult3a" << std::endl;
   int nx = xString.length();
   int ny = yString.length();
   // Base case
   if (nx == 1 || ny == 1)
      return std::to_string(std::stoi(xString) * std::stoi(yString));
   int n = nx;
   if (nx < ny)
      n = ny;
   std::string x1 = xString.substr(0, n/2); //unsigned long long int x1 = x / tenPowull(n/2);
   std::string x2 = xString.substr(n/2); //unsigned long long int x2 = x - x1 * tenPowull(n/2);
   std::string y1 = yString.substr(0, n/2); //unsigned long long int y1 = y / tenPowull(n/2);
   std::string y2 = yString.substr(n/2); //unsigned long long int y2 = y - y1 * tenPowull(n/2);
   std::string xy1 = mult3a(x1, y1);
   std::string xy2 = mult3a(x2, y2);
   std::string xy3 = addBigInt(mult3a(x1, y2), mult3a(x2, y1));
   return addBigInt(addBigInt(stringPow(xy1, n), stringPow(xy3, n/2)), xy2);
}

std::string mult3b(std::string xString, std::string yString) {
   // Base case
	// Since xString is the same length as yString, only need the length of one of them
	int n = xString.length();
	// xString and yString only need to be smaller than the square root of the unsigned long long max value, 18446744073709551615
   if (xString.length() <= 10 && isSmaller(xString, "4294967296") && isSmaller(yString, "4294967296")) 
		return std::to_string(std::stoll(xString) * std::stoll(yString));
   std::string x1 = xString.substr(0, n/2); //unsigned long long int x1 = x / tenPowull(n/2);
   std::string x2 = xString.substr(n/2); //unsigned long long int x2 = x - x1 * tenPowull(n/2);
   std::string y1 = yString.substr(0, n/2); //unsigned long long int y1 = y / tenPowull(n/2);
   std::string y2 = yString.substr(n/2); //unsigned long long int y2 = y - y1 * tenPowull(n/2);
   std::string xy1 = mult3a(x1, y1);
   std::string xy2 = mult3a(x2, y2);
   std::string xy3 = addBigInt(mult3a(x1, y2), mult3a(x2, y1));
   return addBigInt(addBigInt(stringPow(xy1, n), stringPow(xy3, n/2)), xy2);
}

// Return random integer string of length n
string randIntString(int n)
{
	string s(n, '0');
	s[0] = rand() % 9 + '1'; // Avoid leading 0
	for (int i = 1; i < n; i++)
		s[i] = rand() % 10 + '0';
	return s;
}

int main()
{
	char name[] = "Nicolas and Yiran";

	srand((int)time(NULL));
	printf("\nCCPS616 - Lab 2 - %s\n\n", name);

	/********************************************/
	/* Sanity check #1: Example from the slides */
	/********************************************/
	{
		cout << "Sanity check #1: Example from the slides" << endl;
		string op1 = "3563474256143563", op2 = "8976558458718976";
		string sol = "31987734976412811376690928351488";
		cout << "  " << op1 << " * " << op2 << " = " << sol << endl;
		

		/*******************************************/
		/* Call your multiplication functions here */
		/*******************************************/
		string prod_m4  = mult4(op1, op2);
		string prod_m3a = mult3a(op1, op2);
		string prod_m3b = mult3b(op1, op2);
		/*******************************************/
		/*******************************************/

		
		if (prod_m4 == sol) cout << "  mult4...  PASSED!" << endl;
		else cout << "  mult4...  FAILED: " << prod_m4 << endl;
		
		if (prod_m3a == sol) cout << "  mult3a... PASSED!" << endl;
		else cout << "  mult3a... FAILED: " << prod_m3a << endl;

		if (prod_m3b == sol) cout << "  mult3b... PASSED!" << endl;
		else cout << "  mult3b... FAILED: " << prod_m3b << endl;
	}

	/****************************************************************/
	/* Sanity check #2: Small strings tested against primitive mult */
	/****************************************************************/
	{
		cout << "\nSanity check #2: Small strings tested against primitive *" << endl;
        int m4Correct = 0;
        int m3aCorrect = 0;
        int m3bCorrect = 0;
		for (int i = 0; i < 10000; i++)
		{
			// Max Length of 8 means long long unsigned won't overflow
			string op1 = randIntString(8), op2 = randIntString(8);
			// Product using primitive multiplication
			string prod(to_string(stoull(op1) * stoull(op2)));


			/*******************************************/
			/* Call your multiplication functions here */
			/*******************************************/
			string prod_m4  = mult4(op1, op2);
			string prod_m3a = mult3a(op1, op2);
			string prod_m3b = mult3b(op1, op2);
			/*******************************************/
			/*******************************************/
			
			
			// Assert will fail if results don't match primitive mult
            //assert(prod == prod_m4 && prod == prod_m3a && prod == prod_m3b);
            if (prod == prod_m4) m4Correct++;
            if (prod == prod_m3a) m3aCorrect++;
            if (prod == prod_m3b) m3bCorrect++;
                       
		}
		printf("   m4  passed %5d/10000 (%.0lf%%)\n", m4Correct, m4Correct/10000.0);
        printf("   m3a passed %5d/10000 (%.0lf%%)\n", m3aCorrect, m3aCorrect/10000.0);
        printf("   m3b passed %5d/10000 (%.0lf%%)\n", m3bCorrect, m3bCorrect/10000.0);
       
	}

	/******************************************************************/
	/* Time for the real tests! Time all three and verify correctness */
	/******************************************************************/
	{
		// Add string sizes as you see fit, but these are a good starting point
		int string_sizes[] = { 512, 1024, 2048, 4096 }; 
		int n2avg = 10; // Average over 10 trials once again
                
		for (int n : string_sizes)
		{
			int m4_time = 0, m3a_time = 0, m3b_time = 0;
			string op1 = randIntString(n);
			string op2 = randIntString(n);
			string prod_m4, prod_m3a, prod_m3b;
            
			printf("mult4()  %5d digits: ", n);
			for (int k = 0; k < n2avg; k++)
			{
				auto begin = high_resolution_clock::now();

				/********** Call mult4() here **********/
				prod_m4 = mult4(op1, op2);
				/***************************************/

				auto dur = high_resolution_clock::now() - begin;
				m4_time += (int)duration_cast<milliseconds>(dur).count();
				std::cout << "." << std::flush;
			}
			printf(" Avg: %dms\n", m4_time / n2avg);


			printf("mult3a() %5d digits: ", n);
			for (int k = 0; k < n2avg; k++)
			{
				auto begin = high_resolution_clock::now();

				/********** Call mult3a() here **********/
				prod_m3a = mult3a(op1, op2);
				/****************************************/

				auto dur = high_resolution_clock::now() - begin;
				m3a_time += (int)duration_cast<milliseconds>(dur).count();
				std::cout << "." << std::flush;
			}
			printf(" Avg: %dms\n", m3a_time / n2avg);


			printf("mult3b() %5d digits: ", n);
			for (int k = 0; k < n2avg; k++)
			{
				auto begin = high_resolution_clock::now();

				/********** Call mult3b() here **********/
				prod_m3b = mult3b(op1, op2);
				/****************************************/

				auto dur = high_resolution_clock::now() - begin;
				m3b_time += (int)duration_cast<milliseconds>(dur).count();
				std::cout << "." << std::flush;
			}
			printf(" Avg: %dms\n", m3b_time / n2avg);

			// Make sure all three products are equal. Of course they could all still be wrong...
			if (prod_m4 == prod_m3a && prod_m3a == prod_m3b)
                printf("         %5d digits: PASSED (m4==m3a==m3b)\n", n);
            else
                printf("         %5d digits: FAILED (m4,m3a,m3b results differ)\n", n);

		}
	}

	cout << "All done!" << endl;
}


// Integer string addition provided for your convenience
// Feel free to modify, update, whatever.
string addBigInt(string s1, string s2)
{
	if (s1.length() > s2.length())
		swap(s1, s2);

	string ssum = "";
	int n1 = s1.length(), n2 = s2.length();
	int diff = n2 - n1, carry = 0;

	for (int i = n1 - 1; i >= 0; i--) {
		int sum = ((s1[i] - '0') + (s2[i + diff] - '0') + carry);
		ssum.push_back(sum % 10 + '0');
		carry = sum / 10;
	}
	for (int i = n2 - n1 - 1; i >= 0; i--) {
		int sum = ((s2[i] - '0') + carry);
		ssum.push_back(sum % 10 + '0');
		carry = sum / 10;
	}
	if (carry)
		ssum.push_back(carry + '0');
	std::reverse(ssum.begin(), ssum.end());
	return ssum;
}


// Helper function used by subBigInt() below
// Return true if str1 is smaller than str2
bool isSmaller(string str1, string str2)
{
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2) 
		return true;
	if (n2 > n1) 
		return false;

	for (int i = 0; i<n1; i++) {
		if (str1[i] < str2[i]) 
			return true;
		else if (str1[i] > str2[i])	
			return false;
	}
	return false;
}

// Integer string subtraction provided for your convenience
// Feel free to modify, update, whatever.
string subBigInt(string s1, string s2) 
{
	if (isSmaller(s1, s2)) 
		swap(s1, s2);
	
	string sdif = "";
	int n1 = s1.length(), n2 = s2.length();
	int diff = n1 - n2, carry = 0;

	for (int i = n2 - 1; i >= 0; i--) {
		int sub = ((s1[i + diff] - '0') - (s2[i] - '0') - carry);
		if (sub < 0) {
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;
		sdif.push_back(sub + '0');
	}
	for (int i = n1 - n2 - 1; i >= 0; i--) {
		if (s1[i] == '0' && carry) {
			sdif.push_back('9');
			continue;
		}
		int sub = ((s1[i] - '0') - carry);
		if (i > 0 || sub > 0)
			sdif.push_back(sub + '0');
		carry = 0;
	}
	std::reverse(sdif.begin(), sdif.end());

	return sdif;
}


