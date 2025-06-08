#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

std::vector<std::vector<double>> ucitaj_graf(int& a,int& b){
    int n,m;
    std::cin >> n >> m >> a >> b;
    std::vector<std::vector<double>> g(n,std::vector<double>(n,0.0));

    for(int i = 0;i < m;i++){
        int x,y;
        double w;
        std::cin>>x >> y >> w;
        g[x][y] = w;
        g[y][x] = w;
    }
    return g;
}

typedef struct my_cmp{
    bool operator()(std::pair<int,double> a, std::pair<int,double> b){
        return a.second < b.second;
    }
}my_cmp;

std::vector<int> reverse_dijkstra(std::vector<std::vector<double>>& g,int start){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1);
    std::vector<double> distance(g.size(),0.0);

    std::priority_queue<std::pair<int,double>,std::vector<std::pair<int,double>>,my_cmp> pq;
    pq.push(std::make_pair(start,1.0));
    distance[start] = 1.0;

    while(!pq.empty()){
        auto[i,di] = pq.top();
        pq.pop();

        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0.0 && posjecen[j] == 0){
                if(distance[j] < distance[i] * g[i][j]){
                    distance[j] = distance[i] * g[i][j];
                    pq.push(std::make_pair(j,distance[j]));
                    putanja[j] = i;
                }
            }
        }
        posjecen[i] = 1;
    }
    return putanja;
}

void zad17(){
    int a,b;
    std::vector<std::vector<double>> g = ucitaj_graf(a,b);
    std::vector<int> putanja = reverse_dijkstra(g,a);

    std::stack<int> s;
    int curr = b;
    while(curr != -1){
        s.push(curr);
        curr = putanja[curr];
    }
    while(!s.empty()){
        std::cout<<s.top()<<" ";
        s.pop();
    }

}

int main()
{
    zad17();
    return 0;
}
