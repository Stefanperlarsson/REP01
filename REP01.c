/*
    E20C4033 Stefan Larsson
    2021-11-26
    REP01.c
*/

/* TODO
* Confirm teacher requirements
* Add comments to code where required
* Finish README.mc
* Use an assets/ folder for non essentials?
* Make variable names standard, pHead, node, p etc etc
* Issue happening when writing to file after having added a new item. garbled xml. Only garbled when not all fields and being inputted, solved by validation?
* Cleanup move() - At this point we can still move the first item in the list if we have more than 2 items total. Maybe disable the ability to move the first item alltogether? would reduce this if statement a lot.
*/

#include <stdio.h>
#include <stdlib.h>

#include "address.h"
#include "io.h"
#include "input.h"

/*
 * Function:  main 
 * --------------------
 * メイン関数
 */
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
