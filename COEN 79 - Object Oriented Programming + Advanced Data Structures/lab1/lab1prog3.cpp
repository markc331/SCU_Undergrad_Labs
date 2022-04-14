#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdio.h>

using namespace std;

int main(int argc, const char * argv[])
{
	if(argc != 2)
	{
	cout << "Please enter text file\n";
	return 1;
	}
	
	fstream fs;
	string temp;
	fs.open(argv[1]);
	
	while(fs >> temp)
	{
		if(temp.length() >= 10)
		{
			int len = temp.size();
			for(int i= 0; i < len; i++)
			{
				if(ispunct(temp[i]))
					temp.erase(i--, 1);
				if(isdigit(temp[i]))
					temp.erase(i--,1);
				else
					temp[i] = toupper(temp[i]);
			}
			if(temp.length() >= 10)
				cout << temp << "\n";
		}	
	}
	fs.close();
}
