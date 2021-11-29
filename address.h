/*
    E20C4033 Stefan Larsson
    2021-11-26
    address.h
*/

#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_MAX 30
#define ADDRESS_MAX 80
#define PHONE_MAX 20
#define EMAIL_MAX 100

struct list{
	char name[NAME_MAX]; /*指名*/
    char address[ADDRESS_MAX]; /*住所*/
    char phone[PHONE_MAX]; /*電話番号*/
    char email[EMAIL_MAX]; /*eメールアドレス*/
	struct list *next;
    struct list *previous;
};
typedef struct list List;

void printAll(List *pHead);
void print(List *pHead);
void add(List *pHead);
void edit(List *pHead);
void destroyAll(List *pHead);
void destroy(List *pHead);
char* string_input(char *c, int s);
List *find(List *pHead);
List* new();

#endif
