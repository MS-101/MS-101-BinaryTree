#include <stdio.h>
#include <stdlib.h>

typedef struct hashNode {
    char status;

    /*
    a - empty
    b - occupied
    */

    int key;
    int data;
} hashNode;

typedef struct hashTable {
    unsigned int size;
    hashNode *hashArray;
} hashTable;

int hashFunction(hashTable *myHashTable, int key) {
    key %= myHashTable -> size;

    return key;
}

int offsetHashFunction(int key) {
    key %= 1000;

    return key;
}

void insertHash(hashTable **myHashTable, int key, int data) {
    int size, myHash, offsetHash, arrayIndex, originIndex, i;

    size = (*myHashTable) -> size;
    myHash = hashFunction(*myHashTable, key);
    offsetHash = offsetHashFunction(key);

    arrayIndex = myHash % size;
    originIndex = arrayIndex;

    i = 1;
    while ((*myHashTable) -> hashArray[arrayIndex].status != 'a') {
        arrayIndex = (myHash + i * offsetHash) % size;

        if ((*myHashTable) -> hashArray[arrayIndex].key == key) {
            break;
        }

        if (originIndex == arrayIndex) {
            return;
        }

        i++;
    }

    (*myHashTable) -> hashArray[arrayIndex].status = 'b';
    (*myHashTable) -> hashArray[arrayIndex].key = key;
    (*myHashTable) -> hashArray[arrayIndex].data = data;
}

hashNode searchHash(hashTable *myHashTable, int key) {
    hashNode foundNode;
    int size, myHash, offsetHash, i;

    size = myHashTable -> size;
    myHash = hashFunction(myHashTable, key);
    offsetHash = offsetHashFunction(key);

    i = 0;
    while (myHashTable -> hashArray[(myHash + i * offsetHash) % size].key != key) {
        i++;
    }

    foundNode = myHashTable -> hashArray[(myHash + i * offsetHash) % size];

    return foundNode;
}

void resizeHashTable(hashTable **myHashTable) {
    hashTable *newHashTable;
    int oldSize, newSize, myKey, myData, i;

    oldSize = (*myHashTable) -> size;
    newSize = 2 * oldSize;

    newHashTable = (hashTable *)malloc(sizeof(hashTable));

    newHashTable -> size = newSize;
    newHashTable -> hashArray = (hashNode *)malloc(newSize * sizeof(hashNode));

    for (i = 0; i < newSize; i++) {
        newHashTable -> hashArray[i].status = 'a';
        newHashTable -> hashArray[i].key = 0;
        newHashTable -> hashArray[i].data = 0;
    }

    for (i = 0; i < oldSize; i++) {
        if ((*myHashTable) -> hashArray[i].status == 'b') {
            myKey = (*myHashTable) -> hashArray[i].key;
            myData = (*myHashTable) -> hashArray[i].data;
            insertHash(&newHashTable, myKey, myData);
        }
    }

    free((*myHashTable) -> hashArray);
    free(*myHashTable);

    *myHashTable = newHashTable;
}

void printNode(hashNode myHashNode) {
    printf("key = %d\n", myHashNode.key);
    printf("data = %d\n", myHashNode.data);
    printf("\n");
}

void printHashTable(hashTable *myHashTable) {
    int i;

    printf("myHashTable -> size = %d\n", myHashTable -> size);
    printf("==============================\n");

    for (i = 0; i < myHashTable -> size; i++) {
        if (myHashTable -> hashArray[i].status == 'b') {
            printf("myHashTable -> hashArray[%d]:\n", i);
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
        myHashTable -> hashArray[i].key = 0;
        myHashTable -> hashArray[i].data = 0;
    }

    printHashTable(myHashTable);
    insertHash(&myHashTable, 1100, 5);
    printHashTable(myHashTable);
    insertHash(&myHashTable, 2100, 8);
    printHashTable(myHashTable);

    resizeHashTable(&myHashTable);
    printHashTable(myHashTable);

    testNode = searchHash(myHashTable, 2100);
    printf("found node:\n");
    printNode(testNode);

    return 0;
}
