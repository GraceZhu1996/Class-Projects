//FUNCTIONS_C

/*
    Author ( s ) : Toluwanimi Salako
    Description : Lab 4 - Functions
    Date : 4/20/15
*/


#include <stdio.h>



int fibonacci(int n)
{
	
	if (n ==0)
	{
		return n;
	}
	else if (n == 1|| n==2)
	{
		return 1;
	}else{
	
		return fibonacci(n-1) + fibonacci(n-2);
	}


}



int main()
{
	while(1)
	{	
		int number;
		printf("Enter a number (-1 to exit): ");
		scanf("%d", &number);
		if (number == -1)
			break;
		printf("\nFibonacci %d: %d\n", number, fibonacci(number));
	}
	return 0;
}



//FUNCTIONS_C
