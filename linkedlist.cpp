#include "linkedlist.h"
#include <iostream>
using namespace std;

//constructor
LinkedList::LinkedList() {
    this->head=NULL;
}

//destructor
LinkedList::~LinkedList(){
    removeAll();
}

// using insertion sort to ensure the elements are inserted into the linked list in the correct order
void LinkedList::insert(int coef, int expo){
    //cout<<coef<<','<<expo<<endl;

    if (head==NULL){
        Node* n = new Node(coef,expo);
        n -> next = head;
        head=n;
    }

    else{
        Node *temp=head;

        while (temp!=NULL){
            if (expo>head->expo){
                Node *front = new Node(coef,expo);
                front -> next =head;
                head=front;
                break;
            }
            //ensuring like terms get added
            else if (expo==head->expo){
                head->coef=head->coef+coef;
                break;
            }
            else{
                if (temp->next==NULL){
                    //cout<<coef<<','<<expo<<endl;
                    Node* n = new Node(coef,expo);
                    temp->next=n;
                    break;
                }

                else{
                    if (expo>temp->next->expo){
                        Node *temp2 = temp->next;
                        Node* middle = new Node(coef,expo);
                        temp->next=middle;
                        middle->next=temp2;
                        break;
                    }
                    else if (expo==temp->next->expo){
                        temp->next->coef=temp->next->coef+coef;
                        break;
                    }
                    else{
                        temp=temp->next;
                    }
                    }

                
            }
        }
        
    }

}

void LinkedList::display() const{
    Node* temp = head;
    while (temp!=NULL){
        if (temp->coef>=0){
            cout<<"+";
        }

        if (temp->expo==0){
            cout<<temp->coef<<" ";     
        }
        
        else if (temp->expo==1){
            cout<<temp->coef<<"x"<<" ";
        }

        else{
            cout<<temp->coef<<"x^"<<temp->expo<<" ";
        }
        
        temp=temp->next;
    }
    cout<<endl;
}


//display helper to help writing on to the file
string LinkedList::display_helper(){
    string str;
    Node* temp = head;
    while (temp!=NULL){
        if (temp->coef>=0){
            str+="+";
        }

        if (temp->expo==0){
            str=str+to_string(temp->coef)+" ";   
        }
        
        else if (temp->expo==1){
            str=str+to_string(temp->coef)+"x ";
        }

        else{
            str=str+to_string(temp->coef)+"x^"+to_string(temp->expo)+" ";
        }
        
        temp=temp->next;
    }
    return str;

}


//cleaning the linked list to put new things in it
void LinkedList::removeAll(){
    while (head!=NULL){
        Node* tmp;
		tmp = head->next;
		delete head;
		head=tmp;
    }
}

