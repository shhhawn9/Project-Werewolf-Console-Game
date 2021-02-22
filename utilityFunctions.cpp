/*
 * Group Members: Haley Goldlist
                  Adrian Maceiras
                  Shawn Gu
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_UTILITY_FUNCTIONS_CPP__
#define __DEFINE_UTILITY_FUNCTIONS_CPP__

#include <cstdio>
#include <iostream>
using namespace std;
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

int max(int a, int b)
{
	// returns the maximum of a and b
	return (a >= b ? a : b);
}

int min(const int a, const int b)
{
	// returns the minimum of a and b
	return (a <= b ? a : b);
}

int abs(const int a) // EREZ: correct
{
	// returns the absolute value of a
	// for example: abs(3) returns 3; abs(-3) returns 3; abs(0) returns 0
	if(a < 0){
		return a * -1;
	}else{
		return a;
	}
	return a;
}

int sign(const int a) // EREZ: correct
{
	// returns the sign of a:
	// 0 if a is 0; 1 if a is positive; -1 if a is negative
	if(a==0){
		return 0;
	}else if(a > 0){
		return 1;
	}else{
		return -1;
	}
}

int manhattanDistance(const int firstX, const int firstY, const int secondX, const int secondY)
{
	// returns the "Manhattan distance" between two points:
	// the difference in their x-coordinates plus the difference in their y-coordinates.
	// this is the equivalent to picking two squares on a chessboard and counting the number of squares between them (without diagonals).
	return (abs(firstX - secondX) + abs(firstY - secondY));
}

void printChar(ostream &stream, const char c, const int times)
{
	// print a character to the screen a certain number of times
	for (int i = 0; i < times; i++)
	{
		stream << c;
	}
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE
