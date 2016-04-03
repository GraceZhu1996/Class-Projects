/*
 * Author(s): Toluwanimi Salako
 * Description: Lab 1 - Hello World
 * Date: 5/5/2015
 */
	 



#include <stdio.h>
#include <stdlib.h>

void str_concat(char* str1, char* str2, char* str)
{
     while(*str1 != '\0')
	*str++ = *str1++;
	while(*str2 != '\0')
	*str++ = *str2++;

	*str = '\0'; 
}

int main()
{
	char *str1 = "The";
	char *str2 = "King";
	char *str = malloc(sizeof(str1) + sizeof(str2));

	str_concat(str1, str2, str);
	printf("String 1: %s\nString 2: %s\nJoined Strings: %s\n", str1, str2, str);
	
	free(str);
    return 0;   
}
