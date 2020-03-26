#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTree {
    int key;
    struct binaryTree *childLeft;
    struct binaryTree *childRight;
} binaryTree;

int max(int valA, int valB) {
    if (valA > valB) {
        return valA;
    } else {
        return valB;
    }
}

int getHeight(binaryTree *curNode) {
    if (curNode == NULL) {
        return -1;
    }

    return 1 + max(getHeight(curNode -> childLeft), getHeight(curNode -> childRight));
}

binaryTree *createNode(int key) {
    binaryTree *newNode;

    newNode = (binaryTree *)malloc(sizeof(binaryTree));
    newNode -> key = key;
    newNode -> childLeft = NULL;
    newNode -> childRight = NULL;

    return newNode;
}

void insertNode(binaryTree **root, int key) {
    binaryTree *curNode, *prevNode, *newNode;
    binaryTree **nodePath;
    int pathSize, i;

    curNode = *root;

    nodePath = (binaryTree **)malloc(sizeof(binaryTree *));
    pathSize = 0;

    while (curNode != NULL) {
        if (curNode -> key > key) {
            prevNode = curNode;
            curNode = curNode -> childLeft;
        } else if (curNode -> key < key) {
            prevNode = curNode;
            curNode = curNode -> childRight;
        } else {
            free(nodePath);
            return;
        }

        pathSize++;
        if (pathSize == 1) {
            nodePath[0] = *root;
        } else {
            nodePath = (binaryTree **)realloc(nodePath, pathSize * sizeof(binaryTree *));
            nodePath[pathSize - 1] = prevNode;
        }
    }

    newNode = createNode(key);

    pathSize++;
    nodePath = (binaryTree **)realloc(nodePath, pathSize * sizeof(binaryTree *));
    nodePath[pathSize - 1] = newNode;

    if (curNode == *root) {
        *root = newNode;
    } else {
        if (prevNode -> key > key) {
            prevNode -> childLeft = newNode;
        } else {
            prevNode -> childRight = newNode;
        }
    }

    /*
    for (i = 0; i <= pathSize - 1; i++) {
        printf("nodePath[%d]:\n", i);
        printNode(nodePath[i]);
    }
    */

    balanceTree(root, nodePath, pathSize);

    free(nodePath);
}

binaryTree *searchNode(binaryTree *curNode, int key) {
    if (curNode == NULL || curNode -> key == key) {
        return curNode;
    }

    if (curNode -> key > key) {
        searchNode(curNode -> childLeft, key);
    } else {
        searchNode(curNode -> childRight, key);
    }
}

void LL_Rotation(binaryTree **root, binaryTree **origin, binaryTree **a, binaryTree **b, binaryTree **c) {
    if (*a == *root) {
        *root = *b;
    } else {
        if (((*origin) -> childLeft) == *a) {
            (*origin) -> childLeft = *b;
        } else {
            (*origin) -> childRight = *b;
        }
    }

    (*a) -> childLeft = (*b) -> childRight;

    (*b) -> childLeft = *c;
    (*b) -> childRight = *a;
}

void RR_Rotation(binaryTree **root, binaryTree **origin, binaryTree **a, binaryTree **b, binaryTree **c) {
    if (*a == *root) {
        *root = *b;
    } else {
        if (((*origin) -> childLeft) == *a) {
            (*origin) -> childLeft = *b;
        } else {
            (*origin) -> childRight = *b;
        }
    }

    (*a) -> childRight = (*b) -> childLeft;

    (*b) -> childLeft = *a;
    (*b) -> childRight = *c;
}

void LR_Rotation(binaryTree **root, binaryTree **origin, binaryTree **a, binaryTree **b, binaryTree **c) {
    if (*a == *root) {
        *root = *c;
    } else {
        if (((*origin) -> childLeft) == *a) {
            (*origin) -> childLeft = *c;
        } else {
            (*origin) -> childRight = *c;
        }
    }

    (*a) -> childLeft = (*c) -> childRight;
    (*b) -> childRight = (*c) -> childLeft;

    (*c) -> childLeft = *b;
    (*c) -> childRight = *a;
}

void RL_Rotation(binaryTree **root, binaryTree **origin, binaryTree **a, binaryTree **b, binaryTree **c) {
    if (*a == *root) {
        *root = *c;
    } else {
        if (((*origin) -> childLeft) == *a) {
            (*origin) -> childLeft = *c;
        } else {
            (*origin) -> childRight = *c;
        }
    }

    (*a) -> childRight = (*c) -> childLeft;
    (*b) -> childLeft = (*c) -> childRight;

    (*c) -> childLeft = *a;
    (*c) -> childRight = *b;
}

int getBalance(binaryTree *curNode) {
    int balance;

    balance = getHeight(curNode -> childLeft) - getHeight(curNode -> childRight);

    return balance;
}

void balanceTree(binaryTree **root, binaryTree *nodePath[], int pathSize) {
    int i, balance;
    binaryTree *a, *b, *c, *origin;

    for (i = pathSize - 3; i >= 0; i--) {
        balance = getBalance(nodePath[i]);

        if (balance > 1 || balance < 1) {
            a = nodePath[i];
            b = nodePath[i + 1];
            c = nodePath[i + 2];

            if (a != *root) {
                origin = nodePath[i - 1];
            }

            if (balance > 1 && b -> childLeft == c) {
                printf("LL rotation\n\n");
                LL_Rotation(root, &origin, &a, &b, &c);
                return;
            }

            if (balance > 1 && b -> childRight == c) {
                printf("LR rotation\n\n");
                LR_Rotation(root, &origin, &a, &b, &c);
                return;
            }

            if (balance < -1 && b -> childRight == c) {
                printf("RR rotation\n\n");
                RR_Rotation(root, &origin, &a, &b, &c);
                return;
            }

            if (balance < -1 && b -> childLeft == c) {
                printf("RL rotation\n\n");
                RL_Rotation(root, &origin, &a, &b, &c);
                return;
            }
        }
    }
}

void printNode(binaryTree *curNode) {
    printf("NODE:\n");
    printf("================\n");

    printf("key: %d\n", curNode -> key);

    if (curNode -> childLeft != NULL) {
        printf("childLeft: %d\n", curNode -> childLeft -> key);
    } else {
        printf("childLeft: NULL\n");
    }

    if (curNode -> childRight != NULL) {
        printf("childRight: %d\n", curNode -> childRight -> key);
    } else {
        printf("childRight: NULL\n");
    }

    printf("\n");
}

void printTree(binaryTree *curNode) {
    if (curNode != NULL) {
        printNode(curNode);
        printTree(curNode -> childLeft);
        printTree(curNode -> childRight);
    }
}

int main() {
    binaryTree *root, *testNode;
    int testKey;

    root = NULL;

    printf("first insert\n\n");
    insertNode(&root, 10);
    printTree(root);

    printf("second insert\n\n");
    insertNode(&root, 20);
    printTree(root);

    printf("third insert\n\n");
    insertNode(&root, 15);
    printTree(root);

    printf("fourth insert\n\n");
    insertNode(&root, 30);
    printTree(root);

    printf("fifth insert\n\n");
    insertNode(&root, 25);
    printTree(root);

    /*
    testKey = 4;
    testNode = searchNode(root, testKey);

    if (testNode != NULL) {
        printf("Node with key %d succesfully found:\n\n", testKey);
        printNode(testNode);
    }
    */

    return 0;
}
