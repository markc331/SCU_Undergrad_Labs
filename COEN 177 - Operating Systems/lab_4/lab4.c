#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 1024
#define M 1024
#define L 1024

void initializeMatrix(int r, int c, double matrix[r][c]);
void *multiplyRow(void *arg);
void printMatrix(int r, int c, double matrix[r][c]);

pthread_t thread[N];

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

int main()
{
	int i;
	
	initializeMatrix(N, M, matrixA);
	initializeMatrix(M, L, matrixB);
	

	for(i = 0; i< N; i++) //cretaes thread for each row
		pthread_create(&thread[i], NULL, multiplyRow, (void*)(size_t)i);
	
	for(i = 0; i < N; i++)
		pthread_join(thread[i], NULL);
	
	printMatrix(N, M, matrixA);
	printMatrix(M, L, matrixB);
	printMatrix(N, L, matrixC);

	return 0;
}

void initializeMatrix(int r, int c, double matrix[r][c])
{
	srand(time(NULL));
	int i, j;
	for(i = 0; i< r; i++)
	{
		for(j = 0; j < c; j++)
			matrix[i][j] = rand() % 10;
	}
}

void printMatrix(int r, int c, double matrix[r][c])
{
	int i , j;
	for(i = 0; i < r; i++)
	{
		for( j = 0; j< c; j++)
			printf("%1f ", matrix[i][j]);
		printf("\n");
	} 
}
void *multiplyRow(void *arg)
{
	int j,k;
	double value;

	for(j = 0; j< L; j++)
	{
		value = 0.0;
		for(k = 0; k < M; k++)
		{
			value += matrixA[(int)(size_t)arg][k]*matrixB[k][j];
		}
		
		matrixC[(int)(size_t)arg][j] = value;
	}
}
