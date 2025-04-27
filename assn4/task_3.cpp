#include <iostream>
using namespace std;

struct Node
{
    int idx;
    int w = 0;
    Node * next = nullptr;
};

struct path     //s로부터 idx까지의 거리 저장
{
    int idx;
    int w;
    int length;
    path * next = nullptr;

};

bool add_path(path *head, int idx, int length, int w)
{
    path * finder = head;
    while(finder != nullptr)
    {
        if(finder->idx == idx && finder->length == length) {
            if (finder->w <= w) {
            } 
            else {
                finder->w = w;
            }
            return false;
        }
        finder = finder->next;
    }
    return true;
}

void find_SP(Node * Node_list, path *& head, int idx, int length, int k, bool (&visited)[101][1001])
{
    
    if(visited[idx][length]) return;
    visited[idx][length] = true;

    if(length >= k)
    {
        return;
    }

    if(head == nullptr)         //source 자기 자신에 대한 길 생성
    {
        path * p_node = new path;
        p_node->idx = idx;
        p_node->w = 0;
        p_node->length = 0;
        p_node->next = nullptr;
        head = p_node;
    }

    Node * finder = Node_list[idx].next;
    while(finder != nullptr)
    {
        path * path_finder_idx = head;      //path의 idx의 길 검색
        while(path_finder_idx != nullptr)
        {
            if(path_finder_idx->idx == idx && path_finder_idx->length < k)      //길을 더 갈 수 있고, idx에 대한 길이 존재
            {
                int new_idx = finder->idx;
                int new_w = finder->w + path_finder_idx->w;
                int new_length = path_finder_idx->length + 1;

                if(add_path(head, new_idx, new_length, new_w)) {
                    path * p_node = new path;                   //새로운 길 생성 및 저장
                    p_node->idx = new_idx;
                    p_node->w = new_w;
                    p_node->length = new_length;
                    p_node->next = head;
                    head = p_node;
                }
                

            }
            path_finder_idx = path_finder_idx->next;
        }

        find_SP(Node_list, head, finder->idx, length + 1, k, visited);
        finder = finder->next;
    }
}   


void connect_adj(Node& origin, int adj, int w) {
    Node * adj_node = new Node;
    adj_node->idx = adj;
    adj_node->w = w;
    
    if(origin.next == nullptr) {    //인접 노드가 아무것도 없을 때
        origin.next = adj_node;
        return;
    }

    if(w < origin.next->w) {       //맨 앞에 올 때
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
        if(w < finder->next->w) {       //사이에 낄 때
            adj_node->next = finder->next;
            finder->next =adj_node;
            return;
        }
        finder = finder->next;
    } 
}

int main() {

    int n, m, s, d;
    cin >> n >> m >> s >> d;

    Node * Node_list = new Node[n+1];         //그래프 생성
    for(int i = 1 ; i <= n ; i++) {
        Node_list[i].idx = i + 1;
    }
    
    int u, v, w;                            //그래프 정렬
    for(int i = 0 ; i < m ; i++) {
        cin >> u >> v >> w;
        connect_adj(Node_list[u], v, w);
    }

    int k;
    cin >> k;

    path * head = nullptr;
    bool visited[101][1001]; 
   
    find_SP(Node_list, head, s, 0, k, visited);
    path * path_finder = head;
    path * SP = nullptr;
    while(path_finder != nullptr)
    {
        if(path_finder->idx == d)
        {
            if(SP == nullptr)
            {
                SP = path_finder;
            }
            else
            {
                if(SP->w > path_finder->w)
                {
                    SP = path_finder;
                }
            }
        }
        path_finder = path_finder->next;
    }

    if(SP == nullptr)
    {
        cout << -1;
    }
    else
    {
        cout << SP->w;
    }
    return 0;
}