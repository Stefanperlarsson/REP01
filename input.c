/*
    E20C4033 Stefan Larsson
    2021-11-26
    input.c
*/

#include <stdio.h>
#include <string.h>

#include "input.h"

/*
 * Function:  int_input 
 * --------------------
 *   数字入力確認
 *
 *   returns: 入力されたint形の値
 */
int int_input(){
    int c;

    while(1){
        printf("：");
        if(scanf("%d", &c) == 1) {            
            break;
        } else {
            clear();
            fprintf(stderr, "数字のみを入力してください\n\n");
        }
    }

    //メニュー選択からの<ENTER>を無視
    getchar();

    return c;
}

/*
 * Function: string_input
 * ----------------------------
 *   文字型入力
 *
 *   char *c: 確認したいstring
 *   int s: *cの大きさ
 * 
 *   returns: 入力されたstring
 */
char* string_input(char *c, int s){
    fgets(c, s, stdin);
    c[strcspn(c, "\n")] = 0;
    return c;
}

/*
 * Function:  clear 
 * --------------------
 * インプットバッファを消す。
 */
void clear() {
    char c;
    do {
        c = getchar();
    } while(c != '\n' && c != EOF);
}
