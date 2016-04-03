/*
 * Name: Toluwanimi Salako (#30417945)
 * LAB 9
 * Date: 5/29/15
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct rolodexCard
{
	 char lastname[50];
	char firstname[50];
	char phone[50];

};

typedef struct rolodexCard Card;


int read_command(char name[], Card* phonebook, int* size, int* max, char* input);
void load_rolodex();
void store_rolodex(char filename[], Card* phonebook, int* size);
void print_rolodex(Card* phonebook, int* size);
int find_index_of_card_with_name(char cardname[], Card* phonebook, int* size);
void remove_card_from_rolodex_by_name(char cardname[], Card* phonebook, int* size);
void add_card_to_rolodex(Card card, Card* phonebook, int* size, int* max);
void open_file(char filename[], char mode);
Card* sort_rolodex(Card* phonebook, int* size);
void search(Card* phonebook, int* size, char lastname[]);

Card* stringtocard(char stringinput[])
{
		Card* newcard = malloc(sizeof(Card));
		
		int j = 0;
		int i = 0;
		int counter = 0;
		while(j < strlen(stringinput))
		{
		
			if (*(stringinput + j) == ' ')
			{
				if(strlen(newcard->phone) == 13)
					break;
				i = 0;
				counter++;
				j++;
				continue;
			}else if(*(stringinput + j) == '\0')
            {
				break;
            }
		
			
			switch(counter)
			{
				case 0:
					newcard->lastname[i] = *(stringinput+ j);
					newcard->lastname[i+1] = '\0';
					break;
				case 1:
					newcard->firstname[i] = *(stringinput + j);
					newcard->firstname[i+1] = '\0';
					break;
				case 2:
					newcard->phone[i] = *(stringinput + j);
					newcard->phone[i+1] = '\0';
                newcard->phone[13] = '\n';
					break;
			}
			i++;
			j++;

		}
        int k;
        for(k=14; k < 50; k++)
            newcard->phone[k] = '\0';
	return newcard;
}
int main(int argc, char * argv[])
{
	char name[100];

	int* MAX = malloc(sizeof(int));
	*MAX = 256;
	int* size = malloc(sizeof(int));
	*size = 0;
    
	Card* phonebook = malloc(sizeof(Card)*256);
	if (argc > 1)
		strcpy(name, argv[1]);
	else
		strcpy(name, "myRolodex");
	
    FILE *fp;
    char str[150];
    fp = fopen(name, "rt");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }
    while(fgets(str, 150, fp) != NULL)
    {
        int i;
        int len = strlen(str);
        int count = 0;

        for (i = 0; i < len; i++) {
            char c = str[i];
            if (c == ' ')
                count++;
        }
        if (count == 2)
        {
            Card* newcard = stringtocard(str);
            if(newcard != NULL)
                add_card_to_rolodex((*newcard), phonebook, size, MAX);	
            free(newcard);
        }
    }
    fclose(fp);
        
	char* input = malloc(sizeof(char));
	int loop = 1;
	while(loop)
	{
		printf("Enter %s command: ", name);
		scanf("%c", input);
		loop = read_command(name, phonebook, size, MAX, input);	
	}
	free(input);
	free(MAX);
	free(size);
	free(phonebook);
	return 0;
}

int read_command(char name[], Card* phonebook, int* size, int* max, char* input)
{
	
	if (*(input) == 'I' || *(input) == 'i')
	{
		
		char stringinput[250];		
		printf("Enter card: lastname firstname phone\n");
		scanf(" %[^\n]%*c", stringinput);

		if(*(stringinput) != "\n")
		{
            int i;
            int len = strlen(stringinput);
            int count = 0;

            for (i = 0; i < len; i++) {
                char c = stringinput[i];
                if (c == ' ')
                    count++;
            }
            if (count == 2)
            {
                Card* newcard = stringtocard(stringinput);
                if(newcard != NULL)
                    add_card_to_rolodex(*newcard, phonebook, size, max);
                free(newcard);
            }
		}
	}	
	else if(*(input) == 'P' || *(input) == 'p')
	{
		print_rolodex(phonebook, size);
	}
	else if(*(input) == 'D' || *(input) == 'd')
	{
		char lastname[50];
		printf("Enter lastname: ");
		scanf(" %[^\n]%*c", &lastname);
		remove_card_from_rolodex_by_name(lastname, phonebook, size);
	}
	else if(*(input) == 'L' || *(input) == 'l')
	{
		char lastname[50];
		printf("Enter lastname: ");
		scanf(" %[^\n]%*c", &lastname);
		search(phonebook, size, lastname);
	}
	else if(*(input) == 'S' || *(input) == 's')
	{
		phonebook = sort_rolodex(phonebook, size);
	}
	else if(*(input) == 'Q' || *(input) == 'q')
	{
		store_rolodex(name, phonebook, size); 
		return 0;	
	}
	else
	{

    printf("Invalid Command: %c\n", *(input));
	//	break;
	}
	return 1;	
}

void search(Card* phonebook, int* size, char lastname[])
{
    
int result;
int first, last, middle;

first = 0;
last = *size - 1;
middle = (first+last)/2;
int count = 0;
Card sresult[*size];


while(first < last)
{
    result = strcasecmp(lastname, (*(phonebook + middle)).lastname);
    
    if (result < 0)
    {
        first = middle + 1;
    }
    else if(result == 0)		
    {
        int i = middle;
        int r;
       
        sresult[0] = *(phonebook + middle);
        count++;
        
        i = middle - 1;
        r = strcasecmp((*(phonebook + i)).lastname, lastname);
        while(r == 0)
        {
            sresult[count] = *(phonebook + i);
            count++;
            i--;
            r = strcasecmp((*(phonebook + i)).lastname, lastname);
        } 
        
        i = middle + 1;
        r = strcasecmp((*(phonebook + i)).lastname, lastname);
        while(r == 0)
        {
             sresult[count] = *(phonebook + i);
            i++;
             count++;
            r = strcasecmp((*(phonebook + i)).lastname, lastname);
        }  
        
        //Sort result
        int swapped;
        Card temp;
        do
        {
            swapped = 0;
            for(i = 1; i < count; i++)
            {
                
                int r = strcasecmp(sresult[i].firstname, sresult[i-1].firstname);
                if(r < 0 )
                {
                    temp = sresult[i];
                    sresult[i] = sresult[i-1];
                    sresult[i-1] = temp;
                    swapped = 1;
                }
            }
        }while(swapped);
        
        //print rolodex
        for(i = 0; i < count; ++i)
        {
            printf("%d %s %s %s", i, sresult[i].lastname, sresult[i].firstname, sresult[i].phone);
        }
        break;
    }
    else
    {
        last = middle - 1;
    }
    middle = (first+last)/2;
}
}

void store_rolodex(char filename[], Card* phonebook, int * size)
{
		FILE *f = fopen(filename, "w+");
		if (f==NULL)
		{
			printf("Error opening file.\n");
			return;
		}
		int i;
		for (i = 0; i < *size; i++)
		{
			fprintf(f, "%s %s %s", (*(phonebook + i)).lastname, (*(phonebook + i)).firstname, (*(phonebook + i)).phone);
		}
		fclose(f);
}


int find_index_of_card_with_name(char cardname[], Card* phonebook, int* size)
{
    printf("IN");
	int i;
	for (i = 0; i <= *size; ++i)
	{
		if(strcasecmp(cardname, phonebook[i].lastname) == 0)
		{
            //printf("Found: %s %s: ", phonebook[i].lastname, phonebook[i].firstname);
			return i;
		}
    
	}
    return -1;
}

Card* sort_rolodex(Card* phonebook, int* size)
{
	int i;
    Card temp;
	int swapped;
	do
	{
		swapped = 0;
		for(i = 1; i < *size; i++)
		{
			int r = strcasecmp((*(phonebook + i)).lastname, (*(phonebook + i-1)).lastname);
			if(r < 0 )
			{
				temp = *(phonebook + i);
				*(phonebook + i) = *(phonebook + i - 1);
				*(phonebook + i - 1) = temp;
                swapped = 1;
			}
			else if(r == 0)
			{
			if(strcasecmp((*(phonebook + i)).firstname,  (*(phonebook + i-1)).firstname)< 0)
			{
				temp = *(phonebook + i);
				*(phonebook + i) = *(phonebook + i - 1);
				*(phonebook + i - 1) = temp;
                swapped = 1;
			}
				
			}
		}
	}while(swapped);
    return phonebook;
}

void add_card_to_rolodex(Card card, Card* phonebook, int* size, int* max)
{
	//printf("Adding %s %s %s\n", card.lastname, card.firstname, card.phone);
	*(phonebook + *size) = card;	
	(*size)++;
    //printf("Done\n");
}

void remove_card_from_rolodex_by_name(char cardname[], Card* phonebook, int* size)
{
    int i;
    do
    {
        i = find_index_of_card_with_name(cardname, phonebook, size);
        if (i == -1)
            break;
    
        int k;
        for(k = i; k < *size - 1; ++k)
        {
            *(phonebook + k) = *(phonebook + k + 1);	
        }
        *(phonebook + *size - 1) =  *(phonebook + *size);
        (*size)--;
        
    }while(i > -1);
}

void print_rolodex(Card* phonebook, int* size)
{
	if(*size == 0)
		return;
	int i;
	for(i = 0; i < *size; ++i)
	{
		printf("%d %s %s %s\n", i, (*(phonebook + i)).lastname, (*(phonebook + i)).firstname, (*(phonebook + i)).phone);
	}
}
