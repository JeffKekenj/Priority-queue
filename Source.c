/*COSC 2P91 Mini-Project 2 (Assignment 4)
Jeff Kekenj 4759171
Generic Priority Queue*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

//Node Struct, holds generic data pointer
//as well as next and previous pointers
typedef struct Node{
	void * data;
	float rank;
	struct Node * next;
	struct Node * prev;
} Node;

//PQ holds count and front and back pointers
typedef struct PQueue{
	struct Node * front;
	struct Node * back;
	int count;
} PQueue;


//Push new element onto the list
void push(PQueue * q, void * data, float rank){
	Node *n;
	n=(Node*)malloc(100*sizeof(Node));
	n->data = data;
	n->rank = rank;
	n->next = NULL;
	n->prev = NULL;

	if (q->front == NULL){
		q->front = n;
		q->back  = n;
		q->count++;
	} else{ //not first
		Node * temp = q->front;
		q->count++;
		if( rank > temp->rank){
			q->front->prev = n;
			n->next = q->front;
            q->front = n;
        } else {	
			while(rank < temp->rank) {	
				if(temp->next == NULL){
					break;
				}//if last element, break out of loop
					temp = temp->next;
              }//loop to proper priority position 
				if(temp->next == NULL && rank < temp->rank || rank == temp->rank) { //check less than greater or equal rank
						q->back->next = n;
						n->prev = q->back;
						q->back = n;
                    } 
                  else {
					  temp->prev->next = n;
					  n->prev = temp->prev;
					  n->next = temp;
					  temp->prev = n;
                  }//equal rank stores in FIFO priority
        }	
	}
}

//Dequeue element from PQ
void dequeue(PQueue * q) {
	Node *temp;
	if(q->back == NULL ){//no nodes
        printf("Error, Queue is empty\n");
	}
	//there is only one node
	else if(q->back->prev == NULL) {
			Node * temp2 = q->back;
			temp = temp2;
			q->front = NULL;
			q->back = NULL;
            free(temp2);
			q->count--;
            printf("Node Deleted\n");
    } else {
			Node * temp2 = q->back;
            temp = temp2;
			q->back = q->back->prev;
			q->back->next = NULL;
            free(temp2);
			q->count--;
			printf("Node Deleted\n");
    }//there are more than one node
}

void display(Node *n, int type) {
	//Vars for printing char array
	char *cArr;
	int sCount = 0;
	int sLen;

	if (type == 1) { //int
		if( n == NULL ) {
			printf("Queue is empty");
		}
		else {
			printf("\nRank \n%f", n->rank);
			printf("\ndata %d\n\n",n->data);
		}
	}
	if (type == 2) { //char
		if( n == NULL ) {
			printf("Queue is empty\n");
		}
		else {
			printf("\nRank \n%f", n->rank);
			printf("\n%c\n\n", n->data);
		}
	}
	if (type == 3) { //char arr
		if( n == NULL ) {
			printf("Queue is empty\n");
		}
		else {
			printf("\nRank \n%f\n", n->rank);	
			//print sentence
			printf("Data: \n");
			cArr = (char*)n->data;
			sLen = strlen(cArr);
			while (sCount<=sLen){
				printf("%c",cArr[sCount]);
				sCount++;
			}
			printf("\n");
		}
	}
	if (type == 4) { //Float
		if( n == NULL ) {
			printf("Queue is empty");
		}
		else {
			printf("\nRank \n%f", n->rank);
			printf("\ndata %f\n\n",*(float*)n->data);
		}
	}
}

//Delete all elements in the list
void deleteAll(PQueue * q){
	int i = q->count;
	if (i == 0){
		printf("Empty list");
	}
	while (i>0){
		dequeue(q);
		i--;
	}
	printf("List Cleared \n");
}

//Display all elements in the list
void printAll(PQueue * q, int type){
	Node * temp;
	int i;
	i = q->count;
	temp = q->front;
	while (i>0){		
		display(temp, type);
		temp = temp->next;
		i--;
	}
	printf("\n No other nodes to print or empty list\n");
}
 
 

int main ()
{ 
	//Initialize queue
	PQueue *queue; 
	Node * temp;
	int i;
	int input;
	char cInput;
	char *cArr;
	char *otherrthing;
	int iTESTING;
	int stuff;

	void * test;
	float *fVal;
	float ftest;
	float lasttest;

	float rankVar;
	queue = (PQueue*)malloc(100*sizeof(PQueue));
	queue->count = 0;
	queue->front = NULL;
	queue->back = NULL;

	printf("What data type would you like to use?\n");

	/*Four types for user input, PQ is generic but for sake of testing
	uses fours types for usability*/

	printf("1. Integers \n2. Character \n3. Strings \n4. Floats \n5. Exit \n");

	scanf_s("%d", &input);
	switch (input) {
	case 1:
		//INTEGER INPUT
		printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements\n7. Print all \n0: Quit\n");
		scanf_s("%d", &input);
		while (input != 0) {
			switch (input) {
			case 1:
				printf("Enter the integer data\n");
				scanf_s("%d", &test);	  
				printf("Enter the rank\n");
				scanf_s("%f", &rankVar);
				push(queue, test, rankVar);
				break;
			case 2:
				dequeue(queue);
				break;
			case 3:
				deleteAll(queue);
			break;
			case 4:
				if (queue->count > 0)printf("The head element rank: %f \n", queue->front->rank);
				else printf("Empty list\n");
			break;
			case 5:
				if (queue->count == 0) printf("PQ is empty\n");
				else printf("Not empty\n");
				break;
			case 6:
				printf("Number of elements in PQ: %d \n", queue->count);
				break;
			case 7:
				printAll(queue, 1);
				break;
			default:
		  // Code
		  break;
		}
			printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements \n7.Print all \n0: Quit\n");
			scanf_s("%d", &input);
		}
	  break;
	case 2:
		//CHARACTER INPUT
		input = 0;
		printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements\n7. Print all \n0: Quit\n");
		scanf_s("%d", &input);
		while (input != 0) {
			switch (input) {
			case 1:
				printf("Enter a single char\n");
				getchar();
				cInput = getchar();
				printf("Enter the rank\n");
				scanf_s("%f", &rankVar);
				push(queue, (char*)(cInput), rankVar);
				break;
			case 2:
				dequeue(queue);
				break;
			case 3:
				deleteAll(queue);
			break;
			case 4:
				if (queue->count > 0)printf("The head element rank: %f \n", queue->front->rank);
				else printf("Empty list\n");
			break;
			case 5:
				if (queue->count == 0) printf("PQ is empty\n");
				else printf("Not empty\n");
				break;
			case 6:
				printf("Number of elements in PQ: %d \n", queue->count);
				break;
			case 7:
				printAll(queue, 2);
				break;
			default:
		  // Code
		  break;
		}
			printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements \n7.Print all \n0: Quit \n");
			scanf_s("%d", &input);
		}
	  break;
	case 3:
		//STRING INPUT
		input = 0;
		printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements\n7. Print all \n0: Quit\n");
		scanf_s("%d", &input);
		while (input != 0) {
			switch (input) {
			case 1:
				printf("Enter a string\n");
				getchar();
				cArr = malloc(sizeof(char)*100);
				fgets(cArr, 100, stdin);
				printf("Enter the rank\n");
				scanf_s("%f", &rankVar);
				push(queue, (char*)(cArr), rankVar);
				break;
			case 2:
				dequeue(queue);
				break;
			case 3:
				deleteAll(queue);
			break;
			case 4:
				if (queue->count > 0)printf("The head element rank: %f \n", queue->front->rank);
				else printf("Empty list\n");
			break;
			case 5:
				if (queue->count == 0) printf("PQ is empty\n");
				else printf("Not empty\n");
				break;
			case 6:
				printf("Number of elements in PQ: %d \n", queue->count);
				break;
			case 7:
				printAll(queue, 3);
				break;
			default:
		  // Code
		  break;
		}
			printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements \n7.Print all \n0: Quit \n");
			scanf_s("%d", &input);
		}
	  break;
	case 4:
		//FLOAT INPUT
		input = 0;
		printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements\n7. Print all \n0: Quit\n");
		scanf_s("%d", &input);
		while (input != 0) {
			switch (input) {
			case 1:
				printf("Enter a float\n");
				fVal = malloc(sizeof(float)*100);		
				scanf_s("%f",fVal);
				printf("Enter the rank\n");
				scanf_s("%f", &rankVar);				
				push(queue, fVal, rankVar); 
				break;
			case 2:
				dequeue(queue);
				break;
			case 3:
				deleteAll(queue);
			break;
			case 4:
				if (queue->count > 0)printf("The head element rank: %f \n", queue->front->rank);
				else printf("Empty list\n");
			break;
			case 5:
				if (queue->count == 0) printf("PQ is empty\n");
				else printf("Not empty\n");
				break;
			case 6:
				printf("Number of elements in PQ: %d \n", queue->count);
				break;
			case 7:
				printAll(queue, 4);
				break;
			default:
		  // Code
		  break;
		}
			printf("1. Insert Node \n2. Delete Node \n3. Purge List \n4. Test rank \n5. See if PQ is empty \n6. Total Number of elements \n7.Print all \n0: Quit \n");
			scanf_s("%d", &input);
		}
	  break;
	default:
	  // Code
	  break;
	}

   return 0;
}