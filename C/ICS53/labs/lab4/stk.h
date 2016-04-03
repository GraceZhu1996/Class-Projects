
#define STK_MAX 1024

typedef char Buffer[100];
struct Element {
    Buffer buf;
};

#define ELE struct Element

ELE _stk[STK_MAX];

void stk_error(char *msg);
int stk_is_full();
int stk_is_empty();
void stk_push(ELE v);
ELE stk_pop();
ELE make_element(long long i);

