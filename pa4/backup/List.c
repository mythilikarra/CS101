//Mythili Karra
////mmkarra
////CMPS 101
////May 27, 2019
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"

typedef struct NodeObj{
	int value;
	struct NodeObj* previous;
	struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

Node newNode(int v) {
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N -> value = v;
	N -> previous = NULL ;
	N-> next = NULL;
	return N;
}
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ){
		free(*pN);
		*pN = NULL;
	}
}

typedef struct ListObj {
	int length;
	int indexcursor;
	Node front;
	Node back;
	Node cursor;
}ListObj;

List newList() {
	List L = malloc(sizeof(ListObj));
	assert( L != NULL);
	L -> length = 0;
	L -> indexcursor = -1;
	L -> front = NULL;
	L -> back = NULL;
	L -> cursor = NULL;
	return L;
}

void freeList(List* pL) {
	if(pL != NULL && *pL != NULL) {
		while( length(*pL) != 0) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

int length(List L) {
	if(L == NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return L->length;
}

int index(List L) {
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return L -> indexcursor;
}
int front(List L) {
	if(L == NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(length(L) > 0) {
		return L -> front -> value;
	}
	else {
		printf("Cannot print the index of the front node if the front node doesn't exist");
		exit(1);
	}
}
int back(List L) {
	if(L == NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(length(L) > 0) {
		return L -> back -> value;
	}
	else {
		printf("Cannot print the index of the front node if the front node doesn't exist");
		exit(1);
	}
}
int get(List L) {
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(length(L) > 0 && L -> indexcursor >= 0) {
		return L -> cursor -> value;
	}
	else {
		printf("Cannot get the cursor when a cursor does not exist");
	}
}
int equals(List A, List B) {
	if(A == NULL || B == NULL){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}
	if(A->length != B->length) {
		return 0;
	}
	else if(A->length == 0 && B->length == 0) {
		return 1;
	}
	else {
		Node a = A->front;
		Node b = B->front;
		while(a != NULL) {
			if(a->value != b->value) {
				return 0;
			}
			else {
				a = a->next;
				b = b->next;
			}
		}
		return 1;
	}
}

void clear(List L) {
	if(L == NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	while(L->front != NULL) {
		Node x = L->front;
		L->front = L->front->next;
		freeNode(&x);
	}
	//      freeList(&L);
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->indexcursor = -1;
}

void moveFront(List L) {
	if(L == NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	else if(length(L) > 0) {
		L->cursor = L->front;
		L->indexcursor = 0;
	}
}

void moveBack(List L) {
	if(L == NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	else if(length(L) > 0) {
		L->cursor = L->back;
		L->indexcursor = L->length - 1;
	}
}
void moveNext(List L) {
	if(L == NULL){
  		 printf("List Error: calling moveNext() on NULL List reference\n");
	}
	else if(L->cursor != NULL && L->cursor != L->back) {
		L->cursor = L->cursor->next;
		L->indexcursor++;
	}
	else if(L->cursor != NULL && L->cursor == L->back) {
		L->cursor = NULL;
		L->indexcursor = -1;
	}
}
void movePrev(List L) {
	if(L == NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	else if(L->cursor != NULL) {
		if(L->indexcursor != 0 && L->indexcursor != 1) {
			Node a = L->cursor->previous->previous;
			Node b = L->cursor;
			L->cursor = L->cursor->previous;
			L->cursor->previous = a;
			L->cursor->next = b;
			L->indexcursor--;
		}
		else if(L->indexcursor == 0) {
			L->cursor = NULL;
			L->indexcursor = -1;
		}
		else if(L->indexcursor == 1) {
			Node a = L->cursor;
			L->cursor = L->cursor->previous;
			L->indexcursor = 0;
			if(L->indexcursor != length(L) - 1) {
				a->previous = L->cursor;
			}
			if(L->indexcursor != 0) {
				L->cursor->previous = NULL;
			}
		}
	}
	else if(L->cursor == NULL) {
		printf("Cannot move cursor when cursor is undefined");
		exit(1);
	}
}
void prepend(List L, int data) {
	if(L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	if(length(L) > 0) {
		Node temp = L->front;
		Node N = newNode(data);
		L->front = N;
		L->front->next = temp;
		L->front->previous = NULL;
		temp->previous = L->front;
		if(L->indexcursor != -1) {
			L->indexcursor++;
		}
	}
	else if(length(L) == 0) {
		Node N = newNode(data);
		L->front = N;
		L->back = N;
	}
	L->length++;
}
void append(List L, int data) {
	if(L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	if(length(L) > 0) {
		Node temp = L->back;
		Node N = newNode(data);
		L->back = N;
		temp->next = N;
		N->previous = temp;
	}
	else if(length(L) == 0) {
		Node N = newNode(data);
		L->front = N;
		L->back = N;
	}
	L->length++;
}
void insertBefore(List L, int data) {
	if(L == NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if(length(L) > 0 && index(L) >= 0) {
		if(L->cursor->previous == NULL) {
			Node N = newNode(data);
			N->next = L->front;
			L->front = N;
			L->cursor->previous = N;
			N->previous = NULL;
			L->length++;
		}
		else {
			Node temp = L->cursor ->previous;
			Node N = newNode(data);
			temp->next = N;
			N->next = L->cursor;
			L->cursor->previous = N;
			N->previous = temp;
			L->length++;
		}
		L->indexcursor++;
	}
}
void insertAfter(List L, int data) {
	if(length(L) > 0 && index(L) >= 0) {
		if(L->cursor->next != NULL) {
			Node temp = L->cursor->next;
			Node N = newNode(data);
			L->cursor->next = N;
			N->next = temp;
			N->previous = L->cursor;
			temp->previous = N;
			L->length++;
		}
		else {
			Node N = newNode(data);
			L->cursor->next = N;
			N->previous = L->cursor;
			L->back = N;
			L->length++;
		}
	}
	else {
		printf("Cannot insert when a cursor is not defined");
		exit(1);
	}
}
void deleteFront(List L) {
	if(length(L) == 1) {
		L->indexcursor = -1; //add
		L->cursor = NULL;   //add
		clear(L);
	}
	else if(length(L) > 1) {
		if(L->indexcursor == 0) {//add
			L->indexcursor = -1;//add
			L->cursor = NULL;//add
		}//add
		if(L->indexcursor != -1 ) {//add
			L->indexcursor--;//add
		}//add
		Node free = L->front;
		L->front = L->front->next;
		L->front->previous = NULL;
		L->length--;
		freeNode(&free);
		free = NULL;
	}
	else if(length(L) == 0) {
		printf("Cannot delete from an empty list");
		exit(1);
	}
}
void deleteBack(List L) {
	if(length(L) == 1) {
		clear(L);
	}
	else if(length(L)>1) {
		if(L->cursor == L->back) {
			L->cursor = NULL;
			L->indexcursor = -1;
		}
		Node free = L->back;
		L->back = L->back->previous;
		L->back->next = NULL;
		freeNode(&free);
		free = NULL;
		L->length--;
	}
	else if (length(L) == 0) {
		printf("Cannot delete from an empty list");
		exit(1);
	}
}
void delete(List L) {
	if(L->cursor == NULL) {
		printf("Cannot delete a nonexisting cursor");
		exit(1);
	}
	if(length(L) <= 0) {
		printf("Cannot delete from an empty list");
		exit(1);
	}
	if(length(L) > 0 && L->indexcursor >= 0) {
		if(L->cursor->previous != NULL && L->cursor->next != NULL) {
			Node free = L->cursor;
			L->cursor->previous->next = L->cursor->next;
			L->cursor->next->previous = L->cursor->previous;
			L->cursor = NULL;
			L->indexcursor = -1;
			freeNode(&free);
		}
		else if(L->cursor->previous == NULL) {
			Node free = L->cursor;
			L->front = L->cursor->next;
			if(L->cursor->next != NULL) {
				L->front->previous = NULL;
			}
			L->cursor = NULL;
			L->indexcursor = -1;
			freeNode(&free);
		}
		else if(L->cursor->next == NULL) {
			Node free = L->cursor;
			L->back = L->cursor->previous;
			L->back->next = NULL;
			L->cursor = NULL;
			L->indexcursor = -1;
			freeNode(&free);
		}
	}
	L->length--;
}
void printList(FILE* out, List L) {
	Node temp = L->front;
	while(temp != NULL) {
		printf("%s", "HI");
		fprintf(out, "%d ", temp->value);
		temp = temp->next;
	}
}
List copyList(List L) {
	List l = newList();
	if(length(L) != 0) {
		Node N = L->front;
		append(l,N->value);
		while(N->next != NULL) {
			N = N->next;
			append(l,N->value);
		}
	}
	return l;
}
