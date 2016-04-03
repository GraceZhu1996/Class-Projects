#include <stdio.h>
#define n 20

int main()
{
	int array[n];
	int i;
	//int temp;
	char swapped;

	printf("Enter the elements one by one \n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	
	printf("Input array elements \n");
	for (i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}

	/*	Buble sorting begins */
	do
	{
		swapped = 0;
		for (i = 1; i < n; i++)
		{
    		__asm__ __volatile__("cmp %0, %1;"
    				"jg SWAP;"
    				"jmp DONE;"
    				"SWAP: xor %0, %1;"
			        "xor %1, %0;"
			        "xor %0, %1;"
    				"mov %2, 1;"
    				"DONE:"
    				: "+r" (array[i-1]), "+r" (array[i]), "+r" (swapped)
            ); 
		}
	} while (swapped);

	printf("Sorted array is...\n");
	for (i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}
	return 0;
}
