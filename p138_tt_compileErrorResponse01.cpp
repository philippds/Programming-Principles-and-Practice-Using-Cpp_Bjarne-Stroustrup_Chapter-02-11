//	Philipp Siedler
//	Bjarne Stroustrup's PP
//	Chapter 5 Try This page 138

#include "std_lib_facilities.h"

int area(int length, int width) {
	return length * width;
}

int main()
try
{
	//int s1 = area(7;
	//int s2 = area(7)
	//Int s3 = area(7);
	//int s4 = area('7);
	keep_window_open();
}

catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}

catch (...) {
	cerr << "Unknown exception!\n";
	keep_window_open();
	return 2;
}