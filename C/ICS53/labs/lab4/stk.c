/* compile with gcc stk.c -std=c99 */
#include "stk.h"
#include <stdio.h>
#include <stdlib.h>
#define STK_MAX 1024


ELE _stk[STK_MAX];
int _top = 0;

void stk_error(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(-1);
}

int stk_is_full()
{
    return _top >= STK_MAX;
}

int stk_is_empty()
{
    return _top == 0;
}

void stk_push(ELE v)
{
    if ( stk_is_full() )
        stk_error("Push on full stack");
    _stk[_top++] = v;
}

ELE stk_pop()
{
    if ( stk_is_empty() )
        stk_error("pop on empty stack");
    return _stk[--_top];
}

ELE make_element(long long i)
{
    ELE e;
    sprintf(e.buf, "%lld ", i);
    return e;
}

/*int main()
{
    for ( int i=0; i<100; ++i )
        stk_push(make_element(i));
    while ( !stk_is_empty() )
        printf("%s ", stk_pop().buf);
    putchar('\n');
}*/
