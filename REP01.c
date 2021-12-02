/*
    E20C4033 Stefan Larsson
    2021-11-26
    REP01.c
*/

/* Notes
Focus on documentation, .md file convert to pdf
Read teacher docs more
* https://marketplace.visualstudio.com/items?itemName=yzane.markdown-pdf (mdpdf usage)

Code
* maybe make int_input() into input() and just call fgets manually for each string input?

https://stackoverflow.com/questions/5128664/how-to-split-a-c-program-into-multiple-files
https://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples
validation.c - validate address input
io.c - storage
REP01.c - main, menu
address.c - data object, address functions
*/

#include <stdio.h>

#include "address.h"
#include "io.h"

int int_input();
void clear();

int main(void) {

    List *pHead = (List *) malloc(1 * sizeof(List));

    //Load addresses
    printf("Read %d addresses\n", read(pHead));

    printf("Ｃ言語実習２　アドレス帳　E20C4033　ラーション・ステファン\n");
    while(1) {
        printf("\n1)一覧 2)詳細 3)新規登録 4)削除 5)挿入 6)移動 0)終了\n");

        switch(int_input()) {
            case 1:
                printAll(pHead);
                break;
            case 2:
                print(pHead);
                break;
            case 3:
                add(pHead);
                break;
            case 4:
                destroy(pHead);
                break;
            case 5:
                edit(pHead);
                break;
            case 6:
                move(pHead);
                break;
            case 0:
                write(pHead);
                destroyAll(pHead);
                return 0;
                break;
            default:
                fprintf(stderr, "0-7を入力してください\n");
                break;
        }
    }
}

//TODO: move to validation.c?
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

void clear() {
    char c;
    do {
        c = getchar();
    } while(c != '\n' && c != EOF);
}
