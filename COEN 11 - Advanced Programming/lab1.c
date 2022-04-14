#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand((int)time(NULL));
	int count = 0;  						// varibale count tracks the number of correct answers
	for(int test= 0; test < 10; test++)				 // lets us do the test 10 times 
	{

		int div = rand()%12+1; 					// random number greater than 0 
		int quo = rand()%13; 					// random number including 0 
	
		int num = quo*div; 					// make sure num is whole number 
		printf("%d / %d = ",num, div);				// displays the problem 

		int answer;
		scanf("%d",&answer);					 // takes user input on answer

		if( answer == quo)					 // checks if user input is correct
		{
			printf("Right\n");
			count++;					 // adds 1 to count and stores 
		}	

		else
		{
			printf("Wrong, Correct Answer\n%d\n",quo);	 // shows correct answer if user input is wrong  	
		}

	}
	
	printf("Your total score is:%d\n",count);

}
