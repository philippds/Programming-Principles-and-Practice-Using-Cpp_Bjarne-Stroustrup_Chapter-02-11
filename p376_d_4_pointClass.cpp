//	Philipp Siedler
//	Bjarne Stroustrup's PPP
//	Chapter 10 Drill 4

#include "std_lib_facilities.h"

class Point {
public:
	Point(double _x, double _y);
	void set_pt(double _x, double _y);
	double get_pt_x() { return x; }
	double get_pt_y() { return y; }
private:
	double x;
	double y;
};

Point::Point(double _x, double _y) {
	x = _x;
	y = _y;
}

void Point::set_pt(double _x, double _y) {
	x = _x;
	y = _y;
}

ostream& operator<<(ostream& os, Point& _pt) {
	os << "(" << _pt.get_pt_x() << " ," << _pt.get_pt_y() << ")" << endl;
	return os;
}

vector<Point> original_pts;

void fill_original_pts() {
	while (true) {
		cout << "Enter point pairs in format x,y.\n"
			"To end your input type x" << endl;
		double x, y;
		char comma;
		char check;
		cin >> check;

		if (check == 'x') {
			break;
		}
		else {
			cin.putback(check);
		}

		if (cin >> x >> comma >> y) {
			if (comma != ',') {
				cout << "X and y seperated by comma, not: " << comma << endl;
			}
			else {
				Point pt(x, y);
				original_pts.push_back(pt);
			}
		}
		else {
			cin.clear();
			string check1;
			cin >> check1;
			cout << "Invalid value input: " << check1 << endl;
		}
	}
}

void print_original_pts(vector<Point> _pts) {
	for (int i = 0; i < _pts.size(); i++) {
		cout << _pts[i];
	}
}

void output_original_pts(vector<Point> _pts) {
	string oname = "pts.txt";
	ofstream ost{ oname };
	if (!ost) error("can't open output file ", oname);

	cout << "Writing file! " << oname << endl;
	for (int i = 0; i < _pts.size(); i++) {
		ost << "(" << _pts[i].get_pt_x() << ", " << _pts[i].get_pt_y() << ")" << endl;
	}
}

int main()
try
{
	fill_original_pts();
	print_original_pts(original_pts);
	output_original_pts(original_pts);

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