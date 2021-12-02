/*
    E20C4033 Stefan Larsson
    2021-11-26
    io.c
*/

//in header prob
#define FILENAME "REP01.xml"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "address.h"
#include "io.h"

//TODO: issue happening when writing to file after having added a new item. garbled xml. Only garbled when not all fields and being inputted, solved by validation?
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
    
    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
    xmlSaveFormatFileEnc(FILENAME, doc, "UTF-8", 1);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

//https://ubuntuforums.org/showthread.php?p=8805492
int read(List *pHead) {
    
    xmlDocPtr doc;
    xmlNode *root = NULL, *node = NULL;
    xmlAttr *attribute = NULL;
	xmlChar *value = NULL;
    List *p = NULL, *c = pHead;
	FILE *in;
	char *buffer;
	long numBytes;
    int a = 0;

	in = fopen(FILENAME, "r");
	if(in == NULL) {
        //TODO: err message
	    return 0;
    }

    //TODO: err message
	fseek(in, 0L, SEEK_END);
	numBytes = ftell(in);
	fseek(in, 0L, SEEK_SET);

	buffer = (char*)calloc(numBytes, sizeof(char));
	if(buffer == NULL) {
        //TODO: err message
        return 0;
    }
	fread(buffer, sizeof(char), numBytes, in);
	fclose(in);

	doc = xmlParseMemory(buffer, numBytes);
    if (doc == NULL){
		fprintf(stderr, "could not read buffer\n");
		return 0;
	}
    root = xmlDocGetRootElement(doc);

	for (node = root->children; node; node = node->next) {
        if(!strcmp(node->name, "address")) {

            attribute = node->properties;
            p = (List *) malloc(1 * sizeof(List));

            while(attribute) {
                value = xmlNodeListGetString(node->doc, attribute->children, 1);
                
                if(!strcmp(attribute->name, "name")) {
                    strcpy(p->name, (char *) value);
                } else if(!strcmp(attribute->name, "address")) {
                    strcpy(p->address, (char *) value);
                } else if(!strcmp(attribute->name, "phone")) {
                    strcpy(p->phone, (char *) value);
                } else if(!strcmp(attribute->name, "email")) {
                    strcpy(p->email, (char *) value);
                } else {
                    //TODO: err msg, failed to load field
                }
                xmlFree(value);
                attribute = attribute->next;
            }

            //assign our new node to the end of newest node in pHead, then move it forward.
            c->next = p;
            c->next->previous = c;
            c = c->next;
            a++;
        }
    }

    //Free the read buffer and clean up libxml
    free(buffer);
    xmlCleanupParser();

    return a;
}
