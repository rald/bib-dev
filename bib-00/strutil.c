#include "strutil.h"

void token_free(char ***t,size_t *c) {
    for(int i=0;i<*c;i++) free((*t)[i]);
    free(*t);
    (*c)=0;
}

void token_append(char ***t,size_t *c,char *s) {
    (*t)=realloc(*t,sizeof(**t)*(*c+1));
    (*t)[*c]=strdup(s);
    (*c)++;
}

void token_split(char ***t,size_t *c,char *s,char *d,size_t n) {
    char *p1=s;
    char *p2=NULL;
    while(n!=0 && (p2=strstr(p1,d))) {
        *p2='\0';
        token_append(t,c,p1);
        p1=p2+strlen(d);
        if(n!=-1 && *c>=n) break;
    }
    if(*p1) token_append(t,c,p1);
}



char *eat(char *s, int (*p)(int), int r) {
	while(*s != '\0' && p((unsigned char)*s) == r)
		s++;
	return s;
}

char *skip(char *s, char c) {
	while(*s != c && *s != '\0')
		s++;
	if(*s != '\0')
		*s++ = '\0';
	return s;
}

char *trim(char *str) {
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;
    
    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }
    
    len = strlen(str);
    endp = str + len;
    
    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp ) {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }
    
    if(frontp != str && endp == frontp ) {
        // Empty string
        *(isspace((unsigned char) *endp) ? str : (endp + 1)) = '\0';
    }
    else if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    
    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str ) {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }
    
    return str;
}



