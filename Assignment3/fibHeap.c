#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int nNodes;

/* structure of a node */

struct fheap_node
{
	struct fheap_node *parent;
	struct fheap_node *left;
	struct fheap_node *right;
	struct fheap_node *child;
	int degree;
	int mark;
	int key; 
};
struct fheap_node *min,*min1;

/* creating fibonacci heap */

void create_fib()
{
	min->parent=0;
	min->key=0;
	min->left=0;
	min->right=0;
	min->child=0;
	nNodes=0;
}

/* inserting in fibonacci heap */

void Finsert(int val)
{
	struct fheap_node *fheap;
	fheap=malloc(sizeof(struct fheap_node));
	fheap->key=val;
	fheap->parent=0;
	fheap->left=0;
	fheap->right=0;
	fheap->child=0; 
	if(min->key!=0)
	{
		fheap->right=min;
		fheap->left=min->left;
		(min)->left=fheap;
		(fheap->left)->right=fheap;
		if(val<min->key)
			min=fheap; 
	}
	else
	{
		fheap->key=val;
		min=fheap;
		min->left=min;
		min->right=min;
	}
	nNodes++;
}

/* Displaying Fibonacci heap*/

void display()
{
	struct fheap_node *q,*chil;
	if(min==0)
	{
		printf("\n Fibonacci heap is empty");
		return;
	}
	q=min;
	printf("\n Fibonacci heap display");
	do
	{
		printf("\t%d ",q->key);
		if(q->child!=0)
		{
			display(q->child);
		}
		q=q->right;
	}
	while(q!=min);
}

/* finding minimum key in heap */

void findmin()
{
	printf("\nminimum is %d: ",min->key);
}
int main ()
{
	int option,n,i,m;
	min=0;
	while(1)
	{
		printf("\nMenu\n");
		printf("1:create fibonacci heap\n");
		printf("2:insert in fibonacci heap\n");
		printf("3: find min in fibonacci heap \n");
		printf("4:display\n");
		printf("5: exit \n");
		scanf ("%d",&option);
		switch(option)
		{
			case 1 :create_fib();
				break;
			case 2: printf("\nenter the element= ");
				scanf("%d",&n);
				Finsert(n);
				break;
			case 3: findmin();
				break;
			case 4: display();
				break;
			case 5 :exit(1);
			default: printf("\nwrong choice... try again \n ");
		}
	 }
} 
