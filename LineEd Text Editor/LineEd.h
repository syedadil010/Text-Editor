#ifndef LINEED_H_
#define LINEED_H_
#endif // !LINEED_H_
#include<cstring>
#include<stdio.h>
#include<iostream>
#include<ostream>
#include<list>
#include<vector>
using namespace std;


/*Line Editor*/
class LineEd
{
	list<string> buffer;//stores lines
	vector<string> clipboard;//stores copied lines
	int currentLine;//currentline
	string fileName;//filename
	int no_lines; .//number of lines
public:
	string lineaddress(string add);//checks if the lineaddress is valid
	bool correctlines(string add1, string add2);//checks if the lines are valid
	LineEd(string filename);//constructor
	void run();

	void runCommand(string input);//runs the commands.

	void a_command();//appends to buffer

	void i_command(string);//inserts at position

	void v_command(string lineaddress);//pastes text from clipboard to buffer

	void d_command(string start, string end);//deletes specified range of lines

	void x_command(string start, string end);//cuts specified range of lines

	void j_command(string start, string end);//joins specified lines on start line

	void c_command(string start, string end);//changes lines from specified range.

	void u_command();//moves current line up

	void n_command();//moves current line down

	void g_command(string start);//goes to specified lineno and makes it current line.

	void w_command();//saves buffer contents to file with user interaction

	void q_command();//quits lineEd

	void p_command(string x, string y);//prints line range.

};