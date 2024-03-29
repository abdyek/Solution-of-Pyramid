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
int isPrime(int);            // control for prime or non prime
struct node * getNode(int);  // to create node with give number
int findMax();               // find max sum of the numbers in possible way
int getNumberOfNodes();  // in the file
void fillNumbersArray();  // fill number array
int getHeightOfPyramid(int);  // for max size of line
void createPyramid();
void createNodes();

// global variables
int * sumList;  // list of numbers
int indexOfList = -1;  // to write in sumList
int len; // length of all possibility without rules
int numberOfNodes;
int heightOfPyramid;
struct node * head;
char * fileName = "triangle";
int * numbers;      // to keep numbers before creating node

int main(int argc, char *argv[]) {
    
    numberOfNodes = getNumberOfNodes();
    heightOfPyramid = getHeightOfPyramid(numberOfNodes);

    numbers = (int *)malloc(sizeof(int) * numberOfNodes);

    len = 1;               
    for (int i = 0; i<heightOfPyramid - 1; i++) {  // 2 ^ ( height of pyramid -1 ) = length of all possibility without rules
        len *= 2;
    }
    sumList = (int *)malloc(sizeof(int) * len);

    // control for missing number
    if(heightOfPyramid==-1) {
        printf("!! Missing number in your file!\n");
    } else {
        fillNumbersArray();
        
        createPyramid();
        printf("%d\n", head->left->left->left->value);
        go(head,0);
        int max = findMax();
        printf("Maximum sum of the numbers : %d\n", max);
    }

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
    new->left = NULL;
    new->right = NULL;
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

int getNumberOfNodes() {   // in the file , not create nodes in the function
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

void fillNumbersArray() {   // fill numbers array with numbers
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
    struct node * topLine[heightOfPyramid];
    struct node * botLine[heightOfPyramid];
    int topStartInd = 0;
    int botStartInd = 1;
    int lenTop = 1;
    int lenBot = 2;
    head = getNode(numbers[0]);
    topLine[0] = head;
    for(int i = 1; i<heightOfPyramid; i++) {

        // to create nodes in botLine
        for(int k = 0; k < lenBot; k++) {
            botLine[k] = getNode(numbers[botStartInd + k]);
        }

        // lenTop = pair of connection
        for(int l = 0; l<lenTop; l++) {
            topLine[l]->left = botLine[l];
            topLine[l]->right = botLine[l+1];
        }
        
        // I have to copy botLine in topLine
        for(int i = 0 ; i<lenBot; i++) {
            topLine[i] = botLine[i];
        }
        
        topStartInd += i;
        botStartInd += i+1;
        lenTop++;
        lenBot++;

    }
}

