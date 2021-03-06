//	Philipp Siedler
//	Bjarne Stroustrup's PPP
//	Chapter 11 Drill 4

#include "std_lib_facilities.h"

int birth_year = 1988;

int main()
try
{
	int width = 12;
	cout << setw(width) << "decimal\t" << dec << birth_year << endl;
	cout << setw(width) << "hexadecimal\t" << hex << birth_year << endl;
	cout << setw(width) << "octadecimal\t" << oct << birth_year << endl;

	keep_window_open();
}
catch (runtime_error e) {
	cout << e.what() << endl;
	keep_window_open();
}
catch (...) {
	cout << "Exiting" << endl;
	keep_window_open();
}