#include"pch.h"
#include"LineEd.h"
#include"Command.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<ostream>
#include<list>
#include<vector>
#include<string>
#include<utility>
using namespace std;

string LineEd::lineaddress(string add)
{
	if (add == ".")
		return to_string(currentLine);
	else if (add == "$")
		return to_string(buffer.size());
	else
		return add;
}
string tolowercase(string input)
{
	if (input == "")
		return "";
	string op = "";
	for (int i = 0; i < input.length(); i++)
	{
		char temp = tolower(input.at(i));
		op.push_back(temp);
	}
	return op;
}
void print(list<string> buffer)
{
	for (auto i = buffer.begin(); i != buffer.end(); ++i)
		cout << *i << endl;
}
void printv(vector<string> buffer)
{
	for (auto i = buffer.begin(); i != buffer.end(); ++i)
		cout << *i << endl;
}
bool LineEd::correctlines(string add1, string add2)
{
	if (stoi(lineaddress(add1)) > stoi(lineaddress(add2)))
	{
		return true;
	}
	return false;

}
LineEd::LineEd(string filename)
{
	currentLine = 0;
	fileName = filename;
	no_lines = 0;
	if (fileName.length() == 0)
	{
		cout << "\"?\" [New File] \n";
		buffer = { initializer_list<string>{} };
		currentLine = 0;
		return;
	}
	ifstream fin(fileName);
	if (!fin)
	{
		cout << "\"" << fileName << "\" [New File] \n";
		currentLine = 0;
		buffer = { initializer_list<string>{} };
		return;
	}
	string inputline;
	while (getline(fin, inputline))
	{
		buffer.push_back(inputline);
		no_lines++;
	}
	currentLine = no_lines;
	cout << "\"" << fileName << "\" " << no_lines << " lines \n";
}

void LineEd::run()
{

	cout << "Entering command mode" << endl;
	bool flag = false;
	while (flag != true)
	{
		cout << "?";
		string input;
		getline(cin, input);
		input = tolowercase(input);
		Command cd(input);

		if (cd.getStatus() == false)
		{
			cout << "bad command";
		}
		else if (correctlines(cd.getAddress1(), cd.getAddress2()))
		{
			cout << "bad command";
		}
		else if (buffer.size() == 0 && clipboard.size() != 0)
		{
			char comm = cd.getSymbol().at(0);
			switch (comm)
			{

			case 'a':
			{
				a_command();
				break;
			}
			case 'i':
			{
				i_command(lineaddress(cd.getAddress1()));
				break;
			}
			case 'w':

			{
				w_command();
				break;
			}

			case 'v':
			{
				v_command(lineaddress(cd.getAddress1()));
				break;
			}
			default:
				cout << "File Empty: must use one of  I,A,Q and V commands";
				break;
			}
		}
		else if (buffer.size() == 0 && clipboard.size() == 0)
		{
			char comm = cd.getSymbol().at(0);

			switch (comm)
			{

			case 'a':
			{
				a_command();
				break;
			}
			case 'i':
			{
				i_command(lineaddress(cd.getAddress1()));
				break;
			}
			case 'w':

			{
				w_command();
				break;
			}

			default:
				cout << "must use one of  I,A,Q commands";
				break;
			}
		}
		else
		{
			char comm = cd.getSymbol().at(0);
			switch (comm)
			{

			case 'a':
			{
				a_command();
				break;
			}
			case 'i':
			{
				i_command(lineaddress(cd.getAddress1()));
				break;
			}
			case 'v':
			{
				break;
			}
			case 'd':
			{
				d_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
				break;
			}
			case 'x':
			{
				x_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
				break;
			}
			case 'j':
			{
				j_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
				break;
			}
			case 'p':
			{
				p_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
				break;
			}
			case 'c':
			{
				c_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
				break;
			}
			case 'u':
			{
				u_command();
				break;
			}
			case 'n':
			{
				n_command();
				break;
			}
			case 'g':
			{
				g_command(lineaddress(cd.getAddress1()));
				break;
			}
			case 'w':
			{
				w_command();
				break;
			}
			case 'q':
			{
				q_command();
				flag = true;
				break;
			}

			default:
				break;
			}
		}
	}
}
void LineEd::runCommand(string input)
{
	input = tolowercase(input);
	Command cd(input);

	if (cd.getStatus() == false)
	{
		cout << "bad command";
	}
	else if (correctlines(cd.getAddress1(), cd.getAddress2()))
	{
		cout << "bad command";
	}
	else if (buffer.size() == 0 && clipboard.size() != 0)
	{
		char comm = cd.getSymbol().at(0);
		switch (comm)
		{

		case 'a':
		{
			a_command();
			break;
		}
		case 'i':
		{
			i_command(lineaddress(cd.getAddress1()));
			break;
		}
		case 'w':

		{
			w_command();
			break;
		}

		case 'v':
		{
			v_command(lineaddress(cd.getAddress1()));
			break;
		}
		default:
			cout << "File Empty: must use one of  I,A,Q and V commands";
			break;
		}
	}
	else if (buffer.size() == 0 && clipboard.size() == 0)
	{
		char comm = cd.getSymbol().at(0);

		switch (comm)
		{

		case 'a':
		{
			a_command();
			break;
		}
		case 'i':
		{
			i_command(lineaddress(cd.getAddress1()));
			break;
		}
		case 'w':

		{
			w_command();
			break;
		}

		default:
			cout << "must use one of  I,A,Q commands";
			break;
		}
	}
	else
	{
		char comm = cd.getSymbol().at(0);
		switch (comm)
		{

		case 'a':
		{
			a_command();
			break;
		}
		case 'i':
		{
			i_command(lineaddress(cd.getAddress1()));
			break;
		}
		case 'v':
		{
			break;
		}
		case 'd':
		{
			d_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
			break;
		}
		case 'x':
		{
			x_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
			break;
		}
		case 'j':
		{
			j_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
			break;
		}
		case 'p':
		{
			p_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
			break;
		}
		case 'c':
		{
			c_command(lineaddress(cd.getAddress1()), lineaddress(cd.getAddress2()));
			break;
		}
		case 'u':
		{
			u_command();
			break;
		}
		case 'n':
		{
			n_command();
			break;
		}
		case 'g':
		{
			g_command(lineaddress(cd.getAddress1()));
			break;
		}
		case 'w':
		{
			w_command();
			break;
		}
		case 'q':
		{
			q_command();
			//flag = true;
			break;
		}

		default:
			break;
		}
	}
	}
void LineEd::a_command()
{
	string line;
	list<string>::iterator it = buffer.begin();
	advance(it, currentLine);
	while (true)
	{
		getline(cin, line);
		if (line == ".")
			break;
		buffer.emplace(it, line);
	//	print(buffer);
		currentLine++;
	}
}
void LineEd::i_command(string lineaddress)
{
	if (buffer.empty())
	{
		cout << "bad address";
		return;
	}
	string line;
	list<string>::iterator it = buffer.begin();
	advance(it, stoi(lineaddress));
	int c = stoi(lineaddress);
	while (true)
	{
		getline(cin, line);
		if (line == ".")
			break;
		buffer.emplace(it, line);
		c++;
		print(buffer);
	}
	currentLine = c;
}
void LineEd::v_command(string lineaddress)
{
	string line;
	list<string>::iterator it = buffer.begin();
	advance(it, stoi(lineaddress));
	int c = stoi(lineaddress);
	for (vector<string>::iterator i = clipboard.begin(); i != clipboard.end(); ++i)
	{
		buffer.emplace(it, *i);
		c++;
	}
	currentLine = c;
}
void LineEd::d_command(string start, string end)
{
	string line;
	list<string>::iterator it = buffer.begin();
	list<string>::iterator it2 = buffer.begin();
	advance(it, stoi(start));
	advance(it2, stoi(end) + 1);
	int s = stoi(start);
	int e = stoi(end) + 1;
	int count = 0;
	buffer.erase(it, it2);
	print(buffer);
	for (list<string>::iterator i = buffer.begin(); i != buffer.end(); ++i)
	{
		count++;
	}
	currentLine = count;
}
void LineEd::x_command(string start, string end)
{
	string line;
	list<string>::iterator it = buffer.begin();
	list<string>::iterator it2 = buffer.begin();
	advance(it, stoi(start)-1);
	advance(it2, stoi(end));
	int s = stoi(start);
	int e = stoi(end) + 1;
	int count = 0;
	vector<string> vec(it, it2);
	clipboard = vec;
	buffer.erase(it, it2);
	//print(buffer);
	printv(clipboard);
	for (list<string>::iterator i = buffer.begin(); i != buffer.end(); ++i)
	{
		count++;
	}
	currentLine = count++;
	//cout << currentLine;
}
void LineEd::j_command(string start, string end)
{
	string line;
	list<string>::iterator it = buffer.begin();
	list<string>::iterator it2 = buffer.begin();
	advance(it, stoi(start));
	advance(it2, stoi(end) + 1);
	string temp1 = "";
	int s = stoi(start);
	int e = stoi(end) + 1;
	int count = 0;
	for (list<string>::iterator i = it; i != it2; ++i)
	{
		temp1.append(*i);
	}
	buffer.erase(it, it2);
	print(buffer);
	it = buffer.begin();
	advance(it, stoi(start));
	buffer.emplace(it, temp1);
	currentLine = stoi(start);
	//cout << currentLine;
}
void LineEd::p_command(string start, string end)
{
	if (start == end)
	{
		list<string>::iterator it = buffer.begin();
		advance(it, stoi(start)-1);
		cout << *it;
		return;
	}
	list<string>::iterator it = buffer.begin();
	list<string>::iterator it2 = buffer.begin();
	advance(it, stoi(start)-1);
	advance(it2, stoi(end));
	string temp1 = "";
	int s = stoi(start);
	int e = stoi(end) + 1;
	int count = 0;
	for (list<string>::iterator i = it; i != it2; ++i)
	{
		cout << *i<<endl;
	}
}
void LineEd::c_command(string start, string end)
{
	cout << "line " << stoi(start);
	cout << "change?";
	string change = "";
	getline(cin, change);
	cout << "To?";
	string tos = "";
	getline(cin, tos);
	list<string>::iterator it = buffer.begin();
	list<string>::iterator it2 = buffer.begin();
	advance(it, stoi(start));
	advance(it2, stoi(end));
	int ind = 0;
	for (list<string>::iterator i = it; i != it2; ++i)
	{
		while (true)
		{
			ind = 0;
			string s = *i;
			ind = s.find(change, ind);
			if (ind == -1)
				break;
			s.replace(ind, tos.length(), tos);
			ind = ind + tos.length();
			*i = s;
		}
		print(buffer);
	}
}

void LineEd::u_command()
{
	if (currentLine == 1)
	{
		cout << "BOF reached\n";
		list<string>::iterator it1 = buffer.begin();
		advance(it1, currentLine);
		cout << *it1;
		return;
	}
	list<string>::iterator it2 = buffer.begin();
	currentLine = currentLine - 1;
	cout << *it2;
}


void LineEd::n_command()
{
	list<string>::iterator it1 = buffer.begin();
	int count = 0;
	while (it1 != buffer.end())
	{
		count++;
		if (count == currentLine + 1)
		{
			currentLine = currentLine + 1;
			return;
		}
		currentLine = count;
		cout << "EOF reached\n";
	}

}

void LineEd::g_command(string start)
{
	list<string>::iterator it1 = buffer.begin();
	advance(it1, stoi(start));
	cout << *it1;
	currentLine = stoi(start);

}

void LineEd::w_command()
{

	if (fileName.length() > 0)
	{
		string option;
		cout << "save changes to the file: " << fileName << " abc.txt (y or n?)";
		getline(cin, option);
		option = tolowercase(option);
		if (option == "n")
		{
			cout << "enter file name" << endl;
			getline(cin, fileName);
		}
		ofstream fo;
		fo.open(fileName);
		list<string>::iterator it;
		for (it = buffer.begin(); it != buffer.end(); ++it)
		{

			fo << *it;
			fo << "\n";
		}
	}
}

void LineEd::q_command()
{

	cout << "quitting LineEd. Save changes to file? y or n";
	string option = "";
	getline(cin, option);
	option = tolowercase(option);
	if (option == "y")
	{
		w_command();
	}
	cout << "bye";
}