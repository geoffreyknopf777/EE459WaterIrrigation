//Geoffrey Knopf//
//linkedlist.h//
#include <stdlib.h>  //header for malloc(), free()
#include <stdio.h>   //header for console input and output
#include <string.h>  //header for memcpy(), memcmp()
#include <stdbool.h> //header for boolean true/false

typedef struct{
	unsigned int nCount;  //instances of the data
	void* pData;   	      //data to be stored
	void* pNext;          //pointer to the next node
} node;

typedef struct{
	node* pHead;
	void (*pPrintCB)(void*);
	bool (*pEqual)(void*, void*);
	unsigned int nDataSize;
	unsigned int nLength;
} linkedlist;

/* Takes a pointer to the uninitialized linked list,
the size of each data element,
a pointer to a function that prints the linked list,
and a pointer to a function that compares list items for equality. */
bool LinkedListCreate(linkedlist* pLL, unsigned int nDataSize, void (*pPrintCB) (void*), bool (*pEqual)(void*, void*)){
	if(!pLL)
		return false;
	(*pLL).pHead = (void*)NULL;
	(*pLL).pPrintCB = pPrintCB;
	(*pLL).pEqual = pEqual;
	(*pLL).nDataSize = nDataSize;
	(*pLL).nLength = 0;
return true;
}

unsigned int LinkedListSize(linkedlist* pLL){
	return (*pLL).nLength;
}

void LinkedListPrintNode(linkedlist* pLL, node* pNode){
	if((*pLL).pPrintCB){
		(*pLL).pPrintCB( (*pNode).pData );
	}
}

void LinkedListPrintData(linkedlist* pLL, void* pData){
	if((*pLL).pPrintCB){
		(*pLL).pPrintCB( pData );
	}
}

bool LinkedListDisplay(linkedlist* pLL){
	if(!pLL)
		return false;
	node* pCurNode = (*pLL).pHead;	
	if(pCurNode == NULL){
		return false;
	}

	while(pCurNode != NULL){ //find first matching node or end of list		
		LinkedListPrintNode(pLL, pCurNode);
		pCurNode = (node*)((*pCurNode).pNext);
	}
return true;
}

node* LinkedListCreateNode(linkedlist* pLL, void* pData){		
	node* pNode = (node*)calloc(1, (size_t)sizeof(node));
	if(pNode == NULL){ //error if the node could not be allocated
		printf("Error: node could not be allocated\n");
		return NULL;
	}
	(*pNode).nCount = 1;
	(*pNode).pData = (void*)calloc(1, (size_t)(*pLL).nDataSize);
	if(!(*pNode).pData){ //error if the data could not be allocated
		printf("Error: data could not be allocated\n");	
		return NULL;
	}
	memcpy((*pNode).pData, pData, (size_t)(*pLL).nDataSize);
	(*pNode).pNext = (void*)NULL;
	return pNode;
}

bool LinkedListDataEqual(linkedlist* pLL, void* pA, void* pB){
	if(pLL == NULL || pA == NULL || pB == NULL){
		printf("Error: null pointers\n");
		return false;
	}
	if((*pLL).pEqual == NULL){
		return false; //handle comparison pointer == NULL
	}
	if((*pLL).pEqual(pA, pB)){
		return true;
	}
return false;
}

bool LinkedListInsert(linkedlist* pLL, void* pData){
	node* pNode;	
	if(pLL == NULL || pData == NULL){
		printf("Error: insertion failed\n");
		return false;
	}
	pNode = LinkedListCreateNode(pLL, pData);
	if(pNode == NULL){ //error if the node could not be allocated
		printf("Error: insertion failed\n");	
		return false;
	}
	if((*pLL).pHead == NULL){ //if this is the first node inserted		
		(*pLL).pHead = pNode;
		(*pLL).nLength = 1;
		return true;
	}
	else{ //if other nodes are already present
		node* pCurNode = (node*)((*pLL).pHead);	
		node* pPrevNode = NULL;
		while(pCurNode != NULL){ //find first matching node or end of list
			if((*pCurNode).pData == NULL || pData == NULL){
				printf("Error: node has no data\n");
				return false;
			}
			if(LinkedListDataEqual(pLL, (*pCurNode).pData, pData)){				
				(*pCurNode).nCount++; //if the node is already in the list, increment the count
				return true;
			}
		pPrevNode = pCurNode;
		pCurNode = (node*)((*pCurNode).pNext);
		}
		(*pPrevNode).pNext = (void*)pNode;
		(*pLL).nLength++;
		return true;
	}
printf("Error: insertion failed\n");
return false;
}

bool LinkedListRemove(linkedlist* pLL, void* pData){
	if(!pLL || !pData)
		return false;
	if((*pLL).pHead == NULL)
		return false; //if there are no items in the list
	
	node* pPrevNode = NULL;
	node* pCurNode = (node*)(*pLL).pHead;	
		while((*pCurNode).pNext){ //find first matching node or end of list
			if(LinkedListDataEqual(pLL, (*pCurNode).pData, pData)){
				if((*pCurNode).nCount > 1){ //if there is more than one instance, decrement the counter
					(*pCurNode).nCount--;
				}
				else{ //if only one instance, remove node from lsit
					if(pPrevNode == NULL){ //if first node in list, change head
						(*pLL).pHead = (node*)(*pCurNode).pNext;						
					}
					else{ //if other node in list, 
						(*pPrevNode).pNext = (node*)(*pCurNode).pNext;
					}
					free(pCurNode); //free the memory
				}
				return true;
			}
			pPrevNode = pCurNode;			
			pCurNode = (node*)(*pCurNode).pNext;
		}
	(*pLL).nLength--;
return false;
}

int LinkedListCount(linkedlist* pLL, void* pData){		
	if(!pLL || !pData){
		printf("Error: null pointers\n");	
		return 0;
	}
	node* pCurNode = (node*)((*pLL).pHead);	
	if(pCurNode == NULL){
		return 0;
	}
	while(pCurNode != NULL){ //find first matching node or end of list
		if((*pCurNode).pData == NULL || pData == NULL){
			printf("Error: node has no data\n");
			return 0;
		}		
		if(LinkedListDataEqual(pLL, (*pCurNode).pData, pData)){
			return (*pCurNode).nCount;
		}
		pCurNode = (node*)((*pCurNode).pNext);
	}
return 0;
}

bool LinkedListClear(linkedlist* pLL){
	node *pCurNode;
	node *pNextNode;
	if(!pLL)
		return false;
	pCurNode = (*pLL).pHead;
	while(pCurNode != NULL){
		pNextNode = (node*)((*pCurNode).pNext); //store pointer to next
		free(pCurNode); //delete current node
		pCurNode = pNextNode; //move to the next node
	}
(*pLL).pHead = (void*)NULL;
(*pLL).nLength = 0;
return true;
}
