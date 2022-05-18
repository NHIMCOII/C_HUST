#include "cgen.ic"
#include <stdio.h>

sll_t S;

int match(char a, char b)
{
    if (a == '(' && b == ')')
        return 1;
    if (a == '{' && b == '}')
        return 1;
    if (a == '[' && b == ']')
        return 1;
    return 0;
}

int solve(char* x,int n){
    for (int i=0;i<=n-1;i++){
        if(x[i]=='['||x[i]=='('||x[i]=='{'){
            gtype bracket;
            bracket.i=x[i];
            sll_push_front_g(S,bracket);
        }
        else{
            if(sll_is_empty(S))
                return 0;
            else{
                gtype c;
                c.i =  sll_pop_front_g(S).i;
                if(!match(c.i,x[i]))
                    return 0;
            }
        }
    }
    return 1;
}

int main()
{
    S = sll_create_list();
    int ok = solve("[({})]()",8);
    printf("%d\n",ok);
    return 0;
}
