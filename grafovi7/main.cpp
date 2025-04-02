#include <iostream>
#include <queue>
#include <stack>
#include <vector>

typedef std::vector<std::vector<int>> graf;

graf ucitajGraf(int n,int m){
    graf g(n,std::vector<int>(n,0));
    for(int i = 0; i < m;i++){
        int x,y;
        std::cin>>x>>y;
        g[x][y]=1;
    }
    return g;
}

void dfsSort(graf& g,int start,std::vector<int>& posjecen,std::stack<int>& s){
    if(posjecen[start] == 1)
        return;

    posjecen[start] = 1;

    for(int i = 0;i < g.size();i++)
        if(g[start][i] == 1)
        dfsSort(g,i,posjecen,s);
    s.push(start);
}

void topSort(graf& g){
    std::vector<int> posjecen(g.size(),0);
    std::stack<int> s;

    for(int i = 0; i < g.size();i++)
        if(posjecen[i] == 0)
            dfsSort(g,i,posjecen,s);

    while(!s.empty())
    {
        std::cout<<s.top()<<" ";
        s.pop();
    }
    std::cout<<std::endl;
}

void kursevi(){
    int n,m;
    std::cin>>n>>m;
    graf g = ucitajGraf(n,m);
    topSort(g);
}

int main()
{
    kursevi();
    return 0;
}
