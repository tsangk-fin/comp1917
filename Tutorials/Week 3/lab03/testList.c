// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"

void printListState(DLList list);
void printList(DLList list);
void printTestDescription(char* desc, char* longDesc);
void testAssert(int condition, char* conditionDesc, int quitOnError);
char* getNext(DLList list);
char* getPrev(DLList list);
char* getCurr(DLList list);

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);

	printf("========================================\n");
	printf("=   Testing of DLList implementation   =\n");
	printf("========================================\n");

	printTestDescription("Test 0 - Pre-test conditions", "The state of DLList before tests");
	printList(myList);
	printListState(myList);

	// Preset some checker variables

	char* oldNext;
	char* oldCurr;
	char* oldPrev;
	char* newNext;
	char* newCurr;
	char* newPrev;
	int oldListSize;

	// 
	// Test 1: add item after current
	//

	DLListMoveTo(myList, 1); // move to the start of a list

	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 1 - Add item after current at start of list",
		"* Adds string \"test1\" after cur\n* Current becomes \"test1\"\n* nitems should increase by 1"
	);

	printList(myList);
	printListState(myList);

	DLListAfter(myList, "test1");

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	printf("oldPrev: %s\n", oldPrev);
	printf("oldCurr: %s\n", oldCurr);
	printf("oldNext: %s\n", oldNext);
	

	printf("newPrev: %s\n", newPrev);
	printf("newCurr: %s\n", newCurr);
	printf("newNext: %s\n", newNext);

	testAssert( (oldListSize + 1) == DLListLength(myList), "nitems increased by one", 1 );
	testAssert( strcmp ("test1", newCurr)  == 0, "Current pointer is \"test1\"", 1 );

	testAssert( (oldNext == NULL && newNext == NULL) || strcmp(oldNext, newNext) == 0, "Next pointer is as expected", 1 );
	testAssert( (oldCurr == NULL && newPrev == NULL) || strcmp(oldCurr, newPrev) == 0, "Prev pointer is as expected", 1 );

	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);
	// exit(0);



	// 
	// Test 2: add item before current
	//

	DLListMoveTo(myList, 1); // move to the start of a list


	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 2 - Add item before current at start of list",
		"* Adds string \"test2\" before cur\n* Current becomes \"test2\"\n* nitems should increase by 1"
	);

	printList(myList);
	printListState(myList);

	DLListBefore(myList, "test2");

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	testAssert( strcmp ("test2", DLListCurrent(myList))  == 0, "Current pointer is \"test2\"", 1 );
	testAssert( (oldListSize + 1) == DLListLength(myList), "nitems increased by one", 1 );

	testAssert( (oldCurr == NULL && newNext == NULL) || strcmp (oldCurr, newNext)  == 0, "Next pointer is as expected", 1 );
	testAssert( (oldPrev == NULL && newPrev == NULL) || strcmp (oldPrev, newPrev)  == 0, "Previous pointer is as expected", 1 );
	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);

	// 
	// Test 3: add item after current (end of list)
	//

	DLListMove(myList, 99999); // shift to the end of the list by moving by a large integer

	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 3 - Add item at the end of list",
		"* Adds string \"test3\" at the end\n* Current becomes \"test3\"\n* nitems should increase by 1"
	);

	printList(myList);
	printListState(myList);

	DLListAfter(myList, "test3");

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	testAssert( (oldListSize + 1) == DLListLength(myList), "nitems increased by one", 1 );
	testAssert( strcmp ("test3", newCurr)  == 0, "Current pointer is \"test3\"", 1 );

	testAssert( (oldNext == NULL && newNext == NULL) || strcmp(oldNext, newNext) == 0, "Next pointer is as expected", 1 );
	testAssert( (oldCurr == NULL && newPrev == NULL) || strcmp(oldCurr, newPrev) == 0, "Prev pointer is as expected", 1 );

	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);



	// 
	// Test 4: add item before end of list
	//

	DLListMove(myList, 99999); // shift to the end of the list by moving by a large integer

	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 4 - Add item before current",
		"* Adds string \"test4\" before end\n* Current becomes \"test4\"\n* nitems should increase by 1"
	);

	printList(myList);
	printListState(myList);

	DLListBefore(myList, "test4");

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	testAssert( strcmp ("test4", DLListCurrent(myList))  == 0, "Current pointer is \"test4\"", 1 );
	testAssert( (oldListSize + 1) == DLListLength(myList), "nitems increased by one", 1 );

	testAssert( (oldCurr == NULL && newNext == NULL) || strcmp (oldCurr, newNext)  == 0, "Next pointer is as expected", 1 );
	testAssert( (oldPrev == NULL && newPrev == NULL) || strcmp (oldPrev, newPrev)  == 0, "Previous pointer is as expected", 1 );
	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);

	// 
	// Test 5: delete current item
	//

	if (DLListLength(myList) < 5){
		DLListBefore(myList, "an extra line 1 to test delete");
		DLListBefore(myList, "an extra line 2 to test delete");
		DLListBefore(myList, "an extra line 3 to test delete");
		DLListBefore(myList, "an extra line 4 to test delete");
		DLListBefore(myList, "an extra line 5 to test delete");
	}

	DLListMoveTo(myList, 2); // move to somewhere in the middle

	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 5 - Delete current item in middle of list",
		"* nitems should decrease by 1\n* next item should become current"
	);

	printList(myList);
	printListState(myList);

	DLListDelete(myList);

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	testAssert( (oldListSize - 1) == DLListLength(myList), "nitems decreased by one", 1 );

	testAssert( (oldNext == NULL && newCurr == NULL) || strcmp (oldNext, newCurr)  == 0, "Current pointer is as expected", 1 );
	testAssert( (oldPrev == NULL && newPrev == NULL) || strcmp (oldPrev, newPrev)  == 0, "Previous pointer is as expected", 1 );
	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);

	// 
	// Test 6: delete current item
	//

	DLListMoveTo(myList, 1); // move to somewhere in the middle

	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 6 - Delete current item at start of list",
		"* nitems should decrease by 1\n* next item should become current"
	);

	printList(myList);
	printListState(myList);

	DLListDelete(myList);

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	testAssert( (oldListSize - 1) == DLListLength(myList), "nitems decreased by one", 1 );

	testAssert( (oldNext == NULL && newCurr == NULL) || strcmp (oldNext, newCurr)  == 0, "Current pointer is as expected", 1 );
	testAssert( (oldPrev == NULL && newPrev == NULL) || strcmp (oldPrev, newPrev)  == 0, "Previous pointer is as expected", 1 );
	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);

	// 
	// Test 7: delete current item
	//

	DLListMove(myList, 9999999); // move to end of list using large number

	oldCurr = getCurr(myList);
	oldNext = getNext(myList);
	oldPrev = getPrev(myList);

	oldListSize = DLListLength(myList);

	printTestDescription(
		"Test 7 - Delete current item at end of list",
		"* nitems should decrease by 1\n* SPECIAL CASE: since current was    last, current becomes new last"
	);

	printList(myList);
	printListState(myList);

	DLListDelete(myList);

	newCurr = getCurr(myList);
	newNext = getNext(myList);
	newPrev = getPrev(myList);

	testAssert( (oldListSize - 1) == DLListLength(myList), "nitems decreased by one", 1 );

	testAssert( (oldPrev == NULL && newCurr == NULL) || strcmp (oldPrev, newCurr)  == 0, "Current pointer is as expected (special case)", 1 );
	testAssert( (oldNext == NULL && newNext == NULL) || strcmp (oldNext, newNext)  == 0, "Next pointer is as expected", 1 );
	testAssert( validDLList(myList) , "validDLList() is happy? :)", 1);

	printf("\n");
	
	printList(myList);
	printListState(myList);


	printf("****************************************\n");
	printf("*  All tests completed successfully!   *\n"); 
	printf("****************************************\n");

	freeDLList(myList);

	return 0;
}



void printListState(DLList list){
	printf(">> state >>\n");
	printf("* List size: %d\n", DLListLength(list));

	if(DLListLength(list) > 0){
		printf("* Current: %s\n", DLListCurrent(list));
	}else{
		printf("* Current: [no current]\n");
	}
	printf("<< state <<\n\n");
}

void printList(DLList list){
	printf(">> DLList dump >>\n");
	showDLList(stdout, list);
	printf("<< end dump <<\n\n");
}

void printTestDescription(char* desc, char* longDesc){
	printf("\n\n");
	printf("****************************************\n");
	printf(" %s:\n", desc);

	int modi = 0;
	for (int i = 0; i < strlen(longDesc); i++){
		if ((modi % 36) == 0) printf("\n   ");
		
		printf("%c", longDesc[i]);
		if (longDesc[i] == '\n') printf("   ");

		if (longDesc[i] == '\n'){
			modi = 1;
		}else{
			modi++;
		}
	}
	printf("\n");
	printf("****************************************\n");
	printf("\n");
}

void testAssert(int condition, char* conditionDesc, int quitOnError){
	printf("[%s] %s\n", (condition ? "PASS" : "FAIL"), conditionDesc );

	if (quitOnError && !condition){
		exit(0);
	}
}

char* getNext(DLList list){
	if (DLListLength(list) == 0) return NULL;

	char* oldNext;
	char* tmpCmp = getCurr(list);

	if( DLListMove(list, 0) ){
		if (DLListMove(list, 1) && (strcmp(getCurr(list), tmpCmp) == 0)) {
			oldNext = NULL;
		}else{
			oldNext = getCurr(list);
			DLListMove(list, -1);
		}
	}else{
		DLListMove(list, 1);
		oldNext = getCurr(list);
		DLListMove(list, -1);
	}

	return oldNext;
}

char* getPrev(DLList list){
	if (DLListLength(list) == 0) return NULL;

	char* oldPrev;
	char* tmpCmp = getCurr(list);

	if ( DLListMove(list, 0) ) {
		if (DLListMove(list, -1) && (strcmp(getCurr(list), tmpCmp) == 0)) {
			oldPrev = NULL;
		}else{
			oldPrev = getCurr(list);
			DLListMove(list, 1);
		}
	}else{
		DLListMove(list, -1);
		oldPrev = getCurr(list);
		DLListMove(list, 1);
	}

	return oldPrev;
}

char* getCurr(DLList list){
	char* oldCurr;

	if ( DLListLength(list) > 0 ){
		oldCurr = DLListCurrent(list);
	}else{
		oldCurr = NULL;
	}

	return oldCurr;
}