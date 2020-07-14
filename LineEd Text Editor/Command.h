#ifndef COMMAND_H_
#define COMMAND_H_
#endif // !COMMAND_H_

#include<cstring>
#include<stdio.h>
#include<iostream>
#include<ostream>
using namespace std;
class Command
{
	string command_line;//stores command
	bool status;//validity of command
	string symbol;//stores symbol
	string address1;//stores address of start range
	string address2;//stores address of end range
public:
	Command(const string &command_line);//constructor
	void parse(const string &command_line);//parses the command
	string getSymbol();//returns symbol
	string getAddress1();// returns address
	string getAddress2();// returns address 
	bool getStatus();//returns status
	void setStatus(bool status);// sets status of command

};