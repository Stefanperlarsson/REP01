/*
    E20C4033 Stefan Larsson
    2021-11-26
    address.c
*/

//https://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
//Private structures for that file should go in the .c file, with a declaration in the .h file if they are used by any functions in the .h .
//Public structures should go in the .h file.
//TODO: move to .h
//TODO: error went string entered is ""
//TODO: make variable names standard, pHead, node, p etc etc

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "address.h"
#include "input.h"
#include "validation.h"

/*
 * Function: printAll
 * ----------------------------
 *   全部のアドレスを出力、emailだけ
 *
 *   List *pHead: Listのhead
 */
void printAll(List *pHead){
    List *node = pHead;
    
    printf("一覧\n");
    if(!node) //Empty head
        return ;

    printf("HEAD current: %p, previous: %p, next: %p, \n", pHead, pHead->previous, pHead->next);
    while(node->next != NULL){
        node = node->next;
    	//printf("%s\n", node->email);
        printf("email: %s, current: %p, previous: %p, next: %p, \n", node->email, node, node->previous, node->next);
        
    }
}

/*
 * Function: print
 * ----------------------------
 *   一つのアドレスを細かくて出力
 *
 *   List *pHead: Listのhead
 */
void print(List *pHead) {

    List *node = find(pHead);

    if(node) {
        printf("eメールアドレス：%s\n名前：%s\n住所：%s\n電話番号：%s\n\n", node->email, node->name, node->address, node->phone);
    }
}

/*
 * Function: add
 * ----------------------------
 *   アドレスを追加
 *
 *   List *pHead: Listのhead
 */
void add(List *pHead){

    List *p = pHead;
    List *node = (List *) malloc(1 * sizeof(List));
    node->next = NULL;
    
    new(node);
    
    while(p->next != NULL){
		p = p->next;
	}
	p->next = node;
    node->previous = p;
}

/*
 * Function: destroyAll
 * ----------------------------
 *   全部のアドレスを削除
 *
 *   List *pHead: Listのhead
 */
void destroyAll(List *pHead){
	
    List *node;

    while(pHead) {
	    node = pHead;
        pHead = pHead->next;
        printf("free: %p:%s\n", node, node->email);
        free(node);
    }
	
	return;
}

/*
 * Function: destroy
 * ----------------------------
 *   アドレスを削除
 *
 *   List *pHead: Listのhead
 */
void destroy(List *pHead) {

    List *node = find(pHead);

    if(node) {
        if(node->next) {
            node->next->previous = node->previous;
        }
        node->previous->next = node->next;
        free(node);
    }
}

/*
 * Function: edit
 * ----------------------------
 *   アドレスを挿入
 *
 *   List *pHead: Listのhead
 */
void edit(List *pHead) {

    List *node = find(pHead);

    if(node) {
        new(node);
    }
}

/*
 * Function: move
 * ----------------------------
 *   アドレスを移動
 *
 *   List *pHead: Listのhead
 */
void move(List *pHead) {
    
    List *node = find(pHead);

    if(node) {
        if(node->next) {
            node->next->previous = node->previous;
            node->previous->next = node->next;
        } else if(node->previous->previous) { //make sure we're not in pHead
            node->previous->next = NULL;
        } else {
            fprintf(stderr, "一つのアドレスしか入ってない！\n"); //TODO: at this point we can still move the first item in the list if we have more than 2 items total
            //maybe disable the ability to move the first item alltogether? would reduce this if statement a lot.
        }
        node->next = pHead->next;
        node->previous = pHead;
        pHead->next->previous = node;
        pHead->next = node;
    }
}

/*
 * Function: find
 * ----------------------------
 *   emailでアドレスを検索
 *
 *   List *pHead: Listのhead
 * 
 *   returns: 見つけられたアドレス
 */
List *find(List *pHead) {
    List *node = pHead;
    char c[REP01_EMAIL_MAX];
    
    if(!node->next){
        printf("検索する前に、アドレスを追加してください\n");
        return NULL;
    }

    printf(":");
    string_input(c, REP01_EMAIL_MAX);
    c[strcspn(c, "\n")] = 0;
     
    while(node->next != NULL) {
        node = node->next;
        if(!strcmp(c, node->email)) {
            return node;
        }
    }
    fprintf(stderr, "%s: 存在してない\n", c);
    return NULL;
}

/*
 * Function: new
 * ----------------------------
 *   アドレス入力
 *
 *   List *node: 入力したいList
 * 
 */
void new(List *node){
    
    /*
    do {
        printf("名前：");
        string_input(node->name, REP01_NAME_MAX);
    } while(is_empty(node->name));

    do {
        printf("住所：");
        string_input(node->address, REP01_ADDRESS_MAX);
    } while(is_empty(node->address));

    do {
        printf("電話番号：");
        string_input(node->phone, REP01_PHONE_MAX);
    } while(is_empty(node->phone));
    */

    do {
        printf("eメールアドレス：");
        string_input(node->email, REP01_EMAIL_MAX);
    } while(!is_email(node->email));
}
