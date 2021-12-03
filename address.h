/*
    E20C4033 Stefan Larsson
    2021-11-26
    address.h
*/

#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

//アドレス入力文字制限
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

void printAll(List *pHead); /*全部のアドレスを出力*/
void print(List *pHead); /*アドレスを細かくて出力*/
void add(List *pHead); /*アドレスを追加*/
void insert(List *pHead); /*アドレスを挿入*/
void move(List *pHead); /*アドレスを削除*/
void edit(List *pHead); /*アドレスを編集*/
void destroyAll(List *pHead); /*全部のアドレスを削除*/
void destroy(List *pHead); /*アドレスを削除*/
List *find(List *pHead); /*emailでアドレスを検索*/
void new(List *node); /*アドレス入力*/

#endif
