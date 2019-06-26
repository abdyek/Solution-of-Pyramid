#include<stdio.h>
#include<stdlib.h>

struct node {
    int totalValue;  // sum of node values until self
    int value;
    struct node * left;
    struct node * right;
};

// funcs
int go(struct node *, int);  // travel downwards and diagonally
int isPrime(int);            // control for prime or non prime ?
struct node * getNode(int);  // to create node with give number
int findMax();               // find max sum of the numbers in possible way

// new  SONRA SİLMEYİ UNUTMA
int getNumberOfNodes();  // in the file
void fillNumbersArray();  // fill number array
int getHeightOfPyramid(int);  // for max size of line
void createPyramid();
void createNodes();



// global variables
int * sumList;  // list of numbers
int indexOfList = -1;  // to write in sumList
int len; // length of all possibility;
// ^ len i kaldırabilirim globalden
int numberOfNodes;
int heightOfPyramid;
struct node * head;

// new silmei unutma
char * fileName = "triangle";
int * numbers;

int main(int argc, char *argv[]) {
    
    numberOfNodes = getNumberOfNodes();
    heightOfPyramid = getHeightOfPyramid(numberOfNodes);

    numbers = (int *)malloc(sizeof(int) * numberOfNodes);

    // control for missing number
    if(heightOfPyramid==-1) {
        printf("Missing number in your file!\n");
    } else {
        fillNumbersArray();
        
        /*
        for(int a = 0; a<120; a++) {
            printf("%d\n", numbers[a]);
        }
        */
        createPyramid();
    }

    
    


    int height = 4;
    len = 1;  
    for (int i = 0; i<height - 1; i++) {
        len *= 2;
    }
    sumList = (int *)malloc(sizeof(int) * len);

    /*
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
    */

    //int max = findMax();
    //printf("MAX : %d \n", max);

    //readFile("triangle");

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
        sumList[++indexOfList] = n->totalValue;
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
    int max = sumList[0];
    for(int i = 1; i<len; i++) {
        if(max<sumList[i]) {
            max = sumList[i];
        }
    }
    return max;
}


// new SONRA SİLMEY UNUTMA

int getNumberOfNodes() {
    int lengthOfNumbers = 0;
    FILE * file = NULL;
    file = fopen(fileName, "r");
    if(file!=NULL) {
        char ch = fgetc(file);
        int new = 1;
        while(ch!=EOF) {   // I want to learn number of numbers to use it in number array
            if(ch=='\60' ||
               ch=='\61' ||
               ch=='\62' ||
               ch=='\63' ||
               ch=='\64' ||
               ch=='\65' ||
               ch=='\66' ||
               ch=='\67' ||
               ch=='\70' ||
               ch=='\71') {
                if(new==1) {
                    lengthOfNumbers++;
                    new = 0;
                }
            } else if(ch=='\40' || ch=='\n') {
                new = 1;
            }
            ch = fgetc(file);
        }
        printf("number of numbers in the file : %d \n", lengthOfNumbers);
        fclose(file);
    }
    return lengthOfNumbers;
}

void fillNumbersArray() {   // fill numbers in number array
    FILE * file = NULL;
    file = fopen(fileName, "r");
    if(file!=NULL) {
        char ch = fgetc(file);
        int ind = 0;
        int indexOfNumbers = 0;
        char number[10];
        while(ch!=EOF) {
            if(ch=='\60' ||
               ch=='\61' ||
               ch=='\62' ||
               ch=='\63' ||
               ch=='\64' ||
               ch=='\65' ||
               ch=='\66' ||
               ch=='\67' ||
               ch=='\70' ||
               ch=='\71') {
                number[ind] = ch;
                ind++;
            } else if(ch=='\40' || ch=='\n') {
                if(ind!=0) {  // this control is for multiple space chars
                    numbers[indexOfNumbers] = (int)strtol(number,NULL, 10); 
                    indexOfNumbers++;
                }
                ind = 0;
                for(int i = 0 ; i < 10; i++) {
                    number[i] = '\0';
                }
            }
            ch = fgetc(file);
        }
        fclose(file);
    }
}

int getHeightOfPyramid(int len) {
    /*
     * number of nodes = A
     * height of pyramid = base of pyramid = n
     * n * (n+1) / 2 = A
     * I need A because it is max size of line
     */
    int n = 0;
    while (n<100) {
        if((n * (n+1) / 2) == len) {
            return n;
        }
        n++;
    }
    if(n==100) {
        return -1;
    }
}

void createPyramid() {
    // height of pyramid = base of pyramid
    int topLine[heightOfPyramid];
    int botLine[heightOfPyramid];
    int topStartInd = 0;
    int botStartInd = 0;
    int lenTop = 1;
    int lenBot = 2;
    for(int i = 0; i<heightOfPyramid-1; i++) {
        topStartInd += i;
        botStartInd += i+1;
        // to fill top and bot line
        for(int j = 0; j < lenTop;j++) {
            topLine[j] = numbers[topStartInd + j];
        }
        for(int k = 0; k < lenBot; k++) {
            botLine[k] = numbers[topStartInd + k];
        }
        // to create nodes
        // lenTop is number of pair of connection

        for(int l = 0; l<lenTop; l++) {

        }
        for(int l = 0; l<lenBot; l++) {
            
        }
        
        
        lenTop++;
        lenBot++;

    
        /*
        printf("a - >%d\n",a);
        printf("b - >%d\n", b);
        */
    }
}

