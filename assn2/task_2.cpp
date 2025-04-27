#include "ds.h"
using namespace std;

int search_LCA(Node * head, int* arr)       //LCA 찾기
{
    Node * finder1 = head->LC;
    Node * finder2 = head->LC;
    int parent1[1000];
    int parent2[1000];
    int a = 0;
    int b = 0;

    while(finder1->value != -1)
    {
    
        if(finder1->value == arr[0]) {
            break;
        }
        

        if(finder1->LC != NULL) {
            finder1 = finder1->LC;
        }

        else if(finder1->RS != NULL) {
            finder1 = finder1->RS;
        }

        else {
            while(finder1->RS == NULL && finder1->value != -1)
            {
                finder1 = finder1->parent;
            }
            if(finder1->value != -1)
            {
                finder1 = finder1->RS;
            }        
        }
    }

    while(finder2->value != -1)
    {
        if(finder2->value == arr[1]) {       //검사
            break;
        }

        if(finder2->LC != NULL) {            //LC가 있는지 확인 및 LC로 이동
            finder2 = finder2->LC;
        }

        else if(finder2->RS != NULL) {       //LC가 존재하지 않을 때, RS 확인 및 RS로 이동
            finder2 = finder2->RS;            
        }

        else {
            
            while(finder2->RS == NULL && finder2->value != -1)
            {
                finder2 = finder2->parent;
            }
            
            if(finder2->value != -1)
            {
                finder2 = finder2->RS;
            }
        }
    }

    if(finder1->value == -1 || finder2->value == -1)
    {
        return -1;
    }

    while(finder1->value != -1)
    {
        parent1[a] = finder1->value;
        finder1 = finder1->parent;
        a++;
    }
    
    while(finder2->value != -1)
    {
        parent2[b] = finder2->value;
        finder2 = finder2->parent;
        b++;
    }

    int i = 0;
    for(int i = 0; i < 1000 ; i++)
    {
        for(int j = 0; j <1000 ; j++)
        {
            if(parent1[i] == parent2[j])
            {
                int result = parent1[i];
                return result;
            }
        }
    }
    return -1;
}

int main()
{   
    Node * dummy = new Node;        //dummy head 생성
    dummy->value = -1;
    int icount = 0;

    string filename = "output_2.txt";
    ifstream file("input_2.txt");
    ofstream outFile("output_2.txt", ios::app);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << endl;
        return -1;
    }

    string line;
    int numofinstr = 0;

    if(getline(file, line)) {
        numofinstr = stoi(line);  
    }

    while(getline(file, line)) {       //입력 읽기
        icount++;
    }

    if((icount - 1) != numofinstr) {          //입력 변수의 수가 맞지 않을 때
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    
    file.clear();
    file.seekg(0, ios::beg);

    getline(file, line);
    numofinstr = stoi(line);

    for(int i = 0; i < numofinstr; i++) {       //입력 읽기
        getline(file, line);
        int arr[1000];
        int size = 0;
        
        split(line, arr, size);
        if(size == -1) {                        //1000이상의 수가 들어올 때
            outFile << "Error" << endl;
            file.close();
            outFile.close();
            return 0;
        }
        insert(dummy, arr, size);
        
    }
    getline(file, line);
    int arr[1000];
    int size = 0;
        
    split(line, arr, size);
    int result = search_LCA(dummy, arr);
    if(result == -1)
    {
        outFile << "Error" << endl;
    }
    else
    {
        outFile << result << endl;
    }
    file.close();
    outFile.close();
    return 0;
}