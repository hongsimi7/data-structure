#include "ds.h"
#include <fstream>

struct element {      
    int val1, val2;
    element* RC = NULL;
    element* LC = NULL;
    int height = 0;
};

int maxheight(int x, int y)
{
    return (x > y) ? x : y; 
}

void updateheight(element* node)
{
    if(node->LC != NULL && node->RC != NULL)    node->height = 1 + maxheight(node->LC->height,node->RC->height);
    else if(node->LC != NULL)  node->height = 1 + node->LC->height;
    else if(node->RC != NULL)  node->height = 1 + node->RC->height;
    else node->height = 0;
}

int givebf(element *node)
{
    return  (node->LC != NULL ? node->LC->height : -1) - (node->RC != NULL ? node->RC->height : -1);
}


void interval_search(element * root, int val1, int val2, string &output) 
{
    if(root == NULL)    return;

    if(val1 <= root->val1 && root->val2 <= val2)
    {
        output += to_string(root->val1);
        output += "-";
        output += to_string(root->val2);
        output += " ";
    }

    else if(root->val1 <= val1 && val1 <= root->val2)
    {
        output += to_string(root->val1);
        output += "-";
        output += to_string(root->val2);
        output += " ";
    }

    else if(root->val1 <= val2 && val2 <= root->val2)
    {
        output += to_string(root->val1);
        output += "-";
        output += to_string(root->val2);
        output += " ";
    }

    else if(root->val1 <= val1 && val2 <= root->val2)
    {
        output += to_string(root->val1);
        output += "-";
        output += to_string(root->val2);
        output += " ";
    }

    interval_search(root->LC , val1, val2, output);
    interval_search(root->RC , val1, val2, output);
}

element* R_rotation(element* head) 
{   
    element * newhead = head->LC;
    head->LC = newhead->RC;
    newhead->RC = head;
    
    if(newhead->LC != NULL)
    {
        updateheight(newhead->LC);
    }
    if(newhead->RC != NULL)
    {
        updateheight(newhead->RC);
    }
    updateheight(head);
    updateheight(newhead);
    
    return newhead;
}

element* L_rotation(element* head) 
{
    element * newhead = head->RC;
    head->RC = newhead->LC;
    newhead->LC = head;

    
    if(newhead->LC != NULL)
    {
        updateheight(newhead->LC);
    }
    if(newhead->RC != NULL)
    {
        updateheight(newhead->RC);
    }
    updateheight(head);
    updateheight(newhead);
    return newhead;
}

void ADD(element * &head, int val1, int val2) {
    if(head == NULL)                    //root가 존재하지 않을 때
    {
        element * node = new element;
        node->val1 = val1;
        node->val2 = val2;
        head = node;
        return;
    }

    if(val1 < head->val1)
    {
        ADD(head->LC, val1, val2);
    }
    else if(val1 > head->val1)
    {
        ADD(head->RC, val1, val2);
    }

    updateheight(head);

    int bf;
    if(head->LC != NULL && head->RC != NULL)    bf = head->LC->height - head->RC->height;
    else if(head->LC != NULL)  bf = head->LC->height - (-1);
    else if(head->RC != NULL)  bf = (-1) - head->RC->height;
    else bf = 0;
    if(bf > 1 && givebf(head->LC) >= 0)         //LL rotation
    {
        head = R_rotation(head);
    }
    else if(bf < -1 && givebf(head->RC) <= 0)   //RR rotation
    {
        head = L_rotation(head);
    }
    else if(bf > 1 && givebf(head->LC) < 0)    //LR rotation
    {
        head->LC = L_rotation(head->LC);
        head = R_rotation(head);
    }
    else if(bf < -1 && givebf(head->RC) > 0)   //RL rotation
    {
        head->RC = R_rotation(head->RC);
        head = L_rotation(head);
    }
}

bool DEL(element* &head, int val1, int val2, bool &chk, bool root) {
    if(head == NULL)                    //root가 존재하지 않을 때
    {
        chk = false;
        return false;
    }
    
    if(val1 < head->val1)
    {
        if(!(DEL(head->LC, val1, val2, chk, false)))
        {
            return false;
        }
        else{
            if(head->LC->LC == NULL && head->LC->RC == NULL)
            {
                delete head->LC;
                head->LC = NULL;

            }

            else if(head->LC->LC == NULL)
            {   
                element * temp = head->LC;
                head->LC = head->LC->RC;
                delete temp;
            }
            else if(head->LC->RC == NULL)
            {
                element * temp = head->LC;
                head->LC = head->LC->LC;
                delete temp;
            }

            else
            {
                element * finder = head->LC;
                element * max_node = finder->LC;
                while(max_node->RC != NULL)
                {
                    max_node = max_node->RC;
                }

                if(max_node == finder->LC) {        //rihgt subtree의 root가 최솟값일 때
                    max_node->RC = finder->RC;
                    head->LC = max_node;
                }
                else {
                    element * max_parent = finder->LC;
                    while(max_parent->RC != max_node)
                    {
                        max_parent = max_parent->RC;
                    }

                    if( max_node->LC == NULL) {      //자식 존재 X
                        max_parent->RC = NULL;
                    }
                    else {       //자식 존재
                        max_parent->RC = max_node->LC;
                    } 

                    max_node->RC = finder->RC;
                    max_node->LC = finder->LC;

                    if(max_parent->LC == finder)                     //finder node가 왼쪽 자식일 때
                    { 
                        max_parent->LC = max_node;
                    }
                    else {                                              //finder node가 오른쪽 자식일 때
                        max_parent->RC = max_node;
                    }    
                }
                delete finder;
            }
            

            updateheight(head);
            int bf;
            if(head->LC != NULL && head->RC != NULL)    bf = head->LC->height - head->RC->height;
            else if(head->LC != NULL)  bf = head->LC->height - (-1);
            else if(head->RC != NULL)  bf = (-1) - head->RC->height;
            else bf = 0;

            if(bf > 1 && givebf(head->LC) >= 0)         //LL rotation
            {
                head = R_rotation(head);
            }
            else if(bf < -1 && givebf(head->RC) <= 0)   //RR rotation
            {
                head = L_rotation(head);
            }
            else if(bf > 1 && givebf(head->LC) < 0)    //LR rotation
            {
                head->LC = L_rotation(head->LC);
                head = R_rotation(head);
            }
            else if(bf < -1 && givebf(head->RC) > 0)   //RL rotation
            {
                head->RC = R_rotation(head->RC);
                head = L_rotation(head);
            }
            return false;

        }
    }
    else if(val1 > head->val1)
    {
        if(!(DEL(head->RC, val1, val2, chk, false)))
        {
            return false;
        }

        else{
            if(head->RC->LC == NULL && head->RC->RC == NULL)
            {
                delete head->RC;
                head->RC = NULL;

            }

            else if(head->RC->LC == NULL)
            {   
                element * temp = head->RC;
                head->RC = head->RC->RC;
                delete temp;
            }
            else if(head->RC->RC == NULL)
            {
                element * temp = head->RC;
                head->RC = head->RC->LC;
                delete temp;
            }

            else
            {
                element * finder = head->RC;
                element * max_node = finder->LC;
                while(max_node->RC != NULL)
                {
                    max_node = max_node->RC;
                }

                if(max_node == finder->LC) {        //left subtree의 root가 최댓값일 때
                    max_node->RC = finder->RC;
                    head->RC = max_node;
                }
                else {
                    element * max_parent = finder->LC;
                    while(max_parent->RC != max_node)
                    {
                        max_parent = max_parent->RC;
                    }

                    if(max_node->LC == NULL) {      //자식 존재 X
                        max_parent->RC = NULL;
                    }
                    else {       //자식 존재
                        max_parent->RC = max_node->LC;
                    } 

                    max_node->RC = finder->RC;
                    max_node->LC = finder->LC;

                    if(max_parent->LC == finder)                     //finder node가 왼쪽 자식일 때
                    { 
                        max_parent->LC = max_node;
                    }
                    else {                                              //finder node가 오른쪽 자식일 때
                        max_parent->RC = max_node;
                    }    
                }
                delete finder;
            }

            

            updateheight(head);

            int bf;
            if(head->LC != NULL && head->RC != NULL)    bf = head->LC->height - head->RC->height;
            else if(head->LC != NULL)  bf = head->LC->height - (-1);
            else if(head->RC != NULL)  bf = (-1) - head->RC->height;
            else bf = 0;

            if(bf > 1 && givebf(head->LC) >= 0)         //LL rotation
            {
                head = R_rotation(head);
            }
            else if(bf < -1 && givebf(head->RC) <= 0)   //RR rotation
            {
                head = L_rotation(head);
            }
            else if(bf > 1 && givebf(head->LC) < 0)    //LR rotation
            {
                head->LC = L_rotation(head->LC);
                head = R_rotation(head);
            }
            else if(bf < -1 && givebf(head->RC) > 0)   //RL rotation
            {
                head->RC = R_rotation(head->RC);
                head = L_rotation(head);
            }
            return false;

        }
    }
    else{
        if(root)
        {
            if(head->LC == NULL && head->RC == NULL)
            {
                delete head;
                head = NULL;
                return false;
            }

            else if(head->LC == NULL)
            {   
                element * finder = head;
                element * min_node = finder->RC;
                while(min_node->LC != NULL)
                {
                    min_node = min_node->LC;
                }

                if(min_node == finder->RC) {        //left subtree의 root가 최댓값일 때
                    min_node->LC = finder->LC;
                    head = min_node;
                    delete finder;

                }
                else {
                    element * min_parent = finder->RC;
                    while(min_parent->LC != min_node)
                    {
                        min_parent = min_parent->LC;
                    }

                    if(min_node->RC == NULL) {      //자식 존재 X
                        min_parent->LC = NULL;
                    }
                    else {       //자식 존재
                        min_parent->LC = min_node->RC;
                    } 

                    min_node->LC = finder->LC;
                    min_node->RC = finder->RC;

                    head = min_node;
                    delete finder;
                }
            }

            else
            {
                element * finder = head;
                element * max_node = finder->LC;
                while(max_node->RC != NULL)
                {
                    max_node = max_node->RC;
                }

                if(max_node == finder->LC) {        //left subtree의 root가 최댓값일 때
                    max_node->RC = finder->RC;
                    head = max_node;
                    delete finder;

                }
                else {
                    element * max_parent = finder->LC;
                    while(max_parent->RC != max_node)
                    {
                        max_parent = max_parent->RC;
                    }

                    if(max_node->LC == NULL) {      //자식 존재 X
                        max_parent->RC = NULL;
                    }
                    else {       //자식 존재
                        max_parent->RC = max_node->LC;
                    } 

                    max_node->RC = finder->RC;
                    max_node->LC = finder->LC;

                    head = max_node;
                    delete finder;
                }
            }
            
            updateheight(head);
            int bf;
            if(head->LC != NULL && head->RC != NULL)    bf = head->LC->height - head->RC->height;
            else if(head->LC != NULL)  bf = head->LC->height - (-1);
            else if(head->RC != NULL)  bf = (-1) - head->RC->height;
            else bf = 0;
            if(bf > 1 && givebf(head->LC) >= 0)         //LL rotation
            {
                head = R_rotation(head);
            }
            else if(bf < -1 && givebf(head->RC) <= 0)   //RR rotation
            {
                head = L_rotation(head);
            }
            else if(bf > 1 && givebf(head->LC) < 0)    //LR rotation
            {
                head->LC = L_rotation(head->LC);
                head = R_rotation(head);
            }
            else if(bf < -1 && givebf(head->RC) > 0)   //RL rotation
            {
                head->RC = R_rotation(head->RC);
                head = L_rotation(head);
            }
            return false;

        }
        return true;
    }
}


int main() 
{
    int icount = 0;
    Node * head = NULL;
    element * root = NULL;
    string command;
    string value1;
    string value2;
    bool root_ok = true;

    string filename = "output_3.txt";
    ifstream file("input_3.txt");
    ofstream outFile("output_3.txt", ios::app);

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

    if(icount-1 != numofinstr) {          //입력 변수의 수가 맞지 않을 때
        outFile << "ERROR" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    
    
    file.clear();
    file.seekg(0, ios::beg);

    getline(file, line);
    numofinstr = stoi(line);

    int elmt1, elmt2;
    for(int i = 0; i < numofinstr; i++) 
    {
        getline(file, line);
        command = line.substr(0, 3);
        value1 = line.substr(4, line.find('-') - 4);
        value2 = line.substr(line.find('-') + 1);


        try {                       //int 전환 가능 여부
            elmt1 = stoi(value1);
            elmt2 = stoi(value2);
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
            ADD(root, elmt1, elmt2);

        }
        else if(command == "DEL")
        {
            bool chk = true;
            DEL(root, elmt1, elmt2, chk, root_ok);
            if(!chk)
            {
                outFile << "ERROR" << endl;
                file.close();
                outFile.close();
                return 0;
            }
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
    value1 = line.substr(0, line.find('-'));
    value2 = line.substr(line.find('-') + 1);

    try {                       //int 전환 가능 여부
        elmt1 = stoi(value1);
        elmt2 = stoi(value2);
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
    string output;
    
    interval_search(root, elmt1, elmt2, output);
   
    output = output.substr(0, output.length() - 1);
    
    outFile << output << endl;
    file.close();
    outFile.close();
    return 0;
}