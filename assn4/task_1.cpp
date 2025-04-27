#include <iostream>
using namespace std;

struct elmt_edgelist
{
    int u = 0;
    int v = 0;
    int w = 0;
};

void list_sort(elmt_edgelist *edge_list, int count)        //weight의 오름차순으로 정렬
{
    for(int j = 0 ; j < count - 1; j++) {
        for(int i = 0; i < count - j - 1 ; i++) {
            if(edge_list[i].w > edge_list[i + 1].w)
            {
                elmt_edgelist temp;
                temp.u = edge_list[i].u;
                temp.v = edge_list[i].v;
                temp.w = edge_list[i].w;

                edge_list[i].u = edge_list[i+1].u;
                edge_list[i].v = edge_list[i+1].v;
                edge_list[i].w = edge_list[i+1].w;
                
                edge_list[i+1].u = temp.u;
                edge_list[i+1].v = temp.v;
                edge_list[i+1].w = temp.w;
            }
        }
    }
}

int find_root(int *parent, int idx) {           //root 찾기
    if(parent[idx - 1] == idx) return idx;
    return find_root(parent, parent[idx - 1]);
}

int main() {

    int n, m;
    cin >> n >> m;

    int * parent = new int[n];          //parent list 생성
    for(int i = 0; i < n ; i++) {
        parent[i] = i+1;
    }

    elmt_edgelist * edge_list = new elmt_edgelist[m];   //edge list 생성

    int u, v, w;
    for(int i = 0; i < m ; i++) {
        cin >> u >> v >> w;
        edge_list[i].u = u;
        edge_list[i].v = v;
        edge_list[i].w = w;
    }

    list_sort(edge_list, m);
    int weight = 0;
    

    for(int i = 0 ; i < m ; i++) {
        int root_u = find_root(parent, edge_list[i].u);
        int root_v = find_root(parent, edge_list[i].v);

        if (root_u != root_v) {
            parent[root_v - 1] = root_u;
            weight += edge_list[i].w;
        }
    }

    delete [] parent;
    delete [] edge_list;
    cout << weight;
    return 0;
}
