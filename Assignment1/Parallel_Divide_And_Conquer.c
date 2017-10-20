#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
float** divide_and_conquer(int i1,int i2,int j1,int j2,int i3,int i4,int j3,int j4, float** mat1,float** mat2);
void free_array(float **a, int r);
float** divide_and_conquer_thread(int i1,int i2,int j1,int j2,int i3,int i4,int j3,int j4,float** mat1,float** mat2);
void *NoThreads(void *p);
void display(float** mat,int n);
double compute_time(struct timespec start, struct timespec end);
struct dac{
	int i1;int i2;int i3;int i4;int j1;int j2;int j3;int j4;
	float** mat1;
	float** mat2;
};
struct final
{
	float** mat;
};
int threads=0;
int main()
{
	int n;
	struct timespec start,end;
	printf("Enter the size of the matrix in powers of 2 : ");
	scanf("%d",&n);
	float **mat1=malloc(sizeof(float*)*n);
	float **mat2=malloc(sizeof(float*)*n);
	int i,j;
	for(i = 0;i < n;i++)
	{
		mat1[i] = malloc(sizeof(float)*n);
		mat2[i] = malloc(sizeof(float)*n);
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
	mat= divide_and_conquer_thread(0,n,0,n,0,n,0,n,mat1,mat2);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Product matrix from parallelized divide and conquer multiplication using threads\n");
	display(mat,n);
	printf("Execution time: %.6lf sec.\n", compute_time(start, end));
	free_array(mat,n);
	free_array(mat1,n);
	free_array(mat2,n);
	return 0;
}
	

void *NoThreads(void *p)
{
	struct dac* f=p;
	float** temp = divide_and_conquer(f->i1,f->i2,f->j1,f->j2,f->i3,f->i4,f->j3,f->j4,f->mat1,f->mat2);
	struct final *t=malloc(sizeof(struct final));;
	t->mat=temp;
	return t;
}

float** divide_and_conquer_thread(int i1,int i2,int j1,int j2,int i3,int i4,int j3,int j4,float **mat1,float **mat2)
{
	float **mat3;
	struct dac *p1=malloc(sizeof(struct dac));
	p1->i1=i1; p1->i2=i1+(i2-i1)/2; p1->j1=j1; p1->j2=j1+(j2-j1)/2 ; p1->i3=i3;
	p1->i4=i3+(i4-i3)/2 ;  p1->j3=j3; p1->j4=j3+(j4-j3)/2; p1->mat1=mat1;
	p1->mat2=mat2;
	
	struct dac *p2=malloc(sizeof(struct dac));
	p2->i1=i1; p2->i2=i1+(i2-i1)/2; p2->j1=j1+(j2-j1)/2 ; p2->j2=j2; p2->i3=i3+(i4-i3)/2;  p2->i4=i4;  p2->j3=j3; p2->j4=j3+(j4-j3)/2; p2->mat1=mat1;
	p2->mat2=mat2;

	struct dac *p3=malloc(sizeof(struct dac));
	p3->i1=i1; p3->i2=i1+(i2-i1)/2; p3->j1=j1; p3->j2=j1+(j2-j1)/2 ; p3->i4=i3+(i4-i3)/2;  p3->i3=i3;  p3->j4=j4; p3->j3=j3+(j4-j3)/2; p3->mat1=mat1;p3->mat2=mat2;

	struct dac *p4=malloc(sizeof(struct dac));
	p4->i1=i1; p4->i2=i1+(i2-i1)/2; p4->j1=j1+(j2-j1)/2 ; p4->j2=j2; p4->i3=i3+(i4-i3)/2;  p4->i4=i4;  p4->j4=j4; p4->j3=j3+(j4-j3)/2; p4->mat1=mat1;
	p4->mat2=mat2;
	
	struct dac *p5=malloc(sizeof(struct dac));
	p5->i1=i1+(i2-i1)/2; p5->i2=i2; p5->j1=j1; p5->j2=j1+(j2-j1)/2 ; p5->i3=i3;
	p5->i4=i3+(i4-i3)/2 ;  p5->j3=j3; p5->j4=j3+(j4-j3)/2; p5->mat1=mat1;
	p5->mat2=mat2;

	struct dac *p6=malloc(sizeof(struct dac));
	p6->i1=i1+(i2-i1)/2; p6->i2=i2; p6->j1=j1+(j2-j1)/2; p6->j2=j2 ; p6->i4=i4;
	p6->i3=i3+(i4-i3)/2 ;  p6->j3=j3; p6->j4=j3+(j4-j3)/2; p6->mat1=mat1;
	p6->mat2=mat2;

	struct dac *p7=malloc(sizeof(struct dac));
	p7->i1=i1+(i2-i1)/2; p7->i2=i2; p7->j1=j1; p7->j2=j1+(j2-j1)/2 ; p7->i3=i3;
	p7->i4=i3+(i4-i3)/2 ;  p7->j3=j3+(j4-j3)/2; p7->j4=j4; p7->mat1=mat1;
	p7->mat2=mat2;
	
	struct dac *p8=malloc(sizeof(struct dac));
	p8->i1=i1+(i2-i1)/2; p8->i2=i2; p8->j2=j2; p8->j1=j1+(j2-j1)/2 ; p8->i4=i4;
	p8->i3=i3+(i4-i3)/2 ;  p8->j3=j3+(j4-j3)/2; p8->j4=j4; p8->mat1=mat1;
	p8->mat2=mat2;
	
	pthread_t recursive_dac[8];
	int i;
	pthread_create(&recursive_dac[0], NULL, &NoThreads,p1);
	pthread_create(&recursive_dac[1], NULL, &NoThreads,p2);
	pthread_create(&recursive_dac[2], NULL, &NoThreads,p3);
	pthread_create(&recursive_dac[3], NULL, &NoThreads,p4);
	pthread_create(&recursive_dac[4], NULL, &NoThreads,p5);
	pthread_create(&recursive_dac[5], NULL, &NoThreads,p6);
	pthread_create(&recursive_dac[6], NULL, &NoThreads,p7);
	pthread_create(&recursive_dac[7], NULL, &NoThreads,p8);;
	
	struct final *temp1;;struct final *temp2; struct final *temp3; struct final *temp4;
	struct final *temp5; struct final *temp6; struct final *temp7; struct final *temp8;
	pthread_join(recursive_dac[0],(void **)&temp1 );
	pthread_join(recursive_dac[1],(void **)&temp2 );
	pthread_join(recursive_dac[2],(void **)&temp3 );
	pthread_join(recursive_dac[3],(void **)&temp4 );
	pthread_join(recursive_dac[4],(void **)&temp5 );
	pthread_join(recursive_dac[5],(void **)&temp6 );
	pthread_join(recursive_dac[6],(void **)&temp7 );
	pthread_join(recursive_dac[7],(void **)&temp8 );

	int n,m;
	int size=i2 - i1;
	if((size)==2)
	{
		mat3=malloc(sizeof(float*)*2);
		mat3[0]=malloc(sizeof(float)*2);
		mat3[1]=malloc(sizeof(float)*2);
		mat3[0][0]=temp1->mat[0][0]+temp2->mat[0][0];
		mat3[0][1]=temp3->mat[0][0]+temp4->mat[0][0];
		mat3[1][0]=temp5->mat[0][0]+temp6->mat[0][0];
		mat3[1][1]=temp7->mat[0][0]+temp8->mat[0][0];
	}
	else
	{
		mat3=malloc(sizeof(float*)*size);
		for(m=0;m<size;m++)
		{
			mat3[m]=malloc(sizeof(float)*size);
		}
		for(m=0;m<size/2;m++)
		{
			for(n=0;n<size/2 ;n++)
			{
				mat3[m][n]=temp1->mat[m][n]+temp2->mat[m][n];
				mat3[m][n+size/2]=temp3->mat[m][n]+temp4->mat[m][n];
			}
		}
		for(m=size/2;m<size;m++)
		{
			for(n=0;n<size/2;n++)
			{
				mat3[m][n]=temp5->mat[m-size/2][n]+temp6->mat[m-size/2][n];
				mat3[m][n+size/2]=temp7->mat[m-size/2][n]+temp8->mat[m-size/2][n];
			}
		}

	}	
	free(p1);free(p2);free(p3);free(p4);free(p5);free(p6);free(p7);free(p8);
	free_array(temp1->mat,size/2);free_array(temp2->mat,size/2);free_array(temp3->mat,size/2);free_array(temp4->mat,size/2);free_array(temp5->mat,size/2);free_array(temp6->mat,size/2);free_array(temp7->mat,size/2);free_array(temp8->mat,size/2);

	return mat3;
}

float** divide_and_conquer(int i1,int i2,int j1,int j2,int i3,int i4,int j3,int j4, float**mat1,float**mat2)
{
												//i1 starting row index of sub matrix 1
	float** mat3;										//i2 ending row index of sub matrix 1
	if((i2 - i1)==1)									//j1 starting column index of sub matrix 1
	{											//j2 ending column index of sub matrix 1
		mat3 = malloc(sizeof(float*));							//i3 starting row index of sub matrix 2
		mat3[0] = malloc(sizeof(float));						//i4 ending row index of sub matrix 2
		mat3[0][0] = mat1[i1][j1]*mat2[i3][j3] ;					//j3 starting column index of sub matrix 2
		return mat3;									//j4 ending column index of sub matrix 2	
	}
	float **a1=divide_and_conquer(i1,i1+(i2-i1)/2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3,j3+(j4-j3)/2,mat1,mat2); 
	float **a2=divide_and_conquer(i1,i1+(i2-i1)/2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3,j3+(j4-j3)/2,mat1,mat2);
	float **a3=divide_and_conquer(i1,i1+(i2-i1)/2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3+(j4-j3)/2,j4,mat1,mat2);
	float **a4=divide_and_conquer(i1,i1+(i2-i1)/2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3+(j4-j3)/2,j4,mat1,mat2);
	float **a5=divide_and_conquer(i1+(i2-i1)/2,i2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3,j3+(j4-j3)/2,mat1,mat2);
	float **a6=divide_and_conquer(i1+(i2-i1)/2,i2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3,j3+(j4-j3)/2,mat1,mat2);
	float **a7=divide_and_conquer(i1+(i2-i1)/2,i2,j1,j1+(j2-j1)/2,i3,i3+(i4-i3)/2,j3+(j4-j3)/2,j4,mat1,mat2);
	float **a8=divide_and_conquer(i1+(i2-i1)/2,i2,j1+(j2-j1)/2,j2,i3+(i4-i3)/2,i4,j3+(j4-j3)/2,j4,mat1,mat2);
		
	int n,m,i;
	int size= i2-i1;
	if((i2-i1)==2)
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
		mat3=malloc(sizeof(float*)*size);
		for(m=0;m<size;m++)
		{
			mat3[m]=malloc(sizeof(float)*size);
		}
		for(m=0;m<size/2;m++)
		{
			for(n=0;n<size/2 ;n++)
			{
				mat3[m][n]=a1[m][n]+a2[m][n];
				mat3[m][n+size/2]=a3[m][n]+a4[m][n];
			}
		}
		for(m=size/2;m<size;m++)
		{
			for(n=0;n<size/2;n++)
			{
				mat3[m][n]=a5[m-size/2][n]+a6[m-size/2][n];
				mat3[m][n+size/2]=a7[m-size/2][n]+a8[m-size/2][n];
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
