#include "strutil.h"

#include <stdio.h>

int main(void) {

    char **t=NULL;
    size_t c=0;

    char s[]="Goodbye|cruel|world|deds";
    char *d="|";
    size_t n=-1;

    token_split(&t,&c,s,d,n);

    for(int i=0;i<c;i++) {
        printf("\"%s\"\n",t[i]);
    }

    token_free(&t,&c);

    return 0;
}
