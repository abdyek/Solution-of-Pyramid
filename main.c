#include<stdio.h>
#include<stdlib.h>

struct node {
    int totalValue;  // sum of node values until self
    int value;
    struct node * left;
    struct node * right;
};

// funcs
int go(struct node *, int);
int isPrime(int);
struct node * getNode(int);
int findMax();

// global variables
int * list;  // list of numbers
int indexOfList = -1;  // to write in list
int len; // length of all possibility;

int main() {

    int height = 4;
    len = 1;  
    for (int i = 0; i<height - 1; i++) {
        len *= 2;
    }
    //printf("LEN : %d\n", len);
    list = (int *)malloc(sizeof(int) * len);

    // example triangle, not dynamic now
    struct node * n1 = getNode(6);
    struct node * n2 = getNode(4);
    struct node * n3 = getNode(2);
    struct node * n4 = getNode(12);
    struct node * n5 = getNode(1);
    struct node * n6 = getNode(3);
    struct node * n7 = getNode(0);
    struct node * n8 = getNode(9);
    struct node * n9 = getNode(7);
    struct node * n10 = getNode(15);

    // connection of nodes
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->left = n5;
    n3->right = n6;
    n4->left = n7;
    n4->right = n8;
    n5->left = n8;
    n5->right = n9;
    n6->left = n9;
    n6->right = n10;
    n7->left = NULL;
    n7->right = NULL;
    n8->left =NULL;
    n8->right =NULL;
    n9->left =NULL;
    n9->right = NULL;
    n10->left =NULL;
    n10->right = NULL;

    go(n1, 0);  // first node

    int max = findMax();
    printf("MAX : %d \n", max);

    return 0;
}

int isPrime(int number) {
    if(number<2) {
        return 0;
    }
    for (int i = 2; i<number; i++) {
        if(number % i ==0) {
            return 0;
        }
    }
    return 1;
}

int go(struct node * n, int topValue) {
    int data = n->value;
    n->totalValue = topValue + data;
    struct node * l = n->left;
    struct node * r = n->right;
    if(!l && !r) {
        list[++indexOfList] = n->totalValue;
        return 0;
    }
    if(!isPrime(l->value)) {
        go(l, n->totalValue);
    }
    if(!isPrime(r->value)) {
        go(r,n->totalValue);
    }
}

struct node * getNode(int value) {
    struct node * new = (struct node *)malloc(sizeof(struct node));
    new->value = value;
    return new;
}

int findMax() {
    int max = list[0];
    for(int i = 1; i<len; i++) {
        if(max<list[i]) {
            max = list[i];
        }
    }
    return max;
}
