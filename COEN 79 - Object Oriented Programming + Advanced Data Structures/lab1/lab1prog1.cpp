#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
int main()
{
	cout << "Please type something:";
	char input[50];
	cin.get(input, 50);
	int num;
	int non;
	int i = 0;
	while(input[i] != '\0')
	{
		if(isalnum(input[i]));
		 num++;
		if(ispunct(input[i]))
		non++;
		i++; 
	} 
	cout << input << " has " << num << " alphanumerical characters and " << non << " non-alphanumerical characters.";	
}
