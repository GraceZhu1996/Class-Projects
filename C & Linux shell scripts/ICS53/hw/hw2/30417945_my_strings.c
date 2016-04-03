#include <stdio.h>
#include <string.h>

#define require(e) if (!(e)) fprintf(stderr, "FAILED line %d        %s: %s       %s\n", __LINE__, __FILE__, __func__, #e)
char* strtok_pointer;

int i_strlen(const char* src);
char* i_strcat(char* dest, char* src);
char* i_strncat(char* dest, char* src, size_t n);
char* i_strcpy(char* dest, char* src);
char* i_strncpy(char* dest, char* src, size_t n);
int i_strcmp(const char* str1, const char* str2);
int i_strncmp(const char* str1, const char* str2, size_t n);
const char* i_strpbrk(const char *str1, const char *str2);
const char *i_strrchr(const char *str, int c);
const char *i_strchr(const char *str, int c);
char *i_strtok(char *str, const char *delim);
const char *i_strstr(const char *haystack, const char *needle);
size_t i_strcspn(const char *str1, const char *str2);
size_t i_strspn(const char *str1, const char *str2);

//My Helper Functions
int c_in_str(const char *str, const char c){
	const char* d = str;
	while(*d){
		if (*d == c)
			return 1;
		d++;
	}
	return 0;
}
 /* EXCEEDING 5 LINES BY 2 */ 
char *i_strtok_from_arg(char *str, const char *delim){
	char *c = str; 
	if (!*c) return NULL;
	const char *loc = i_strchr(str, *delim);
	while(*c && c != loc)
		c++;
	*c = '\0';
	strtok_pointer = (c + 1);
	return str;
}

//My String Functions
int i_strlen(const char* src){
	int i = 0; 
	const char* c = src;
	while(*c){
		i++;
		c++;
	}
	return i;
}
char* i_strcat(char* dest, char* src){
	char *c = src;
	char *d = dest + i_strlen(dest);
	while(*c){
		*d = *c;
		c++; d++;
	}
	*d = '\0';
	return dest;
}
char* i_strncat(char* dest, char* src, size_t n){
	char *c = src;
	char *d = dest + i_strlen(dest);
	while(*c && n){
		*d = *c;
		c++; d++; n--;
	}
	*d = '\0';
	return dest;
}
char* i_strcpy(char* dest, char* src){
	char *c = src;
	char *d = dest;
	while(*c){
		*(d++) = *(c++);
	}
	*d = '\0';
	return dest;
}
char* i_strncpy(char* dest, char* src, size_t n){
	char *c = src;
	char *d = dest;
	while(*c && n){
		*(d++) = *(c++);
		n--;
	}
	*d = '\0';
	return dest;
}
int i_strcmp(const char* str1, const char* str2){
	const char *c = str1, *d = str2;
	char result = 0;
	while(*c || *d){
		if (*c != *d)
			return *(const unsigned char*)c - *(const unsigned char*)d;
		c++; d++;
	}
	return result;
}
int i_strncmp(const char* str1, const char* str2, size_t n){
	const char *c = str1, *d = str2;
	char result = 0;
	while(n && (*c || *d)){
		if (*c != *d)
			return *(const unsigned char*)c - *(const unsigned char*)d;
		c++; d++; n--;
	}
	return result;
}
const char* i_strpbrk(const char *str1, const char *str2){
	const char *c = str1, *d = str2;
	while(*c){
		if (c_in_str(str2, *c))
			return c;
		c++;
	}
	return NULL;
}
const char *i_strrchr(const char *str, int c){
	const char* d = str, *result;
	while(*d){
		if (*d == c)
			result = d;
		d++;
	}
	return result;
}
const char *i_strchr(const char *str, int c){
	const char* d = str;
	while(*d){
		if (*d == c)
			return d;
		d++;
	}
	return NULL;
}
char *i_strtok(char *str, const char *delim){
	if (str == NULL && strtok_pointer != NULL)
		str = strtok_pointer;
	char *r = i_strtok_from_arg(str, delim);
	return r;
}
 /* EXCEEDING 5 LINES BY 2 */ 
const char *i_strstr(const char *haystack, const char *needle){
	const char* c = haystack, *d = needle, *result;
	int matched = 0;
	while(*c && *d){
		if (*c == *d){
			result = (matched == 0) ? c : result; matched++; d++;
		}else{
			matched = 0; result = NULL;
		}
		c++;
	}
	return result;
}
size_t i_strspn(const char *str1, const char *str2){
	const char* c = str1;
	int matched = 0;
	while(*c){
		if(!c_in_str(str2, *c))
			break;
		matched++; c++;
	}
	return matched;
}
size_t i_strcspn(const char *str1, const char *str2){
	const char* c = str1;
	int unmatched = 0;
	while(*c){
		if(c_in_str(str2, *c))
			break;
		unmatched++; c++;
	}
	return unmatched;
}

//My Test Functions
void test_strlen(){
	require(i_strlen("") == 0);
	require(i_strlen("hello") == 5);
	require(i_strlen(" ") == 1);
}
void test_strcat(){
	char src[50], dest[50];
	strcpy(src,  "SPARTA!!!");
   	strcpy(dest, "This is ");
   	i_strcat(dest, src);
   	require(strcmp(dest, "This is SPARTA!!!") == 0);

   	strcpy(dest,  "Hello ");
   	strcpy(src,  "It's Me.");
   	i_strcat(dest, src);
   	require(strcmp(dest, "Hello It's Me.") == 0);

   	strcpy(dest, "This is ");
   	strcpy(src,  "PATRICK!");
   	i_strcat(dest, src);
   	require(strcmp(dest, "This is PATRICK!") == 0);
}
void test_strncat(){
	char src[50], dest[50];
	strcpy(src,  "SPARTA!!!");
   	strcpy(dest, "This is ");
   	i_strncat(dest, src, 6);
   	require(strcmp(dest, "This is SPARTA") == 0);

   	strcpy(dest,  "Hello ");
   	strcpy(src,  "It's Me.");
   	i_strncat(dest, src, 4);
   	require(strcmp(dest, "Hello It's") == 0);

   	strcpy(dest, "This is ");
   	strcpy(src,  "PATRICK!");
   	i_strncat(dest, src, 3);
   	require(strcmp(dest, "This is PAT") == 0);
}
void test_strcpy(){
	char src[50], dest[50];
	strcpy(src,  "SPARTA!!!");
   	i_strcpy(dest, src);
   	require(strcmp(dest, src) == 0);

   	i_strcat(dest, "YES!");
   	i_strcpy(src, dest);
   	require(strcmp(src, dest) == 0);

   	i_strcpy(src, "000");
   	require(strcmp(src, "000") == 0);
}
void test_strncpy(){
	char src[50], dest[50];
	strcpy(src,  "SPARTA");
   	i_strncpy(dest, src, 5);
   	require(strcmp(dest, "SPART") == 0);

   	i_strncpy(src, "Why so serious?", 6);
   	require(strcmp(src, "Why so") == 0);

   	i_strncpy(src, "000", 1);
   	require(strcmp(src, "0") == 0);
}
void test_strcmp(){
	char src[50], dest[50];
	strcpy(src,  "SPARTA");
   	strcpy(dest, "SPARTA");
   	require(i_strcmp(dest, src) == 0);

	strcpy(src,  "Hello");
   	strcpy(dest, "Hellooo");
   	require(i_strcmp(dest, src) == strcmp(dest, src));

   	strcpy(src,  "Hello");
   	strcpy(dest, "Hell");
   	require(i_strcmp(dest, src) == strcmp(dest, src));
}
void test_strncmp(){
	char src[50], dest[50];
	strcpy(src,  "SPARTA");
   	strcpy(dest, "SPARTO");
   	require(i_strncmp(dest, src,5) == 0);

	strcpy(src,  "Hello");
   	strcpy(dest, "Hellooo");
   	require(i_strncmp(dest, src, 5) == strncmp(dest, src, 5));

   	strcpy(src,  "Hello");
   	strcpy(dest, "Hell");
   	require(i_strncmp(dest, src, 4) == strncmp(dest, src, 4));
}
void test_strpbrk(){
	char src[50];
	strcpy(src,  "SPARTA");
   	require((*i_strpbrk(src, "BTS")) == 'S');
   	require(i_strpbrk(src, "BCD") == strpbrk(src, "BCD"));
   	require(i_strpbrk(src, "123") == NULL);
}
void test_strrchr(){
	char src[50];
	strcpy(src,  "SPARTA");
   	require(strrchr(src, 'S') == i_strrchr(src, 'S'));
   	require(i_strrchr(src, 'S') != i_strrchr(src, 'A'));
   	require(*(i_strrchr(src, 'S')) == 'S');
}
void test_strchr(){
	char src[50];
	strcpy(src,  "SPARTA");
   	require(i_strchr(src, 'A') != i_strrchr(src, 'A'));
   	require(i_strchr(src, 'S') == strchr(src, 'S'));
   	require(i_strchr(src, 'B') == NULL);
}
void test_strtok(){
	char src[50], src2[50], *token, *token2;
	strcpy(src,  "This IS SPARTA");
	strcpy(src2,  "This IS SPARTA");
   	token = i_strtok(src, " ");
   	token2 = strtok(src2, " "); //Original string function
   	while(token != NULL){
   		require(strcmp(token, token2) == 0); //Should check 3 examples.
   		token = i_strtok(NULL, " ");
   		token2 = strtok(NULL, " ");
   	}
}
void test_strstr(){
	const char haystack[20] = "Hello My Name.";
  	require(i_strstr(haystack, "Name") == strstr(haystack, "Name"));
  	require(i_strstr(haystack, "My") == strstr(haystack, "My"));
  	require(i_strstr(haystack, "llo") == strstr(haystack, "llo"));
}
void test_strspn(){
   const char str1[] = "ACBCACDEFG019874";
   const char str2[] = "ACD";
   require(i_strspn(str1, str2) == strspn(str1, str2));
   require(i_strspn(str1, "012") == strspn(str1, "012"));
   require(i_strspn(str1, "CA") == strspn(str1, "CA"));
}
void test_strcspn(){
   const char str1[] = "ABCDEFG019874";
   const char str2[] = "01";
   require(i_strcspn(str1, str2) == strcspn(str1, str2));
   require(i_strcspn(str1, "BC") == strcspn(str1, "BC"));
   require(i_strcspn(str1, "DJ") == strcspn(str1, "DJ"));
}
int main(){
	char* str = "Hello";
	char* str2 = "Hellu";
	test_strlen();
	test_strcat();
	test_strncat();
	test_strcpy();
	test_strncpy();
	test_strcmp();
	test_strncmp();
	test_strpbrk();
	test_strrchr();
	test_strchr();
	test_strtok();
	test_strstr();
	test_strspn();
	test_strcspn();	
	return 0;
}		      
