#ifndef STRUTIL_H
#define STRUTIL_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void token_free(char ***t,size_t *c);
void token_append(char ***t,size_t *c,char *s);
void token_split(char ***t,size_t *c,char *s,char *d,size_t n);



char *eat(char *s, int (*p)(int), int r);
char *skip(char *s, char c);
char *trim(char *str);



#endif
