#include <stdio.h>

void sort(int a[], int n);

int main()
{
	int arr[6] = {7,9,6,12,3,1};
	sort(arr,6);
	for(int i = 0; i<6; i++)
	{
		printf("%d\t", arr[i]);
	}
	return 0;
}

void sort(int a[], int n)
{
	int i;
	int j;
	int temp;
	for(i=0; i<n-1; i++)
	{
		for(j=0; j<n-1-i; j++)
		{
			if(  a[j] > a[j+1] )
			{
				temp  = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}