#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include"IntegerQueue.h"

typedef struct QueueObj{
   int item;
   struct QueueObj* next;
}QueueObj;

// Node type
typedef QueueObj* Node;

// IntegerListObj type
typedef struct IntegerQueueObj{
   Node top;     // pointer to first Node in list   
   int numItems;      // number of items in this IntegerList
   Node bottom; //pointer to last Node in list
} IntegerQueueObj;

Node newNode(int x) {
   Node N = malloc(sizeof(QueueObj));
   assert(N!=NULL);
   N->item = x;
   N->next = NULL;
   return (N);
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
   free(*pN);
   *pN = NULL;
   }
}

IntegerQueue newIntegerQueue(){
   IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
   assert(Q!=NULL);
   Q->top = NULL;
   Q->bottom = NULL;
   Q->numItems = 0;
   return Q;
}

void freeIntegerQueue(IntegerQueue* pQ){
   if( pQ!=NULL && *pQ!=NULL ){
   dequeueAll(*pQ);
   free(*pQ);
   *pQ = NULL;
   }
}

int isEmpty(IntegerQueue Q){
   if( Q==NULL ){
      fprintf(stderr,
         "IntegerQueue Error: calling isEmpty() on NULL IntegerQueue reference\n");
         exit(EXIT_FAILURE);
   }
      if (Q->numItems==0) {
         return 1;
      }else return 0;
}

int length(IntegerQueue Q){
   return Q->numItems;
}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x){
   if(Q->numItems == 0){
      Q->top = Q->bottom = newNode(x);
   }else{
      Node N;
      N = newNode(x);
      Q->bottom->next = N;
      Q->bottom = N;
   }
   Q->numItems++;
}


// Deletes and returns the item at front of Q.
int dequeue(IntegerQueue Q){
    int x;
    Node N;
    if(Q->top==NULL){
    fprintf(stderr, "cannot dequeue() empty queue\n");
    exit(EXIT_FAILURE);
    }
    N = Q->top;
    Q->top = N->next;
    x = N->item;
    //memory errors could be because here . . . . 
    freeNode(&N);
    Q->numItems--;
    return x;
    
}


// Returns the item at front of Q.
int peek(IntegerQueue Q){
    int x;
    Node N;
    if(Q->top==NULL){
    fprintf(stderr, "cannot peek() empty queue\n");
    exit(EXIT_FAILURE);
    }
    N = Q->top;
    x = N->item;
    return x;
}


void dequeueAll(IntegerQueue Q){
    if( Q==NULL ){
       fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "\
                      "IntegerQueue reference");
       exit(EXIT_FAILURE);
    }

    Q->bottom = NULL;
    Q->top = NULL;
    Q->numItems =0;
}


int digits(int n){
    long long num;
    int count = 0;

   num = n;
    
    while(num != 0)
    {   
        count++;
        num /= 10;
    }

    return count;
}



int countChars(IntegerQueue Q){
   Node N = Q->top;
   int count = 0;
   while(N != NULL){
      // if(N->next = NULL){
      //    count += digits(N->item);
      //    N = N->next;
      // }else{
         count += digits(N->item)+1;
         N = N->next;
         
      // }

   }
   //another memory problem might arise here from not freeing N
   freeNode(&N);
   return count;   
}

char * integerToCharArray(Node N){
   int n = digits(N->item);
   char *numArray = calloc(n, sizeof(char));
   sprintf(numArray, "%d", N->item);
   return numArray;
   free(numArray);
}

char* toStringInOrder(char* buf, Node R){
   while(R != NULL){
      strcpy(buf, integerToCharArray(R));
      buf += strlen(integerToCharArray(R));
      *buf = ' ';
      buf++;
      R = R->next;
   }
   return buf;

}


// Returns a pointer to a char array, containing the integer sequence represented by Q.
char* IntegerQueueToString(IntegerQueue Q){
   char* str;
   //int i, n;
   int n;
   if( Q==NULL ){
      fprintf(stderr, 
         "IntegerQueue Error: calling IntegerQueueToString() on NULL IntegerQueue "\
         "reference\n");
      exit(EXIT_FAILURE);
   }

   n = countChars(Q); 
   str = calloc(n+1, sizeof(char));
   
   
   toStringInOrder(str, Q->top);
   str[n] = '\0';
   return str;
   free(str);
}

// Returns true (1) if Q and R are matching, else false
int equals(IntegerQueue Q, IntegerQueue R){
    int i;
    if( Q==NULL || R==NULL ){
        fprintf(stderr, "IntegerQueue Error: equals() called on NULL IntegerQueue "\
                        "reference");
        exit(EXIT_FAILURE);
    }
    Node N = Q->top;
    Node O = R->top;
    if(Q->numItems != R->numItems){
        return 0;
    }else{
        for(i=0; i<Q->numItems; i++){
            if(N->item == O->item){
                N = N->next;
                O = O->next;
            }else{
                return 0;
            }
        }
        return 1;
    }
}