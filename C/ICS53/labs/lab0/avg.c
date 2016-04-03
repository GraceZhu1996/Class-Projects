#include <stdio.h>
int main(int argc, char* argv[]){
	if (argc > 1){
		FILE *f = fopen(argv[1], "r");
		if (f == 0){
			printf("Could not open file.\n");
		}else{
			printf("Opening %s\n", argv[1]);
			
			while(fgets(
		}
		fclose(f);
	}

	return 0;
}
