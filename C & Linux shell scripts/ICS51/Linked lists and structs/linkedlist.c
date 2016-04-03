/*
    Name: Toluwanimi Salako
    Date: 2/18/15
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MovieNode
{
	char title[250];
	int year;
	unsigned char rating;
	struct MovieNode *next;
};

typedef struct MovieNode mNode;

mNode* update(mNode *last)
{
		//Gather Movies
		struct MovieNode *movie = malloc(sizeof(mNode));
		printf("Name: ");
		char tempname[250];
		scanf(" %[^\n]%*c", tempname);
		strcpy(movie->title, tempname);
		printf("Year: ");
		scanf("%d", &(movie->year));
		printf("Rating: ");
		scanf("%hhu", &(movie->rating));
		printf("\n");

       if (last == NULL)
        {
	last = malloc(sizeof(mNode));
        last = movie;
        }
        else
        {
            last->next = malloc(sizeof(mNode));
            last->next = movie;
            last = movie;
	last->next = NULL;
        }
return last;
}


void search(char name[], mNode *first)
{
    	if (first == NULL)
    {
          printf("Movie %s does not exist in the database.\n", name);   
          return;
    }    
    mNode *temp = malloc(sizeof(mNode));
    temp = first;
    while(1)
    {
           if (strcmp(temp->title, name) == 0)
           {
                          printf("Year: %d\n", temp->year);
                          printf("Rating: %hhu\n", temp->rating);
                          return;
           }
           else
           {
               temp = temp->next;
               if (temp == NULL)
               {
                    printf("Movie %s does not exist in the database.\n", name); 
                    return;    
               }
           }
    }
}

int main()
{
	int count = 0;
	mNode *first = NULL;
	mNode *last = NULL;
    
    do
    {
             char input;
             printf("%d Movie(s) in the datablase. Update, Search, or Quit (U/S/Q):", count);
             scanf("%c", &input);
             if (input == 'U')
             {
                   last = update(&(*last));
                   count++;
                   
                   if (first == NULL)
                   {
                    first = malloc(sizeof(mNode));
                    first = last;
                   }    
	}
           else if(input == 'S')
           {
                char tempname[250];
                printf("\nName of the movie: ");
                scanf(" %[^\n]%*c", tempname);
                search(tempname, &(*first));
            }else if(input == 'Q')
            {
                  mNode *temp = malloc(sizeof(mNode));
                  mNode *temp2 = malloc(sizeof(mNode));
                  temp = first;
                  while(1)
                  {
                   temp2 = temp->next;
                   free(temp);
                   temp = temp2;
                   if (temp2 == NULL)
                      break;
                   }
                  break;
            }
            printf("\n");
    }while(1);
return 0;
}
