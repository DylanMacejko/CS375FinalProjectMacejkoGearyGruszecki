#ifndef FIBHEAP_H
#define FIBHEAP_H

struct node{
    int n;
    int degree;
    node* parent;
    node* child;
    node* left;
    node* right;
    char mark;
    char C;
};

class FibonacciHeap{
    node* initializaHeap(){
        node* n;
        n = NULL;
        return n;
    }
}

#endif