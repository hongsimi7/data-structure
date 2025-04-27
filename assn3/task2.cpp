#include "ds.h"
#include <fstream>

struct element {      
    int value;
    bool dummy = true;
    element* parent = NULL;
    element* RC = NULL;
    element* LC = NULL;
};

void find_min_value(element* node, element ** min_find) {
    if (node == NULL) return;  

    if (node->value < (*min_find)->value) {
        *min_find = node;
    }

    find_min_value(node->LC, min_find);
    find_min_value(node->RC, min_find);
}

void inorder_traversal(element* node, int list[], int &idx) {
    if(node == NULL) return;

    inorder_traversal(node->LC, list, idx);


    list[idx] = node->value;
    idx++;

    inorder_traversal(node->RC, list, idx);
}

bool check_sorted(int list[], int count)
{
    for(int i = 0 ; i < (count - 1) ; i++)
    {
        if(list[i] > list[i+1])
        {
            return false;
        }
    }
    return true;
}
void POS(element * root, int list[], int count) {
    element * node_elem = new element;
    node_elem->dummy = false;
    node_elem->value = list[count-1];

    if(count == 0)
    {
        return;
    }

    if(root->dummy) 
    {
        root->LC = node_elem;
        node_elem->parent = root;
    }
    else {
        if(node_elem->value <= root->value)     //LC에 삽입
        {
            root->LC = node_elem;
            node_elem->parent = root;
        }
        else                                    //RC에 삽입
        {
            root->RC = node_elem;
            node_elem->parent = root;
        }
    }

    if(count == 1) {
        return;
    }

    int idx = count-2;
    while(list[idx] >= node_elem->value)
    {
        idx--;
        if(idx < 0) {
            break;
        }
    }

    if(idx == -1) {                                 //left subtree x        
        int * right_sub = new int[count - idx - 2]; //right 재귀
        for(int i = 0 ;i < count - idx - 2 ; i++) 
        {
            right_sub[i] = list[i];
        }
        POS(node_elem, right_sub, count - idx - 2);   
    }

    else if(idx == count - 2) {                 //right subtree x
        int * left_sub = new int[idx + 1];          //left 재귀
        for(int i = 0 ;i < idx + 1; i++) 
        {
            left_sub[i] = list[i];
        }
        POS(node_elem, left_sub, idx + 1);
    }
    else {
        int * left_sub = new int[idx + 1];          //left 재귀
        for(int i = 0 ;i < idx + 1; i++) 
        {
            left_sub[i] = list[i];
        }
        POS(node_elem, left_sub, idx + 1);

        int * right_sub = new int[count - idx - 2]; //right 재귀
        for(int i = 0 ;i < count - idx - 2 ; i++) 
        {
            right_sub[i] = list[idx + i + 1];
        }
        POS(node_elem, right_sub, count - idx - 2);    
    }
}

void PRE(element * root, int list[], int count) {
    element * node_elem = new element;
    node_elem->dummy = false;
    node_elem->value = list[0];

    if(count == 0)
    {
        return;
    }

    if(root->dummy) 
    {
        root->LC = node_elem;
        node_elem->parent = root;
    }
    else {
        if(node_elem->value <= root->value)     //LC에 삽입
        {
            root->LC = node_elem;
            node_elem->parent = root;
        }
        else                                    //RC에 삽입
        {
            root->RC = node_elem;
            node_elem->parent = root;
        }
    }

    if(count == 1) {
        return;
    }

    int idx = 1;
    while(list[idx] <= node_elem->value)
    {
        idx++;
        if(idx >= count) {
            break;
        }
    }

    if(idx == count) {                                //right subtree x  
        int * left_sub = new int[idx - 1];          //left 재귀
        for(int i = 0; i < idx - 1; i++) 
        {
            left_sub[i] = list[i + 1];
        }
        PRE(node_elem, left_sub, idx - 1);      
    }
       
    else if(idx == 1) {                             //left subtree x
        int * right_sub = new int[count - idx];       //right 재귀
        for(int i = 0 ;i < count - idx; i++) 
        {
            right_sub[i] = list[idx + i];
        }
        PRE(node_elem, right_sub, count - idx);      
    }
    else {
        int * left_sub = new int[idx - 1];          //left 재귀
        for(int i = 0; i < idx - 1; i++) 
        {
            left_sub[i] = list[i + 1];
        }
        PRE(node_elem, left_sub, idx - 1);

        int * right_sub = new int[count - idx]; //right 재귀
        for(int i = 0 ;i < count - idx ; i++) 
        {
            right_sub[i] = list[idx + i];
        }
        PRE(node_elem, right_sub, count - idx);    
    }
    
}

void ADD(element * root, int value) {
    element * finder = root->LC;
    element * node_elem = new element;
    node_elem->dummy = false;
    node_elem->value = value;

    if(finder == NULL)              //root가 존재하지 않을 때
    {
        root->LC = node_elem;
        node_elem->parent = root;
        return;
    }

    while(true) 
    {
        if(value <= finder->value)  //left
        {
            if(finder->LC == NULL)
            {
                finder->LC = node_elem;
                node_elem->parent = finder;
                break;
            }
            else
            {
                finder = finder->LC;
            }
        }
        else                        //right
        {
            if(finder->RC == NULL)
            {
                finder->RC = node_elem;
                node_elem->parent = finder;
                break;
            }
            else
            {
                finder = finder->RC;
            }
        }
    }
}

bool DEL(element * root, int value) {
    element * finder = root->LC;

    if(finder == NULL)              //존재x
    {
        return false;
    }

    while(true) 
    {
        if(value < finder->value)  //left
        {
            if(finder->LC == NULL)  //존재x
            {
                return false;
            }
            else
            {
                finder = finder->LC;
            }
        }
        else if(value > finder->value)  //right
        {
            if(finder->RC == NULL)  //존재x
            {
                return false;
            }
            else
            {
                finder = finder->RC;
            }
        }
        else        //존재할 때
        {
            break;
        }
    }

    if(finder->LC == NULL && finder->RC == NULL) {      //leaf node일 때
        if(finder->parent->LC == finder)                //왼쪽 자식일 때
        {
            finder->parent->LC = NULL;
        }
        else                                            //오른쪽 자식일 때
        {
            finder->parent->RC = NULL;
        }
        delete finder;
    }

    else if(finder->LC == NULL || finder->RC == NULL) {     //degree 1 node일 때
        if(finder->parent->LC == finder)                //삭제 노드가 왼쪽 자식일 때
        {
            if(finder->LC != NULL)                      //왼쪽 자식 존재
            {
                finder->LC->parent = finder->parent;
                finder->parent->LC = finder->LC;
            }
            else                                        //오른쪽 자식 존재
            {
                finder->RC->parent = finder->parent;
                finder->parent->LC = finder->RC;
            }
            
        }
        else                                            //삭제 노드가 오른쪽 자식일 때
        {
            if(finder->LC != NULL)                      //왼쪽 자식 존재
            {
                finder->LC->parent = finder->parent;
                finder->parent->RC = finder->LC;
            }
            else                                        //오른쪽 자식 존재
            {
                finder->RC->parent = finder->parent;
                finder->parent->RC = finder->RC;
            }
        }
        delete finder;
    }

    else {              //degree 2 node일 때
        element * max_node = finder->LC;
        while(max_node->RC != NULL)
        {
            max_node = max_node->RC;
        }

        if(max_node == finder->LC) {        //rihgt subtree의 root가 최솟값일 때
            max_node->parent = finder->parent;
            max_node->RC = finder->RC;
            finder->RC->parent = max_node;
            
            if(finder->parent->LC == finder)                     //finder node가 왼쪽 자식일 때
            { 
                finder->parent->LC = max_node;
            }
            else {                                              //finder node가 오른쪽 자식일 때
                finder->parent->RC = max_node;
            }    

        }
        else {
            if( max_node->LC == NULL) {      //자식 존재 X
                max_node->parent->RC = NULL;
            }
            else {       //자식 존재
                max_node->parent->RC = max_node->LC;
                max_node->LC->parent = max_node->parent;
            } 
            max_node->parent = finder->parent;
            max_node->RC = finder->RC;
            max_node->LC = finder->LC;
            finder->RC->parent = max_node;
            finder->LC->parent = max_node;

            if(finder->parent->LC == finder)                     //finder node가 왼쪽 자식일 때
            { 
                finder->parent->LC = max_node;
            }
            else {                                              //finder node가 오른쪽 자식일 때
                finder->parent->RC = max_node;
            }    
        }
        delete finder;
    }
    return true;
    
}

bool NOD(element * root, int value, int list[], int &rank, string & output) {
    element * finder = root;

    if(finder == NULL)              //존재x
    {
        return false;
    }

    while(true) 
    {
        if(value < finder->value)  //left
        {
            if(finder->LC == NULL)  //존재x
            {
                return false;
            }
            else
            {
                output += to_string(finder->value);
                output += " ";
                finder = finder->LC;
            }
        }
        else if(value > finder->value)  //right
        {
            if(finder->RC == NULL)  //존재x
            {
                return false;
            }
            else
            {
                output += to_string(finder->value);
                output += " ";
                finder = finder->RC;
            }
                
        }
        else        //존재할 때
        {
            output += to_string(finder->value);
            break;
        }
    }

    while(true)
    {
        if(list[rank] == value)
        {
            break;
        }
        rank++;
    }
    return true;

    
}

int main() 
{
    int icount = 0;
    Node * head = NULL;
    element * dummy = new element;
    string command;
    string value;

    string filename = "output_2.txt";
    ifstream file("input_2.txt");
    ofstream outFile("output_2.txt", ios::app);

    if (!file.is_open()) {
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    string line;
    int numofinstr = 0;

    if(getline(file, line)) {
        numofinstr = stoi(line);  
    }

    while(getline(file, line)) {       //입력 읽기
        icount++;
    }

    if(icount != numofinstr) {          //입력 변수의 수가 맞지 않을 때
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    
    
    file.clear();
    file.seekg(0, ios::beg);

    getline(file, line);
    numofinstr = stoi(line);

    getline(file, line);
    command = line.substr(0, 3);
    value = line.substr(4);

    if(value.front() != '[' || value.back() != ']') {
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    value = value.substr(1, value.length() - 2);

    int count = 0;
    int i = 0;
    while (i != string::npos) {             //마지막 요소까지 확인을 했는지
        string check;
        int commaPos = value.find(',', i);
        
        if(commaPos == string::npos) {      //,가 존재하지 않을 때(즉, array의 끝)
            check = value.substr(i);
            if(i == 0 && check == "") {                    //array 안에 아무것도 존재 X
                break;
            }
        }
        else {
            check = value.substr(i, commaPos - i);
        }


        Node* Node_elmt = new Node;         //node 생성
        Node_elmt->next = NULL;
        Node_elmt->pre = NULL;

        if (head == NULL) {              //처음일 때
            head = Node_elmt; 
        } 
        else {
            Node* finder = head;
            while (finder->next != NULL) {
                finder = finder->next;
            }
            finder->next = Node_elmt;
            Node_elmt->pre = finder;
        }

        try {                               //int로 변환 가능 여부
            Node_elmt->value = stoi(check);
            count++;
        } 
        catch (invalid_argument& e) {
            outFile << "ERROR" << std::endl;
            file.close();
            outFile.close();
            return 0;
        } 
        catch (out_of_range& e) {
            outFile << "ERROR" << std::endl;
            file.close();
            outFile.close();
            return 0;
        }
        if (commaPos == string::npos) {
            break;
        }
        i = commaPos + 1;
    }
    int* list = new int[count];
    Node * finder = head;
    for(int i = 0 ; i < count ; i++) 
    {
        list[i] = finder->value;
        finder = finder->next;
    }



    if(command == "POS")
    {
        POS(dummy, list, count);
        if(count > 1)
        {
            int idx = 0;
            int * check_inorder = new int[count];
            inorder_traversal(dummy->LC, check_inorder, idx);

            if(!(check_sorted(check_inorder, count)))
            {
                outFile << "ERROR" << endl;
                file.close();
                outFile.close();
                return 0;
            }
        }
    }
    else if(command == "PRE")
    {
        PRE(dummy, list, count);
        if(count > 1)
        {
            int idx = 0;
            int *check_inorder = new int[count];
            inorder_traversal(dummy->LC, check_inorder, idx);
            if(!(check_sorted(check_inorder, count)))
            {
                outFile << "ERROR" << endl;
                file.close();
                outFile.close();
                return 0;
            }
        }
    }
    else                  
    {
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    
    int elmt;
    for(int i = 0; i < numofinstr - 2; i++) 
    {
        getline(file, line);
        command = line.substr(0, 3);
        value = line.substr(4);

        try {                       //int 전환 가능 여부
            elmt = stoi(value);
        } 
        catch(invalid_argument& e) {
            outFile << "ERROR" << endl;
            file.close();
            outFile.close();
            return 0;
        }
        catch(out_of_range& e) {
            outFile << "ERROR" << endl;
            file.close();
            outFile.close();
            return 0;
        }
     
        if(command == "ADD")
        {
            
            ADD(dummy, elmt);
            count++;
        }
        else if(command == "DEL")
        {
            bool chk = DEL(dummy, elmt);
            if(!chk) {
                outFile << "ERROR: " << command << " " << elmt << endl;
                file.close();
                outFile.close();
                return 0;
            }
            count--;
        }
        else
        {
            outFile << "ERROR" << endl;
            file.close();
            outFile.close();
            return 0;
        }   
    }

    getline(file, line);
    command = line.substr(0, 3);
    value = line.substr(4);
    

    try {                       //int 전환 가능 여부
        elmt = stoi(value);
    } 
    catch(invalid_argument& e) {
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    catch(out_of_range& e) {
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    if(command == "NOD")
    {   
        
        int * inorder = new int[count];
        int idx = 0;
        int rank = 0;
        string output;
        inorder_traversal(dummy->LC, inorder, idx);
        bool chk = NOD(dummy->LC, elmt, inorder, rank, output);
        if(!chk)
        {
            outFile << "ERROR: " << command << " " << elmt << endl;
            file.close();
            outFile.close();
            return 0;
        }
        outFile << "Rank: " << rank << endl;
        outFile << "Path: " << output << endl;
    }
    else                  
    {
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    file.close();
    outFile.close();
    return 0;
}