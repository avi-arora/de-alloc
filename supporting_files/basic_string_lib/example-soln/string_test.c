#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringlib.h"

/*
 * Test out the safe string library. We'll have a little interactive loop
 * that can do the following.
 * 
 * S <string> : create string
 * F : free last string made 
 * P : print current string
 * C <string> concatenate <string> to current string; result becomes curent
 *  and the argument is freed; print result
 * D : duplicate current string; delete old current replace with new current
 * E : exit
 * Q : compare current string to entered one and return integer indicator
 */
void
usage(void)
{
    printf("Valid commands are:  \n");
    printf("\tC <newstr> Concatenate new string with current string\n");
    printf("\tD Duplicate string\n");
    printf("\tE Exit\n");
    printf("\tF Free string\n");
    printf("\tP Print current string\n");
    printf("\tQ Compare given string to current string\n");
    printf("\tS <string> Create new string\n");
}

int
main(int argc, char *argv[])
{
    char cmd;
    char *msg;
    char *curstr = NULL, *tmpstr;
    char input_str[129];
    int cmp;

    while (1) {
        printf("> ");
        do {
            scanf("%c", &cmd);
        } while (cmd == '\n');

        switch(cmd) {
            case 'C':
                scanf("%128s", input_str);
                tmpstr = string_new(input_str);
                if (tmpstr == NULL)
                    fprintf(stderr, "Unable to create string %s\n",
                        strerror(errno));
                else {
                    curstr = string_cat(curstr, tmpstr);
                    if (curstr == NULL)
                        fprintf(stderr, "Unable to create string %s\n",
                            strerror(errno));
                }
                break;
            case 'D':
                tmpstr = string_dup(curstr);
                if (tmpstr == NULL)
                    fprintf(stderr, "Unable to create string %s\n",
                        strerror(errno));
                else {
                    string_free(curstr);
                    curstr = tmpstr;
                }
                break;
            case 'E':
                return (0);
                break;
            case 'F':
                if (curstr != NULL) {
                    string_free(curstr);
                    curstr = NULL;
                }
                break;
            case 'P':
                string_print(curstr);
                printf("\n");
                break;
            case 'Q':
                if (curstr == NULL) {
                    fprintf(stderr, "No current string\n");
                    break;
                }
                scanf("%128s", input_str);
                tmpstr = string_new(input_str);
                if (tmpstr == NULL)
                    fprintf(stderr, "Unable to create string %s\n",
                        strerror(errno));
                else {
                    cmp = string_cmp(tmpstr, curstr);
                    if (cmp < 0)
                        msg = "less than";
                    else if (cmp > 0)
                        msg = "greater than";
                    else
                        msg = "equal to";
                    string_print(tmpstr);
                    printf(" is %s ", msg);
                    string_print(curstr);
                    printf("\n");
                }
                break;
            case 'S':
                scanf("%128s", input_str);
                if (curstr != NULL)
                    string_free(curstr);
                curstr = string_new(input_str);
                if (curstr == NULL)
                    fprintf(stderr, "Unable to create string %s\n",
                        strerror(errno));
                break;
            default:
                usage();
                break;
        }
    }
}
