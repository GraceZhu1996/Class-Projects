/*
 * 	Author(s): Toluwanimi Salako
 * 	Description: Addressing
 * 	Date: 05/11/15
 */

#include <stdio.h>
#define ARRAY_LENGTH 20

int main()
{
	int i;
	int array[ARRAY_LENGTH];
	int swapped;

	printf("Enter the elements one by one \n");
	for (i = 0; i< ARRAY_LENGTH; i++)
	{
		scanf("%d", &array[i]);
	}

	printf("Input array elements \n");
	for (i = 0; i< ARRAY_LENGTH; i++)
	{
		printf("%d\n", array[i]);
	}

	do
	{
		swapped = 0;
		i = 1;
		__asm__ __volatile__("mov ecx, 1;"
			"LOOPSTART: cmp ecx, eax;"
	                	"jge EXIT;" //If rcp >= array length go to EXIT. Else continue
        		        "mov edx, dword ptr [rbx + 4 * rcx - 4];"
				"mov esi, dword ptr [rbx + 4 * rcx];"
				"cmp edx, esi;"
				"jg SWAP;"
				"jmp DONE;"
			"SWAP: mov dword ptr [rbx + 4 * rcx - 4], esi;"
				"mov dword ptr [rbx + 4 * rcx], edx;"
				"mov %0, 1;"
				"jmp DONE;"
			"DONE: add ecx, 1;" //Incrememnt
	               		"jmp LOOPSTART;"
	                "EXIT:"
				:"+r" (swapped)
				:"b" (array), "a" (ARRAY_LENGTH)
				: "memory", "edx", "ecx", "esi"
				);
	}while (swapped > 0);
	
	printf("Sorted array is...\n");
	for (i = 0; i < ARRAY_LENGTH; i++)
	{
		printf("%d\n", array[i]);
	}
	return 0;
} 
