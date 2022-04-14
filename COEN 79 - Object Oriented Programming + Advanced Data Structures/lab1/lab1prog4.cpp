#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;
int main()
{
	cout << "Think of a number between 1 and 20. Press enter when you are ready\n";
	int x;
	char answer = 'N';
	int count;
	cin >> x;
	cin.ignore();
	srand(time(0));
	if(x >= 1 && x<=20)
	{
		while(answer != 'Y')
		{
			int num = rand() % 20 +1;
			count++; 
			
			cout << "Is the number " << num << "? Y or N?\n";
			cin >> answer;
			if(answer == 'Y')
				cout << "I found the number in " << count << " steps.\n";
		}
	}
	
}
