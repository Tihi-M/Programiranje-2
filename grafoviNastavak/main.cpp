#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <limits.h>

typedef struct std::vector<std::vector<int>> graf;

graf ucitajGraf(){
    int n,m,usmjeren;

    std::cin>> n >> m >> usmjeren;

    graf g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y,w;
        std::cin>>x>>y>>w;

        g[x][y] = w;
        if(!usmjeren)
            g[y][x] = w;
    }

    return g;
}

int shortest_path(graf& g,int start,int target,std::vector<int>& posjecen,std::vector<int>& putanja){
    if(start == target)
        return 0; /// pronadjena duzina puta

    posjecen[start] = 1;
    int min_w = INT_MAX;

    for(int i = 0;i < g.size();i++){
        if(g[start][i] != 0 && posjecen[i] == 0){ /// ako postoji granan i nije posjecen cvor
            int w_i_target = shortest_path(g,i,target,posjecen,putanja);
            if(w_i_target != INT_MAX){
                int w = g[start][i] + w_i_target; /// dobijenu duzinu od i do target dodajemo na put od start do i
                if(w < min_w){
                    min_w = w;/// ako smo nasli kraci put
                    putanja[start] = i;/// biljezimo prethodni cvor
                }
            }
        }
    }

    posjecen[start] = 0; /// kako bi nasli sve puteve na kraju se resetuje niz za posjecenim cvorovima

    return min_w; /// vracemo duzinu najkraceg puta
}

struct my_cmp{
    bool operator() (std::pair<int,int> a,std::pair<int,int> b){
        return a.second > b.second;
    }
};

void dijkstra(graf& g,int start,int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1); /// -1 jer ne postoji prethodni trenutno
    std::vector<int> d(g.size(),INT_MAX); /// int_max - temp najkraca duzina puta

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,my_cmp> pq;
    pq.push(std::make_pair(start,0));
    d[start] = 0;

    while(!pq.empty()){
        int i = pq.top().first;
        int di = pq.top().second;
        pq.pop();

        for(int j = 0;j < g.size();j++){
            if(g[i][j] != 0 && posjecen[j] == 0){
                if(d[j] > d[i] + g[i][j]){
                    d[j] = d[i] + g[i][j];
                    putanja[j] = i;
                    pq.push(std::make_pair(j,d[j]));
                }
            }

        }

        posjecen[i] = 1;
    }

    for(int i = 0;i < g.size();i++){
        std::cout<<d[i] << " ";
    }
    std::cout<<std::endl;

     for(int i = 0;i < g.size();i++){
        std::cout<<putanja[i] << " ";
    }
    std::cout<<std::endl;

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

/*
6 7 0
0 1 3
0 2 5
1 3 7
2 4 6
3 5 2
3 4 4
4 5 1
*/

int main()
{
    /*
    graf g = ucitajGraf();
   std::vector<int> posjecen(g.size(),0);
    std::vector<int> putanja(g.size(),-1); /// -1 jer ne postoji prethodni trenutno
    int start = 3;
    int target = 2;
    std::cout << shortest_path(g, start, target, posjecen, putanja) << std::endl;
    int curr = start;
    while (curr != target) {
        std::cout << curr << " ";
        curr = putanja[curr];
    }
    std::cout << target << std::endl;
    */

    return 0;
}
