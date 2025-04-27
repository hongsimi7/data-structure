#include "ds.h"
string erase(string str)        // 띄어쓰기, ) 지우기
{
    string result;
    for(int i = 0; i < str.length() ; i++)
    {
        if(str[i] != '(' && str[i] != ')' && str[i] != ' ')
        {
            result += str[i];
        }
    }
    return result;
}

string side_erase(string str) {
    int first = 0;                                  //양 사이드 띄어쓰기 지우기
    while(first < str.length() && (str[first] == ' ')) {
        first++;
    }
    int last = str.length() -1;
    while(last>first && (str[last] == ' ')) {
        last--;
    }
    return str.substr(first, last - first + 1); 
}

bool check_hyphen(string str) {     //-개수 확인
    int count = 0;
    for(int i = 0 ; i < str.length() ; i++) {
        if(str[i] == '-') count++;
    }
    return count > 1;
}

int check_correct(string str) {
    if(str.find('?') == string::npos) {         //?가 존재하지 않을 때
        return -1;
    }
    int cntr = 0; // ) 개수
    int cntl = 0; // ( 개수
    int cntq = 0; // ? 개수
    int cntd = 0; // : 개수

    for(int i = 0; i < str.length() ; i ++) {
        if(str[i] == ':') {  
            cntd++;
        }
        else if(str[i] == '(') {
            cntl++;
        }
        else if(str[i] == ')') {
            cntr++;
        }
        else if(str[i] == '?') {
            cntq++;
        }
        else {}
    }

    if(cntd != cntq || cntl != cntr) {      //() 수가 같지 않거나, ?:가 같지 않을 때
        return -1;
    }

    return 0;   
}

bool check_num(string str) {                //숫자가 존재하는지 확인(split3에서 감지)
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] >= '0' && str[i] <= '9') {
            return false;
        }
    }
    return true;
}

bool check_ok(Nodestr * head, int N)    
{                                                        //부호 표현이 제대로 되어있는지
    Nodestr * point = head->LC;
    while(point != NULL)
    {
        
        string con = point->str;
        string left;
        string right;
        string temp;

        for(int i = 0; i < con.length() ; i++)          //괄호 지우기
        {
            if(con[i] != '(' && con[i] != ')')
            {
                temp += con[i];
            }
        }          

        int first = 0;                                  //양 사이드 띄어쓰기 지우기
        while(first < temp.length() && (temp[first] == ' ')) {
            first++;
        }
        int last = temp.length() -1;
        while(last>first && (temp[last] == ' ')) {
            last--;
        }
        con = temp.substr(first, last - first + 1);

    
        if(con.find('>') != string::npos)  // >일 때
            {
                left = side_erase(con.substr(0, con.find('>')));
                right = side_erase(con.substr(con.find('>') + 1));

                if(check_num(left)) {           //숫자가 없을 때
                    head->str = "Error";
                    return true;
                }
                if(check_num(right)) {
                    head->str = "Error";
                    return true;
                }

                if(right.find(' ') != string::npos) {   //두 변수가 들어가 있을 때
                head->str = "Error";
                return true;
                }
                if(left.find(' ') != string::npos) {
                head->str = "Error";
                return true;
                }

                left = erase(left);
                right = erase(right);


                if(check_hyphen(left) || check_hyphen(right))   //-가 2개 이상
                {
                    head->str = "Error";
                    return true;
                }
        

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(left.substr(left.find('i') + 1));
                    if(a >= N)                                  //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(right.substr(right.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
                }
            }
        else if(con.find('<') != string::npos)  // <일 때
            {
                left = side_erase(con.substr(0, con.find('<')));
                right = side_erase(con.substr(con.find('<') + 1));

                if(check_num(left)) {           //숫자가 없을 때
                    head->str = "Error";
                    return true;
                }
                if(check_num(right)) {
                    head->str = "Error";
                    return true;
                }
                if(right.find(' ') != string::npos) {
                head->str = "Error";
                return true;
                }
                if(left.find(' ') != string::npos) {
                head->str = "Error";
                return true;
                }

                left = erase(left);
                right = erase(right);

                if(check_hyphen(left) || check_hyphen(right))   //-가 2개 이상
                {
                    head->str = "Error";
                    return true;
                }

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(left.substr(left.find('i') + 1));
                    if(a >= N)                                  //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(right.substr(right.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
                }
            }
        else if(con.find("==") != string::npos)  //  == 일 때
            {
                left = side_erase(con.substr(0, con.find("==")));
                right = side_erase(con.substr(con.find("==") + 2));

                if(check_num(left)) {           //숫자가 없을 때
                    head->str = "Error";
                    return true;
                }
                if(check_num(right)) {
                    head->str = "Error";
                    return true;
                }
                if(right.find(' ') != string::npos) {
                head->str = "Error";
                return true;
                }
                if(left.find(' ') != string::npos) {
                head->str = "Error";
                return true;
                }

                left = erase(left);
                right = erase(right);

                if(check_hyphen(left) || check_hyphen(right))   //-가 2개 이상
                {
                    head->str = "Error";
                    return true;
                }

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(left.substr(left.find('i') + 1));
                    if(a >= N)                                  //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(right.substr(right.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
                }
            }
        else 
        {          //부호 없이 변수가 두 개 들어갔는지 확인 혹은 범위 초과
            if(con.find(' ') != string::npos) {
                head->str = "Error";
                return true;
            }

            con = erase(con);

            if(check_hyphen(con))   //-가 2개 이상
            {
                head->str = "Error";
                return true;
            }

            if(con.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(con.substr(con.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        head->str = "Error";
                        return true;
                    }
            }

        }

        if(point->LC != NULL) {     //순환 코드
            point = point->LC;
        }

        else {
            while(point != NULL && point->RS == NULL)
            {
                point = point->parent;
            }
            if(point != NULL)
            {
                point = point->RS;
            }        
        }
    }
    return false;
}

bool check_ok_str(string str, int N) {              //부호 표현이 제대로 되어있는지                                                               
        string con = str;
        string left;
        string right;
        string temp;

        for(int i = 0; i < con.length() ; i++)          //괄호 지우기
        {
            if(con[i] != '(' && con[i] != ')')
            {
                temp += con[i];
            }
        }          

        int first = 0;                                  //양 사이드 띄어쓰기 지우기
        while(first < temp.length() && (temp[first] == ' ')) {
            first++;
        }
        int last = temp.length() -1;
        while(last>first && (temp[last] == ' ')) {
            last--;
        }
        con = temp.substr(first, last - first + 1);
    
        if(con.find('>') != string::npos)  // >일 때
            {
                left = side_erase(con.substr(0, con.find('>')));
                right = side_erase(con.substr(con.find('>') + 1));

                if(check_num(left)) {           //숫자가 없을 때
                    return true;
                }
                if(check_num(right)) {
                    return true;
                }

                if(right.find(' ') != string::npos) {   //두 변수가 들어가 있을 때
                return true;
                }
                if(left.find(' ') != string::npos) {
                return true;
                }

                left = erase(left);
                right = erase(right);


                if(check_hyphen(left) || check_hyphen(right))   //-가 2개 이상
                {
                    return true;
                }
        

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(left.substr(left.find('i') + 1));
                    if(a >= N)                                  //범위 초과
                    {
                        return true;
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(right.substr(right.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        return true;
                    }
                }
            }
        else if(con.find('<') != string::npos)  // <일 때
            {
                left = side_erase(con.substr(0, con.find('<')));
                right = side_erase(con.substr(con.find('<') + 1));

                if(check_num(left)) {           //숫자가 없을 때
                    return true;
                }
                if(check_num(right)) {
                    return true;
                }
                if(right.find(' ') != string::npos) {
                return true;
                }
                if(left.find(' ') != string::npos) {
                return true;
                }

                left = erase(left);
                right = erase(right);

                if(check_hyphen(left) || check_hyphen(right))   //-가 2개 이상
                {
                    return true;
                }

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(left.substr(left.find('i') + 1));
                    if(a >= N)                                  //범위 초과
                    {
                        return true;
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(right.substr(right.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        return true;
                    }
                }
            }
        else if(con.find("==") != string::npos)  //  == 일 때
            {
                left = side_erase(con.substr(0, con.find("==")));
                right = side_erase(con.substr(con.find("==") + 2));

                if(check_num(left)) {           //숫자가 없을 때
                    return true;
                }
                if(check_num(right)) {
                    return true;
                }
                if(right.find(' ') != string::npos) {
                return true;
                }
                if(left.find(' ') != string::npos) {
                return true;
                }

                left = erase(left);
                right = erase(right);

                if(check_hyphen(left) || check_hyphen(right))   //-가 2개 이상
                {
                    return true;
                }

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(left.substr(left.find('i') + 1));
                    if(a >= N)                                  //범위 초과
                    {
                        return true;
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(right.substr(right.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {
                        return true;
                    }
                }
            }
        else 
        {          //부호 없이 변수가 두 개 들어갔는지 확인 혹은 범위 초과
            if(con.find(' ') != string::npos) {
                return true;
            }

            con = erase(con);

            if(check_hyphen(con))   //-가 2개 이상
            {
                return true;
            }

            if(con.find('i') != string::npos) {            //변수가 존재할 때
                    int a = stoi(con.substr(con.find('i') + 1));
                    if(a >= N)                                   //범위 초과
                    {                        
                        return true;
                    }
            }

        }
    return false;
}
void split3(string str, Nodestr * head , int N) {

    if(str.find('?') == string::npos) {     //더 이상 나눌 수 없을 때
        return;
    }

    else {
        int splitcon = str.find('?');
        string con = str.substr(0, splitcon - 1);

        if(con.empty()) {
            head->str = "Error";
            return;
        }

        if(check_num(con)) {
            head->str = "Error";
            return;
        }

        if(check_ok_str(con, N)) {
            head->str = "Error";
            return;
        }

        int splitTF = splitcon + 1;
        int cntr = 0;
        int cntl = 0;

        while(true) {
            if(str[splitTF] == ':' && cntr == cntl) {   // '(', ')'의 개수가 같고, :가 나왔을 때
                break;
            }
            else if(str[splitTF] == '(') {
                cntl++;
            }
            else if(str[splitTF] == ')') {
                cntr++;
            }
            else {}
            splitTF++;
        }


        string T = str.substr(splitcon + 1, splitTF - splitcon - 1);
        string F = str.substr(splitTF + 1);

        if(T.empty()) {             //Error 감지
            head->str = "Error";
            return;
        }

        if(check_num(T)) {
            head->str = "Error";
            return;
        }

        if(F.empty()) {
            head->str = "Error";
            return;
        }

        if(check_num(F)) {
            head->str = "Error";
            return;
        }

        insertstr(head, con, T, F);

        split3(T, head, N);        //재귀적으로 나누기
        split3(F, head, N);
        
    }
}

int read_str(Nodestr * head, int inum[])
{
    Nodestr * point = head->LC;
    while(true)
    {
        string con = erase(point->str);     //깔끔하게 만들기
        string left;
        string right;
        int a , b;
        if(point->LC != NULL)       //non terminal node 일 때
        {
            if(con.find('>') != string::npos)  // > 일 때
            {
                left = con.substr(0, con.find('>'));
                right = con.substr(con.find('>') + 1);

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(left.substr(left.find('i') + 1));
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = -inum[a];
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = stoi(left.substr(left.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(left);
                    }
                }

                if(right.find('i') != string::npos) {           //변수가 존재할 때
                    b = stoi(right.substr(right.find('i') + 1));
                    if(right.find('-') != string::npos)         //부호 관리
                    {
                        b = -inum[b];
                    }
                    else
                    {
                        b = inum[b];
                    }
                }
                else {
                    if(right.find('-') != string::npos)         //부호 관리
                    {
                        b = stoi(right.substr(right.find('-') + 1));
                        b = -b;
                    }
                    else
                    {
                        b = stoi(right);
                    }
                }
                
                if(a > b)       //참일 때
                {
                    point = point->LC;
                }
                else            //거짓일 때
                {
                    point = point->LC->RS;
                }

            }
            else if(con.find("<") != string::npos) // < 일 때
            {
                left = con.substr(0, con.find("<"));
                right = con.substr(con.find("<") + 1);

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(left.substr(left.find('i') + 1));
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = -inum[a];
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(left.find('-') != string::npos)          //부호관리
                    {
                        a = stoi(left.substr(left.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(left);
                    }
                }

                if(right.find('i') != string::npos) {            //변수가 존재할 때
                    b = stoi(right.substr(right.find('i') + 1));
                    if(right.find('-') != string::npos)          //부호 관리
                    {
                        b = -inum[b];
                    }
                    else
                    {
                        b = inum[b];
                    }
                }
                else {
                    if(right.find('-') != string::npos)         //부호 관리
                    {
                        b = stoi(right.substr(right.find('-') + 1));   
                        b = -b;
                    }
                    else
                    {
                        b = stoi(right);
                    }
                }
                
                if(a < b)       //참일 때
                {
                    point = point->LC;
                }
                else            //거짓일 때
                {
                    point =point->LC->RS;
                }

            }
            else if(con.find("==") != string::npos) //==일 때
            {
                left = con.substr(0, con.find("=="));
                right = con.substr(con.find("==") + 2);

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(left.substr(left.find('i') + 1));
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = -inum[a];
                
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = stoi(left.substr(left.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(left);
                    }
                }

                if(right.find('i') != string::npos) {               //변수가 존재할 때
                    b = stoi(right.substr(right.find('i') + 1));
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = -inum[b];
                    }
                    else
                    {
                        b = inum[b];
                    }
                }
                else {
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = stoi(right.substr(right.find('-') + 1));
                        b = -b;
                    }
                    else
                    {
                        b = stoi(right);
                    }
                }
                
                if(a == b)       //참일 때
                {
                    point = point->LC;
                }
                else            //거짓일 때
                {
                    point =point->LC->RS;
                }

            }
            else                //판단 기호가 없을 때
            {
                if(con.find('i') != string::npos) {         //변수가 존재할 때
                    a = stoi(con.substr(con.find('i') + 1));
                    a = inum[a];
                }
                else {
                    a = stoi(con);
                }

                if(a)       //참일 때
                {
                    point = point->LC;
                }
                else            //거짓일 때
                {
                    point =point->LC->RS;
                }
            }
        }

        else        //leaf node 일 때
        {
            if(con.find('>') != string::npos)  // > 일 때
            {
                left = con.substr(0, con.find('>'));
                right = con.substr(con.find('>') + 1);

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(left.substr(left.find('i') + 1));
                    if(left.find('-') != string::npos)      //부호 관리
                    {
                        a = -inum[a];
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(left.find('-') != string::npos)      //부호 관리
                    {
                        a = stoi(left.substr(left.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(left);
                    }
                }

                if(right.find('i') != string::npos) {           //변수가 존재할 때
                    b = stoi(right.substr(right.find('i') + 1));
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = -inum[b];
                    }
                    else
                    {
                        b = inum[b];
                    }
                }
                else {
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = stoi(right.substr(right.find('-') + 1));
                        b = -b;
                    }
                    else
                    {
                        b = stoi(right);
                    }
                }            
                return a > b;
            }
            else if(con.find("<") != string::npos)  // < 일 때
            {
                left = con.substr(0, con.find("<"));
                right = con.substr(con.find("<") + 1);

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(left.substr(left.find('i') + 1));
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = -inum[a];
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(left.find('-') != string::npos)          //부호 관리
                    {
                        a = stoi(left.substr(left.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(left);
                    }
                }

                if(right.find('i') != string::npos) {           //변수가 존재할 때
                    b = stoi(right.substr(right.find('i') + 1));
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = -inum[b];
                    }
                    else
                    {
                        b = inum[b];
                    }
                }
                else {
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = stoi(right.substr(right.find('-') + 1));
                        b = -b;
                    }
                    else
                    {
                        b = stoi(right);
                    }
                }
                return a < b;
            }

            else if(con.find("==") != string::npos)
            {
                left = con.substr(0, con.find("=="));
                right = con.substr(con.find("==") + 2);

                if(left.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(left.substr(left.find('i') + 1));
                    if(left.find('-') != string::npos)      //부호 관리
                    {
                        a = -inum[a];
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(left.find('-') != string::npos)      //부호 관리
                    {
                        a = stoi(left.substr(left.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(left);
                    }
                }

                if(right.find('i') != string::npos) {           //변수가 존재할 때
                    b = stoi(right.substr(right.find('i') + 1));    
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = -inum[b];
                    }
                    else
                    {
                        b = inum[b];
                    }
                }
                else {
                    if(right.find('-') != string::npos)     //부호 관리
                    {
                        b = stoi(right.substr(right.find('-') + 1));
                        b = -b;
                    }
                    else
                    {
                        b = stoi(right);
                    }
                }
                return a == b;
            }
            else                //판단 기호가 없을 때
            {
                if(con.find('i') != string::npos) {            //변수가 존재할 때
                    a = stoi(con.substr(con.find('i') + 1));
                    if(con.find('-') != string::npos)       //부호 관리
                    {
                        a = -inum[a];
                    }
                    else
                    {
                        a = inum[a];
                    }
                }
                else {
                    if(con.find('-') != string::npos)       //부호 관리
                    {
                        a = stoi(con.substr(con.find('-') + 1));
                        a = -a;
                    }
                    else
                    {
                        a = stoi(con);
                    }
                }
                return a;
            }
        }
    }
}

int main() {
    Nodestr * dummy = new Nodestr;        //dummy head 생성
    int inum[1000];
    int icount = 0;

    string filename = "output_3.txt";           //입출력 파일 생성
    ifstream file("input_3.txt");
    ofstream outFile("output_3.txt", ios::app);


    if (!file.is_open()) {                      //파일이 안열릴 때
        outFile << "Error" << endl;
        return 0;
    }

    string line;
    int numofinstr = 0;

    if(getline(file, line)) {           
        numofinstr = stoi(line);  
    }


    while(getline(file, line)) {       //입력 수 읽기
        icount++;
    }

    if((icount - 1) != numofinstr) {          //입력 변수의 수가 맞지 않을 때
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }
    
    file.clear();                       //읽기 초기화
    file.seekg(0, ios::beg);
    
    getline(file, line);                //입력 수 읽기
    numofinstr = stoi(line);

    if(numofinstr >= 1000) {            //N이 1000이상일 때(Error)
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    for(int i = 0; i < numofinstr; i++)     //입력 읽기
    {
        getline(file, line);
        inum[i] = stoi(line);

    }

    getline(file, line);

    if(line.length() >= 1000) {        //문자열이 1000이상일 때(Error)
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    int check = check_correct(line);        //Error check
    if(check == -1) {
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    split3(line, dummy, numofinstr);

    if(dummy->str == "Error") {             //Error check
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    if(check_ok(dummy, numofinstr)) {       //Error check
        outFile << "Error" << endl;
        file.close();
        outFile.close();
        return 0;
    }

    int result = read_str(dummy, inum);

    outFile << result << endl; 

    file.close();
    outFile.close();

    return 0;
}