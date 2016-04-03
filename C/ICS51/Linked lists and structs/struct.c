#include <stdio.h>
#include <string.h>

struct Movie
{
	char title[250];
	int year;
	unsigned char rating;
};

void sortMovie(struct Movie array[], int ARRAY_LENGTH)
{
    int i;
    int swapped;

    do
    {
        swapped = 0;
        
        for (i = 1; i < ARRAY_LENGTH; i++)
        {
	    struct Movie temp;
            if (array[i].rating > array[i-1].rating)
            {
                 swapped = 1;
                 temp = array [i-1];
                 array [i-1] = array [i];
                 array[i] = temp;
            }
		else if (array[i].rating == array[i-1].rating)
		{
			if (array[i].year < array[i-1].year)
			{
					
                 	swapped = 1;
                 	 temp = array [i-1];
	                 array [i-1] = array [i];
        	         array[i] = temp;
			}
		}	
        }
    } while (swapped > 0);                                  
	
	//Print Sorted movies
	for (i = 0; i < ARRAY_LENGTH; ++i)
	{
		printf("(%d)\n", i+1);
		printf("Title: %s\n", array[i].title);
		printf("Year: %d\n", array[i].year);
		printf("Rating %hhu\n", array[i].rating);
		printf("\n");
	}
} 
int main()
{
	printf("Enter your 10 favorite movies\n.");
	
	int i;
	struct Movie movies[10];
	for (i = 1; i < 11; i++)
	{
		//Gather Movies
		struct Movie movie;		
		printf("Entering info for movie %d: \n", i);
		printf("Name: ");
		char tempname[250];
		scanf(" %[^\n]%*c", tempname);
		strcpy(movie.title, tempname);
		printf("Year: ");
		scanf("%d", &(movie.year));
		printf("Rating: ");
		scanf("%hhu",&(movie.rating));
		printf("\n");
		movies[i-1] = movie;
	}
	//Sort Movies
	printf("\n===============Sorted List===============\n");
	sortMovie(movies, 10);		
	return 0;
}
