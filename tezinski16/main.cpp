#include <iostream>
#include <vector>
#include <queue>
#include <limits>

std::vector<std::vector<int>> ucitaj_graf(int& d){
    int n,m;
    std::cin>> n >> m >> d;
    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>> x >> y >> w;

        g[x][y] = w;
        g[y][x] = w;
    }
    return g;
}

typedef struct my_cmp{
    bool operator()(std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
}my_cmp;

std::vector<int> dijkstra(std::vector<std::vector<int>>& g,int start){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> distance(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp> pq;
    pq.push(std::make_pair(start,0));
    distance[start] = 0;
    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();
        for(int j = 0;j < g.size();j++)
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distance[j] > distance[i] + g[i][j]){
                    distance[j] = distance[i] + g[i][j];
                    pq.push(std::make_pair(j,distance[j]));
                }
        }
        posjecen[i] = 1;
    }

    return distance;
}

void zad16(){
    int d;
    std::vector<std::vector<int>> g = ucitaj_graf(d);
    int cnt_d = 0;
    int res_node = -1;
    int min_cnt_d = INT_MAX;
    for(int i = 0;i < g.size();i++){
        std::vector<int> distance = dijkstra(g,i);
        for(int j = 0;j < g.size();j++)
            if(i != j && distance[j] <= d)
                cnt_d++;


        if(min_cnt_d > cnt_d){
            res_node = i;
            min_cnt_d = cnt_d;
        }
        else if(min_cnt_d == cnt_d){
            res_node = std::max(res_node,i);
        }
        cnt_d = 0;
    }

    std::cout<<res_node;
}

int main()
{
    zad16();
    return 0;
}
