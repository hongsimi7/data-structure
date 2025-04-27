#include "ds.h"
using namespace std;

struct LC_node
{
    int count_ch = 0;
    int value;
    NodeS * child = NULL;
};

int ADD(LC_node *CTT, int & CTT_count, int parent, int child) {

    for(int i = 0; i<CTT_count; i++)    //parent node 존재
    {
        if(CTT[i].value == parent)
        {               
            insert_node(&CTT[i].child, child);       //child 추가
            CTT[i].count_ch += 1;                   //child count 추가
            for(int j = 0; j < 1000; j++)
            {
                if(CTT[j].value == -1)
                {
                    CTT[j].value = child;                 //child array에 추가

                    CTT_count += 1;
                    break;
                }            
            }
            if(CTT[i].count_ch > 3) {   //children이 3을 초과한 경우(error)
                return -1;
            }
            else {
                return 0;
            }
        }
    }
    return -1; //parent node가 존재하지 않는 경우(error)
}

int DEL(LC_node *CTT, int & CTT_count, int value) {
    int result = -1;
    for(int i = 0; i < CTT_count; i++)      //child에서 삭제
    {
        int ok = 0;
        NodeS * find = CTT[i].child;
        while(find)
        {
            if(find->value == value) {
                delete_node(&CTT[i].child, value);
                int ok = 1;
                break;
            }
            find = find->next;
        }
        if(ok == 1) break;
    }
    for(int i = 0; i < CTT_count; i++)
    {
        if(CTT[i].value == value)       //요소 찾음
        {   
            if(CTT[i].child != NULL) {
                NodeS * temp = CTT[i].child;
                do
                {
                    int trash = DEL(CTT, CTT_count, temp->value);
                    temp = temp->next;
                } while((temp != NULL));

            }
        
            CTT[i].value = -1;
            CTT_count -= 1;
            CTT[i].count_ch = 0;
            CTT[i].child = NULL;
            result = 0;
            break;
        }    
    }
    return result;
}

void split1(string &str, string &command, int &a, int &b) {
    bool check = true;
    int space1 = str.find(' ');
    command = str.substr(0, space1);
    if(command != "ADD" && command !="DEL") {
        command = "Error";
        return;
    }

    if(space1 != string::npos) {
        int space2 = str.find(' ', space1 + 1);
        string firstargu = str.substr(space1+ 1, space2 - 1 - space1);

        for(int i = 0 ; i < firstargu.length() ;i++)       //띄어쓰기 밖에 없을 때
            {
                if(firstargu[i] != ' ') {
                    check = false;
                    break;
                }
            }

        if(check) {
                a = -1;
                b = -1;
                return;
            }

        for(int i = 0 ; i < firstargu.length() ;i++)
            {
                if(firstargu[i] < '0' || firstargu[i] > '9') {
                    command = "Error";
                    return;
                }
            }
        a = stoi(firstargu);

        if(space2 != string::npos) {
            string secondargu = str.substr(space2 + 1);
            for(int i = 0 ; i < secondargu.length() ;i++)       //띄어쓰기 밖에 없을 때
            {
                if(secondargu[i] != ' ') {
                    check = false;
                    break;
                }
            }
            if(check) {
                b = -1;
                return;
            }

            if(command == "DEL") {
                command = "Error";
                return;
            }

            for(int i = 0 ; i < secondargu.length() ;i++)
            {
                if(secondargu[i] < '0' || secondargu[i] > '9') {
                    command = "Error";
                    return;
                }
            }
            b = stoi(secondargu);        
        }
        else {
            if(command == "ADD") {
                command = "Error";
                return;
            }
        }
    }
    else {
        if(command == "ADD" || command == "DEL") {
            command = "Error";
            return;
        }
    }

}

void sort(LC_node *CTT, int CTT_count) 
{
    for(int i = 0; i < 999; i++)
    {
        for(int j = 0; j < 999 - i; j++)
        {
            if(CTT[j].value > CTT[j+1].value) {
                LC_node temp = CTT[j];
                CTT[j] = CTT[j+1];
                CTT[j+1] = temp;
            }
        }
    }
}

int main()
{
    using namespace std;
    int check;
    int icount = 0;
    LC_node CTT[1000];
    int CTT_count = 1;
    int aboveCTT = 1;

    CTT[0].value = 0;
    ofstream outFile("output_1.txt", ios::app);

    for(int i = 1; i < 1000; i++)
    {
        CTT[i].value = -1;
    }

    string filename = "output_1.txt";
    ifstream file("input_1.txt");

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

    if(icount != numofinstr) {          //입력 변수의 수가 맞지 않을 때
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
        string command;
        int a, b;
        
        split1(line, command, a, b);

        if(command == "Error" || a < 0 || a > 999 || b < 0 || b> 999) {
            outFile << "Error" << endl;
            file.close();
            outFile.close();
            return 0;
        }

        if(command == "ADD") {
            aboveCTT++;
            if(aboveCTT > 1000) {               //요소가 1000개를 넘겼을 때(error)
                outFile << "Error" << endl;
                file.close();
                outFile.close();
                return 0;
            }         
            check = ADD(CTT, CTT_count, a, b);
        }

        else if(command == "DEL") {
            aboveCTT--;
            check = DEL(CTT, CTT_count, a);
        }

        else {}

        if(check == -1) {       //error 발생
            break;
        }
    }

    sort(CTT, CTT_count);
    

    if(check == - 1)            //error
    {
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    for(int i = 0; i < 1000; i++)
    {
        
        if(CTT[i].value == -1) {
            continue;
        }
        int ok = 0;
        for(int j = 0; j < 1000; j++)  //child에 있는지 확인
        {
            NodeS * check_ch = CTT[j].child;
            while(check_ch)
            {
                if(check_ch->value == CTT[i].value) {
                    ok = 1;
                    break;
                }
                check_ch = check_ch->next;
            }
            if(ok == 1) {
                break;
            }
        }

        if(ok == 0 && CTT[i].value != 0) {       //child에 없음.
            continue;
        }

        string result = "";
        result += to_string(CTT[i].value);
        NodeS * read_child = CTT[i].child;

        if(read_child == NULL) {
            continue;
        }
        
        while(read_child)
        {
            result += " ";
            result += to_string(read_child->value);
            read_child = read_child->next;
        }
        outFile << result << endl;
    }
    file.close();
    outFile.close();
    return 0;
}