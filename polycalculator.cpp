#include "polycalculator.h"
#include <regex>

// counter to check which polynomial to cater
int c = 0;

// validating input
bool PolyCalculator:: input_validator(string str){
    return regex_match(str,regex("([+-]{1}[0-9]*x?(\\^[0-9]+)?)+"));
}

// parsing the string, extracting terms, sorting and putting into linked list
void PolyCalculator:: parse(string str,LinkedList& list){

    if (str[0]!='-'&&str[0]!='+'){
        str = "+"+str;
    }

    // proceed if input valid
    if (!input_validator(str)){
        if (c==0){
            cout<<"Please enter the first polynomial correctly"<<endl;
            c++;
        }

        else{
            cout<<"Please enter the second polynomial correctly"<<endl;
        }
        
        return;
    }

    int N=str.length();
    int i =0;

    //cout<<str<<endl;
    while (i<N){
        string coef="";
        int expo;
        if (str[i]=='+'||str[i]=='-'||i==0){
            if ((str[i]=='x'||str[i]=='X') && coef==""){
                coef="1";
            }
            
            while (isdigit(str[i])||str[i]=='+'||str[i]=='-'){
                coef=coef+str[i];
                // cout<<"hrllo +"<<endl;
                if (i<N-1){
                    i++;
                    //cout<<i<<endl;
                }
                else{
                    break;
                }
                
                if (str[i]=='+'||str[i]=='-'){
                    break;
                }
            }
            
            //cout<<coef<<endl;

            if(str[i]=='X' || str[i]=='x'){
                if (str[i+1]!='^'){
                    expo=1;
                }
                else{
                    string temp_expo;
                    while (isdigit(str[i+2])){
                        temp_expo+=str[i+2];
                        i++;
                    }
                    expo=stoi(temp_expo);
                    
                }
                
            }
            else{
                expo=0;
            }

            if (coef=="+"){
                coef="+1";
            }
            
            int coef2=stoi(coef);
            //cout<<coef2<<','<<expo<<endl;
            if (c==0){
                list1.insert(coef2,expo);
                //cout<<"Inserted: "<<coef2<<expo<<endl;
            }
            else if (c==1){
                list2.insert(coef2,expo);
            }
            
            
            
        }
        if (str[i]!='+'&&str[i]!='-')
            i++;
        //cout<<i<<endl;
        //cout<<"N="<<N<<endl;

    }
    c++;


}

//getting input from user and passing to parse
void PolyCalculator:: input(){
    //cleaning list 1 and 2 to input in it
    list1.removeAll();
    list2.removeAll();
    c=0;
    string exp1;
    string exp2;
    cout<<"Enter first Polynomial Expression: ";
    getline(cin,exp1);

    cout<<"Enter second Polynomial Expression: ";
    getline(cin,exp2);

    parse(exp1,list1);
    parse(exp2,list2);

}

// cleaning list 3 before add, sub and mul to make space for the operations

//adding the polynomials together and inserting into list 3
void PolyCalculator:: add(){
    list3.removeAll();
    Node* temp = list1.head;
    Node* temp2 = list2.head;

    while (temp!=NULL || temp2!=NULL){
        if (temp2==NULL){
            list3.insert(temp->coef,temp->expo);
            temp=temp->next;
        }
        
        else if (temp==NULL){
            list3.insert(temp2->coef,temp2->expo);
            temp2=temp2->next;
        }

        else{
            if (temp->expo>temp2->expo){
                list3.insert(temp->coef,temp->expo);
                temp=temp->next;            
            }
            else if (temp->expo==temp2->expo){
                list3.insert(temp->coef+temp2->coef,temp->expo);
                temp=temp->next;
                temp2=temp2->next;
            }

            else if (temp->expo<temp2->expo){
                list3.insert(temp2->coef,temp2->expo);
                temp2=temp2->next;
            }

        }

        
    }

    cout<<"Exp1 + Exp2 = ";
    list3.display();
}

//subtracting polynomials and putting into list 3
void PolyCalculator:: sub(){
    list3.removeAll();
    Node* temp = list1.head;
    Node* temp2 = list2.head;

    while (temp!=NULL || temp2!=NULL){
        if (temp2==NULL){
            list3.insert(temp->coef,temp->expo);
            temp=temp->next;
        }
        
        else if (temp==NULL){
            list3.insert(-temp2->coef,temp2->expo);
            temp2=temp2->next;
        }

        else{
            if (temp->expo>temp2->expo){
                list3.insert(temp->coef,temp->expo);
                temp=temp->next;            
            }
            else if (temp->expo==temp2->expo){
                list3.insert(temp->coef-temp2->coef,temp->expo);
                temp=temp->next;
                temp2=temp2->next;
            }

            else if (temp->expo<temp2->expo){
                list3.insert(-temp2->coef,temp2->expo);
                temp2=temp2->next;
            }

        }

        
    }

    cout<<"Exp1 - Exp2 = ";
    list3.display();
}

//multiplying polynomials and putting into list 3
void PolyCalculator:: mul(){
    list3.removeAll();
    Node* temp = list1.head;
    Node* temp2 = list2.head;

    while (temp!=NULL){   
        while (temp2!=NULL){
            int new_coef=temp->coef*temp2->coef;
            int new_expo=temp->expo+temp2->expo;
            list3.insert(new_coef,new_expo);
            //cout<<"inserted";
            temp2=temp2->next;
        }
        temp=temp->next;
        temp2=list2.head;
    }

    cout<<"Exp1 * Exp2 = ";
    list3.display();
}

//reading data from file and inputting into list1 and 2
void PolyCalculator:: readData(string str){
    list1.removeAll();
    list2.removeAll();
    ifstream myFile(str);
    string myText;
    string exp1;
    string exp2;
    int cnt =0;
    while (getline(myFile,myText)){
        if (cnt==0){
            exp1=myText;
        }
        else{
            exp2=myText;
        }
        cnt++;
    }
    parse(exp1,list1);
    parse(exp2,list2);


}

//writing both the polynomials and all operation results into given file
void PolyCalculator:: writeData(string str){
    ofstream myFile(str);
    myFile <<"Exp1 = "<< list1.display_helper()<<endl;
    myFile <<"Exp2 = "<< list2.display_helper()<<endl;
    add();
    myFile <<"Exp1 + Exp2 = "<< list3.display_helper()<<endl;
    sub();
    myFile <<"Exp1 - Exp2 = "<< list3.display_helper()<<endl;
    mul();
    myFile <<"Exp1 * Exp2 = "<< list3.display_helper()<<endl;

    myFile.close();

}

//displaying the polynomials calling linked list display method
void PolyCalculator:: display(){
    cout<<"Exp1: ";
    list1.display();
    cout<<"Exp2: ";
    list2.display();
}