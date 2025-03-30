#include <iostream>
#include <vector>
#include <stack>
#include <queue>

typedef std::vector<std::vector<int>> graf;

///racunarska mreza

graf ucitajGraf(int n,int m){
    graf G(n,std::vector<int>(n,0));

    for(int i = 0; i < m;i++){
        int x,y;
        std::cin>>x>>y;
        G[x][y] = 1;
        G[y][x] = 1;
    }
    return G;
}

void dfs(graf& g,int start, std::vector<int>& posjecen){
    posjecen[start] = 1;
    for(int i =0 ; i < g.size();i++)
        if(g[start][i] == 1 && posjecen[i] == 0)
            dfs(g,i,posjecen);
}

void brojKonekcija(){
    int n,m;
    std::cin>>n>>m;

    graf G = ucitajGraf(n,m);

    std::vector<int> posjecen(n,0);
    int cnt = 0;
    for(int i = 0; i < G.size();i++)
        if(posjecen[i] == 0){
            cnt++;
            dfs(G,i,posjecen);
    }

    std::cout<<cnt-1<<std::endl;
}

///zeljeznicke stanice
void bfs(graf& g,int start,std::vector<int>& posjecen){
    int cnt = 0;
    std::queue<int> red;
    red.push(start);
    while(!red.empty()){
        int temp = red.front();
        red.pop();
        posjecen[temp] = 1;
        for(int i = 0;i < g.size();i++)
            if(g[temp][i] == 1 && posjecen[i] == 0)
                red.push(i);
    }
}

void brojStanica(){
    int n;
    std::cin>> n;
    std::vector<int> posjecen(n,0);
    graf g(n,std::vector<int>(n,0));
    graf koord(n,std::vector<int>(2,0));
    int cnt = 0;

    for(int i = 0; i < n;i++)
        std::cin>>koord[i][0]>>koord[i][1];


    for(int i = 0; i < n;i++){
        for(int j = 0;j < n;j++)
        if(j != i && (koord[i][0] == koord[j][0] || koord[i][1] == koord[j][1])){
           g[i][j] = 1;
           g[j][i] = 1;
        }
    }

    for(int i = 0; i < g.size();i++)
        if(posjecen[i]==0){
            cnt++;
            bfs(g,i,posjecen);
        }

    std::cout<<cnt-1<<std::endl;
}


int main()
{
     brojStanica();
    return 0;
}
