//Array_C
/*
    Author ( s ) : Toluwanimi Salako
    Description : Lab 4 - Arrays
    Date : 4/20/15
*/


#include <stdio.h>

int getMin(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
int getMax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int isSorted(int A[20])
{
     int i;
    for (i = 0; i < 19; i++)
    {
        if (A[i] > A[i+1])
           return 0;
    }
    if (A[18] > A[19])
       return 0;
    
    return 1;
}

int findMin(int A[20], int i, int j)
{
	int min = A[i];
		
	for (i = i+1; i <= j; i++)
      {
            if (A[i] < min)
               min = A[i];
      }
      return min;
}

int* sort(int A[20])
{
	
/*	while(!isSorted(A))
	{
     int i;
    	for (i = 0; i<19; i++)
    	{
            int temp = A[i];
            int temp2 = A[i+1];
	        A[i] = getMin(temp, temp2);
    		A[i+1] = getMax(temp, temp2);
    	}
     }*/
     while(!isSorted(A))
	{
                        int i;
    	for (i = 0; i<19; i++)
    	{
            int temp = A[i];
            int temp2 = A[i+1];
	        A[i] = findMin(A, i, i+1);
	        A[i+1] = getMax(temp, temp2);
    	}
     }
     return A;
     
}

void printArray(int A[20])
{
     int i;
     for (i = 0; i < 20; i++)
         printf("%d\n", A[i]);    
}


int main()
{
	int count = 0;
	int A[20];
	
	while(count < 20)
	{
		int temp;
		printf("Enter number %d: ", count + 1);
		scanf("%d", &temp);
		A[count] = temp;
		count++;
	}
	
	printf("\nSorting....\n");
	int *B = sort(A);
	printArray(B);
	return 0;
}
//Array_C
