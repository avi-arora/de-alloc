#include <limits.h>
#define STRINGLEN_TYPE  unsigned short
#define STRINGLEN   sizeof(STRINGLEN_TYPE)
#define MAXSTRING   USHRT_MAX
#define LENOF(S) *(STRINGLEN_TYPE *)(MEMOF(S))
#define MEMOF(S) (S - STRINGLEN)


char *string_cat(char *, char *);
int string_cmp(char *, char *);
char *string_dup(char *);
void string_free(char *);
char *string_new(char *);
void string_print(char *);
