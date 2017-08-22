#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct solve_{
	//indices
	int i1,i2;
	//pointers to matrices
	int **m1,**m2,**ans;
	//size of matirces
	int n,m,l;
}solve;
//This function takes indices of two rows and computes the matrix for all the rows in between
void *function(void *value){
	solve *val = (solve*)value;
	int i,j;
	for(i = val->i1;i <= val->i2;i++)
	{
		for(j = 0;j <= val->l - 1;j++)
		{
			int k = 0;
			val->ans[i][j] = 0;
			for(k = 0;k < val->m;k++)
			{
				val->ans[i][j] += val->m1[i][k]*val->m2[k][j];
			}
		}
	}
}
int main()
{
	int threads;
	scanf("%d",&threads);
	int n,m,l;
	scanf("%d %d %d",&n,&m,&l);
	int i = 0,j = 0;
	int **m1 = (int**)malloc(n*sizeof(int*));
	int **m2 = (int**)malloc(m*sizeof(int*));
	int **ans = (int**)malloc(n*sizeof(int*));
	for(i = 0;i < n;i++)
	{
		m1[i] = (int*)malloc(m*sizeof(int));
	}
	for(i = 0;i < m;i++)
	{
		m2[i] = (int*)malloc(l*sizeof(int));
	}
	for(i = 0;i < n;i++)
	{
		ans[i] = (int*)malloc(l*sizeof(int));
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < m;j++)
		scanf("%d",&m1[i][j]);
	}
	for(i = 0;i < m;i++)
	{
		for(j = 0;j < l;j++)
		scanf("%d",&m2[i][j]);
	}
	//input taken
	clock_t t;
	t = clock();
	pthread_t arr[threads];
	int i1 = 0,i2 = (n/threads) - 1;
	for(i = 0;i < threads;i++)
	{
		if(i == threads - 1) i2 = n - 1;
		solve *val = (solve*)malloc(sizeof(solve));
		val->m1 = m1;
		val->m2 = m2;
		val->n = n;
		val->m = m;
		val->l = l;
		val->ans = ans;
		val->i1 = i1;
		val->i2 = i2;
		pthread_create(&arr[i],NULL,function,(void*)val);
		i1 = i2 + 1;
		i2 = i1 + (n/threads) - 1;
	}
	for(i = 0;i < threads;i++)
	{
		pthread_join(arr[i],NULL);
	}
	t = clock() - t;
	double time_taken = (double)t/CLOCKS_PER_SEC;
	printf("time taken is %f\n",time_taken);
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < l;j++)
		{
			printf("%d ",ans[i][j]);
		}
		printf("\n");
	}
}
