#include <iostream>
#include <stack>
#include <queue>
#include <vector>

typedef std::vector<std::vector<int>> graf;

graf ucitajGraf(){
    int n,m;
    std::cin>>n>>m;
    graf g(n,std::vector<int>(n,0));
    for(int i = 0 ; i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;
        y--;
        g[x][y] = 1;
        //g[y][x] = 1;
     }
    return g;
}

void dfs(graf& g,int start,std::vector<int>& posjecen,std::vector<int>& prethodni){
    posjecen[start] = 1;
    for(int i = 0; i < g.size();i++){
        if(g[start][i] == 1 && posjecen[i]==0){
                prethodni[i] = start;
                dfs(g,i,posjecen,prethodni);
            }
    }
}

bool postojiPut(graf& g,int start,int kraj){
    std::vector<int> posjecen(g.size(),0);
    std::vector<int> prethodni(g.size(),0);
    dfs(g,start,posjecen,prethodni);
    return posjecen[kraj];
}
/*
int duzinaPuta(graf& g,int start,int kraj){
    ///dodati ovdje posjecen prethodni
    if(postojiPut(g,start,kraj,posjecen,prethodni))
    {
        int temp = kraj;
        int cnt = 0;
        while(temp!=start){
            temp = prethodni[temp];
            cnt++;
        }
        return cnt;
    }
    else return -1;
}
*/
void www(){
    graf g = ucitajGraf();
    int sum = 0;
    for(int i = 0; i < g.size();i++){
        for(int j = 0; j < g.size();j++){

                int l=0;///duzinaPuta fn
                sum += l;
        }
    }

    float prosjek  =  (float)sum/((float)g.size()*((float)g.size()-1));
    printf("%.2f",prosjek);
}


void glavniGrad(){
    graf g = ucitajGraf();
    std::stack<int> gradovi;
    int cnt = 0;
    for(int i = 0; i < g.size();i++){
        for(int j = 0;j < g.size();j++)
            if(postojiPut(g,j,i))
                cnt++;
        if(cnt == g.size())
            gradovi.push(i+1);

        cnt = 0;
    }
    std::cout<<gradovi.size()<<std::endl;
    while(!gradovi.empty()){
        std::cout<<gradovi.top()<< " ";
        gradovi.pop();
    }
}

int main()
{
    glavniGrad();
    return 0;
}
