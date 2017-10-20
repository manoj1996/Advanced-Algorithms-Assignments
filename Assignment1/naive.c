#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float** naive(float** mat1,float** mat2,int n);
void display(float** mat,int n);
void free_array(float **a, int r);
double compute_time(struct timespec start, struct timespec end);
int main()
{
	int n;
	struct timespec start,end;
	printf("Enter the size of the matrix in powers of 2 : ");
	scanf("%d",&n);
	float** mat1=malloc(sizeof(float*)*n);
	float** mat2=malloc(sizeof(float*)*n);
	int i,j;
	for(i = 0;i < n;i++)	//allocates memory to the two matrices
	{
		mat1[i]=malloc(sizeof(float)*n);
		mat2[i]=malloc(sizeof(float)*n);
	}
	/*
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			mat1[i][j] = random()%10;
			mat2[i][j] = random()%10;
		}
	}
	*/
	printf("Enter the elements of matrix 1 in row major form\n");
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			scanf("%f",&mat1[i][j]);
		}
	}
	printf("Enter the elements of matrix 2 in row major form\n");
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			scanf("%f",&mat2[i][j]);
		}
	}
	float** mat;
	clock_gettime(CLOCK_REALTIME, &start);	
	mat = naive(mat1,mat2,n);	//calls matrix multiplication by naive method
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Product matrix from naive multipication\n");
	display(mat,n);
	printf("Execution time: %.6lf sec.\n", compute_time(start, end));
	free_array(mat,n);
	return 0;
}
float** naive(float** mat1,float** mat2,int n)
{
	int i,j,k;
	float** mat3 = malloc(sizeof(float*)*n); //product matrix
	for(i = 0;i < n;i++)
	{
		mat3[i]=calloc(n,sizeof(float)); //calloc initializes all matrix elements to their default values
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			float c = 0;
			for(k = 0;k < n;k++)
			{
				c = c + mat1[i][k] * mat2[k][j];  //partial product computation
			}
			mat3[i][j]=c;
		}
	}
	return mat3;
}
void display(float** mat,int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			printf("%.2lf   ",mat[i][j]);
		}
		printf("\n");
	}
}
void free_array(float **a, int r)
{
	int i;
	for(i = 0; i < r; i++)
	{
		free(a[i]);
	}
	free(a);
}
double compute_time(struct timespec start, struct timespec end)
{
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}
