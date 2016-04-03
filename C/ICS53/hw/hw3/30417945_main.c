#include "30417945_my_ls.h"

int main(int argc, char* argv[]){
    int i;
    if (argc < 2)
        do_ls(".");
    for (i = 1; i < argc; ++i)
        do_ls(argv[1]);
    return 0;
}
