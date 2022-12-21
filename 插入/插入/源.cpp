
#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
int main()
{
	int arr[10], N, i, j, x;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	scanf("%d", &x);
	for (i = 0; x > arr[i] && i < N; i++);
	for (j = N; j > i; j--)
		arr[j] = arr[j - 1];
	arr[i] = x;
	for (i = 0; i < N + 1; i++)
		printf("%d ", arr[i]);
	return 0;
}
/*
int main()
{
	int arr[10],N,i,j;
	scanf("%d",&N);
	for(i=0;i<N;i++)
		scanf("%d",&arr[i]);
	scanf("%d",&arr[N]);
	for(i=0;i<N+1;i++)
		for(j=i+1;j<N+1-i;j++)
			if(arr[j-1]>arr[j])
			{
				arr[j-1]+=arr[j];
				arr[j]=arr[j-1]-arr[j];
				arr[j-1]=arr[j-1]-arr[j];
			}
	printf("%d",arr[0]);
	for(i=1;i<N+1;i++)
		printf(" %d",arr[i]);
	return 0;
}*/
