//	Philipp Siedler
//	Bjarne Stroustrup's PP
//	Chapter 7 Exercise 10

#include "std_lib_facilities.h"

const char let = '#';
const char quitProg = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqroot = 'S';
const char power = 'P';
const char constant = 'C';
const char reset = 'R';
const char help = 'H';

struct Token {
	char kind;
	int value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, int val) :kind(ch), value(val) { }
	Token(char ch, string val) :kind(ch), name(val) { } //Error 1: Line missing
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char);
};

Token Token_stream::get()
{
	if (full) {
		full = false; return buffer;
	}
	char ch;
	cin.get(ch);

	while (isspace(ch)) {
		if (ch == '\n') return Token(print); // if newline detected, return print Token
		cin.get(ch);
	}

	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case 'k':
	case ',':
	{
		return Token(ch);
	}
	case '#':
	{
		return Token(let);
	}
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.unget();
		double val;
		cin >> val;
		int valInt = narrow_cast<double>(val);
		return Token(number, valInt);
	}
	default:
	{
		if (isalpha(ch) || ch == '_') { //is ch a letter?
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) { //reads chars, strings or digits
				s += ch;
			}
			cin.unget(); //puts the most recently read character back into the stream
			if (s == "quit") return Token(quitProg);
			if (s == "sqrt") return Token(sqroot);
			if (s == "pow") return Token(power);
			if (s == "const") return Token(constant);
			if (s == "reset") return Token(reset);
			if (s == "help" || s == "Help") return Token(help);
			return Token(name, s);
		}
		error("Bad token");
		return Token(' ');
	}
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch;
	while (cin >> ch) {
		if (ch == c) return;
	}
}

struct Variable {
	string name;
	int value;
	bool immutable;
	Variable(string n, int v, bool i) :name(n), value(v), immutable(i) { }
};

class Symbol_table {
public:
	vector<Variable> var_table;
	int get(string);
	void set(string, int);
	bool is_declared(string);
	int declare(char);
	bool is_immutable(string);
};

Token_stream ts;
int expression();
int primary();

int Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i) {
		if (var_table[i].name == s) {
			return var_table[i].value;
		}
	}
	error("get: undefined name ", s);
	return 0.0;
}

void Symbol_table::set(string s, int d)
{
	for (int i = 0; i <= var_table.size(); ++i) {
		if (var_table[i].name == s) {
			var_table[i].value = d;
			return;
		}
	}
	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < var_table.size(); ++i) {
		if (var_table[i].name == s) return true;
	}
	return false;
}

int Symbol_table::declare(char kind)
{
	Token t = ts.get();
	if (t.kind != name) {
		error("name expected in declaration");
	}

	string name = t.name;
	if (kind == let || kind == constant) {
		if (is_declared(name)) error(name, " declared twice");
	}
	else if (kind == reset) {
		if (!is_declared(name))
			error(name, " has not been declared");
		if (is_immutable(name))
			error(name, " is a constant");
	}
	else {
		error("unknown statement");
	}

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	int d = expression();
	if (is_declared(name))
		set(name, d);
	else
		var_table.push_back(Variable(name, d, (kind == constant)));
	return d;
}

bool Symbol_table::is_immutable(string s)
{
	for (int i = 0; i<int(var_table.size()); ++i)
		if (var_table[i].name == s && var_table[i].immutable) return true;
	return false;
}

int pow_function(Token _t) {
	_t = ts.get();
	if (_t.kind != '(') {
		error("'(' expected");
	}

	int x = expression();

	_t = ts.get();
	if (_t.kind != ',') {
		error("',' expected");
	}

	int n = expression();
	_t = ts.get();
	if (_t.kind == ')') {
		return pow(x, n);
	}
	else {
		error("Expected ')'");
	}
}

int sqrt_function(Token _t) {
	_t = ts.get();
	if (_t.kind != '(') {
		error("'(' expected");
	}
	ts.unget(_t);
	int d = primary();
	if (d < 0.0) {
		error("negative square root");
	}
	return sqrt(d);
}


Symbol_table st;

int primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		int d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
	{
		return -primary();
	}
	case '+':
	{
		return primary();
	}
	case number:
	{
		return t.value;
	}
	case sqroot:
	{
		return sqrt_function(t);
	}
	case power:
	{
		return pow_function(t);
	}
	case name:
	{
		return st.get(t.name);
	}
	default:
	{
		error("primary expected");
		return 0.0;
	}
	}
}

int term()
{
	int left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case 'k':
		{
			left *= 1000;
			break;
		}
		case '*':
		{
			left *= primary();
			break;
		}
		case '/':
		{
			int d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<double>(left);
			int i2 = narrow_cast<double>(primary());
			if (i2 == 0) error("%: divide by zero");
			left = i1%i2;
			break;
		}
		default: {
			ts.unget(t);
			return left;
		}
		}
	}
}

int expression()
{
	int left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
		{
			left += term();
			break;
		}
		case '-':
		{
			left -= term();
			break;
		}
		default:
		{
			ts.unget(t);
			return left;
		}
		}
	}
}

int statement()
{
	Token t = ts.get();
	int d;
	if (t.kind == let || t.kind == reset || t.kind == constant) {
		d = st.declare(t.kind);
	}
	else {
		ts.unget(t);
		d = expression();
	}
	t = ts.get();
	if (t.kind != print) {
		error("Missing terminator");
	}

	return d;
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	cout << "Welcome to my calculator.\n"
		<< "Just hit enter or ; at the end of your function to calculate.\n"
		<< "Enter help or Help for help or quit to exit the program.\n";
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) {
			t = ts.get();
		}
		if (t.kind == help) {
			cout << "You can use / *-+operators.\n"
				<< "Declaring variables using #, for example: # x = 5.\n";
		}
		else {
			if (t.kind == quitProg) {
				return;
			}
			ts.unget(t);
			cout << result << statement() << endl;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c&& c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}