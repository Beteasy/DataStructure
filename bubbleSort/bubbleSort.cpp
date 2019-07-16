#include <stdio.h>

#define TRUE 1
#define FALSE 0

void bubble_sort(int a[], int n);


int main()
{
	int arr[6] = {7,9,6,12,3,1};
	bubble_sort(arr,6);
	for(int i = 0; i<6; i++)
	{
		printf("%d\t", arr[i]);
	}
	return 0;
}

void bubble_sort(int a[], int n)
{
	int i;
	int j;
	int change;
	int temp;
	for(i=n-1, change=TRUE; i>=1 && change; --i)
	{
		change = FALSE;
		for(j = 0; j<i; ++j)
		{
			if(a[j]>a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				change = TRUE;
			}
		}
	}
}