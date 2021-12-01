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

#include "address.h"

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

void print(List *pHead) {

    List *node = find(pHead);

    if(node) {
        printf("eメールアドレス：%s\n名前：%s\n住所：%s\n電話番号：%s\n\n", node->email, node->name, node->address, node->phone);
    }
}

void add(List *pHead){

    List *p = pHead;
    List *node = new();
    
    //TODO assign directly to head
    //issue is probably cause node is a local variable, needs to be supplied from main? or use return
    //if(!pHead->next) {
    //    *pHead = *node;
    //} else {
        //pHead->next = node;
    //}
    while(p->next != NULL){
		p = p->next;
	}
	p->next = node;
    node->previous = p;
}

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

void edit(List *pHead) { //TODO: technically this replaces the entire node with a new one, should it only replace the data and not create a new memory object?

    List *node = find(pHead);
    List *p = NULL;

    if(node) {
        p = new();
        if(node->next) {
            node->next->previous = p;
            p->next = node->next;
        }
        node->previous->next = p;
        p->previous = node->previous;
        free(node);     
    }
}

void move(List *pHead) {
    
    List *node = find(pHead);

    if(node) {
        if(node->next) {
            node->next->previous = node->previous;
            node->previous->next = node->next;
        } else if(node->previous->previous) { //make sure we're not in pHead
            node->previous->next = NULL;
        } else {
            fprintf(stderr, "Only one item in list!"); //TODO: at this point we can still move the first item in the list if we have more than 2 items total
            //maybe disable the ability to move the first item alltogether? would reduce this if statement a lot.
        }
        node->next = pHead->next;
        node->previous = pHead;
        pHead->next->previous = node;
        pHead->next = node;
    }
}

List *find(List *pHead) {
    List *node = pHead;
    char c[REP01_EMAIL_MAX];
    
    if(!node->next){
        printf("Insert data before searching\n");
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
    fprintf(stderr, "%s: Not found", c);
    return NULL;
}

//TODO: supply new() with a node, instead of creating it here?
List* new(){

    List *node = (List *) malloc(1 * sizeof(List));
    node->next = NULL;
    
    /*
    printf("名前：");
    string_input(node->name, REP01_NAME_MAX);
    node->name[strcspn(node->name, "\n")] = 0;

    printf("住所：");
    string_input(node->address, REP01_ADDRESS_MAX);
    node->address[strcspn(node->address, "\n")] = 0;

    printf("電話番号：");
    string_input(node->phone, REP01_PHONE_MAX);
    node->phone[strcspn(node->phone, "\n")] = 0;
    */

    printf("eメールアドレス：");
    string_input(node->email, REP01_EMAIL_MAX);
    node->email[strcspn(node->email, "\n")] = 0;
    //TODO: validation

    return node;
}

char* string_input(char *c, int s){
    fgets(c, s, stdin);
    return c;
}