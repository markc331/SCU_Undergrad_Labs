#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	string input;
	string reverse;
	cout << "Please type a string of 10 digits (0-9) with no space\n";
	cin >> input;
	reverse = input;
	
	int len = reverse.length();
	int n = len-1;
	for(int i = 0; i<(len/2); i++)
	{
		swap(reverse[i], reverse[n]);
		n-=1;
	}
	int counter= 11;
	for(int j = 0; j<5;j++)
	{
		cout << setw(counter);
		cout << input;
		cout << setw(counter + 6);
		cout << reverse << "\n";
		counter += 2;
	}
}
