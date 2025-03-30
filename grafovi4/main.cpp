#include <iostream>
#include <vector>
#include <stack>
#include <queue>

typedef std::vector<std::vector<int>> graf;

///racunarska mreza

graf ucitajGraf(int n,int m,bool usmjeren){
    graf G(n,std::vector<int>(n,0));

    for(int i = 0; i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;
        y--;
        G[x][y] = 1;
        if(!usmjeren)
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

    graf G = ucitajGraf(n,m,false);

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
/*
void bande(){
    int n,m;
    std::cin>>n>>m;
    graf g = ucitajGraf(n,m);

    std::vector<int> posjecen(n,0);
    int cnt = 0;
    for(int i = 0; i < n;i++)
        if(posjecen[i] == 0){
            cnt++;
            dfs(g,i,posjecen);
    }

    if(cnt == 2)
        std::cout<<"Inspektor je u pravu"<<std::endl;
    else std::cout<<"Inspektor nije  u pravu"<<std::endl;
}
*/

void bande(){
    int n,m;
    std::cin>>n>>m;
    graf g = ucitajGraf(n,m,false);

    std::vector<int> boja(n,-1);
    std::queue<int> red;

    for(int i = 0; i < n; i++){
        if(boja[i] == -1){
            red.push(i);
            boja[i] = 0;

            while(!red.empty()){
                int tren = red.front();
                red.pop();

                for(int j = 0;j < n;j++){
                    if(g[tren][j] == 1){
                        if(boja[j] == boja[tren]){
                            std::cout<<"Inspektor nije u pravu"<<std::endl;
                            return;
                        }
                        else if(boja[j] == -1){
                            boja[j] = 1 - boja[tren];
                            red.push(j);
                        }
                    }
                }
            }
        }
    }
    std::cout<<"Inspektor je u pravu"<<std::endl;
}
typedef struct tacka{
    int x;
    int y;
}tacka;
void nafta(){
    int n,m;
    std::cin>>m>>n;
    graf mat(m,std::vector<int>(n,0));

    for(int i = 0; i < m;i++)
        for(int j = 0; j < n;j++)
            std::cin>>mat[i][j];

    graf posjecen(m,std::vector<int>(n,0));
    int cnt = 0;
    int dirs[8][8] = {{1,0},{1,-1},{1,1},{0,-1},{0,1},{-1,0},{-1,-1},{-1,1}};
    std::queue<tacka> red;

    for(int i = 0; i < m;i++){
        for(int j = 0;j < n;j++){
            if(mat[i][j] == 1 && posjecen[i][j] == 0){
                cnt++;
                red.push({i,j});
                posjecen[i][j] == 1;
                while(!red.empty()){
                    tacka tren = red.front();
                    red.pop();

                    for(int k = 0; k < 8;k++)
                    {
                        int x_ = tren.x + dirs[k][0];
                        int y_ = tren.y + dirs[k][1];

                        if(x_>=0 && x_<m && y_>=0 && y_<n){
                            tacka susjed = {x_,y_};
                            if(mat[susjed.x][susjed.y] == 1 && posjecen[susjed.x][susjed.y] == 0){
                                red.push(susjed);
                                posjecen[susjed.x][susjed.y] = 1;
                            }

                        }

                    }
                }
            }
        }

    }
    std::cout<<cnt<<std::endl;
}

void dfs2(graf& g,int start,std::vector<int>& posjecen,int& cnt){
    posjecen[start] = 1;
    cnt++;
    for(int i = 0; i < g.size();i++){
        if(g[start][i] == 1 && posjecen[i] == 0)
            dfs2(g,i,posjecen,cnt);
    }
}

void stampajGraf(graf& g){
    for(int i = 0;i < g.size();i++){
        for(int j = 0;j < g.size();j++)
            std::cout<<g[i][j]<<" ";
        std::cout<<std::endl;
    }
}

void prijatelji(){
    int n,m;
    std::cin>>n>>m;
    graf g = ucitajGraf(n,m,false);
    std::vector<int> posjecen(n,0);
    int maxx = 0;
    int cnt = 0;
    for(int i = 0; i < n;i++){
        if(posjecen[i] == 0){
            dfs2(g,i,posjecen,cnt);
        }
        if(maxx < cnt)
            maxx = cnt;
        cnt = 0;
    }
    std::cout<<maxx<<std::endl;
}


int main()
{
    prijatelji();
    return 0;
}
