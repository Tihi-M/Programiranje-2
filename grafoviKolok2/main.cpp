#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <limits.h>

std::vector<std::vector<int>> ucitaj_graf(){
    int n,m,usmjeren;

    std::cin>> n >> m >> usmjeren;
    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin >> x >> y >> w;
        g[x][y] = w;
        if(!usmjeren)
            g[y][x] = w;
    }
    return g;
}

void stampaj_matrix(std::vector<std::vector<int>>& g,int n){
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++)
            std::cout<<g[i][j] << " ";
        std::cout<<std::endl;
    }
}

void floyd_warshall(std::vector<std::vector<int>>* g,std::vector<std::vector<int>>& distance,std::vector<std::vector<int>>& putanja){
    for(int i = 0;i < g.size();i++){
        for(int j = 0;j < g.size();j++){
            if(i == j){
                distance[i][j] = 0;
                putanja[i][j] = i;
            }
            else if(g[i][j] != 0){
                distance[i][j] = g[i][j];
                putanja[i][j] = j;
            }
            else{
                distance[i][j]=INT_MAX;
                putanja[i][j] = -1;
            }
        }
    }

    for(int k = 0; k < g.size();k++){
        for(int i = 0;i < g.size();i++){
            for(int j = 0;j < g.size();j++){
                if(distance[i][j] < INT_MAX && distance[k][j] < INT_MAX){
                    if(distance[i][j] > distance[i][k] + distance[k][j]){
                        distance[i][j] = distance[i][k] + distance[k][j];
                        putanja[i][j] = putanja[i][k];
                    }
                }
            }
        }
    }

    print_matrix(distance,g.size());
    std::cout<<std::endl;
    print_matrix(putanja,g.size());
}

void recon_path(std::vector<std::vector<int>>& putanja,int i,int j){
    int curr = i;
    while(curr != j){
        std::cout<<curr << " ";
        curr = putanja[curr];
    }
    std::cout<< j << std::endl;
}


typedef struct Edge{
    int i;
    int j;
    int w;

}Edge;

typedef struct my_cmp{
    bool operator()(Edge a,Edge b){
        return a.w > b.w;
    }
}my_cmp;

int kruskal1(std::vector<std::vector<int>>& g){
    int cc[g.size()];

    for(int i = 0;i < g.size();i++)
        cc[i] = i;

    std::priority_queue<Edge,std::vector<Edge>, my_cmp> pq;

    for(int i = 0; i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]});

    int wt = 0;

    while(!pq.empty()){
        Edge e = pq.top();
        pq.pop();
        auto[i,j,w] = e;

        if(cc[i] != cc[j]){
            for(int k = 0;k < g.size();k++)
                if(cc[i] == cc[k])
                cc[k] = cc[j];
        }
        wt+=w;
        std::cout<<i<< " "<<j<<std::endl;
    }

    return wt;
}

int find_root(int i,int parent[]){
    if(parent[i] == -1)
        return i;

    int r = find_root(parent[i],parent);
    parent[i] = r;
    return r;
}

void dsu_union(int ri,int rj,std::vector<int>& parent,std::vector<int>& rang){
    if(rang[ri] < rang[rj]){
        parent[ri] = rj;
        rang[rj] += rang[ri];
    }
    else {
        parent[rj] = ri;
        rang[ri] += rang[rj];
    }
}

int kruskal2(std::vector<std::vector<int>>& g){
    std::vector<int> parent(g.size(),-1);
    std::vector<int> rang(g.size(),1);

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]});

    int wt = 0;
    while(!pq.empty()){
        Edge e = pq.top();
        pq.pop();
        auto[i,j,w] = e;
        int ri = find_root(i,parent);
        int rj = find_root(j,parent);
        if(ri != rj){
            wt+=w;
            dsu_union(ri,rj,parent,rang);
        }
    }
    return wt;
}

typedef struct my_cmp2{
    bool operator()(std::pair<int,int> a, std::pair<int,int>b){
        return a.second > b.second;
    }
}my_cmp2;

void dijkstra(std::vector<std::vector<int>>& g,int start,int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1);
    std::vector<int> d(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp2> pq;

    pq.push(std::make_pair(start,0));
    d[start] = 0;

    while(!pq.empty){
        auto[i,di] = pq.top();

        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(d[j] > d[i] + g[i][j]){
                    d[j] = d[i] + g[i][j];
                    putanja[j] = i;
                    pq.push(std::make_pair(j,d[j]));
                }
            }
        }
        posjecen[i]= 1;

    }

    std::stack<int> s;
    int curr = kraj;

    while(curr != -1){
        s.push(curr);
        curr = putanja[curr];
    }
    while(!s.empty()){
        std::cout<<s.top()<< " ";
        s.pop();
    }
}




int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
