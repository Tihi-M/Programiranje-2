#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <limits.h>

std::vector<std::vector<int>> ucitaj_graf(){
    int n,m,usmjeren;

    std::cin>> n>>m>>usmjeren;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;

        std::cin>>x>>y>>w;
        g[x][y] = w;

        if(!usmjeren)
            g[y][x] = w;
    }
    return g;
}

int shortest_path(std::vector<std::vector<int>>& g,int start,int kraj,std::vector<int>& posjecen,std::vector<int>& prethodni){
    if(start == kraj)
        return 0;

    posjecen[start] = 1;
    int min_w = INT_MAX;

    for(int i = 0; i < g.size();i++){
        if(g[start][i] != 0 && posjecen[i] == 0){
            int w_i_target = shortest_path(g,i,kraj,posjecen,prethodni);
            if(w_i_target != INT_MAX){
                int w = w_i_target + g[start][i];
                if(w < min_w){
                    min_w = w;
                    prethodni[start] = i
                }
            }
        }

    }

    posjecen[start] = 0;
    return min_w;
}

struct my_cmp{
    bool operator()(std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
};

void dijkstra(std::vector<std::vector<int>>& g,int start,int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1);
    std::vector<int> distance(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp> pq;

    pq.push(std::make_pair(start,0));
    distane[start] = 0;

    while(!pq.empty()){
        int i = pq.top().first;
        int di = pq.top().second;
        pq.pop();

        for(int j = 0; j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(d[j] > d[i] + g[i][j]){
                    d[j] = d[i] + g[i][j];
                    putanja[start] = i;
                    pq.push(std::make_pair(j,d[j]));
                }
            }
        }
        posjecen[i] = 1;
    }

    for(int i = 0; i < g.size();i++)
        std::cout<<distance[i] << " ";
    std::cout<<"\n";

    for(int j = 0;j < g.size(); j++)
        std::cout<<putanja[i] << " ";
    std::cout<<"\n";

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

void stampaj_matricu(int** mat,int len){
    for(int i = 0;i < len;i++){
        for(int j = 0;j < len;j++)
            std::cout<<mat[i][j] << " ";
        std::cout<<std::endl;
    }
}

void floyd_marshall(std::vector<std::vector<int>>& g,int** distance,int** putanja){
    for(int i = 0; i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(i == j){
                distance[i][j] = 0;
                putanja[i][j] = i;
            }
            else if (g[i][j] != 0){
                distane[i][j] = g[i][j];
                putanja[i][j] = j;
            }
            else{
                distance[i][j] = INT_MAX;
                putanja[i][j] = -1;
            }

    for(int k = 0;k < g.size();++k){
        for(int i = 0;i < g.size();++i){
            for(int j = 0;j < g.size();++j){
                if(distance[i][j] < INT_MAX && distance[k][j] < INT_MAX){
                    if(distance[i][j] > distance[i][k] + distance[k][j]){
                        distance[i][j] = distance[i][k] + distance[k][j];
                        putanja[i][j] = putanja[i][k];
                    }
                }
            }
        }
    }
    stampaj_matricu(distance,g.size());
    std::cout<<std::endl;
    stampaj_matricu(path,g.size());
}

void recon_path(int** putanja,int start,int kraj){
    int curr = start;
    while(curr != kraj){
        std::cout<<curr<<" ";
        curr = path[curr][kraj];
    }
    std::cout<<kraj<<"\n";
}

typedef struct Edge{
    int i;
    int j;
    int w;
}Edge;

typedef struct my_cmp{
    bool operator()(Edge a, Edge b){
        return a.w > b.w;
    }
}my_cmp;

int kruskal1(std::vector<std::vector<int>>& g){
    int cc[g.size()];

    for(int i = 0;i < g.size();i++)
        cc[i] = i;

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;
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
            int ci = cc[i];
            for(int k = 0;k < g.size();k++)
                if(cc[k] == ci)
                cc[k] = cc[j];
            wt+=w;
            std::cout<< i <<" "<< j << "\n";
        }
    }
    std::cout<<"\n";
    return wt;
}


int find_root(int i, int parent[]){
    if(parent[i] == -1)
        return i;

    int r = find_root(parent[i],parent);
    parent[i] = r;
    return r;
}

void dsu_union(int ri,int rj,int parent[],int rang[]){
    if(rang[ri] < rang[rj])
    {
        parent[ri] = rj;
        rang[rj] = rang[ri];
    }
    else{
        parent[rj] = ri;
        rang[ri]+=rang[rj];
    }
}

int kruskal2(std::vector<std::vector<int>>& g){
    int parent[g.size()];
    int rang[g.size()];

    for(int i = 0;i < g.size();i++){
        parent[i] = -1;
        rang[i] = 1;
    }

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0)
                pq.push({i,j,g[i][k]});

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

    std::cout<<"\n";
    return wt;
}




int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
