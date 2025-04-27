#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


struct NodeS {      //task1 child
    int value;
    NodeS* next;
};

void insert_node(NodeS ** head, int value) {
    NodeS *element = new NodeS;
    element->value = value;
    element->next = NULL;

    if(*head == NULL) {

        *head = element;
        return;
    }

    NodeS* finder = *head;

    if (value <= finder->value) {
        element->next = *head;
        *head = element;
        return;
    }
    while(finder->next != NULL &&  finder->next->value < value) {
        finder = finder->next;
    }
    element->next = finder->next;
    finder->next = element;
}

void delete_node(NodeS** head, int value) {
    if(*head == NULL) {
        return;
    }

    NodeS * finder = *head;

    if(finder->value == value)  {
        *head = finder->next;
        delete finder;
        return;
    }

    while(finder->next != NULL) {
        if(value == finder->next->value)
        {
            NodeS * temp = finder->next;
            finder->next = temp->next;
            delete temp;
            return;
        }
        else {
            finder = finder->next;
        }
    }
}



struct Node         //task2 Node
{
    Node * parent = NULL;
    int value;
    Node * LC = NULL;
    Node * RS = NULL;
};

void insert(Node * head, int *arr, int size)
{
    Node * element0 = new Node;
    element0->value = arr[0];

    if(head->LC == NULL)    //root가 존재하지 않을 때
    {
        element0->parent = head;
        head->LC = element0;

        Node * element1 = new Node;         //LC 추가
        element1->value = arr[1];
        element1->parent = element0;
        element0->LC = element1;

        Node * temp = element1;
        for(int i = 2 ; i < size ; i++)     //RS 추가
        {
            Node *element = new Node;
            element->value = arr[i];
            element->parent = element0;
            temp->RS = element;
            temp = element;
        }
        return;
    }

    for(int i = 1 ; i < size ; i++)
    {
        if(head->LC->value == arr[i])    //root가 바뀌어야 할 때
        {    
            element0->LC = head->LC;     //root 교체
            head->LC->parent =element0;
            head->LC = element0;
            element0->parent = head;
              

            Node * temp = element0->LC;
            for(int j = 1; j < size ; j++)      //RS 추가
            {
                if(element0->LC->value != arr[j]) {         //원래의 root가 아닐 시에 추가
                    Node *element = new Node;
                    element->value = arr[j];
                    element->parent = element0;
                    temp->RS = element;
                    temp = element;
                }
            }
            return;
        }
    }

    delete element0;
                                                //일반적일 때
    Node * finder = head->LC;
    while(finder->value != -1)
    {
    
        if(finder->value == arr[0]) {
            break;
        }
        
        if(finder->LC != NULL) {
            finder = finder->LC;
        }

        else if(finder->RS != NULL) {
            finder = finder->RS;
        }

        else {
            while(finder->RS == NULL && finder->value != -1)
            {
                finder = finder->parent;
            }
            if(finder->value != -1)
            {
                finder = finder->RS;
            }        
        }
    }
    if(finder->LC == NULL)                  //leaf node에 추가
    {
        Node * element1 = new Node;         //LC 추가
        element1->value = arr[1];
        element1->parent = finder;
        finder->LC = element1;

        Node * temp = element1;
        for(int i = 2 ; i < size ; i++)     //RS 추가
            {
                Node *element = new Node;
                element->value = arr[i];
                element->parent = finder;
                temp->RS = element;
                temp = element;
            }
    }
    else                                   //non terminal node에 추가
    {
        Node * temp = finder->LC;
        while(temp->RS != NULL) {
            temp = temp->RS;
        }

        for(int i = 1 ; i < size ; i++)     //RS 추가
            {
                Node *element = new Node;
                element->value = arr[i];
                element->parent = finder;
                temp->RS = element;
                temp = element;
            }

    }
    return;
}

void split(string &str, int* arr, int& size) 
{
    int i = 0;
    int j = 0;
    while(i < str.length())
    {
        if(str[i] == ' ') {
            i++;
            continue;
        }

        else if((str[i] >= 48) && (str[i] <= 57)) {
            int num = 0;
            while(i < str.length() && (str[i] >= 48) && (str[i] <= 57))
            {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            if(num >= 1000) //1000이상일 떼
            {
                size = -1;
                return;
            }
            arr[j] = num;
            j++;
            size++;
        }        
        else {}//오류
    }
    return;
}



struct Nodestr      //task3 Node
{
    string str;
    Nodestr * parent = NULL;
    Nodestr * LC = NULL;
    Nodestr * RS = NULL;
};

void insertstr(Nodestr * head, string con, string T, string F)
{
    if(T.find('?') != string::npos) {
        T = T.substr(0, T.find('?')-1);
    }

    if(F.find('?') != string::npos) {
        F = F.substr(0, F.find('?')-1);
    }
    Nodestr * element0 = new Nodestr;
    element0->str = con;

    if(head->LC == NULL)    //root가 존재하지 않을 때
    {
        head->LC = element0;
        element0->parent = head;

        Nodestr * element1 = new Nodestr;         //LC 추가(true)
        element1->str = T;
        element1->parent = element0;
        element0->LC = element1;

        Nodestr * element2 = new Nodestr;        //RS 추가(false)
        element2->str = F;
        element2->parent = element0;
        element1->RS = element2; 
        return;
    }
    Nodestr * finder = head->LC;
    while(!(finder->str.empty()))
    {
    
        if(finder->str == con) {
            break;
        }
        

        if(finder->LC != NULL) {
            finder = finder->LC;
        }

        else if(finder->RS != NULL) {
            finder = finder->RS;
        }

        else {
            while(finder->RS == NULL && !(finder->str.empty()))
            {
                finder = finder->parent;
            }
            if(!(finder->str.empty()))
            {
                finder = finder->RS;
            }        
        }
    }
    
    Nodestr * element1 = new Nodestr;         //LC 추가
    element1->str = T;
    element1->parent = finder;
    finder->LC = element1;

    Nodestr * element2 = new Nodestr;         //RS 추가
    element2->str = F;
    element2->parent = finder;
    element1->RS = element2;
    return;
}