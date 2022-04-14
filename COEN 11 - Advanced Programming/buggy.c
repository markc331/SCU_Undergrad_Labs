#include <stdio.h>
#include <math.h>

typedef struct point
{
	float x, y;
}POINT;
  
POINT add(POINT p1, POINT p2)
{
	p1.x = p1.x + p2.x;
	p1.x = p1.x + p2.x;

	return p1; 
}

float distance(POINT p1, POINT p2)
{
	float xdiff, ydiff; 
	xdiff = p1.x - p2.x;
	ydiff = p1.y - p2.y; 

	return sqrt(xdiff*xdiff+ydiff*ydiff); 
}

int main(void)
{
	POINT a, b, c; 

	a.x = 0; 
	a.y = 0; 
	
	b.x = 2; 
	b.y = 2; 
	
	c.x = 3; 
	c.y = 2; 

	printf("%f\n", distance(a, add(b,c))); 
}

