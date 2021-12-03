/*
    E20C4033 Stefan Larsson
    2021-11-26
    io.c
*/

#define REP01_FILENAME "REP01.xml"

#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/stat.h>

#include "address.h"
#include "io.h"

/*
 * Function: write
 * ----------------------------
 *   アドレスをXMLファイルで保存
 *
 *   List *pHead: Listのhead
 */
void write(List *pHead) {

    xmlDocPtr doc = NULL;
    xmlNodePtr root = NULL, child = NULL;
    List *node = pHead;

    doc = xmlNewDoc(BAD_CAST "1.0");
    root = xmlNewNode(NULL, BAD_CAST "addresses");
    xmlDocSetRootElement(doc, root);

    while(node->next != NULL) {
        node = node->next;

        child = xmlNewChild(root, NULL, BAD_CAST "address", NULL);
        xmlNewProp(child, BAD_CAST "name", BAD_CAST node->name);
        xmlNewProp(child, BAD_CAST "address", BAD_CAST node->address);
        xmlNewProp(child, BAD_CAST "phone", BAD_CAST node->phone);
        xmlNewProp(child, BAD_CAST "email", BAD_CAST node->email);
    }
    xmlSaveFormatFileEnc(REP01_FILENAME, doc, "UTF-8", 1);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

/*
 * Function: read
 * ----------------------------
 *   アドレスをXMLファイルから読み込む
 *
 *   List *pHead: Listのhead
 */
int read(List *pHead) {
    
    xmlDocPtr doc;
    xmlNode *root = NULL, *node = NULL;
    xmlAttr *attribute = NULL;
	xmlChar *value = NULL;
    List *p = NULL, *c = pHead;
	FILE *in;
    struct stat b;
	char *buffer;
	long numBytes;
    int a = 0;

    //REP01_FILENAME存在チェック
    if(stat(REP01_FILENAME, &b)){
        return 0;
    }

    //libxml2のxmlParseFile()を使用して、直接ファイルを読み込もうとしたが、バグがあって、fopenのバッファから読むことにした。
    //バグ：http://ubuntuforums.org/showthread.php?p=8805492
	in = fopen(REP01_FILENAME, "r");
	if(in == NULL) {
        fprintf(stderr, "XMLファイルを開けない！\n");
	    return 0;
    }

    fseek(in, 0L, SEEK_END);
	numBytes = ftell(in);
	fseek(in, 0L, SEEK_SET);

	buffer = (char*)calloc(numBytes, sizeof(char));
	if(buffer == NULL) {
        fprintf(stderr, "バッファ使えない！\n");
        return 0;
    }
	fread(buffer, sizeof(char), numBytes, in);
	fclose(in);

    //バッファから読み込む
	doc = xmlParseMemory(buffer, numBytes);
    if (doc == NULL){
		fprintf(stderr, "バッファを読み込めない！\n");
		return 0;
	}
    root = xmlDocGetRootElement(doc);

    //<address>を繰り返して、データを読み込む
	for (node = root->children; node; node = node->next) {
        if(!strcmp(node->name, "address")) {

            attribute = node->properties;
            p = (List *) malloc(1 * sizeof(List));

            while(attribute) {
                value = xmlNodeListGetString(node->doc, attribute->children, 1);
                
                //データをListに入れる
                if(!strcmp(attribute->name, "name")) {
                    strcpy(p->name, (char *) value);
                } else if(!strcmp(attribute->name, "address")) {
                    strcpy(p->address, (char *) value);
                } else if(!strcmp(attribute->name, "phone")) {
                    strcpy(p->phone, (char *) value);
                } else if(!strcmp(attribute->name, "email")) {
                    strcpy(p->email, (char *) value);
                } else {
                    fprintf(stderr, "知らいないXMLフィールド：%s(%s)\n", attribute->name, (char *) value);
                }
                xmlFree(value);
                attribute = attribute->next;
            }

            //pHeadに追加
            c->next = p;
            c->next->previous = c;
            c = c->next;
            a++;
        }
    }

    //バッファやXMLを開放する
    free(buffer);
    xmlCleanupParser();

    return a;
}
