#include <iostream>
using namespace std;

#ifndef Queue_LLImplementation_h
#define Queue_LLImplementation_h


class Node{
    public:
        int data;
        Node *next;

        Node(int);
        Node();
};

Node :: Node(int x){
    data = x;
    next = NULL;
}

Node :: Node(){
    data = -1;
    next = NULL;
}


class Queue{
    Node *front, *rear;

    public:
        Queue();

        void Enqueue(int);
        int Dequeue();
        void Display();

        bool isEmpty();
};

Queue :: Queue(){
    front = NULL;
    rear = NULL;
}

void Queue :: Enqueue(int x) {
    Node *t = new Node(x); 
    if (t == NULL){				
        cout << "\nOVERFLOW!\n"; 
    }else{
        if (front == NULL){
            front = rear = t; 
        }else{
            rear->next = t; 
            rear = t;	
        }			
    }
}

int Queue :: Dequeue() {					
    int x = -1;
    Node *p;
    if (isEmpty()){
        cout << "\nEMPTY!\n"; 
    }else{
        p = front;				
        front = front->next; 
        x = p->data;
        delete p;				
    }	
    return x;		
}
					
void Queue :: Display() {					
    struct Node *p = front;
    cout << "\nQ : "; 
    while(p){					
        cout << " " << p->data ;					
        p = p->next; 
    }
    cout << endl; 
}

bool Queue :: isEmpty(){
    return (front == NULL);
}


#endif 