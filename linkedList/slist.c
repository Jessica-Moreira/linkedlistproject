#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "slist.h"

snode* snode_create( int data, snode* next){
	snode* p = (snode*)malloc(sizeof(snode));
	p->data = data;
	p->next = next;
	return p;
}

slist* slist_create() {
	slist* p = (slist*)malloc(sizeof(slist));
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;

	return p;
}

bool slist_empty(slist* list) {return list->size == 0;};
size_t slist_size(slist* list) {return list->size;};

void slist_popfront(slist* list){
	if(slist_empty(list)) {fprintf(stderr,"empty list\n"); return;}
	
	snode* p = list->head;
	list->head = list->head->next;
	free(p);
	-- list->size;
}

void slist_popback(slist* list){
	if(slist_empty(list)) {fprintf(stderr, "Underflow error\n"); return;}

	snode* p = list->head;
	while(p->next != list->tail) {p = p->next;}
	p->next = NULL;
	free(list->tail);
	list->tail = p;
	-- list->size;
}

void slist_pushfront(slist* list, int data){
	snode* p = snode_create(data, list->head);
	list->head = p;
	if (list->size == 0) {list->tail = p;}
	++list->size;
}

void slist_pushback(slist* list, int data){
	if(list->size == 0) {slist_pushfront(list,data); return;}

	snode* p = snode_create(data, NULL);
	list->tail->next = p;
	list->tail = p;
	++list->size;
}

void slist_clear(slist *list) {
	while(!slist_empty(list)){
		slist_popfront(list);
	}
}

void slist_print(slist* list, const char* msg){
	printf("%s\n", msg);
	if(slist_empty(list)) {printf("empty list\n"); return;}

	snode* p = list->head;
	while (p != NULL){
		printf("%d --> %p\n", p->data,  p->next);
		p = p->next;
	}
}

int slist_front(slist* list){
	if(slist_empty(list)) {printf("empty list\n"); exit(1);}
	return list->head->data;
}

int slist_back(slist* list){
	if(slist_empty(list)) {printf("empty list\n"); exit(1);}
	return list->tail->data;
}
