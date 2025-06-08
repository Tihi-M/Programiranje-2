#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>

std::vector<std::vector<int>> ucitaj_graf(){
    int n,m;
    std::cin>>n>>m;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));
    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>>x>>y>>w;
        g[x][y] = w;
    }
    return g;
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

int kruskal(std::vector<std::vector<int>>& g){
    int cc[g.size()];
    int nadredjeni[g.size()];//~~~putanja

    for(int i = 0;i < g.size();i++){
        cc[i] = i;
        nadredjeni[i] = -1;
    }

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0 && i!= j)
                pq.push({i,j,g[i][j]});

    int wt = 0;
    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();

        if(cc[i] != cc[j] && nadredjeni[j] == -1){
            nadredjeni[j] = i;

            for(int k = 0;k < g.size();k++){
                if(cc[k] == cc[i])
                    cc[k] = cc[j];
            }

            wt+=w;
        }
    }

    int temp = 0;
    for(int i = 0;i < g.size();i++)
        if(nadredjeni[i] == -1)
            temp++;

    if(temp != 1)
        return -1;

    return wt;
}

void zad19(){
    std::vector<std::vector<int>> g = ucitaj_graf();

    std::cout<<kruskal(g);
}

int main()
{
    zad19();
    return 0;
}
