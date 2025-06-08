#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
std::vector<std::vector<int>> ucitaj_graf(){
    int n,m;
    std::cin>>n>>m;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));
    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>>x>>y>>w;
        x--;
        y--;
        g[x][y] = w;
        g[y][x] = w;
    }
    return g;
}

typedef struct my_cmp{
    bool operator() (std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
}my_cmp;

std::vector<int> dijkstra(std::vector<std::vector<int>>& g,int start){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> distance(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>, my_cmp> pq;

    pq.push(std::make_pair(start,0));
    distance[start] = 0;

    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();
        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distance[j] > distance[i] + g[i][j]){
                    distance[j] = distance[i] + g[i][j];
                    pq.push(std::make_pair(j,distance[j]));
                }
            }
        }
        posjecen[i] = 1;
    }

    return distance;
}

void zad15(){
    std::vector<std::vector<int>> g = ucitaj_graf();
    int k;
    std::cin>> k;
    k--;
    std::vector<int> distance = dijkstra(g,k);
    int maxxDelay = 0;
    for(int i = 0;i < g.size();i++){
        if(i != k){
            if(distance[i] == INT_MAX){
                std::cout<< -1;
                return;
            }
            else if(distance[i] > maxxDelay)
                maxxDelay = distance[i];
        }
    }

    std::cout<<maxxDelay;
}

int main()
{
    zad15();
    return 0;
}
