#include"pch.h"
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
Command::Command(const string &commandline)
{
	this->command_line = commandline;
	status = false;
	parse(commandline);
}

int getCommaPos(string line)
{
	for (int i = 0; i < line.length(); i++)
	{
		if (line.at(i) == ',')
		{
			return i;
		}
	}
	return 0;
}
bool containsComma(string line)
{
	for (int i = 0; i < line.length(); i++)
	{
		if (line.at(i) == ',')
		{
			return true;
		}
	}
	return false;
}
bool containsDollar(string line)
{
	for (int i = 0; i < line.length(); i++)
	{
		if (line.at(i) == '$')
		{
			return true;
		}
	}
	return false;
}
bool isCommand(char c)
{
	int arr[] = { 'a','i','v','d','x','j','p','c','u','n','g','w','q' };
	for (int i = 0; i < size(arr); i++)
	{
		if (arr[i] == c)
		{
			return true;
		}
	}
	return false;
}
bool isComma(char c)
{
	if (c == ',')
		return true;
	return false;
}
bool isNumber(string line, int pos)
{
	if (isdigit(line.at(pos)))
		return true;
	else if (line.at(pos)=='$')
		return true;
	return false;
}
string getNumber(string line, int pos)
{
	string out = "";
	//out.append(line.substr(pos, 1));
	int i = pos;
	while (i <= line.length() - 1 && line.at(i) != ',' && line.at(i) != '\0')
	{
		out.append(line.substr(i, 1));
		i++;
	}
	return out;
}
void Command::parse(const string &commandline)
{
	if (commandline.length() == 0)
	{
		this->symbol = "p";
		this->address1 = ".";
		this->address2 = ".";
		//cout << " empty";
		return;
	}
	else if (isCommand(commandline.at(0)))
	{
		if (commandline.length() == 1)
		{
			this->symbol = commandline.at(0);
			this->address1 = ".";
			this->address2 = ".";
			status = true;
		//	cout << "z";
			return;
		}
		else if (isComma(commandline.at(1)))
		{
			this->symbol = tolower(commandline.at(0));
			status = true;
			this->address1 = ".";
			this->address2 = getNumber(commandline, 2);
		//	cout << "z,y";
			return;
		}
		else if (isNumber(commandline, 1) && !containsComma(commandline))
		{
			status = true;
			this->symbol = commandline.at(0);
			this->address1 = getNumber(commandline, 1);
			this->address2 = getNumber(commandline, 1);
		//	cout << "zx";
			return;
		}
		else if (isNumber(commandline, 1) && containsComma(commandline) && (getCommaPos(commandline) + 1 == commandline.length()))
		{
			status = true;
			this->symbol = commandline.at(0);
			this->address1 = getNumber(commandline, 1);
			this->address2 = getNumber(commandline, 1);
		//	cout << "zx,";
			return;
		}
		else if (isNumber(commandline, 1) && containsComma(commandline) && isNumber(commandline, getCommaPos(commandline) + 1))
		{
			status = true;
			this->symbol = commandline.at(0);
			this->address1 = getNumber(commandline, 1);
			this->address2 = getNumber(commandline, getCommaPos(commandline) + 1);
		//	cout << "zx,y";
			return;
		}
		else
		{
			//cout << "bad command";
			return;
		}
	}
	else if (isNumber(commandline, 0))
	{
		if (containsComma(commandline) && getCommaPos(commandline) + 1 == commandline.length())
		{

			this->symbol = "p";
			status = true;
			this->address1 = getNumber(commandline, 0);
			this->address2 = getNumber(commandline, 0);
		//	cout << "x,";
			return;
		}
		else if (containsComma(commandline) && isNumber(commandline, getCommaPos(commandline) + 1))
		{
			this->symbol = "p";
			status = true;
			this->address1 = getNumber(commandline, 0);
			this->address2 = getNumber(commandline, getCommaPos(commandline) + 1);
		//	cout << "x,y";
			return;
		}
		else if (getNumber(commandline, 0).length() == commandline.length())
		{
			if (commandline == "1$")
				return;
			this->symbol = "p";
			status = true;
			this->address1 = getNumber(commandline, 0);
			this->address2 = getNumber(commandline, 0);
		//	cout << "x";
			return;
		}
		else
		{
			//cout << "bad command";
			return;
		}
	}
	else if (isComma(commandline.at(0)))
	{
		if (commandline.length() == 1)
		{
			this->symbol = "p";
			status = true;
			this->address1 = ".";
			this->address2 = ".";
		//	cout << ",";
			return;
		}
		else if (isNumber(commandline, 1))
		{
			this->symbol = "p";
			status = true;
			this->address1 = ".";
			this->address2 = getNumber(commandline, 1);
		//	cout << ",y";
			return;
		}
		else
		{
			cout << "bad address";
		}
	}
	else
	{
	//cout << "bad command";
 }
}

string Command::getSymbol()
{
	return symbol;
}
string Command::getAddress1()
{
	return address1;
}
string Command::getAddress2()
{
	return address2;
}
bool Command::getStatus()
{
	return status;
}
void Command::setStatus(bool status)
{
	this->status = status;
}