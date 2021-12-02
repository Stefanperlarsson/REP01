/*
    E20C4033 Stefan Larsson
    2021-11-26
    address.h
*/

//should define field names as constants so i can use them for the XML file

#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REP01_NAME_MAX 30
#define REP01_ADDRESS_MAX 80
#define REP01_PHONE_MAX 20
#define REP01_EMAIL_MAX 100

struct list{
	char name[REP01_NAME_MAX]; /*指名*/
    char address[REP01_ADDRESS_MAX]; /*住所*/
    char phone[REP01_PHONE_MAX]; /*電話番号*/
    char email[REP01_EMAIL_MAX]; /*eメールアドレス*/
	struct list *next;
    struct list *previous;
};
typedef struct list List;

void printAll(List *pHead);
void print(List *pHead);
void add(List *pHead);
void edit(List *pHead);
void move(List *pHead);
void destroyAll(List *pHead);
void destroy(List *pHead);
List *find(List *pHead);
void new(List *node);

#endif
