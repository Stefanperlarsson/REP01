/*
    E20C4033 Stefan Larsson
    2021-11-26
    address.c
*/

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
    
    printf("\n一覧\n");
    while(node->next != NULL){
        node = node->next;
    	printf("* %s\n", node->email);
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
        printf("\neメールアドレス：%s\n名前：%s\n住所：%s\n電話番号：%s\n", node->email, node->name, node->address, node->phone);
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
    
    //アドレス入力
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
 *   アドレスを編集
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

    //次のはそんなにきれいではないけれど、next/previousを繋がう処理
    if(node) {
        if(node->next) {
            node->next->previous = node->previous;
            node->previous->next = node->next;
        } else if(node->previous->previous) {
            node->previous->next = NULL;
        } else {
            fprintf(stderr, "一つのアドレスしか入ってないので、移動できない！\n");
        }
        node->next = pHead->next;
        node->previous = pHead;
        pHead->next->previous = node;
        pHead->next = node;
    }
}

/*
 * Function: insert
 * ----------------------------
 *   アドレスを
 *
 *   List *pHead: Listのhead
 */
void insert(List *pHead) {
    
    List *node = find(pHead);
    List *p = NULL;

    if(node) {
        //新しいアドレス入力
        p = (List *) malloc(1 * sizeof(List));
        new(p);

        //next/previousを繋がう
        if(node->next) {
            p->next = node->next;
            node->next->previous = p;
        }
        p->previous = node;
        node->next = p;
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

    printf("検索(email):");
    string_input(c, REP01_EMAIL_MAX);
     
    while(node->next != NULL) {
        node = node->next;
        if(!strcmp(c, node->email)) {
            return node;
        }
    }
    fprintf(stderr, "%s：存在してない\n", c);
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

    do {
        printf("eメールアドレス：");
        string_input(node->email, REP01_EMAIL_MAX);
    } while(!is_email(node->email));

    node->next = NULL;
}
