#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
float** strassen(float** mat1,float** mat2,int size);
void display(float** mat,int n);
void free_array(float **a, int r);
double compute_time(struct timespec start, struct timespec end);
void* NoThreads(void* p);
float** parallel_strassen(float** mat1,float** mat2,int size);
struct strassen_pass
{
	float**mat1;
	float **mat2;
	int l;
};
struct final
{
	float** mat;
};
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
	float **mat;
	clock_gettime(CLOCK_REALTIME, &start);
	mat=parallel_strassen(mat1,mat2,n);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Product matrix from parallelized strassen multiplication using threads:\n");
	display(mat,n);
	printf("Execution time: %.6lf sec.\n", compute_time(start, end));
	free_array(mat,n);
	free_array(mat1,n);
	free_array(mat2,n);
	return 0;
}
	
void* NoThreads(void*p)
{
	struct strassen_pass* info=p;
	float**t=strassen(info->mat1,info->mat2,info->l);
	struct final *temp=malloc(sizeof(struct final));
	temp->mat=t;
	return temp;
}

float**parallel_strassen(float**x,float**y,int size)
{
	int i,j;
	int len=size/2;
	
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
		s1[i] = malloc(sizeof(float)*len);
		s2[i] = malloc(sizeof(float)*len);
		s3[i] = malloc(sizeof(float)*len);
		s4[i] = malloc(sizeof(float)*len);
		s5[i] = malloc(sizeof(float)*len);
		s6[i] = malloc(sizeof(float)*len);
		s7[i] = malloc(sizeof(float)*len);
		s8[i] = malloc(sizeof(float)*len);
		s9[i] = malloc(sizeof(float)*len);
		s10[i] = malloc(sizeof(float)*len);
		a[i] = malloc(sizeof(float)*len);
		b[i] = malloc(sizeof(float)*len);
		c[i] = malloc(sizeof(float)*len);
		d[i] = malloc(sizeof(float)*len);
		e[i] = malloc(sizeof(float)*len);
		f[i] = malloc(sizeof(float)*len);
		g[i] = malloc(sizeof(float)*len);
		h[i] = malloc(sizeof(float)*len);	
	}
	for(i = 0;i < len;i++)
	{
		for(j = 0;j < len;j++)
		{
			s1[i][j] = y[i][j+len]-y[i+len][j+len]; //p1=a(f-h) ; s1=(f-h)
			s2[i][j] = x[i][j]+x[i][j+len];//p2=(a+b)h ; s2=(a+b)
			s3[i][j] = x[i+len][j]+x[i+len][j+len] ;//p3=(c+d)e ; s3=(c+d)
			s4[i][j] = y[i+len][j]-y[i][j];//s4=g-e
			s5[i][j] = x[i][j]+x[i+len][j+len]; //s5=a+d
			s6[i][j] = y[i][j]+y[i+len][j+len]; // s6=e+h
			s7[i][j] = x[i][j]-x[i+len][j] ; //s7=a-c
			s8[i][j] = y[i][j]+y[i][j+len] ; //s8=e+f
			s9[i][j] = x[i][j+len]-x[i+len][j+len]; //s9=b-d
			s10[i][j] = y[i+len][j]+y[i+len][j+len]; //s10=g+h
			a[i][j] = x[i][j];
			b[i][j] = x[i][j+len];
			c[i][j] = x[i+len][j];
			d[i][j] = x[i+len][j+len];
			e[i][j] = y[i][j];
			f[i][j] = y[i][j+len];
			g[i][j] = y[i+len][j];
			h[i][j] = y[i+len][j+len];			
		}
	}
	//float **p1=strassen(a,s1,len);

	struct strassen_pass*p1=malloc(sizeof(struct strassen_pass));
	p1->mat1=a;
	p1->mat2=s1;
	p1->l=len;
	//float **p2=strassen(s2,h,len);
	struct strassen_pass*p2=malloc(sizeof(struct strassen_pass));
	p2->mat1=s2;
	p2->mat2=h;
	p2->l=len;

	//float **p3=strassen(s3,e,len);
	struct strassen_pass*p3=malloc(sizeof(struct strassen_pass));
	p3->mat1=s3;
	p3->mat2=e;
	p3->l=len;

	//float **p4=strassen(d,s4,len);
	struct strassen_pass*p4=malloc(sizeof(struct strassen_pass));
	p4->mat1=d;
	p4->mat2=s4;
	p4->l=len;

	//float **p5=strassen(s5,s6,len);
	struct strassen_pass*p5=malloc(sizeof(struct strassen_pass));
	p5->mat1=s5;
	p5->mat2=s6;
	p5->l=len;

	//float **p6=strassen(s9,s10,len);
	struct strassen_pass* p6=malloc(sizeof(struct strassen_pass));
	p6->mat1=s9;
	p6->mat2=s10;
	p6->l=len;

	//float **p7=strassen(s7,s8,len);
	struct strassen_pass* p7=malloc(sizeof(struct strassen_pass));
	p7->mat1=s7;
	p7->mat2=s8;
	p7->l=len;

	pthread_t recursive_strassen[7];
	pthread_create(&recursive_strassen[0], NULL, &NoThreads,p1);
	pthread_create(&recursive_strassen[1], NULL, &NoThreads,p2);
	pthread_create(&recursive_strassen[2], NULL, &NoThreads,p3);
	pthread_create(&recursive_strassen[3], NULL, &NoThreads,p4);
	pthread_create(&recursive_strassen[4], NULL, &NoThreads,p5);
	pthread_create(&recursive_strassen[5], NULL, &NoThreads,p6);
	pthread_create(&recursive_strassen[6], NULL, &NoThreads,p7);
	
	struct final *temp1;;struct final *temp2; struct final *temp3; struct final *temp4;
	struct final *temp5; struct final *temp6; struct final *temp7; 
	pthread_join(recursive_strassen[0],(void **)&temp1 );
	pthread_join(recursive_strassen[1],(void **)&temp2 );
	pthread_join(recursive_strassen[2],(void **)&temp3 );
	pthread_join(recursive_strassen[3],(void **)&temp4 );
	pthread_join(recursive_strassen[4],(void **)&temp5 );
	pthread_join(recursive_strassen[5],(void **)&temp6 );
	pthread_join(recursive_strassen[6],(void **)&temp7 );



	free_array(s1,len);free_array(s2,len);free_array(s3,len);free_array(s4,len);free_array(s5,len);free_array(s6,len);free_array(s7,len);free_array(s8,len);
	free_array(s9,len);free_array(s10,len);
	free_array(a,len);free_array(b,len);free_array(c,len);free_array(d,len);free_array(e,len);free_array(f,len);free_array(g,len);free_array(h,len);
	free(p1);free(p2);free(p3);free(p4);free(p5);free(p6);free(p7);

	float **final=malloc(sizeof(float*)*size);
	for(i=0;i<size;i++)
	{
		final[i]=malloc(sizeof(float)*size);

	}
	for(i=0;i<len;i++)
	{
		for(j=0;j<len;j++)
		{
			final[i][j]=temp5->mat[i][j]+temp4->mat[i][j]-temp2->mat[i][j]+temp6->mat[i][j];
			final[i][j+len]=temp1->mat[i][j]+temp2->mat[i][j];
			final[i+len][j]=temp3->mat[i][j]+temp4->mat[i][j];
			final[i+len][j+len]=temp1->mat[i][j]+temp5->mat[i][j]-temp3->mat[i][j]-temp7->mat[i][j];
		}
	}
	
	free_array(temp1->mat,len);free_array(temp2->mat,len);free_array(temp3->mat,len);free_array(temp4->mat,len);free_array(temp5->mat,len);free_array(temp6->mat,len);free_array(temp7->mat,len);
	//free_array(temp1,len);free_array(temp2,len);free_array(temp3,len);free_array(temp4,len);free_array(temp5,len);free_array(temp6,len);free_array(temp7,len);
	return final;
}
float** strassen(float**x,float**y,int size)
{
	int i,j;
	int len=size/2;
	if(size==1)
	{
		float **temp=malloc(sizeof(float*));
		temp[0]=malloc(sizeof(float));
		temp[0][0]= x[0][0]*y[0][0];
		return temp;	

	}
	float**s1=malloc(sizeof(float*)*len);
	float**s2=malloc(sizeof(float*)*len);
	float**s3=malloc(sizeof(float*)*len);
	float**s4=malloc(sizeof(float*)*len);
	float**s5=malloc(sizeof(float*)*len);
	float**s6=malloc(sizeof(float*)*len);
	float**s7=malloc(sizeof(float*)*len);
	float**s8=malloc(sizeof(float*)*len);
	float**s9=malloc(sizeof(float*)*len);
	float**s10=malloc(sizeof(float*)*len);
	float **a=malloc(sizeof(float*)*len);
	float **b=malloc(sizeof(float*)*len);
	float **c=malloc(sizeof(float*)*len);
	float **d=malloc(sizeof(float*)*len);
	float **e=malloc(sizeof(float*)*len);
	float **f=malloc(sizeof(float*)*len);
	float **g=malloc(sizeof(float*)*len);
	float **h=malloc(sizeof(float*)*len);
	for(i=0;i<len;i++)
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
			s1[i][j]=y[i][j+len]-y[i+len][j+len]; //p1=a(f-h) ; s1=(f-h)
			s2[i][j]=x[i][j]+x[i][j+len];//p2=(a+b)h ; s2=(a+b)
			s3[i][j]=x[i+len][j]+x[i+len][j+len] ;//p3=(c+d)e ; s3=(c+d)
			s4[i][j]=y[i+len][j]-y[i][j];//s4=g-e
			s5[i][j]=x[i][j]+x[i+len][j+len]; //s5=a+d
			s6[i][j]=y[i][j]+y[i+len][j+len]; // s6=e+h
			s7[i][j]=x[i][j]-x[i+len][j] ; //s7=a-c
			s8[i][j]=y[i][j]+y[i][j+len] ; //s8=e+f
			s9[i][j]=x[i][j+len]-x[i+len][j+len]; //s9=b-d
			s10[i][j]=y[i+len][j]+y[i+len][j+len]; //s10=g+h
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

	float **p1=strassen(a,s1,len);
	float **p2=strassen(s2,h,len);
	float **p3=strassen(s3,e,len);
	float **p4=strassen(d,s4,len);
	float **p5=strassen(s5,s6,len);
	float **p6=strassen(s9,s10,len);
	float **p7=strassen(s7,s8,len);

	free_array(s1,len);free_array(s2,len);free_array(s3,len);free_array(s4,len);free_array(s5,len);free_array(s6,len);free_array(s7,len);free_array(s8,len);
	free_array(s9,len);free_array(s10,len);
	free_array(a,len);free_array(b,len);free_array(c,len);free_array(d,len);free_array(e,len);free_array(f,len);free_array(g,len);free_array(h,len);

	float **final=malloc(sizeof(float*)*size);
	for(i=0;i<size;i++)
	{
		final[i]=malloc(sizeof(float)*size);

	}
	for(i=0;i<len;i++)
	{
		for(j=0;j<len;j++)
		{
			final[i][j]=p5[i][j]+p4[i][j]-p2[i][j]+p6[i][j];
			final[i][j+len]=p1[i][j]+p2[i][j];
			final[i+len][j]=p3[i][j]+p4[i][j];
			final[i+len][j+len]=p1[i][j]+p5[i][j]-p3[i][j]-p7[i][j];
		}
	}
	free_array(p1,len);free_array(p2,len);free_array(p3,len);free_array(p4,len);free_array(p5,len);free_array(p6,len);free_array(p7,len);
	
	return final;
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
