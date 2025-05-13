#include <iostream>
#include <vector>
#include <stack>
#include <limits.h>
#include <queue>

std::vector<std::vector<int>> ucitaj_graf(){
    int n,m,usmjeren;

    std::cin>>n>>m>>usmjeren;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>>x>>y>>w;
        g[x][y] = w;
        if(!usmjeren)
            g[x][y] = w;
    }
    return g;
}

void stampaj_matricu(int** x,int n){
    for(int i = 0;i < n;++i){
        for(int j = 0;j < n;++j)
            std::cout<<x[i][j]<<" ";
        std::cout<<"\n";
    }
}

///Floyd-warshall - najkraci put parova

void floyd_warshall(std::vector<std::vector<int>>& g,int** distance,int** path){
    for(int i = 0; i < (signed)g.size();++i){ /// prolazimo sve kombinacije cvorova
        for(int j = 0;j < (signed)g.size();++j){
            if(i == j){ /// distanca izmedju cvora do samog sebe je 0
                distance[i][j]= 0;
                path[i][j] = i;
            }
            else if(g[i][j] != 0){ /// ako postoji  grana izmedju i i j
                distance[i][j] = g[i][j];
                path[i][j] = j;
            }
            else{ /// ako ne postoji  grana
                distance[i][j] = INT_MAX;
                path[i][j] = -1;
            }
        }
    }
    /// zelimo da izmedju cvorova i i j stavimo k kako bi smanjilo
    /// duzinu puta od i do j
    for(int k = 0; k < (signed)g.size();++k){/// k - izmedju i i j
        for(int i = 0;i < (signed)g.size();++i){ /// i - pocetni cvor
            for(int j = 0;j < (signed)g.size();++j){/// j - krajnji cvor
                if(distance[i][j] < INT_MAX && distance[k][j] < INT_MAX){
                    if(distance[i][j] > distance[i][k] + distance[k][j]){/// da li se put skracuje?
                        distance[i][j] = distance[i][k] + distance[k][j];/// update distance
                        path[i][j] = path[i][k];///update path
                    }
                }
            }
        }
    }
    stampaj_matricu(distance,g.size());
    std::cout<< "\n";
    stampaj_matricu(path,g.size());
}

void recon_path(int** path,int i,int j){
    int curr = i;
    while(curr != j){
        std::cout<< curr << " ";
        curr = path[curr][j];
    }
    std::cout<< j << "\n";
}

typedef struct Edge{
    int i;
    int j;
    int w;
}Edge;

typedef struct my_cmp{
    bool operator() (Edge a, Edge b){
        return a.w > b.w;
    }
} my_cmp;

int kruskal1(std::vector<std::vector<int>> g){
    int cc[g.size()] /// cc - connected components

    for(int i = 0;i < (signed)g.size();++i)
        cc[i] = i;/// cc[i] - govori kojoj komponenti pripada cvor i

    /// cuva sve grane, sortirane u opadajucem redu, po tezini
    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < (signed)g.size();++i){
        for(int j = 0;j < (signed)g.size();++j){
            if(g[i][j] != 0)
                pq.push({i,j,g[i][j]}); /// dodajemo sve grane u red
        }
    }

    int wt = 0; /// tezina minimalnog razapinjuceg stabla

    while(!pq.empty()){
        Edge e = pq.top(); /// uzimamo najmanju granu
        pq.pop();
        auto[i,j,w] = e;
        if(cc[i] != cc[j]){ /// ako se njeni cvorovi nalaze u drugim comp
            int ci = cc[i]; /// onda nece formirati ciklus
            for(int k = 0;k < (signed)g.size();++k){ /// merge components
                if(cc[k] == ci)
                    cc[k] = cc[j];
            }
            wt += w; ///povecavamo tezinu mst
            std::cout<< i << " " << j << "\n";
        }
    }
    std::cout<<"\n";
    return wt;
}

 /// odredjuje kojoj komponenti cvor i pripada
int find_root(int i, int parent[]){
    if(parent[i] == -1)/// ako i nema parent,
        return i;/// onda je i korijen te komp

    int r = find_root(parent[i],parent);/// ako ima idemo unazad, dok ne dodjemo do korijena
    parent[i] = r;
    return r; /// vracemo korijen komponente
}

/// za povezivanje dvije komp ciji korijeni su ri,rj
/// rang[i] - broj cvorova u komp sa korijenom i
void dsu_union(int ri,int rj,int parent[],int rang[]){
    if(rang[ri] < rang[rj]) /// manje pridruzujemo vecem
    {
        parent[ri] = rj;
        rang[rj] += rang[ri];
    }
    else{
        parent[rj] = ri;
        rang[ri] += rang[rj];
    }
}

/// ponovo trazimo mst

int kruskal2(std::vector<std::vector<int>> g){
    int parent[g.size()];
    int rang[g.size()];

    for(int i = 0;i < (signed)g.size();++i){
        parent[i] = -1; /// -1 - i je korijen svoje komp
        rang[i] = 1; /// pocetna velicina, sadrzi samo i
    }

    /// opadajuci pq
    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < (signed)g.size();++i){
        for(int j = 0;j < (signed)g.size();++j){
            if(g[i][j] != 0)    /// dodajemo sve grane
                pq.push({i,j,g[i][j]});
        }
    }

    int wt = 0;
    while(!pq.empty()){
        Edge e = pq.top(); ///uzimamo najlaksu granu
        pq.pop();
        auto[i,j,w] = e;
        /// trazimo kojim komp pripadaju i i j
        int ri = find_root(i,parent);
        int rj = find_root(j,parent);
        if(ri != rj){/// ako su iz razlicitih
            wt += w;-///povecavamo val
            dsu_union(ri,rj,parent,rang);.///merge-ujemo te dvije komp
        }
    }

    std::cout<< "\n";
    return wt;
}


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
