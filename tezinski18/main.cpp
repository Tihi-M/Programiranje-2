#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

std::vector<std::vector<int>> ucitaj_graf(int& s,int& t,int& k){
    int n,m;
    std::cin>> n >> m >> s >> t >> k;

    std::vector<std::vector<int>> g(n,std::vector<int>(n,0));

    for(int i = 0; i < m;i++){
        int x,y,w;
        std::cin>>x>>y>>w;
        x--;
        y--;
        g[x][y] = w;
    }
    return g;
}

typedef struct my_cmp{
    bool operator()(std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
}my_cmp;

int dijkstra(std::vector<std::vector<int>>& g,int start,int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1);
    std::vector<int> distance(g.size(),INT_MAX);

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp> pq;
    pq.push(std::make_pair(start,0));
    distance[start] = 0;

    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();

        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(distance[j] > distance[i] + g[i][j]){
                    distance[j] = distance[i] + g[i][j];
                    putanja[j] = i;
                    pq.push(std::make_pair(j,distance[j]));
                }
            }
        }
        posjecen[i] = 1;
    }

    int dist = 0;
    int curr = kraj;
    std::stack<int> s;

    while(curr != -1){
        s.push(curr);
        curr = putanja[curr];
    }

    while(!s.empty()){
        //std::cout<<s.top()<< " ";
        int top = s.top();
        s.pop();
        if(!s.empty()){
            dist += g[top][s.top()];
        }
    }
    //std::cout<<std::endl;
    return dist;
}

void zad18(){
    int s,t,k;

    std::vector<std::vector<int>> g = ucitaj_graf(s,t,k);
    s--;
    t--;

    int min_dist = dijkstra(g,s,t);
    int temp_dist;
    for(int i = 0; i < k;i++){
        int x,y,w;
        temp_dist = 0;
        std::cin>> x >> y >> w;
        x--;
        y--;
        if(g[x][y] == 0){
            g[x][y] = w;
            temp_dist = dijkstra(g,s,t);
            if(min_dist > temp_dist)
                min_dist = temp_dist;
            g[x][y] = 0;

        }
        else{
            int temp = g[x][y];
            g[x][y] = w;
            temp_dist = dijkstra(g,s,t);
            if(min_dist > temp_dist)
                min_dist = temp_dist;
            g[x][y] = temp;
        }
    }

    std::cout<<min_dist;
}

int main()
{
    zad18();
    return 0;
}
