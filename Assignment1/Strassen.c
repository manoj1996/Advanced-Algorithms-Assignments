#include<stdio.h>
#include<stdlib.h>
#include<time.h>
float** Strassen(float** mat1,float** mat2,int size);
void display(float** mat,int n);
void free_array(float **a, int r);
double compute_time(struct timespec start, struct timespec end);
int main()
{
	int n;
	struct timespec start,end;
	printf("Enter the size of the matrix in powers of 2 : ");
	scanf("%d",&n);
	float** mat1 = malloc(sizeof(float*)*n);
	float** mat2 = malloc(sizeof(float*)*n);
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
	mat = Strassen(mat1,mat2,n);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Product matrix from strassen multiplication:\n");
	display(mat,n);
	printf("Execution time: %.6lf sec.\n", compute_time(start, end));
	free_array(mat,n);
	return 0;
}
float** Strassen(float** x,float** y,int size)
{
	int i,j;
	int len = size/2;
	if(size == 1)
	{
		float **temp=malloc(sizeof(float*));
		temp[0]=malloc(sizeof(float));
		temp[0][0]= x[0][0]*y[0][0];
		return temp;	

	}
	float** s1=malloc(sizeof(float*)*len);
	float** s2=malloc(sizeof(float*)*len);
	float** s3=malloc(sizeof(float*)*len);
	float** s4=malloc(sizeof(float*)*len);
	float** s5=malloc(sizeof(float*)*len);
	float** s6=malloc(sizeof(float*)*len);
	float** s7=malloc(sizeof(float*)*len);
	float** s8=malloc(sizeof(float*)*len);
	float** s9=malloc(sizeof(float*)*len);
	float** s10=malloc(sizeof(float*)*len);
	float** a=malloc(sizeof(float*)*len);
	float** b=malloc(sizeof(float*)*len);
	float** c=malloc(sizeof(float*)*len);
	float** d=malloc(sizeof(float*)*len);
	float** e=malloc(sizeof(float*)*len);
	float** f=malloc(sizeof(float*)*len);
	float** g=malloc(sizeof(float*)*len);
	float** h=malloc(sizeof(float*)*len);
	for(i = 0;i < len;i++)
	{
		s1[i]=malloc(sizeof(float)*len);
		s2[i]=malloc(sizeof(float)*len);
		s3[i]=malloc(sizeof(float)*len);
		s4[i]=malloc(sizeof(float)*len);
		s5[i]=malloc(sizeof(float)*len);
		s6[i]=malloc(sizeof(float)*len);
		s7[i]=malloc(sizeof(float)*len);
		s8[i]=malloc(sizeof(float)*len);
		s9[i]=malloc(sizeof(float)*len);
		s10[i]=malloc(sizeof(float)*len);
		a[i]=malloc(sizeof(float)*len);
		b[i]=malloc(sizeof(float)*len);
		c[i]=malloc(sizeof(float)*len);
		d[i]=malloc(sizeof(float)*len);
		e[i]=malloc(sizeof(float)*len);
		f[i]=malloc(sizeof(float)*len);
		g[i]=malloc(sizeof(float)*len);
		h[i]=malloc(sizeof(float)*len);	
	}
	for(i=0;i<len;i++)
	{
		for(j=0;j<len;j++)
		{
			s1[i][j]=y[i][j+len]-y[i+len][j+len];				 //p1=a(f-h) ; s1=(f-h)
			s2[i][j]=x[i][j]+x[i][j+len];					 //p2=(a+b)h ; s2=(a+b)
			s3[i][j]=x[i+len][j]+x[i+len][j+len];				 //p3=(c+d)e ; s3=(c+d)
			s4[i][j]=y[i+len][j]-y[i][j];					 //s4=g-e
			s5[i][j]=x[i][j]+x[i+len][j+len];				 //s5=a+d
			s6[i][j]=y[i][j]+y[i+len][j+len];				 // s6=e+h
			s7[i][j]=x[i][j]-x[i+len][j];					 //s7=a-c
			s8[i][j]=y[i][j]+y[i][j+len];					 //s8=e+f
			s9[i][j]=x[i][j+len]-x[i+len][j+len];				 //s9=b-d
			s10[i][j]=y[i+len][j]+y[i+len][j+len];				 //s10=g+h
			a[i][j]=x[i][j];
			b[i][j]=x[i][j+len];
			c[i][j]=x[i+len][j];
			d[i][j]=x[i+len][j+len];
			e[i][j]=y[i][j];
			f[i][j]=y[i][j+len];
			g[i][j]=y[i+len][j];
			h[i][j]=y[i+len][j+len];			
		}
	}

	float** p1=Strassen(a,s1,len);
	float** p2=Strassen(s2,h,len);
	float** p3=Strassen(s3,e,len);
	float** p4=Strassen(d,s4,len);
	float** p5=Strassen(s5,s6,len);
	float** p6=Strassen(s9,s10,len);
	float** p7=Strassen(s7,s8,len);

	free_array(s1,len);free_array(s2,len);free_array(s3,len);free_array(s4,len);free_array(s5,len);free_array(s6,len);free_array(s7,len);free_array(s8,len);
	free_array(s9,len);free_array(s10,len);
	free_array(a,len);free_array(b,len);free_array(c,len);free_array(d,len);free_array(e,len);free_array(f,len);free_array(g,len);free_array(h,len);

	float** mat = malloc(sizeof(float*)*size);
	for(i = 0;i < size;i++)
	{
		mat[i] = malloc(sizeof(float)*size);

	}
	for(i = 0;i < len;i++)
	{
		for(j=0;j<len;j++)
		{
			mat[i][j]=p5[i][j]+p4[i][j]-p2[i][j]+p6[i][j];
			mat[i][j+len]=p1[i][j]+p2[i][j];
			mat[i+len][j]=p3[i][j]+p4[i][j];
			mat[i+len][j+len]=p1[i][j]+p5[i][j]-p3[i][j]-p7[i][j];
		}
	}
	free_array(p1,len);free_array(p2,len);free_array(p3,len);free_array(p4,len);free_array(p5,len);free_array(p6,len);free_array(p7,len);
	return mat;
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
