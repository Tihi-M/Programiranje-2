#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
#include <cmath>

int manhattan(int x1,int y1,int x2,int y2){
    return std::abs(x1-x2)+std::abs(y1-y2);
}

typedef struct tacka{
    int x;
    int y;
    int pos;//mjesto u matrici grafa
}tacka;

std::vector<std::vector<int>> ucitaj_graf(){
    int n;
    std::cin>> n;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));
    std::vector<tacka> tacke;
    for(int i = 0;i < n;i++){
        int x,y;
        std::cin >> x >> y;
        tacke.push_back({x,y,i});
    }

    for(int i = 0;i < n;i++){
        for(int j = i+1;j < n;j++){
            g[tacke[i].pos][tacke[j].pos] = manhattan(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
            g[tacke[j].pos][tacke[i].pos] = manhattan(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
        }
    }

    return g;
}

typedef struct Edge{
    int i;
    int j;
    int w;
}Edge;

typedef struct my_cmp{
    bool operator() (Edge a,Edge b){
        return a.w > b.w;
    }
}my_cmp;

int kruskal(std::vector<std::vector<int>>& g){
    int roditelj[g.size()];/// roditelj[i] - roditelj cvora i

    for(int i = 0;i < g.size();i++)
        roditelj[i] =-1;/// na pocetku ni jedan cvor nije povezan, nema roditelja

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = 0;j < g.size();j++)
            if(i != j && g[i][j] != 0)
                pq.push({i,j,g[i][j]});

    int wt = 0;

    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();


        while(roditelj[i] != -1)///trazimo korijen za jedan kraj grane
            i = roditelj[i];

        while(roditelj[j] != -1)///trazimo korijen za drugi kraj grane
            j = roditelj[j];

        if(i != j){/// ako ne pripadaju istom stablu
            wt+=w;/// dodajemo vrijednost grane
            roditelj[j] = i;/// povezujemo
        }

    }

    return wt;
}

void zad20(){
    std::vector<std::vector<int>> g = ucitaj_graf();
    std::cout<<kruskal(g);
}

int main()
{
    zad20();
    return 0;
}
