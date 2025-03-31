#include <iostream>
#include <stack>
#include <queue>
#include <vector>

typedef std::vector<std::vector<int>> graf;
///####################################################
void putanjaDfs(graf& g, std::vector<int>& posjecen,std::vector<int>& prethodni, int start){
    posjecen[start] = 1;
    for(int i = 0; i <g.size();i++)
        if(g[start][i] == 1 && posjecen[i] == 0){
            prethodni[i] = start;
            putanjaDfs(g,posjecen,prethodni,i);
        }
}

bool postojiPutDfs(graf& g,std::vector<int>& posjecen,std::vector<int>& prethodni,int start,int kraj){
    putanjaDfs(g,posjecen,prethodni,start);
    return posjecen[kraj];
}



int duzinaPuta(graf& g, int start, int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> prethodni(g.size(),0);
    if(postojiPutDfs(g,posjecen,prethodni,start,kraj)){
        int cnt = 1;
        int temp = kraj;
        while(temp!=start){
            temp = prethodni[temp];
            cnt++;
        }

        return cnt;
    }
    else return -1;

}

graf ucitajGraf(int n,int m){
    graf g(n,std::vector<int>(n,0));
    for(int i = 0; i < m;i++){
        int x,y;
        std::cin>>x>>y;
        g[x][y] = 1;
    }
    return g;
}

void najbliziCvor(){
    int n,m,cvor1,cvor2;
    std::cin>>n>>m>>cvor1>>cvor2;
    graf g = ucitajGraf(n,m);

    int cvor3 = -1;
    int minLen = 100000;
    for(int i = 0; i < n;i++){
        int d1 = duzinaPuta(g,cvor1,i);
        std::cout<<d1<<" izmedju: "<< cvor1<< " "<<i<<std::endl;

        int d2 = duzinaPuta(g,cvor2,i);
        std::cout<<d2<<" izmedju: "<< cvor2<< " "<<i<<std::endl;
        if(d1>0 && d2>0)
            if(d1+d2<minLen){
                minLen = d1+d2;
                cvor3 = i;
            }
    }
    std::cout<<cvor3;
}
///###############################################

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
