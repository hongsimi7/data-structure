#include <sstream>
#include <iostream>
#include <string>
using namespace std;

struct Node {      
    int value;
    bool empty = true;
    string command;
    Node* next;
    Node* pre;
};

long long square(int n)
{
    long long a = n;
    return a * a;
}

string make_binary(long long num, int key_size)
{
    string binary = "";

    for(int i = 0; i < 2 * key_size ; i++)          // 2 * n bit로 만들기
    {
        binary = to_string((num % 2))  + binary;
        num = num / 2;
    }

    return binary;
}

int MSH(Node * element, int key_size, int idx_size)     //hash function
{
    long long num = square(element->value);

    string binary = make_binary(num, key_size);

    int mid = (2 * key_size - idx_size) / 2;
    string mid_bit = binary.substr(mid , idx_size);
    int dicimal = stoi(mid_bit, nullptr, 2);
    return dicimal;
}

int collision(int i)
{
    return i*i + i + 1;
}

void insert_HT(Node HT[], int key_size, int idx_size, int table_size, Node * element)
{
    int hash_value = MSH(element, key_size, idx_size);

    if(HT[hash_value % table_size].empty)
    {
        HT[hash_value % table_size].value = element->value;
        HT[hash_value % table_size].empty = false;
        return;
    }

    int i = 1;
    while(true)
    {
        if(HT[(hash_value + collision(i)) % table_size].empty)
        {
            HT[(hash_value + collision(i)) % table_size].value = element->value;
            HT[(hash_value + collision(i)) % table_size].empty = false;
            return;
        }
        i++;
    }
}

bool delete_HT(Node HT[], int key_size, int idx_size, int table_size, Node * element)
{
    int hash_value = MSH(element, key_size, idx_size);

    if(!(HT[hash_value % table_size].empty) && HT[hash_value % table_size].value == element->value)
    {
        HT[hash_value % table_size].value = -1;
        HT[hash_value % table_size].empty = true;
        return true;
    }
    
    int i = 1;
    while(true)
    {
        if(!(HT[(hash_value + collision(i)) % table_size].empty) && HT[(hash_value + collision(i)) % table_size].value == element->value)
        {
            HT[(hash_value + collision(i)) % table_size].value = -1;
            HT[(hash_value + collision(i)) % table_size].empty = true;
            return true;
        }

        i++;

        if(i >= table_size)
        {
            return false;
        }
    }
}

void print_HT(Node HT[], int table_size)
{
    for(int i = 0; i < table_size; i++)
    {
        if(HT[i].empty)
        {
            cout << i << ": empty" << endl;  
        }
        else
        {
            cout << i << ": " << HT[i].value << endl;
        }
        
    }
}

void insert_node(Node** head, int value, string command) {
    Node* element = new Node;
    element->value = value;
    element->command = command;
    element->next = NULL;
    element->pre = NULL;

    if (*head == NULL) {
        *head = element;
        return;
    }

    Node* finder = *head;

    while(finder->next != NULL)
    {
        finder= finder->next;
    }
    finder->next = element;
    element->pre = finder;
}

void split(string arg, int &key_size, int &idx_size, int& arg_size, Node ** head) {
    int i = 0;
    int count = 0;
    
    while(arg[i] != ']') {
        int left = arg.find('(' , i);
        int right = arg.find(')', i);
        string str = arg.substr(left + 1, right - left - 1);
        string command = str.substr(1, str.find(',') - 2);
    
        int element = stoi(str.substr(str.find(',') + 1));
        if(command == "n") {
            key_size = element;
        }
        else if(command == "r") {
            idx_size = element;
        }
        else {                      //insert or delete일 때
            insert_node(head, element, command);
            arg_size++;
        }
        i = right + 1;
    }
}



int main(int argc, char* argv[]) {
    if(argc == 1) {                             //인자가 들어오지 않았을 때
        return 1;
    }

    string arg = "";
    int key_size = 0;
    int idx_size = 0;
    int element_num = 0;
    int arg_size = 0;
    Node* head_node = NULL;
    Node ** head = &head_node;

    for (int i = 0; i < argc; ++i) {
         arg += string(argv[i]);                //string 변환
    }
    
    split(arg, key_size, idx_size, arg_size, head);
    int table_size = 1;
    for(int i = 0 ; i < idx_size; i++)
    {
        table_size = table_size * 2;
    }

    Node * HT = new Node[table_size];

    for(int i = 0 ; i < arg_size ; i++)
    {
        Node * finder = *head;
        for(int j = 0 ; j < i ; j++)
        {
            finder = finder->next;
        }

        if(finder->command == "insert")     //삽입
        {
            element_num++;
            if(element_num > table_size)
            {
                cout << "FULL" << endl;
                return 0;
            }
            insert_HT(HT,key_size, idx_size, table_size, finder);
        }
        else                                //삭제
        {
            bool chk = delete_HT(HT,key_size, idx_size, table_size, finder);
            if(!chk)
            {
                cout << "ERROR" << endl;
                return 0;
            }
            element_num--;
        }
    }

    print_HT(HT, table_size);
    return 0;
}