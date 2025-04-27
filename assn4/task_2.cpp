#include <iostream>
using namespace std;
struct Node
{
    int idx;
    Node * next = nullptr;
};

struct queue
{
    int idx;
    queue * next = nullptr;
};

void enqueue(queue * front, int idx)
{
    queue * elmt = new queue;
    elmt->idx = idx;

    if(front->next == nullptr) {    //요소가 아무것도 없을 때
        front->next = elmt;
        return;
    }

    queue * finder = front->next;
    while(finder->next != nullptr) {
        finder = finder->next;
    }
    finder->next = elmt;
}

int dequeue(queue * front)
{
    int pop = front->next->idx;

    queue * trash = front->next;
    front->next = trash->next;
    delete trash;
    return pop;
}

void DFS(Node * Node_list, int * complete, int * element, int s)
{
    if(complete[s] == 1) return;    //완료된 요소이면 리턴

    complete[s] = 1;    //완료된 표시

    int i = 0;          //출력 리스트에 저장
    while(element[i] != -1)
    {
        i++;
    }
    element[i] = s;

    Node * finder = Node_list[s].next;        
    while(finder != nullptr)
    {
        DFS(Node_list, complete, element, finder->idx);
        finder = finder->next;
    }
}

void BFS(Node * Node_list, int * shortest, int s)
{
    int length = 0;
    shortest[s] = length;
    
    queue * front = new queue;
    front->idx = -1;
    front->next = nullptr;
    enqueue(front, s);

    while(front->next != nullptr)
    {
        
        int pop = dequeue(front);
        length = shortest[pop] + 1;

        Node * point = Node_list[pop].next;
        while(point != nullptr)
        {
            if (shortest[point->idx] == -1) {   //방문하지 않은 노드만
                enqueue(front, point->idx);
                shortest[point->idx] = length;
            }
            point = point->next;              
        }
    }
    delete front;
}

void sorted_element(int * elmt, int num_node)
{
    int n = 0;              //elmt의 크기 확인
    while(elmt[n] != -1)
    {
        n++;
        if(num_node == n)
        {
            break;
        }
    }

    for(int i = 0 ; i < n - 1; i++)
    {
        for(int j = 0 ; j < n - i - 1; j++)
        {
            
            if(elmt[j] > elmt [j+1])
            {
                int temp = elmt[j];
                elmt[j] = elmt[j+1];
                elmt[j+1] = temp;
            }
        }
    }
}

void connect_adj(Node& origin, int adj) {
    Node * adj_node = new Node;
    adj_node->idx = adj;
    
    if(origin.next == nullptr) {    //인접 노드가 아무것도 없을 때
        origin.next = adj_node;
        return;
    }

    if(adj < origin.next->idx) {       //맨 앞에 올 때
        Node * temp = origin.next;
        origin.next = adj_node;
        adj_node->next = temp;
        return;
    }

    Node * finder = origin.next;
    while (finder != nullptr)
    {
        if(finder->next == nullptr) {       //맨 뒤에 올 때
            finder->next = adj_node;
            return;
        }
        if(adj < finder->next->idx) {       //사이에 낄 때
            adj_node->next = finder->next;
            finder->next =adj_node;
            return;
        }
        finder = finder->next;
    } 
}

int main() {
    int n, m;
    cin >> n >> m;

    Node * Node_list = new Node[n];
    for(int i = 0 ; i < n ; i++) {
        Node_list[i].idx = i;
    }

    int u, v;
    for(int i = 0 ; i < m ; i++) {
        cin >> u >> v;
        connect_adj(Node_list[u], v);
        connect_adj(Node_list[v], u);
    }

    int s;
    cin >> s;

    
    int * shortest = new int[n];
    for(int i = 0 ; i < n ; i++) {
        shortest[i] = -1;
    }
    
    BFS(Node_list, shortest, s);
    for(int i = 0; i < n ; i++) {
        if(i == n - 1) {
            cout << shortest[i] << endl;
            break;
        }
        cout << shortest[i] << " ";
    }

    int * complete = new int[n];
    for(int i = 0 ; i < n ; i++) {
        complete[i] = 0;
    }

    for(int i = 0 ; i < n ; i++)
    {
        if(complete[i] == 1) //이미 어떤 요소에 속해 있을 때
        {
            continue;
        }

        int * element = new int[n]; //저장할 리스트 생성
        for(int j = 0 ; j < n ; j++)
        {
            element[j] = -1;
        }
        
        DFS(Node_list, complete, element, i);
        
        sorted_element(element, n);

        for(int j = 0 ; j < n ; j++)
        {
            if(element[j + 1] == -1)    //요소가 끝날 때
            {
                for(int k = 0 ; k < n ; k++)
                {
                    if(complete[k] != 1)            //모든 요소가 탐색이 되지 않았을 때
                    {
                        cout << element[j] << endl;
                        break;
                    }
                    if(k == n - 1)                  //모든 요소가 탐색 되었을 때
                    {
                        cout << element[j];
                    }
                }  
                break;
            }

            cout << element[j] << " ";
        }

    }
    return 0;
}