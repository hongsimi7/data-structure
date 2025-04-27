#include "ds.h"

void split(string arg, int &bubble_num, int &element_num, Node ** head) {
    int i = 0;
    int count = 0;
    
    while(arg[i] != ']') {
        int left = arg.find('(' , i);
        int right = arg.find(')', i);
        string str = arg.substr(left + 1, right - left - 1);
        string command = str.substr(1, str.find(',') - 2);
        int element = stoi(str.substr(str.find(',') + 1));
        if(command == "Bubble") {
            bubble_num = element;
        }
        else {                      //insert일 때
            insert_node(head, element);
            element_num++;
        }
        i = right + 1;
    }
}

void bubble_sort(Node ** head, int& sort_num, const int element_num) { 
    Node * finder = *head;

    for(int i = 0; i < element_num - 1; i++) {     //맨 뒤로 가기
        finder = finder->next;
    }

    for(int i = 0; i < sort_num - 1; i++) {
        if(finder->value < finder->pre->value) {              //변경
            int temp = finder->pre->value;
            finder->pre->value = finder->value;
            finder->value = temp;
        }
        finder = finder->pre;
    }
    sort_num--;
}

void selection_sort(Node ** head, int& sort_num, const int element_num) {
    Node * finder = *head;
    for(int i = 0; i < element_num - sort_num; i++) {     //정렬된 부분 제외하기
        finder = finder->next;
    }

    Node * min = finder;
    Node * finder2 = finder;

    for(int i = 0; i < sort_num -1; i++) {
        finder2 = finder2->next;
        if(finder2->value < min->value) {
            min = finder2;
        }
    }

    int temp = min->value;
    min->value = finder->value;
    finder->value = temp;
    sort_num--;
}

void print_element(Node ** head) {
    Node * finder = *head;
    while(finder != NULL) 
    {
        cout << finder->value << " ";
        finder = finder->next;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if(argc == 1) {                             //인자가 들어오지 않았을 때
        return 1;
    }

    string arg = "";
    int bubble_num = 0;
    int element_num = 0;
    Node* head_node = NULL;
    Node ** head = &head_node;

    for (int i = 0; i < argc; ++i) {
         arg += string(argv[i]);                //string 변환
    }
    
    split(arg, bubble_num, element_num, head);
    int sort_num = element_num;
    print_element(head);

    if(bubble_num >= element_num) {             //bubble sort만 진행할 때

        for(int i = 0; i < element_num - 1 ; i++)  
        {
            bubble_sort(head, sort_num, element_num);
            print_element(head);
        }
    }
    else {                                      //bubble sort 및 selection sort 모두 진행될 때
        for(int i = 0; i < bubble_num ; i++)
        {
            bubble_sort(head, sort_num, element_num);
            print_element(head);
        }
        for(int i = 0; i < element_num - bubble_num - 1; i++)
        {
            selection_sort(head, sort_num, element_num);
            print_element(head);
        }
    }

    return 0;
}