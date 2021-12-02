/*
    E20C4033 Stefan Larsson
    2021-11-26
    validation.c
*/

#define REP01_MSG_BUFFER_MAX 100
#define REP01_EMAIL_REGEXP "^([a-zA-Z0-9_.+-])+\\@(([a-zA-Z0-9-])+\\.)+([a-zA-Z0-9]{2,4})+$"

#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "validation.h"

/*
 * Function:  is_email 
 * --------------------
 *   emailをregexpで確認
 *
 *   returns: １＝合格、０＝不合格
 */
int is_email(char *s){

    regex_t regex;
    int r, i = 0;
    char msgbuf[REP01_MSG_BUFFER_MAX];

    /* Compile regular expression */
    r = regcomp(&regex, REP01_EMAIL_REGEXP, REG_ICASE | REG_EXTENDED);
    if (r) {
        fprintf(stderr, "Failed to buiild regexp\n");
        return 0;
    }

    r = regexec(&regex, s, 0, NULL, 0);
    if (!r) {
        i = 1;
    }
    else if (r == REG_NOMATCH) {
        fprintf(stderr, "Please enter a valid email\n");
    } else {
        regerror(r, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    regfree(&regex);
    return i;
}

/*
 * Function:  is_empty 
 * --------------------
 *   空のstring確認
 *
 *   returns: １＝合格、０＝不合格
 */
int is_empty(char *s){
    if(!strlen(s)){
        fprintf(stderr, "Please enter a valid string\n");
        return 1;
    } else {
        return 0;
    }
}
