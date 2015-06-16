/*
    Author ( s ) : Toluwanimi Salako
    Description : Lab 5 - Warm up 1
    Date : 4/27/2015
*/

#include <stdio.h>


int main()
{
	int no = 100, val;
	
	//val = no;
	asm volatile ("mov ebx, %1;"
			"mov %0, ebx;"
			: "=r" (val)  //output
			: "r" (no)	//input
			: "ebx" 	//clobbered register
			);
	printf("%d\n", val);
	return 0;
}
