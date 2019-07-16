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
		for(j = i+1; j<n; j++)
		{
			if(a[i]>a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}