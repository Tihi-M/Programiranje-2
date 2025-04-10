#include <iostream>
#include <stack>
#include <queue>
#include <vector>

typedef std::vector<std::vector<int>> graf;

graf ucitajGraf(int& n,int& m,bool usmjeren){
    std::cin>> n >> m;
    graf g(n,std::vector<int>(n,0));

    for(int i = 0;i < m;i++){
        int x,y;
        std::cin>>x>>y;
        g[x][y] = 1;
        if(!usmjeren)
            g[y][x] = 1;
    }
    return g;
}

void dfsNajblizi(graf& g,int start, std::vector<int>& posjecen,std::vector<int>& duzine){
    posjecen[start] =1;
    for(int i = 0;i < g.size();i++)
        if(g[start][i] == 1 && posjecen[i] == 0){
            duzine[i] = duzine[start]+1;
            dfsNajblizi(g,i,posjecen,duzine);
    }
}

void bfsNajblizi(graf& g,int start,std::vector<int>& duzine){
    std::queue<int> red;
    red.push(start);
    std::vector<int> posjecen(g.size(),0);
    duzine[start] = 0;
    posjecen[start] = 1;
    while(!red.empty()){
        int temp = red.front();
        red.pop();

        for(int i = 0;i < g.size();i++){
            if(g[temp][i] == 1 && posjecen[i] == 0){
                red.push(i);
                posjecen[i] = 1;
                duzine[i] = duzine[temp]+1;
            }
        }
    }
}

void najblizi(){
    int n,m,cvor1,cvor2;
    std::cin>>cvor1>>cvor2;
    graf g = ucitajGraf(n,m,true);

    std::vector<int> duzine1(n,-1);
    std::vector<int> duzine2(n,-1);

    bfsNajblizi(g,cvor1,duzine1);
    bfsNajblizi(g,cvor2,duzine2);

    int minLen = 100000;
    int najbliziC = -1;
    for(int i = 0; i<n;++i){
        if(duzine1[i] != -1 && duzine2[i] != -1 && duzine1[i] != 0 && duzine2[i] != 0){
            int temp = std::max(duzine1[i],duzine2[i]);
            if(temp < minLen){
                najbliziC = i;
                minLen = temp;
            }
        }
    }
    std::cout<<najbliziC<<std::endl;
}

bool postojiPut(graf& g,int start,int kraj){
    if(g[start][kraj] == 1)
        return true;
    for(int i = 0;i < g.size();i++)
        if(g[start][i] == 1)
        return postojiPut(g,i,kraj);
    return false;
}

void preci(){
    int n,m;
    std::cin>>n>>m;
    graf g = ucitajGraf(n,m);

    int cnt = 0;

    for(int i = 0;i < n;i++){
        for(int j =0;j < n;j++){
            if(postojiPut(g,j,i)){
                std::cout<<j<<" ";
                cnt++;
            }
        }

        if(cnt == 0)
            std::cout<<-1<<std::endl;
        else {
            cnt = 0;
            std::cout<<std::endl;
        }
    }
}



int main()
{
    preci();
    return 0;
}
