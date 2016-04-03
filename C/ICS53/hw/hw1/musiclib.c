#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#define true 1;
#define false 0;



struct SongStruct{
	char title[50];
	char artist[50];
	int year;
};

struct IntPair{
	int x;
	int y;
};


typedef struct SongStruct Song;
typedef struct IntPair Pair;
typedef int bool;
char* libname = "myMusic";
const int STR_SIZE = 50;
const int BOUND = 1024;

char read_command(Song* musicLibrary, int* size);
Song get_song();
char* get_title();
char* get_artist();
int get_year();
int evaluate_command(char command, Song* musicLibrary, int* size);
void load_MusicLibrary(char name[], Song* musicLibrary, int* size);
void add_song_to_MusicLibrary(Song song, Song* musicLibrary, int* size);
void write_song(FILE* f, Song song);
void read_song(FILE* f, Song songs[], int* size);
FILE* openfile(char filename[], char* mode);


bool validate_command(char c){
	char commandlist[] = "IipPDdLlqQ";
	int i; 
	int listsize = 10;
	for (i = 0; i < listsize; ++i)
		if (commandlist[i] == c) return true;
	return false;
}

/* EXCEEDING 5 LINES BY 2 */ 
char read_command(Song* musicLibrary, int* size){
	char input = 'n';
	while (1){
		printf("%s Command: ", libname);
		scanf(" %[^\n]%*c", &input);
		if (validate_command(input)){
			int result = evaluate_command(input, musicLibrary, size);
			if (result != 0)
				break;
		}
	song.year = get_year();
	return song;
}

char* get_title(){
	char title[STR_SIZE];
	printf("Title: "); 
	scanf(" %[^\n]%*c", &title);
	char* p = title;
	return p;
}

char* get_artist(){
	char artist[STR_SIZE];
	printf("Artist: ");
	scanf(" %[^\n]%*c", &artist);
	char* p = artist;
	return p;
}

int get_year(){
	int year;
    char y[STR_SIZE];
	printf("Year Published: ");
	scanf(" %[^\n]%*c", &y);
	year = strtol(y, NULL, 10);
	return year;
}


int evaluate_command(char command, Song* musicLibrary, int* size){
    char title[STR_SIZE];
    switch (command){
		case 'I':
		case 'i':
			add_song_to_MusicLibrary(get_song(), musicLibrary, size);
			break;
		case 'P':
		case 'p':
			print_MusicLibrary(1, musicLibrary, size);
			break;
		case 'D':
		case 'd':
			remove_song_from_MusicLibrary_by_name(get_title(), musicLibrary, size);
			break;
		case 'L':
		case 'l':
            strcpy(title, get_title());
			look_up_song(title, musicLibrary, size);
			break;
		case 'Q':
		case 'q':
			print_MusicLibrary(0, musicLibrary, size);
			return 1;
	}
	return 0;
}


void load_MusicLibrary(char name[], Song* musicLibrary, int* size){
    FILE* f = openfile(name, "r");
    if (f == NULL)
		return;
    read_song(f, musicLibrary, size);
	fclose(f);
}

Song copyMemoryToSong(char* first, char* middle, char* last, int t_offset, int a_offset, int y_offset){
	Song song;
	char y[50];
	strncpy(song.title, first+2, t_offset);
	strncpy(song.artist, middle+2, a_offset);
	strncpy(y, last+2, y_offset);
	song.year = strtol(y, NULL, 10);
	return song;
}

Song songFromMemory(char* line, char* first, char* middle, char* last, char* end){
	int t_offset = (middle-line) - (first-line) - 10;
	int a_offset = (last-line) - (middle-line) - 18;
	int y_offset = (end-line) - (last-line) - 3;
	return copyMemoryToSong(first, middle, last, t_offset, a_offset, y_offset);
}

Song songFromLine(char* line){
	char c = ':';
    char* first = strchr(line, c);
    char* middle = strchr(first+1, c);
    char* last = strchr(middle+1, c);
    char* end = strchr(last+1, '\0');
	return songFromMemory(line, first, middle, last, end);
}

void store_MusicLibrary(Song* musicLibrary, int* size){
	int i;
	FILE* f = openfile(libname, "w");
	if (f != NULL){
		for (i = 0; i < *size; ++i)
			write_song(f, musicLibrary[i]);
		fclose(f);
	}
}

void print_MusicLibrary(bool terminalPrint, Song* musicLibrary, int* size){
		int i;
		if (terminalPrint){
			for (i = 0; i < *size; ++i)
				printf("%i Title: %s, Artist: %s, Year Published: %i\n", i+1,  musicLibrary[i].title, musicLibrary[i].artist, musicLibrary[i].year);
		}else{
			store_MusicLibrary(musicLibrary, size);
		}
}

Pair pair_from_int(int i, int j){
	Pair p;
	p.x = i;
	p.y = j;
	return p;
}

Pair alternate_index(int cmpresult, int middle){
	if (cmpresult <= 0){
		return pair_from_int(middle+1, 0);
	}else{
		return pair_from_int(middle, 0);
	}
}

void binary_search_inner_loop(int* first, int* middle, int* last, int cmpresult){
   	if (cmpresult < 0)
   		*first = *middle + 1;
   	else if (cmpresult > 0)
   		*last = *middle - 1;
}

/* EXCEEDING 5 LINES BY 2 */ 
Pair find_index_of_song_with_name(char songname[], Song* musicLibrary, int* size){
	//Returns (x, y) x = location for song, y = actual song or location it should be
	int cmpresult = 1;
	int first = 0, last = *size - 1, middle = 0;
	while(first <= last && *size > 0)
	{
		middle = (first+last)/2;
		cmpresult = strcasecmp((*(musicLibrary + middle)).title, songname);
        if (cmpresult == 0)
	   		return pair_from_int(middle, 1);
	   	else
	   		binary_search_inner_loop(&first, &middle, &last, cmpresult);
	}
	return alternate_index(cmpresult, middle);
}

void look_up_song(char songname[], Song* musicLibrary, int* size){
	Pair pos = find_index_of_song_with_name(songname, musicLibrary, size);
	int i = pos.x;
	if (pos.y)
		printf("%i Title: %s, Artist: %s, Year Published: %i\n",
					i+1,  musicLibrary[i].title, musicLibrary[i].artist, musicLibrary[i].year);
}

void crunch_up_from_index(int index, Song* musicLibrary, int* size){
	int i = index; 
	while(i < *size - 1)
	{
		musicLibrary[i] = musicLibrary[i+1];
		i++;
	}
}
void crunch_down_from_index(int index, Song* musicLibrary, int* size){
	int i = *size - 1; 
	while(i >= index){
		musicLibrary[i+1] = musicLibrary[i];
		i--;
	}
}

void add_song_to_MusicLibrary(Song song, Song* musicLibrary, int* size){
	Pair pos = find_index_of_song_with_name(song.title, musicLibrary, size);
	if (pos.x > -1){
		crunch_down_from_index(pos.x, musicLibrary, size);
		musicLibrary[pos.x] = song;
		(*size)++;
	}
} 

void remove_song_from_MusicLibrary_by_name(char songname[], Song* musicLibrary, int* size){
	Pair pos = find_index_of_song_with_name(songname, musicLibrary, size);
	if (pos.y){ //Song exists
		crunch_up_from_index(pos.x, musicLibrary, size);
		(*size)--;
	}
}

void write_song(FILE* f, Song song){
	char* currentSongs = NULL;
	char s[200];
	snprintf(s, sizeof(s), "Title: %s, Artist: %s, Year Published: %i",
						 song.title, song.artist, song.year);
	fprintf(f, "%s\n", s);
}

void read_song(FILE* f, Song songs[], int* size){
	char s[150];
	int i = 0;
	while (fgets(s, 150, f) != NULL)
		songs[i++] = songFromLine(s);
	*size = i;
}


FILE* openfile(char filename[], char* mode){
    FILE *f = NULL;
    if (*mode == 'r' || *mode == 'w'){
        f = fopen(filename, mode);
    }
    return f;
}

int main (int argc, char* argv[])
{
	Song musicLibrary[BOUND]; 
	int size = 0;
	if (argc > 1){	
		libname = argv[1];	
	}
    load_MusicLibrary(libname, musicLibrary, &size);
	read_command(musicLibrary, &size);
	return 0;
}
