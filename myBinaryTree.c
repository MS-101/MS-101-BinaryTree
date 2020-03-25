#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTree {
    int key;
    struct binaryTree *childLeft;
    struct binaryTree *childRight;
} binaryTree;

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

    curNode = *root;

    while (curNode != NULL) {
        if (curNode -> key > key) {
            prevNode = curNode;
            curNode = curNode -> childLeft;
        } else if (curNode -> key < key) {
            prevNode = curNode;
            curNode = curNode -> childRight;
        } else {
            return;
        }
    }

    newNode = createNode(key);

    if (curNode == *root) {
        *root = newNode;
    } else {
        if (prevNode -> key > key) {
            prevNode -> childLeft = newNode;
        } else {
            prevNode -> childRight = newNode;
        }
    }
}

binaryTree *searchNode(binaryTree *curNode, int key) {
    if (curNode -> key == key || curNode == NULL) {
        return curNode;
    }

    if (curNode -> key > key) {
        searchNode(curNode -> childLeft, key);
    } else {
        searchNode(curNode -> childRight, key);
    }
}

void balanceTree() {

}

void preorder(binaryTree *curNode) {
    printf("%d ", curNode -> key);

    if (curNode -> childLeft != NULL) {
        preorder(curNode -> childLeft);
    }

    if (curNode -> childRight != NULL) {
        preorder(curNode -> childRight);
    }
}

int main() {
    binaryTree *root, *test;

    root = NULL;

    insertNode(&root, 5);
    insertNode(&root, 2);
    insertNode(&root, 10);
    insertNode(&root, 4);

    preorder(root);
    printf("\n");

    test = searchNode(root, 6);

    if (test != NULL) {
        printf("test -> key: %d\n", test -> key);
    }

    return 0;
}
