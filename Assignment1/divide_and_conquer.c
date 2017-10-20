#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void free_array(float **a, int r);
float** divide_and_conquer(int i1,int i2,int j1,int j2,int i3,int i4,int j3,int j4, float** mat1,float** mat2);
void display(float** mat,int n);
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
	for(i = 0;i < n;i++)
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
	mat = divide_and_conquer(0,n,0,n,0,n,0,n,mat1,mat2);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Product matrix from divide and conquer multiplication\n");
	display(mat,n);
	printf("Execution time: %.6lf sec.\n", compute_time(start, end));
	free_array(mat,n);
	return 0;
}
float** divide_and_conquer(int i1,int i2,int j1,int j2,int i3,int i4,int j3,int j4, float** mat1,float** mat2)
{												//i1 starting row index of sub matrix 1
	float** mat3;										//i2 ending row index of sub matrix 1
	if((i2 - i1)==1)									//j1 starting column index of sub matrix 1
	{											//j2 ending column index of sub matrix 1
		mat3 = malloc(sizeof(float*));							//i3 starting row index of sub matrix 2
		mat3[0] = malloc(sizeof(float));						//i4 ending row index of sub matrix 2
		mat3[0][0] = mat1[i1][j1]*mat2[i3][j3] ;					//j3 starting column index of sub matrix 2
		return mat3;									//j4 ending column index of sub matrix 2
	}	
														
	float** a1=divide_and_conquer(i1,i1+(i2-i1)/2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3,j3+(j4-j3)/2,mat1,mat2); 
	float** a2=divide_and_conquer(i1,i1+(i2-i1)/2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3,j3+(j4-j3)/2,mat1,mat2);
	float** a3=divide_and_conquer(i1,i1+(i2-i1)/2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3+(j4-j3)/2,j4,mat1,mat2);
	float** a4=divide_and_conquer(i1,i1+(i2-i1)/2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3+(j4-j3)/2,j4,mat1,mat2);
	float** a5=divide_and_conquer(i1+(i2-i1)/2,i2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3,j3+(j4-j3)/2,mat1,mat2);
	float** a6=divide_and_conquer(i1+(i2-i1)/2,i2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3,j3+(j4-j3)/2,mat1,mat2);
	float** a7=divide_and_conquer(i1+(i2-i1)/2,i2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3+(j4-j3)/2,j4,mat1,mat2);
	float** a8=divide_and_conquer(i1+(i2-i1)/2,i2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3+(j4-j3)/2,j4,mat1,mat2);
		
	int n,m,i;
	int size= i2 - i1;
	if((i2-i1) == 2)
	{
		mat3=malloc(sizeof(float*)*2);
		mat3[0]=malloc(sizeof(float)*2);
		mat3[1]=malloc(sizeof(float)*2);
		mat3[0][0]=a1[0][0]+a2[0][0];
		mat3[0][1]=a3[0][0]+a4[0][0];
		mat3[1][0]=a5[0][0]+a6[0][0];
		mat3[1][1]=a7[0][0]+a8[0][0];
	}
	else
	{
		mat3 = malloc(sizeof(float*)*size);
		for(m = 0;m < size;m++)
		{
			mat3[m]=malloc(sizeof(float)*size);
		}
		for(m = 0;m < size/2;m++)
		{
			for(n = 0;n < size/2 ;n++)
			{
				mat3[m][n]=a1[m][n]+a2[m][n];
				mat3[m][n+size/2]=a3[m][n]+a4[m][n];
			}
		}
		for(m = size/2;m < size;m++)
		{
			for(n = 0;n < size/2;n++)
			{
				mat3[m][n] = a5[m-size/2][n]+a6[m-size/2][n];
				mat3[m][n+size/2] = a7[m-size/2][n]+a8[m-size/2][n];
			}
		}

	}	
	free_array(a1,size/2);free_array(a2,size/2);free_array(a3,size/2);free_array(a4,size/2);free_array(a5,size/2);free_array(a6,size/2);free_array(a7,size/2);free_array(a8,size/2);
	return mat3;
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
double compute_time(struct timespec start, struct timespec end)
{
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}
