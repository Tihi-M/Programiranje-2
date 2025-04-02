#include <iostream>
#include <vector>
#include <stack>
#include <queue>

typedef std::vector<std::vector<char>> graf;

typedef struct tacka{
    int x;
    int y;
}tacka;

void macka_i_mis(){
    int m,n;
    std::cin>>m>>n;
    int misX,misY,ciljX,ciljY;
    graf g(m,std::vector<char>(n,0));

    std::stack<tacka> macke;
    for(int i = 0; i < m;i++){
        for(int j = 0;j < n;j++)
            {
                std::cin>>g[i][j];
                if(g[i][j] == 'M')
                {
                    misX=i;
                    misY=j;
                }
                else if(g[i][j] == 'C')
                {
                    macke.push({i,j});
                }
                else if(g[i][j] == 'R')
                {
                    ciljX=i;
                    ciljY=j;
                }
        }
    }

    int misPut = abs(ciljX-misX) + abs(ciljY-misY);

    int misK = (misPut+1)/2;
    while(!macke.empty()){
            auto[mackaX,mackaY]=macke.top();
            int mackaPut = abs(ciljX-mackaX) + abs(ciljX-mackaY);
        if(misK>=mackaPut){
            std::cout<<"Ne"<<std::endl;
            return;
        }
        macke.pop();
    }
    std::cout<<"Da"<<std::endl;
}

int main()
{
    macka_i_mis();
    return 0;
}
