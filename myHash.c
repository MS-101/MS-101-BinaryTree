#include <stdio.h>
#include <stdlib.h>

typedef struct hashNode {
    char status;

    /*
    a - empty
    b - occupied
    */

    int val;
} hashNode;

typedef struct hashTable {
    unsigned int size;
    hashNode *hashArray;
} hashTable;

int hashFunction(hashTable *myHashTable, int val) {
    val %= myHashTable -> size;

    return val;
}

int offsetHashFunction(int val) {
    val %= 1000;

    return val;
}

void insertHash(hashTable **myHashTable, int val) {
    int size, myHash, offsetHash, i;

    size = (*myHashTable) -> size;
    myHash = hashFunction(*myHashTable, val);
    offsetHash = offsetHashFunction(val);


    i = 0;
    while ((*myHashTable) -> hashArray[(myHash + i * offsetHash) % size].status != 'a') {
        if ((*myHashTable) -> hashArray[(myHash + i * offsetHash) % size].val == val) {
            return;
        }

        i++;
    }

    (*myHashTable) -> hashArray[(myHash + i * offsetHash) % size].status = 'b';
    (*myHashTable) -> hashArray[(myHash + i * offsetHash) % size].val = val;
}

hashNode searchHash(hashTable *myHashTable, int val) {
    hashNode foundNode;
    int size, myHash, offsetHash, i;

    size = myHashTable -> size;
    myHash = hashFunction(myHashTable, val);
    offsetHash = offsetHashFunction(val);

    i = 0;
    while (myHashTable -> hashArray[(myHash + i * offsetHash) % size].val != val) {
        i++;
    }

    foundNode = myHashTable -> hashArray[(myHash + i * offsetHash) % size];

    return foundNode;
}

void resizeHashTable(hashTable **myHashTable) {
    hashTable *newHashTable;
    int oldSize, newSize, myVal, i;

    oldSize = (*myHashTable) -> size;
    newSize = 2 * oldSize;

    newHashTable = (hashTable *)malloc(sizeof(hashTable));

    newHashTable -> size = newSize;
    newHashTable -> hashArray = (hashNode *)malloc(newSize * sizeof(hashNode));

    for (i = 0; i < newSize; i++) {
        newHashTable -> hashArray[i].status = 'a';
        newHashTable -> hashArray[i].val = 0;
    }

    for (i = 0; i < oldSize; i++) {
        if ((*myHashTable) -> hashArray[i].status == 'b') {
            myVal = (*myHashTable) -> hashArray[i].val;
            insertHash(&newHashTable, myVal);
        }
    }

    free((*myHashTable) -> hashArray);
    free(*myHashTable);

    *myHashTable = newHashTable;
}

void printNode(hashNode myHashNode) {
    printf("%c/%d\n", myHashNode.status, myHashNode.val);
}

void printHashTable(hashTable *myHashTable) {
    int i;

    printf("myHashTable -> size: %d\n", myHashTable -> size);
    printf("===========================\n");

    for (i = 0; i < myHashTable -> size; i++) {
        if (myHashTable -> hashArray[i].status == 'b') {
            printf("myHashTable[%d]: ", i);
            printNode(myHashTable -> hashArray[i]);
        }
    }

    printf("\n");
}

int main() {
    int keyCapacity, i;
    hashTable *myHashTable;
    hashNode testNode;

    keyCapacity = 1000;

    myHashTable = (hashTable *)malloc(sizeof(myHashTable));

    myHashTable -> size = keyCapacity;
    myHashTable -> hashArray = (hashNode *)malloc(keyCapacity * sizeof(hashNode));

    for (i = 0; i < keyCapacity; i++) {
        myHashTable -> hashArray[i].status = 'a';
        myHashTable -> hashArray[i].val = 0;
    }

    printHashTable(myHashTable);
    insertHash(&myHashTable, 1100);
    printHashTable(myHashTable);
    insertHash(&myHashTable, 2100);
    printHashTable(myHashTable);

    /*
    resizeHashTable(&myHashTable);
    printHashTable(myHashTable);
    */

    testNode = searchHash(myHashTable, 2100);
    printf("found node: ");
    printNode(testNode);

    return 0;
}
