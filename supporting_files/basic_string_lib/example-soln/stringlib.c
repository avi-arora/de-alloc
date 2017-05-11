/*
 * Library to provide strings with explicit sizes.
 *
 * Representation: 
 *  We will preface each string by a 2-byte length (limiting length to
 *  64KB).
 * Throughout the code, sstr variables refer to these safe strings and
 * point to the beginning of data, while the length occupies the two
 * bytes before.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringlib.h"

#define MAKE_STRING(MEM, LEN, STR)  { \
        *(STRINGLEN_TYPE *)MEM = LEN;          \
        MEM += STRINGLEN;             \
        memcpy(MEM, STR, (size_t)LEN);       \
}

/* Create a safe string from a (Null-terminated) C-string. */
char *
string_new(char *cstr)
{
    char *retp;
    size_t len;

    len = strlen(cstr);
    if (len > USHRT_MAX) {
        fprintf(stderr, "String too long\n");
        return (NULL);
    }

    retp = malloc((size_t)(len + STRINGLEN));
    if (retp != NULL)
        MAKE_STRING(retp, len, cstr);

    return (retp);
}

/* Make a copy of a safe string. */
char *
string_dup(char *sstr) {
    STRINGLEN_TYPE  len;
    char *retp;

    len = LENOF(sstr);
    retp = malloc((size_t)(len + STRINGLEN));
    if (retp != NULL)
        memcpy(retp, sstr - 2, (size_t)len + STRINGLEN);
    return (retp + STRINGLEN);
}

/* Compare two safe strings. */
int
string_cmp(char *sstr1, char * sstr2) {
    STRINGLEN_TYPE len1, len2, minlen;
    char diff;

    len1 = LENOF(sstr1);
    len2 = LENOF(sstr2);

    if (len1 < len2)
        minlen = len1;
    else
        minlen = len2;

    for (; minlen > 0; minlen--, sstr1++, sstr2++) {
        diff = *sstr1 - *sstr2;
        if (diff != 0)
            return (diff);
    }
    /*
     * If we got here; the two strings compared equally up to the length
     * of the shorter one; so either they are identical in which case
     * they will have the same lengths, or the shorter one should compare
     * first.
     */
    return (len1 - len2);
}

/* Concatenate two safe strings. */
char *
string_cat(char *sstr1, char *sstr2) {
    STRINGLEN_TYPE len1, len2;

    /*
     * We'll try realloc -- in many cases that might be relatively
     * efficient.
     */

    len1 = LENOF(sstr1);
    len2 = LENOF(sstr2);

    sstr1 = realloc(MEMOF(sstr1), len1 + len2 + STRINGLEN);
    sstr1 += STRINGLEN;
    memcpy(sstr1 + len1, sstr2, (size_t) len2);
    LENOF(sstr1) += len2;
    return (sstr1);
}

void
string_free(char *sstr)
{
    free(MEMOF(sstr));
}

/* Print out safe string */
void
string_print(char *sstr)
{
    STRINGLEN_TYPE  len;

    if (sstr == NULL)
        return;
    len = LENOF(sstr);
    while (len--)
        printf("%c", *sstr++);
}

