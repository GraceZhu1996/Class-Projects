/*
    Author ( s ) : Toluwanimi Salako
    Description : Lab 5 - Warm up 2
    Date : 4/27/2015
*/


#include <stdio.h>

int main()
{
	int num1, num2, sum;

	printf("Enter number 1: ");
	scanf("%d", &num1);

	printf("Enter number 2: ");
	scanf("%d", &num2);

	asm	volatile ("add eax, ebx;"
			: "=a" (sum)
			: "a" (num1), "b" (num2)
			);
	printf("The sum of %d and %d is: %d\n", num1, num2, sum);
	return 0;
}
