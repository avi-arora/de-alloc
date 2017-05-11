/*
 * Library to provide strings with explicit sizes.
 * Your goal is to implement a (somewhat) safer string that uses explicit
 * sizes rather than Nul termination to indicate how long a string is.
 *
 * You should return to the caller a pointer to the memory location where
 * the characters comprising the string start, but you should prepend enough
 * metadata to that storage space to store the size of the string.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringlib.h"

/* Create a safe string from a (Null-terminated) C-string. */

struct safe_string {
    int size;
    char *str;
};


char *
string_new(char *cstr)
{
    int length = strlen(cstr);
    struct safe_string *sstr = malloc(sizeof(struct safe_string));
    sstr->size = length;
    sstr->str = malloc(sizeof(length));
    memcpy(sstr->str, cstr, length);
    return (sstr->str);
}

/* Make a copy of a safe string. */
char *
string_dup(char *sstr) {
    struct safe_string *newsstr = malloc(sizeof(struct safe_string));
    int *len = (int *) sstr - sizeof(int) ; 
    newsstr->size = *len;
    newsstr->str = (char *) malloc(*len);
    memcpy(newsstr->str, sstr, *len);
    return (newsstr->str);
}

/* Compare two safe strings. */
int
string_cmp(char *sstr1, char * sstr2) {
    int *l1 = (int *) sstr1 - sizeof(int);
    int *l2 = (int *)sstr2 - sizeof(int);
    if(*l1 > *l2)
        return 1;
    else if(*l1 < *l2)
        return -1;
    return (0);
}

/* Concatenate two safe strings. */
char *
string_cat(char *sstr1, char *sstr2) {
    int *l1, *l2;
    int  s;
    struct safe_string *newstr = malloc(sizeof(struct safe_string));
    l1 = (int *) sstr1 - sizeof(int);
    l2 = (int *) sstr2 - sizeof(int);
    s = *l1 + *l2;
    newstr->size = s;
    newstr->str = (char *) malloc(s);
    memcpy(newstr->str, sstr1, *l1);
    memcpy(newstr->str + (*l1), sstr2, *l2);
    return (newstr->str);
}

void
string_free(char *sstr)
{
    free(sstr - sizeof(int));
}

/* Print out safe string */
void
string_print(char *sstr)
{   int *len = (int *) sstr - sizeof(int);
    int i = 0;
    printf("\n");
    for(; i < *len; i++)
    {
        printf("%c", sstr[i]);
    }
    printf("\n");
    return;
}

