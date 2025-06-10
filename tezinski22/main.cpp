#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
#include <cmath>

double euclid(int x1,int y1,int x2,int y2){
    return std::sqrt(std::pow((x2-x1),2)+std::pow((y2-y1),2));
}

typedef struct tacka{
    int x;
    int y;
    int pos;//mjesto u matrici grafa
    bool voda;
}tacka;



std::vector<std::vector<double>> ucitaj_graf(int& k){
    int n;
    std::cin>> n >> k;

    std::vector<std::vector<double>> g(n,std::vector<double>(n,-1.0));
    std::vector<tacka> tacke;

    for(int i = 0;i < n;i++){
        int x,y,v;
        std::cin >> x >> y >> v;
        tacke.push_back({x,y,i,v});
    }

    for(int i = 0;i < n;i++){
        for(int j = i+1;j < n;j++){
            if(tacke[i].voda && tacke[j].voda){
                g[tacke[i].pos][tacke[j].pos] = 0;
                g[tacke[j].pos][tacke[i].pos] = 0;
            }
            else{
                 g[tacke[i].pos][tacke[j].pos] = euclid(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);
                g[tacke[j].pos][tacke[i].pos] = euclid(tacke[i].x,tacke[i].y,tacke[j].x,tacke[j].y);

            }
        }
    }

    return g;
}

typedef struct Edge{
    int i;
    int j;
    double w;
}Edge;

typedef struct my_cmp{
    bool operator() (Edge a,Edge b){
        return a.w > b.w;
    }
}my_cmp;

double kruskal(std::vector<std::vector<double>>& g,int k){
    int roditelj[g.size()];

    for(int i = 0;i < g.size();i++)
        roditelj[i] = -1;

    std::priority_queue<Edge,std::vector<Edge>,my_cmp> pq;

    for(int i = 0;i < g.size();i++)
        for(int j = i+1;j < g.size();j++)
            if(g[i][j] >= 0.0)
                pq.push({i,j,g[i][j]});

    double wt = 0;

    while(!pq.empty()){
        auto[i,j,w] = pq.top();
        pq.pop();


        while(roditelj[i] != -1)
            i = roditelj[i];

        while(roditelj[j] != -1)
            j = roditelj[j];

        if(i != j){
            wt+=w;
            std::cout<< i << " "<<j << std::endl;

            roditelj[j] = i;
        }

    }

    return wt*k;
}

void zad21(){
    int k;
    std::vector<std::vector<double>> g = ucitaj_graf(k);



    std::cout<<std::ceil(kruskal(g,k)*100.0)/100.0;
}

int main()
{
    zad21();
    return 0;
}
